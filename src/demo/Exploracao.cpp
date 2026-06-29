#include <stdexcept>
#include <string>

#include "demo/Exploracao.hpp"
#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "demo/CondutorBatalha.hpp"
#include "demo/ConfigExploracao.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "database/BancoNpcInteracao.hpp"
#include "database/BancoItem.hpp"
#include "database/BancoInimigo.hpp"
#include "entities/battle/Batalha.hpp"
#include "core/Dados.hpp"
#include "utils/TipoArcanoEnum.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// Tabelas de mapeamento (cena -> boss / arcano)
// ─────────────────────────────────────────────────────────────────────────────

static int bossIdParaCena(int cenaId)
{
    if (cenaId < 1 || cenaId > 7)
        throw std::out_of_range(
            "bossIdParaCena: cenaId fora do intervalo [1,7]: " +
            std::to_string(cenaId));
    if (cenaId == 7)
        return 999; // Sonath — boss final
    return 100 + cenaId; // 101 … 106 -> Arautos por fase
}

static TipoArcano arcanoParaCena(int cenaId)
{
    if (cenaId < 1 || cenaId > 7)
        throw std::out_of_range(
            "arcanoParaCena: cenaId fora do intervalo [1,7]: " +
            std::to_string(cenaId));
    switch (cenaId)
    {
    case 1: return TipoArcano::Alma;
    case 2: return TipoArcano::Elementos;
    case 3: return TipoArcano::Caos;
    case 4: return TipoArcano::Mente;
    case 5: return TipoArcano::Vida;
    case 6: return TipoArcano::Natureza;
    default: return TipoArcano::Nenhum; // cena 7: boss final, sem arcano novo
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Eventos de exploração
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Verifica e executa batalha com inimigo comum do trecho atual.
 * Retorna false se o jogador foi derrotado.
 */
static bool verificarCombate(
    IView& view, IController& ctrl,
    Jogador& jogador, Cena& cena, Dados& dados,
    const ConfigExploracao& cfg)
{
    if (!cena.pegarTrechoAtual().possuiInimigo())
        return true;

    int inimigoId = cena.pegarTrechoAtual().pegarIdInimigo();
    Personagem inimigo = BancoInimigo::obterInimigo(inimigoId);

    view.exibirLinha();
    view.exibir("Um inimigo apareceu: " + inimigo.getNome() + "!");
    view.exibirLinha();

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena, cfg);
    return (condutor.executar() != ResultadoBatalha::Derrota);
}

static void interagirNpc(IView& view, const Cena& cena)
{
    int npcId = cena.pegarTrechoAtual().pegarNPCInteracao();

    if (npcId <= 0)
    {
        view.exibir("Não há NPCs neste trecho.");
        return;
    }

    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(npcId);

    view.exibirLinha();
    view.exibir("Nome: " + npc.nome);
    view.exibir("Descrição: " + npc.descricaoFisica);
    view.exibir("Fala: " + npc.fala);
    view.exibirLinha();
}

// ─────────────────────────────────────────────────────────────────────────────
// Sub-menus
// ─────────────────────────────────────────────────────────────────────────────

static void gerenciarInventario(
    IView& view, IController& ctrl,
    Jogador& jogador,
    const ConfigExploracao& cfg)
{
    auto& inv = jogador.getInventario();
    view.exibir("\n--- Inventário ---");

    if (inv.quantidadeItens() == 0)
    {
        view.exibir("Inventário vazio.");
    }
    else
    {
        inv.listarItens(view);
        view.exibir("Usar item? [índice / -1]");
        int idx = ctrl.lerInteiro();

        if (idx >= 0 && idx < inv.quantidadeItens())
        {
            jogador.usarItem(idx);
            view.exibir("Item usado!");
        }
        else if (idx != -1)
        {
            view.exibir("Índice inválido.");
        }
        else
        {
            view.exibir("Inventário fechado. Nenhum item utilizado.");
        }
    }
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
}

/** Retorna 0 (derrota) ou 2 (vitória sobre o boss da cena). */
static int executarEncontroBoss(
    IView& view, IController& ctrl,
    Jogador& jogador, Cena& cena, Dados& dados,
    const ConfigExploracao& cfg)
{
    int bossId = bossIdParaCena(cena.pegarId());
    Personagem boss = BancoInimigo::obterInimigo(bossId);

    view.exibirLinha();
    view.exibir("Um inimigo poderoso barra o seu caminho! A fuga não é possível.");
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
    view.exibir(boss.getDescricao());
    view.exibirLinha();

    CondutorBatalha condutor(view, ctrl, jogador, boss, dados, cena, cfg);
    if (condutor.executar() == ResultadoBatalha::Derrota)
        return 0;

    TipoArcano arcano = arcanoParaCena(cena.pegarId());
    if (arcano != TipoArcano::Nenhum)
    {
        jogador.adicionarArcano(arcano);
        view.exibir("Arcano concedido: " + cena.pegarArcano() + "!");
    }

    return 2;
}

// ─────────────────────────────────────────────────────────────────────────────
// Diálogos pós-boss
// ─────────────────────────────────────────────────────────────────────────────

static void dialogoPosBoss(
    IView& view, IController& ctrl,
    int cenaId, const ConfigExploracao& cfg)
{
    if (cfg.skipLore) return;
    view.exibirLinha();
    exibirDialogo(view,
        "data/dialogos/pos_boss_" + std::to_string(cenaId) + ".txt");
    view.exibirLinha();
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
}

static void confrontoRuffen(
    IView& view, IController& ctrl,
    const ConfigExploracao& cfg)
{
    if (cfg.skipLore) return;
    view.exibirLinha();
    exibirDialogo(view, "data/dialogos/confronto_ruffen.txt");
    view.exibirLinha();

    view.exibir("  [1] Enfrentar Ruffen");
    view.exibir("  [2] Deixa-lo passar e seguir em frente");
    int op = ctrl.lerInteiro();
    if (op == 1)
        view.exibir("  A batalha foi brutal. Ruffen recuou -- por ora.");
    else
        view.exibir("  Voce deixa Ruffen para tras. O santuario de Sonath aguarda.");

    view.exibirLinha();
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
}

// ─────────────────────────────────────────────────────────────────────────────
// Loop de exploração por cena
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Retorna:
 *   0 -> player derrotado ou encerramento voluntário
 *   2 -> boss da cena derrotado (avançar para próxima cena)
 */
static int loopExploracaoCena(
    IView& view,
    IController& ctrl,
    Jogador& jogador,
    Cena& cena,
    Dados& dados,
    const ConfigExploracao& cfg)
{
    cena.iniciarCena();
    limparTela();
    exibirHeaderCena(view, cena);
    // Pausa para o jogador ver o arcano e o título da cena
    aguardarEnter(view, ctrl, "\n  [ Pressione qualquer tecla para explorar... ]", cfg);

    if (!verificarCombate(view, ctrl, jogador, cena, dados, cfg))
        return 0;

    while (true)
    {
        limparTela();
        view.exibirLinha();
        view.exibir("[Localização] " + cena.pegarTrechoAtual().pegarDescricao());

        bool temItens = cena.pegarTrechoAtual().possuiItensRestantes();

        view.exibir("O que deseja fazer?\n");
        view.exibir("  [1] Vasculhar o local");
        view.exibir("  [2] Interagir com NPCs");
        view.exibir("  [3] Abrir inventário");
        view.exibir("  [4] Avançar");
        view.exibir("  [5] Encerrar");

        int opcao = ctrl.lerInteiro();

        switch (opcao)
        {
        case 1:
        {
            if (temItens)
            {
                int itemId = cena.pegarTrechoAtual().sortearItem();
                Item preview = BancoItem::obterItem(cena.pegarId(), itemId);

                view.exibir("Você encontrou: " + preview.pegarNome() +
                            " — " + preview.pegarDescricao());
                view.exibir("Pegar item? [s/n]");
                std::string resp = ctrl.lerTexto();

                if (!resp.empty() && (resp[0] == 's' || resp[0] == 'S'))
                {
                    cena.vasculhar();
                    view.exibir("Item adicionado ao inventário!");
                }
                else
                {
                    cena.descartarItem();
                    view.exibir("Você deixou o item para trás.");
                }
            }
            else
            {
                view.exibir("Nada para vasculhar aqui.");
            }
            aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
            break;
        }

        case 2:
            interagirNpc(view, cena);
            aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]", cfg);
            break;

        case 3:
            gerenciarInventario(view, ctrl, jogador, cfg);
            break;

        case 4:
        {
            if (cena.pegarTrechoAtual().pegarProximoTrecho() == -1) {
                limparTela();
                return executarEncontroBoss(view, ctrl, jogador, cena, dados, cfg);
            }

            cena.andar();

            if (!verificarCombate(view, ctrl, jogador, cena, dados, cfg))
                return 0;

            break;
        }

        case 5:
            view.exibir("Run encerrada.");
            return 0;

        default:
            view.exibir("Opção inválida. Tente novamente");
            break;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Ponto de entrada da demo
// ─────────────────────────────────────────────────────────────────────────────

void executarExploracao(IView& view, IController& ctrl)
{
    executarExploracao(view, ctrl, ConfigExploracao{});
}

void executarExploracao(IView& view, IController& ctrl, const ConfigExploracao& cfg)
{
    int cenaInicial = 1;
    Jogador jogador = criarPersonagem(view, ctrl, cenaInicial, cfg);
    Dados dados;

    int idCenaAtual = cenaInicial;

    while (idCenaAtual <= 7)
    {
        limparTela();
        InfoCena dadosCena = BancoCena::obterCena(idCenaAtual);
        Cena cena(dadosCena, jogador);

        int estado = loopExploracaoCena(view, ctrl, jogador, cena, dados, cfg);

        if (estado == 0)
            return;

        if (estado == 2)
        {
            if (idCenaAtual >= 1 && idCenaAtual <= 5)
                dialogoPosBoss(view, ctrl, idCenaAtual, cfg);
            else if (idCenaAtual == 6)
                confrontoRuffen(view, ctrl, cfg);
            idCenaAtual++;
        }
    }

    exibirRelatorio(view, jogador);
    aguardarEnter(view, ctrl, "Pressione Enter para sair...", cfg);
}
