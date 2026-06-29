#include "demo/CondutorBatalha.hpp"
#include "demo/UI.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/battle/Batalha.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoDadosAtaque.hpp"
#include "core/Dados.hpp"
#include "core/rules/Regras.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

CondutorBatalha::CondutorBatalha(IView& view, IController& ctrl,
                                 Jogador& jogador, Personagem& inimigo,
                                 Dados& dados, Cena& cena,
                                 const ConfigExploracao& cfg)
    : _view(view), _ctrl(ctrl),
      _jogador(jogador), _inimigo(inimigo),
      _dados(dados), _cena(cena),
      _cfg(cfg)
{}

// ── Label do menu ─────────────────────────────────────────────────────────────
std::string CondutorBatalha::_labelAcao(AcaoBatalha acao, Jogador& jogador)
{
    int ppRapido = jogador.getClasse().getAtaque(TipoAtaque::Rapido).custoPP;
    int ppForte  = jogador.getClasse().getAtaque(TipoAtaque::Forte).custoPP;
    switch (acao) {
    case AcaoBatalha::AtaqueSimples: return "Ataque Simples";
    case AcaoBatalha::AtaqueRapido:  return "Ataque Rapido  (PP: " + std::to_string(ppRapido) + ")";
    case AcaoBatalha::AtaqueForte:   return "Ataque Forte   (PP: " + std::to_string(ppForte)  + ")";
    case AcaoBatalha::Defesa:        return "Defender";
    case AcaoBatalha::Esquiva:       return "Esquivar";
    case AcaoBatalha::UsarItem:      return "Usar Item";
    case AcaoBatalha::Fugir:         return "Fugir";
    }
    return "???";
}

// ── HUD ───────────────────────────────────────────────────────────────────────
void CondutorBatalha::_exibirHUD(Batalha& batalha, int turno) const
{
    (void)batalha;
    int hpA = static_cast<int>(_jogador.getVidaAtual());
    int hpT = static_cast<int>(_jogador.getVidaTotal());
    int ppA = static_cast<int>(_jogador.getManaAtual());
    int ppT = static_cast<int>(_jogador.getManaTotal());
    int atk = static_cast<int>(_jogador.getAtaque());
    int def = static_cast<int>(_jogador.getDefesa());
    int agi = static_cast<int>(_jogador.getAgilidade());
    int xp  = static_cast<int>(_jogador.getXp());
    int niv = _jogador.getNivel();

    // Barra de HP
    int barW = 20;
    int filled = (hpT > 0) ? (hpA * barW / hpT) : 0;
    std::string hpBar = "[" + std::string(filled, '#') + std::string(barW - filled, '-') + "]";

    // Linha fechada com ║ na coluna 62 (inner = 58 chars, total = 2+1+58+1=62)
    auto row = [](const std::string& s) -> std::string {
        const int W = 58;
        std::string line = "  ║  " + s;
        // conta bytes do prefixo "  ║  " = 2+3+2=7, mas ║ = 3 bytes → prefixo visual = 5
        // usamos tamanho visual (só ASCII aqui), então size() ok
        int vis = 5 + (int)s.size(); // "  ║  " visual = 5
        int pad = (W + 3) - vis;     // 3 = "  ║" visual
        if (pad < 0) pad = 0;
        return line + std::string(pad, ' ') + "║";
    };

    std::ostringstream l1, l2, l3, l4;
    l1 << "Turno " << std::setw(2) << turno
       << "  |  " << _jogador.getNome()
       << "  (" << _jogador.getClasse().getNome() << ")"
       << "  Nv." << niv << "  XP:" << xp;
    l2 << "HP: " << hpBar << " " << hpA << "/" << hpT
       << "    PP: " << ppA << "/" << ppT;
    l3 << "ATK:" << atk << "  DEF:" << def << "  AGI:" << agi;

    int hpI = static_cast<int>(_inimigo.getVidaAtual());
    int hpIT = static_cast<int>(_inimigo.getVidaTotal());
    int filledI = (hpIT > 0) ? (hpI * barW / hpIT) : 0;
    std::string hpBarI = "[" + std::string(filledI, '#') + std::string(barW - filledI, '-') + "]";
    l4 << _inimigo.getNome() << "  HP: " << hpBarI << " " << hpI << "/" << hpIT;

    std::string SEP = "  ╠" + std::string(58, '=') + "╣";
    // Troca = por ═ (ASCII aqui, mas usamos o char certo)
    std::string sep58(58, '\0');
    for (auto& c : sep58) c = '='; // placeholder
    // Melhor: construir direto
    std::string topBot58 = "";
    for (int i = 0; i < 58; i++) topBot58 += "\xe2\x95\x90"; // ═
    std::string sepMid58 = "";
    for (int i = 0; i < 58; i++) sepMid58 += "\xe2\x95\x90"; // ═

    std::cout << "\n";
    std::cout << "  \xe2\x95\x94" << topBot58 << "\xe2\x95\x97\n"; // ╔═...═╗
    std::cout << row(l1.str()) << "\n";
    std::cout << row(l2.str()) << "\n";
    std::cout << row(l3.str()) << "\n";
    std::cout << "  \xe2\x95\xa0" << sepMid58 << "\xe2\x95\xa3\n"; // ╠═...═╣
    std::cout << row(l4.str()) << "\n";
    std::cout << "  \xe2\x95\x9a" << topBot58 << "\xe2\x95\x9d\n\n"; // ╚═...═╝
}

// ── Descrição de ataques ──────────────────────────────────────────────────────
void CondutorBatalha::_exibirDescricaoAtaques() const
{
    const auto& ataques = _jogador.getClasse().getAtaques();
    static const char* tipoStr[] = {"Simples","Rapido ","Forte  "};
    // Top: 2+ ┌ + ─── + " Seus ataques " (14) + 40×─ + ┐  = 61 cols
    // Content: "  │" (3) + inner (57) + "│" (1) = 61
    const int ATK_W = 57;
    auto visLen = [](const std::string& s) {
        int w = 0;
        for (size_t i = 0; i < s.size(); ) {
            unsigned char c = (unsigned char)s[i];
            if      (c < 0x80)           { w++; i += 1; }
            else if ((c & 0xE0) == 0xC0) { w++; i += 2; }
            else if ((c & 0xF0) == 0xE0) { w++; i += 3; }
            else                         { w++; i += 4; }
        }
        return w;
    };
    auto arow = [ATK_W, &visLen](const std::string& s) {
        int pad = ATK_W - visLen(s);
        if (pad < 0) pad = 0;
        std::cout << "  \xe2\x94\x82" << s << std::string(pad, ' ') << "\xe2\x94\x82\n";
    };
    std::cout << "  \xe2\x94\x8c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80 Seus ataques ";
    for (int i = 0; i < 40; i++) std::cout << "\xe2\x94\x80"; // ─
    std::cout << "\xe2\x94\x90\n"; // ┐
    for (int i = 0; i < 3; i++) {
        const Ataque& a = ataques[i];
        const DadosAtaque& d = BancoDadosAtaque::getDadosAtaque(a.id);
        std::string coef;
        switch (d.atributoCoef) {
            case AtributoCoef::Ataque:    coef = "+ATK"; break;
            case AtributoCoef::Defesa:    coef = "+DEF"; break;
            case AtributoCoef::Agilidade: coef = "+AGI"; break;
        }
        std::string formula;
        if (d.dadosPorNivel)
            formula = "Nv x d" + std::to_string(d.faces) + coef;
        else if (d.numeroDeExecucoes > 1)
            formula = std::to_string(d.quantidadeDados) + "d" + std::to_string(d.faces)
                    + coef + " x" + std::to_string(d.numeroDeExecucoes);
        else
            formula = std::to_string(d.quantidadeDados) + "d" + std::to_string(d.faces) + coef;

        std::string linha1 = "  [" + std::string(tipoStr[i]) + "] " + a.nome + "  " + formula;
        arow(linha1);
        if (!a.descricao.empty())
            arow("          " + a.descricao);
    }
    std::cout << "  \xe2\x94\x94";
    for (int i = 0; i < ATK_W; i++) std::cout << "\xe2\x94\x80";
    std::cout << "\xe2\x94\x98\n\n"; // └...┘
}

// ── Animação de ataque do player ──────────────────────────────────────────────
void CondutorBatalha::_animarAtaquePlayer(Batalha& batalha)
{
    const auto& res = batalha.getUltimoTurno();
    std::string nome = res.nomeAtaque.empty() ? "Simples" : res.nomeAtaque;
    int mod = static_cast<int>(_jogador.getAtaque()) / 5;
    animarDadoComResultado("Seu ataque (" + nome + ")", 20, res.playerRollD20, 8, mod);
    if (res.playerAcertou) {
        std::cout << "  \033[1;32mACERTO!\033[0m  " << _inimigo.getNome() << " foi atingido!\n";
        int danoInt = static_cast<int>(res.playerDano);
        animarDadoComResultado("  Dano", 12, danoInt > 0 ? danoInt : 1);
        std::cout << "  \033[1;33m" << _inimigo.getNome() << " sofreu "
                  << danoInt << " de dano!\033[0m\n";
    } else {
        std::cout << "  \033[1;31mERRO!\033[0m  " << _inimigo.getNome() << " desviou.\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
}

// ── Animação de ataque do inimigo ─────────────────────────────────────────────
void CondutorBatalha::_animarAtaqueInimigo(Batalha& batalha)
{
    const auto& res = batalha.getUltimoTurno();
    int mod = static_cast<int>(_inimigo.getAtaque()) / 5;
    animarDadoComResultado("Ataque de " + _inimigo.getNome(), 20, res.inimigoRollD20, 8, mod);
    if (res.inimigoAcertou) {
        std::cout << "  \033[1;31mACERTO!\033[0m  " << _jogador.getNome() << " foi atingido!\n";
        int danoInt = static_cast<int>(res.inimigoDano);
        animarDadoComResultado("  Dano recebido", 10, danoInt > 0 ? danoInt : 1);
        std::cout << "  \033[1;31m" << _jogador.getNome() << " sofreu "
                  << danoInt << " de dano!\033[0m\n";
    } else {
        std::cout << "  Voce desviou do ataque de " << _inimigo.getNome() << "!\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
}

// ── Loop principal ────────────────────────────────────────────────────────────
ResultadoBatalha CondutorBatalha::executar()
{
    Batalha batalha(&_jogador, &_inimigo, _dados);
    batalha.iniciarBatalha();

    limparTela();
    std::cout << "\n  \033[1;31m══ BATALHA ══\033[0m\n";
    std::cout << "  " << _inimigo.getNome() << ": \"" << _inimigo.getFala() << "\"\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    while (_jogador.estaVivo() && _inimigo.estaVivo())
    {
        limparTela();
        _exibirHUD(batalha, batalha.getTurno());

        const auto& acoes = batalha.getAcoesDisponiveis();

        // Paralisado
        if (acoes.empty()) {
            std::cout << "  \033[1;31mVoce esta paralisado! Turno perdido.\033[0m\n\n";
            batalha.limparLog();
            batalha.pularTurno();
            // Anima ataque do inimigo
            _animarAtaqueInimigo(batalha);
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";
            std::cout << "\n  [Enter para continuar]\n";
            _ctrl.lerTexto();
            continue;
        }

        // Mostrar descrição dos ataques
        _exibirDescricaoAtaques();

        // Menu de ações
        std::cout << "  O que deseja fazer?\n";
        for (int i = 0; i < static_cast<int>(acoes.size()); ++i)
            std::cout << "  [" << (i+1) << "] " << _labelAcao(acoes[i], _jogador) << "\n";
        std::cout << "\n  > ";

        int escolha = _ctrl.lerInteiro();
        if (escolha < 1 || escolha > static_cast<int>(acoes.size())) {
            std::cout << "  Opcao invalida.\n";
            continue;
        }

        AcaoBatalha acao = acoes[escolha - 1];

        // Fuga
        if (acao == AcaoBatalha::Fugir) {
            batalha.realizarAcao(AcaoBatalha::Fugir);
            std::cout << "  Voce fugiu da batalha!\n";
            batalha.finalizarBatalha();
            return ResultadoBatalha::Fuga;
        }

        // Usar Item
        if (acao == AcaoBatalha::UsarItem) {
            auto& inv = _jogador.getInventario();
            if (inv.quantidadeItens() == 0) {
                std::cout << "  Inventario vazio!\n";
                continue;
            }
            inv.listarItens(_view);
            std::cout << "  Indice do item (ou -1 para cancelar): ";
            int idxItem = _ctrl.lerInteiro();
            if (idxItem < 0 || idxItem >= inv.quantidadeItens()) {
                std::cout << "  Cancelado.\n";
                continue;
            }
            _jogador.usarItem(idxItem);
            std::cout << "  Item usado!\n";
            batalha.limparLog();
            batalha.realizarAcao(AcaoBatalha::UsarItem);
            std::cout << "  \033[33m(Atordoado por 2 turnos: ataques especiais bloqueados)\033[0m\n";
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";
            std::cout << "\n  [Enter para continuar]\n";
            _ctrl.lerTexto();
            continue;
        }

        // Defesa / Esquiva (inimigo já embutido)
        if (acao == AcaoBatalha::Defesa || acao == AcaoBatalha::Esquiva) {
            batalha.limparLog();
            batalha.realizarAcao(acao);
            // Para defesa/esquiva, mostra resultado direto do log
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";
            std::cout << "\n  [Enter para continuar]\n";
            _ctrl.lerTexto();
            continue;
        }

        // Verificar mana
        if (acao == AcaoBatalha::AtaqueRapido && !batalha.temManaSuficiente(TipoAtaque::Rapido)) {
            std::cout << "  PP insuficiente!\n";
            continue;
        }
        if (acao == AcaoBatalha::AtaqueForte && !batalha.temManaSuficiente(TipoAtaque::Forte)) {
            std::cout << "  PP insuficiente!\n";
            continue;
        }

        // ── ATAQUES: rolagem de iniciativa ────────────────────────────────────
        limparTela();
        _exibirHUD(batalha, batalha.getTurno());

        int modPlayer  = static_cast<int>(_jogador.getAgilidade()) / 5;
        int modInimigo = static_cast<int>(_inimigo.getAgilidade()) / 5;
        int d20Player  = _dados.rolar(1, 20);
        int d20Inimigo = _dados.rolar(1, 20);
        int initPlayer  = d20Player  + modPlayer;
        int initInimigo = d20Inimigo + modInimigo;
        bool inimigoFirst = initInimigo > initPlayer;

        std::cout << "  \033[1m── Iniciativa ──\033[0m\n";
        animarDadoComResultado("  " + _jogador.getNome(),  20, d20Player,  6, modPlayer);
        animarDadoComResultado("  " + _inimigo.getNome(), 20, d20Inimigo, 6, modInimigo);

        if (inimigoFirst) {
            std::cout << "\n  \033[1;31m" << _inimigo.getNome() << " age primeiro!\033[0m\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Inimigo ataca ANTES
            batalha.limparLog();
            batalha.processarAtaqueInimigo();
            _animarAtaqueInimigo(batalha);
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";

            if (!_jogador.estaVivo()) {
                std::cout << "\n  [Enter]\n"; _ctrl.lerTexto();
                break;
            }

            std::cout << "\n  \033[1m-- Sua vez --\033[0m\n\n";
            // Player ataca (sem contra-ataque automático)
            batalha.limparLog();
            batalha.realizarAcao(acao, false);
            _animarAtaquePlayer(batalha);
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";

        } else {
            std::cout << "\n  \033[1;32m" << _jogador.getNome() << " age primeiro!\033[0m\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Player ataca (sem contra-ataque automático)
            batalha.limparLog();
            batalha.realizarAcao(acao, false);
            _animarAtaquePlayer(batalha);
            for (const auto& msg : batalha.getLog())
                std::cout << "  > " << msg << "\n";

            if (_inimigo.estaVivo()) {
                std::cout << "\n  \033[1;31m" << _inimigo.getNome() << " contra-ataca!\033[0m\n\n";
                // Inimigo ataca depois
                batalha.limparLog();
                batalha.processarAtaqueInimigo();
                _animarAtaqueInimigo(batalha);
                for (const auto& msg : batalha.getLog())
                    std::cout << "  > " << msg << "\n";
            }
        }

        std::cout << "\n  [Enter para continuar]\n";
        _ctrl.lerTexto();
    }

    // Resultado
    if (!_jogador.estaVivo()) {
        limparTela();
        std::cout << "\n  \033[1;31mVoce foi derrotado...\033[0m\n\n";
        batalha.finalizarBatalha();
        return ResultadoBatalha::Derrota;
    }

    limparTela();
    std::cout << "\n  \033[1;32m" << _inimigo.getNome() << " foi derrotado!\033[0m\n\n";
    batalha.definirRecompensa(_cena);
    batalha.finalizarBatalha();
    _jogador.recuperarVida(_jogador.getVidaTotal());
    _jogador.recuperarMana(_jogador.getManaTotal());
    return ResultadoBatalha::Vitoria;
}
