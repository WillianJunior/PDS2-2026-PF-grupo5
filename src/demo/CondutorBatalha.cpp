#include "demo/CondutorBatalha.hpp"
#include "demo/UI.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/battle/Batalha.hpp"
#include "entities/map/Cena.hpp"
#include "core/Dados.hpp"

CondutorBatalha::CondutorBatalha(IView& view, IController& ctrl,
                                 Jogador& jogador, Personagem& inimigo,
                                 Dados& dados, Cena& cena,
                                 const ConfigExploracao& cfg)
    : _view(view), _ctrl(ctrl),
      _jogador(jogador), _inimigo(inimigo),
      _dados(dados), _cena(cena),
      _cfg(cfg)
{}

std::string CondutorBatalha::_labelAcao(AcaoBatalha acao, Jogador& jogador)
{    
    int manaAtaqueRapido = jogador.getClasse().getAtaque(TipoAtaque::Rapido).custoPP;
    int manaAtaqueForte = jogador.getClasse().getAtaque(TipoAtaque::Forte).custoPP;
    switch (acao)
    {
    case AcaoBatalha::AtaqueSimples: return "Ataque Simples";
    case AcaoBatalha::AtaqueRapido:  return "Ataque Rápido  (custa: "   + std::to_string(manaAtaqueRapido) +   " de PP)";
    case AcaoBatalha::AtaqueForte:   return "Ataque Forte   (custa: "   + std::to_string(manaAtaqueForte)  +   " de PP)";
    case AcaoBatalha::Defesa:        return "Defender";
    case AcaoBatalha::Esquiva:       return "Esquivar";
    case AcaoBatalha::UsarItem:      return "Usar Item";
    case AcaoBatalha::Fugir:         return "Fugir";
    }
    return "???";
}

/**
 * Fluxo por turno:
 *  1. Exibe estado (HP/PP de ambos).
 *  2. Se paralisado -> pularTurno() (inimigo ataca, condições avançam).
 *  3. Lê ação do player via ctrl.
 *  4. Fugir: finaliza e retorna Fuga.
 *  5. UsarItem: aplica item inline, depois realizarAcao + processarAtaqueInimigo.
 *  6. Defesa / Esquiva: o contra-ataque do inimigo já está embutido em realizarAcao.
 *  7. Ataques: realizarAcao -> processarAtaqueInimigo (se inimigo ainda vivo).
 */
ResultadoBatalha CondutorBatalha::executar()
{
    Batalha batalha(&_jogador, &_inimigo, _dados);
    batalha.iniciarBatalha();

    _view.exibirLinha();
    _view.exibir("=== BATALHA ===");
    _view.exibir(_inimigo.getNome() + ": \"" + _inimigo.getFala() + "\"");
    _view.exibirLinha();

    while (_jogador.estaVivo() && _inimigo.estaVivo())
    {
        _view.exibirLinha();
        _view.exibir("[ Turno " + std::to_string(batalha.getTurno()) + " ]");
        _view.exibir("Seu HP : " +
                     std::to_string(static_cast<int>(_jogador.getVidaAtual())) +
                     " / " +
                     std::to_string(static_cast<int>(_jogador.getVidaTotal())) +
                     "   PP: " +
                     std::to_string(static_cast<int>(_jogador.getManaAtual())));
        _view.exibir(_inimigo.getNome() + " HP: " +
                     std::to_string(static_cast<int>(_inimigo.getVidaAtual())) +
                     " / " +
                     std::to_string(static_cast<int>(_inimigo.getVidaTotal())));

        const auto& acoes = batalha.getAcoesDisponiveis();

        // Paralisado: sem ações, inimigo ataca e turno avança
        if (acoes.empty())
        {
            _view.exibir("Você está paralisado! Turno perdido.");
            batalha.limparLog();
            batalha.pularTurno();
            for (const auto& msg : batalha.getLog())
                _view.exibir("  > " + msg);
            continue;
        }

        _view.exibir("O que deseja fazer?");
        for (int i = 0; i < static_cast<int>(acoes.size()); ++i)
            _view.exibir("  [" + std::to_string(i + 1) + "] " + _labelAcao(acoes[i], _jogador));

        int escolha = _ctrl.lerInteiro();
        if (escolha < 1 || escolha > static_cast<int>(acoes.size()))
        {
            _view.exibir("Opção inválida.");
            continue;
        }

        AcaoBatalha acao = acoes[escolha - 1];

        if (acao == AcaoBatalha::Fugir)
        {
            batalha.realizarAcao(AcaoBatalha::Fugir);
            _view.exibir("Você fugiu da batalha!");
            batalha.finalizarBatalha();
            return ResultadoBatalha::Fuga;
        }

        batalha.limparLog();

        if (acao == AcaoBatalha::UsarItem)
        {
            auto& inv = _jogador.getInventario();
            if (inv.quantidadeItens() == 0)
            {
                _view.exibir("Inventário vazio! Escolha outra ação.");
                continue; // não consome turno
            }
            inv.listarItens(_view);
            _view.exibir("Índice do item (ou -1 para cancelar):");
            int idxItem = _ctrl.lerInteiro();
            if (idxItem < 0 || idxItem >= inv.quantidadeItens())
            {
                _view.exibir("Cancelado.");
                continue; // não consome turno
            }
            _jogador.usarItem(idxItem);
            _view.exibir("Item usado!");
            batalha.realizarAcao(AcaoBatalha::UsarItem);
        }
        else if (acao == AcaoBatalha::Defesa || acao == AcaoBatalha::Esquiva)
        {
            // Contra-ataque do inimigo já embutido em realizarAcao
            batalha.realizarAcao(acao);
        }
        else if (acao == AcaoBatalha::AtaqueRapido) 
        {
            if(batalha.verificarManaSuficiente(TipoAtaque::Rapido)) {
                batalha.realizarAcao(acao);
            }
            else
                _view.exibir("Mana insuficiente.");
        }
        else if (acao == AcaoBatalha::AtaqueForte) 
        {
            if(batalha.verificarManaSuficiente(TipoAtaque::Forte)) {
                batalha.realizarAcao(acao);
            }
            else
                _view.exibir("Mana insuficiente.");
        }
        else
        {
            // Ataque Simples
            batalha.realizarAcao(acao);
        }

        for (const auto& msg : batalha.getLog())
            _view.exibir("  > " + msg);
    }

    if (!_jogador.estaVivo())
    {
        _view.exibirLinha();
        _view.exibir("Você foi derrotado...");
        batalha.finalizarBatalha();
        return ResultadoBatalha::Derrota;
    }

    _view.exibirLinha();
    _view.exibir(_inimigo.getNome() + " foi derrotado!");
    batalha.definirRecompensa(_cena);
    batalha.finalizarBatalha();
    _jogador.recuperarVida(_jogador.getVidaTotal());
    _jogador.recuperarMana(_jogador.getManaTotal());
    return ResultadoBatalha::Vitoria;
}
