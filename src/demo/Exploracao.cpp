#include <string>

#include "demo/Exploracao.hpp"
#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
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
// Tipos locais
// ─────────────────────────────────────────────────────────────────────────────

enum class ResultadoBatalha
{
    Vitoria,
    Derrota,
    Fuga
};

// ─────────────────────────────────────────────────────────────────────────────
// Tabelas de mapeamento (cena → boss / arcano)
// ─────────────────────────────────────────────────────────────────────────────

static int bossIdParaCena(int cenaId)
{
    if (cenaId == 7)
        return 999;      // Sonath — boss final
    return 100 + cenaId; // 101 … 106 → Arautos por fase
}

static TipoArcano arcanoParaCena(int cenaId)
{
    switch (cenaId)
    {
    case 1:
        return TipoArcano::Alma;
    case 2:
        return TipoArcano::Elementos;
    case 3:
        return TipoArcano::Caos;
    case 4:
        return TipoArcano::Mente;
    case 5:
        return TipoArcano::Vida;
    case 6:
        return TipoArcano::Natureza;
    default:
        return TipoArcano::Nenhum; // cena 7: boss final, sem arcano novo
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers de UI
// ─────────────────────────────────────────────────────────────────────────────

static void aguardarEnter(IView &view, IController &ctrl, const std::string &msg)
{
    view.exibir(msg);
    ctrl.lerTexto();
}

static void exibirHeaderCena(IView &view, const Cena &cena)
{
    exibirAsciiArtArquivo(
        view,
        "data/arcanos/" + std::to_string(cena.pegarId()) + ".txt");

    std::string titulo =
        "  Cena " + std::to_string(cena.pegarId()) +
        "  ~*~  " + cena.pegarArcano() + "  ";
    std::string borda = "+" + std::string(titulo.size(), '=') + "+";

    exibirCentrado(view, borda);
    exibirCentrado(view, "|" + titulo + "|");
    exibirCentrado(view, borda);
    view.exibir("");
    exibirCentrado(view, cena.pegarDescricao());
    view.exibir("");
}

static void exibirRelatorio(IView &view, Jogador &jogador)
{
    view.exibirLinha();
    view.exibir("=== Relatório de Validação ===");
    view.exibir("Personagem  : " + jogador.getNome() +
                " (" + jogador.getClasse().getNome() + ")");
    view.exibir("Nível       : " + std::to_string(jogador.getNivel()) +
                " | XP: " + std::to_string(static_cast<int>(jogador.getXp())));
    view.exibir("HP          : " + std::to_string(static_cast<int>(jogador.getVidaAtual())) +
                " / " + std::to_string(static_cast<int>(jogador.getVidaTotal())));

    view.exibir("\n--- Inventário final ---");
    int qtd = jogador.getInventario().quantidadeItens();
    if (qtd == 0)
        view.exibir("Inventário vazio.");
    else
        jogador.getInventario().listarItens();

    view.exibirLinha();
    view.exibir("Fim da demo c:");
    view.exibirLinha();
}

static std::string labelAcao(AcaoBatalha acao)
{
    switch (acao)
    {
    case AcaoBatalha::AtaqueSimples:
        return "Ataque Simples";
    case AcaoBatalha::AtaqueRapido:
        return "Ataque Rápido  (custa PP)";
    case AcaoBatalha::AtaqueForte:
        return "Ataque Forte   (custa PP)";
    case AcaoBatalha::Defesa:
        return "Defender";
    case AcaoBatalha::Esquiva:
        return "Esquivar";
    case AcaoBatalha::UsarItem:
        return "Usar Item";
    case AcaoBatalha::Fugir:
        return "Fugir";
    }
    return "???";
}

// ─────────────────────────────────────────────────────────────────────────────
// Loop de batalha
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Executa um combate completo entre jogador e inimigo.
 *
 * Fluxo por turno:
 *  1. Exibe estado (HP/PP de ambos).
 *  2. Se paralisado → pularTurno() (inimigo ataca, condições avançam).
 *  3. Lê ação do player via ctrl.
 *  4. Fugir: finaliza e retorna Fuga.
 *  5. UsarItem: aplica item inline, depois realizarAcao + processarAtaqueInimigo.
 *  6. Defesa / Esquiva: o contra-ataque do inimigo já está embutido em realizarAcao.
 *  7. Ataques: realizarAcao → processarAtaqueInimigo (se inimigo ainda vivo).
 */
static ResultadoBatalha loopBatalha(
    IView &view,
    IController &ctrl,
    Jogador &jogador,
    Personagem &inimigo,
    Dados &dados,
    Cena &cena)
{
    Batalha batalha(&jogador, &inimigo, dados);
    batalha.iniciarBatalha();

    view.exibirLinha();
    view.exibir("=== BATALHA ===");
    view.exibir(inimigo.getNome() + ": \"" + inimigo.getFala() + "\"");
    view.exibirLinha();

    while (jogador.estaVivo() && inimigo.estaVivo())
    {
        view.exibirLinha();
        view.exibir("[ Turno " + std::to_string(batalha.getTurno()) + " ]");
        view.exibir("Seu HP : " + std::to_string(static_cast<int>(jogador.getVidaAtual())) + " / " + std::to_string(static_cast<int>(jogador.getVidaTotal())) + "   PP: " + std::to_string(static_cast<int>(jogador.getManaAtual())));
        view.exibir(inimigo.getNome() + " HP: " + std::to_string(static_cast<int>(inimigo.getVidaAtual())) + " / " + std::to_string(static_cast<int>(inimigo.getVidaTotal())));

        const auto &acoes = batalha.getAcoesDisponiveis();

        // Paralisado: sem ações, inimigo ataca e turno avança
        if (acoes.empty())
        {
            view.exibir("Você está paralisado! Turno perdido.");
            batalha.limparLog();
            batalha.pularTurno();
            for (const auto& msg : batalha.getLog())
                view.exibir("  > " + msg);
            continue;
        }

        view.exibir("O que deseja fazer?");
        for (int i = 0; i < static_cast<int>(acoes.size()); ++i)
            view.exibir("  [" + std::to_string(i + 1) + "] " + labelAcao(acoes[i]));

        int escolha = ctrl.lerInteiro();
        if (escolha < 1 || escolha > static_cast<int>(acoes.size()))
        {
            view.exibir("Opção inválida.");
            continue;
        }

        AcaoBatalha acao = acoes[escolha - 1];

        if (acao == AcaoBatalha::Fugir)
        {
            batalha.realizarAcao(AcaoBatalha::Fugir);
            view.exibir("Você fugiu da batalha!");
            batalha.finalizarBatalha();
            return ResultadoBatalha::Fuga;
        }

        batalha.limparLog();

        if (acao == AcaoBatalha::UsarItem)
        {
            auto &inv = jogador.getInventario();
            if (inv.quantidadeItens() == 0)
            {
                view.exibir("Inventário vazio! Escolha outra ação.");
                continue; // não consome turno
            }
            inv.listarItens();
            view.exibir("Índice do item (ou -1 para cancelar):");
            int idxItem = ctrl.lerInteiro();
            if (idxItem < 0 || idxItem >= inv.quantidadeItens())
            {
                view.exibir("Cancelado.");
                continue; // não consome turno
            }
            jogador.usarItem(idxItem);
            view.exibir("Item usado!");
            batalha.realizarAcao(AcaoBatalha::UsarItem);
            if (inimigo.estaVivo())
                batalha.processarAtaqueInimigo();
        }
        else if (acao == AcaoBatalha::Defesa || acao == AcaoBatalha::Esquiva)
        {
            // Contra-ataque do inimigo já embutido em realizarAcao para essas ações
            batalha.realizarAcao(acao);
        }
        else
        {
            // Ataque Simples / Rápido / Forte: player ataca; inimigo contra-ataca depois
            batalha.realizarAcao(acao);
            if (inimigo.estaVivo())
                batalha.processarAtaqueInimigo();
        }

        for (const auto& msg : batalha.getLog())
            view.exibir("  > " + msg);
    }

    if (!jogador.estaVivo())
    {
        view.exibirLinha();
        view.exibir("Você foi derrotado...");
        batalha.finalizarBatalha();
        return ResultadoBatalha::Derrota;
    }

    view.exibirLinha();
    view.exibir(inimigo.getNome() + " foi derrotado!");
    batalha.definirRecompensa(cena);
    batalha.finalizarBatalha();
    return ResultadoBatalha::Vitoria;
}

// ─────────────────────────────────────────────────────────────────────────────
// Eventos de exploração
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Verifica e executa batalha com inimigo comum do trecho atual.
 * Retorna false se o jogador foi derrotado (run encerra).
 */
static bool verificarCombate(
    IView &view, IController &ctrl,
    Jogador &jogador, Cena &cena, Dados &dados)
{
    if (!cena.pegarTrechoAtual().possuiInimigo())
        return true;

    int inimigoId = cena.pegarTrechoAtual().pegarIdInimigo();
    Personagem inimigo = BancoInimigo::obterInimigo(inimigoId);

    view.exibirLinha();
    view.exibir("Um inimigo apareceu: " + inimigo.getNome() + "!");
    view.exibirLinha();

    ResultadoBatalha res = loopBatalha(view, ctrl, jogador, inimigo, dados, cena);
    return (res != ResultadoBatalha::Derrota);
}

static void interagirNpc(IView &view, const Cena &cena)
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
// Loop de exploração por cena
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Retorna:
 *   0 → player derrotado ou encerramento voluntário (run termina)
 *   2 → boss da cena derrotado (avançar para próxima cena)
 */
static int loopExploracaoCena(
    IView &view,
    IController &ctrl,
    Jogador &jogador,
    Cena &cena,
    Dados &dados)
{
    cena.iniciarCena();
    exibirHeaderCena(view, cena);

    // Verifica inimigo no trecho inicial
    if (!verificarCombate(view, ctrl, jogador, cena, dados))
        return 0;

    while (true)
    {
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
            aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");
            break;
        }

        case 2:
            interagirNpc(view, cena);
            aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");
            break;

        case 3:
        {
            auto &inv = jogador.getInventario();
            view.exibir("\n--- Inventário ---");

            if (inv.quantidadeItens() == 0)
            {
                view.exibir("Inventário vazio.");
            }
            else
            {
                inv.listarItens();
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
            aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");
            break;
        }

        case 4:
        {
            if (cena.pegarTrechoAtual().pegarProximoTrecho() == -1)
            {
                // Trecho final da cena — batalha do boss
                int bossId = bossIdParaCena(cena.pegarId());
                Personagem boss = BancoInimigo::obterInimigo(bossId);

                view.exibirLinha();
                view.exibir("Um inimigo poderoso barra o seu caminho! A fuga não é possível.");

                aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");

                view.exibir(boss.getDescricao());
                view.exibirLinha();

                ResultadoBatalha res = loopBatalha(view, ctrl, jogador, boss, dados, cena);

                if (res == ResultadoBatalha::Derrota)
                    return 0;

                // Boss derrotado: concede arcano e avança cena
                TipoArcano arcano = arcanoParaCena(cena.pegarId());
                if (arcano != TipoArcano::Nenhum)
                {
                    jogador.adicionarArcano(arcano);
                    view.exibir("Arcano concedido: " + cena.pegarArcano() + "!");
                }

                return 2;
            }

            cena.andar();

            if (!verificarCombate(view, ctrl, jogador, cena, dados))
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
// ─────────────────────────────────────────────────────────────────────────────
// Dialogos pos-boss — Ruffen guia o jogador para a proxima regiao
// ─────────────────────────────────────────────────────────────────────────────

static void dialogoPosBoss(IView &view, IController &ctrl, int cenaId)
{
    view.exibirLinha();
    switch (cenaId) {
    case 1:
        view.exibir("  RUFFEN: \"Bem feito! O poder de Talos e seu.");
        view.exibir("           Mas a Legiao nao recua. Va ate Mantuu.");
        view.exibir("           Vaelthor, arauto de Glaron, comanda as forcas draconicas la!\"");
        break;
    case 2:
        view.exibir("  RUFFEN: \"Os Elementos sao seus. Mas Xantares arde em caos.");
        view.exibir("           Malphas, arauto de Asmodeus, semeia destruicao pelos portos.");
        view.exibir("           Va -- antes que seja tarde!\"");
        break;
    case 3:
        view.exibir("  RUFFEN: \"O Caos foi dominado. As academias de Kenyrock precisam de voce.");
        view.exibir("           N'baki D'Itris, arauto de Azuth, usa os segredos arcanos como arma.");
        view.exibir("           Nao perca tempo!\"");
        break;
    case 4:
        view.exibir("  RUFFEN: \"A Mente e sua. Mas Skyprout pulsa com energia sombria.");
        view.exibir("           Livies, arauto de Lathander, medita entre as pedras.");
        view.exibir("           Ela esta preparando algo. Impeca-a!\"");
        break;
    case 5:
        view.exibir("  RUFFEN: \"Cinco arcanos. Sonath ja se move.");
        view.exibir("           Volte a Magisk. Nyriel, arauto de Eldath, guarda algo la.");
        view.exibir("           Chegou a hora.\"");
        break;
    default: break;
    }
    view.exibirLinha();
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");
}

static void confrontoRuffen(IView &view, IController &ctrl)
{
    view.exibirLinha();
    view.exibir("  [ Templo das Sombras -- apos a queda de Nyriel ]");
    view.exibir("");
    view.exibir("  Uma figura bloqueia o caminho para o santuario de Sonath. Ruffen.");
    view.exibir("");
    view.exibir("  RUFFEN: \"O principe foi convencido por mim.");
    view.exibir("           Eu precisava que alguem reunisse os arcanos.\"");
    view.exibir("  RUFFEN: \"Agora voce os tem. E eu precisarei deles.\"");
    view.exibir("");
    view.exibir("  [1] Enfrentar Ruffen");
    view.exibir("  [2] Deixa-lo passar e seguir em frente");
    view.exibirLinha();
    int op = ctrl.lerInteiro();
    if (op == 1) {
        view.exibir("  A batalha foi brutal. Ruffen recuou -- por ora.");
    } else {
        view.exibir("  Voce deixa Ruffen para tras. O santuario de Sonath aguarda.");
    }
    view.exibirLinha();
    aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");
}

// ─────────────────────────────────────────────────────────────────────────────
// Ponto de entrada da demo
// ─────────────────────────────────────────────────────────────────────────────

void executarExploracao(IView &view, IController &ctrl)
{
    int cenaInicial = 1;
    Jogador jogador = criarPersonagem(view, ctrl, cenaInicial);
    Dados dados;

    int idCenaAtual = cenaInicial;

    while (idCenaAtual <= 7)
    {
        InfoCena dadosCena = BancoCena::obterCena(idCenaAtual);
        Cena cena(dadosCena, jogador);

        int estado = loopExploracaoCena(view, ctrl, jogador, cena, dados);

        if (estado == 0)
            return;

        if (estado == 2) {
            if (idCenaAtual >= 1 && idCenaAtual <= 5)
                dialogoPosBoss(view, ctrl, idCenaAtual);
            else if (idCenaAtual == 6)
                confrontoRuffen(view, ctrl);
            idCenaAtual++;
        }
    }

    exibirRelatorio(view, jogador);
    view.exibir("Pressione Enter para sair...");
    ctrl.lerTexto();
}
