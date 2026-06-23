#include <string>

#include "demo/Exploracao.hpp"
#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "database/BancoNpcInteracao.hpp"
#include "database/BancoItem.hpp"

static void exibirHeaderCena(IView& view, const Cena& cena)
{
    exibirAsciiArtArquivo(
        view,
        "data/arcanos/" + std::to_string(cena.pegarId()) + ".txt"
    );

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

static void exibirRelatorio(IView& view, Jogador& jogador)
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

static void verificarCombate(IView& view, const Cena& cena)
{
    if (!cena.pegarTrechoAtual().possuiInimigo())
        return;

    view.exibirLinha();
    view.exibir("Um inimigo apareceu!");
    view.exibir("Batalha em desenvolvimento.");
    view.exibirLinha();
}

static void avancarCena(IView& view, int& idCenaAtual)
{
    view.exibirLinha();
    view.exibir("Chefe da cena encontrado!");
    view.exibir("Batalha do chefe em desenvolvimento.");
    view.exibir("Chefe derrotado!");
    view.exibirLinha();

    idCenaAtual++;
}

static bool processarAndar(IView& view, Cena& cena)
{
    if (cena.pegarTrechoAtual().pegarProximoTrecho() == -1)
        return false;

    cena.andar();
    verificarCombate(view, cena);
    return true;
}

static void interagirNpc(IView& view, const Cena& cena)
{
    int npcId = cena.pegarTrechoAtual().pegarNPCInteracao();

    if (npcId <= 0)
    {
        view.exibir("Nao ha NPCs neste trecho.");
        return;
    }

    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(npcId);

    view.exibirLinha();
    view.exibir("Nome: " + npc.nome);
    view.exibir("Descricao: " + npc.descricaoFisica);
    view.exibir("Fala: " + npc.fala);
    view.exibirLinha();
}

static int loopExploracaoCena(
    IView& view,
    IController& ctrl,
    Jogador& jogador,
    Cena& cena
)
{
    cena.iniciarCena();
    exibirHeaderCena(view, cena);

    if (cena.pegarTrechoAtual().possuiInimigo())
    {
        view.exibir("Um inimigo apareceu!");
        view.exibir("Batalha em desenvolvimento.");
    }

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
            break;
        }

        case 2:
            interagirNpc(view, cena);
            break;

        case 3:
        {
            auto& inv = jogador.getInventario();
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
            }
            break;
        }

        case 4:
            if (!processarAndar(view, cena))
                return 2;
            break;

        case 5:
            view.exibir("Run encerrada");
            return 0;

        default:
            view.exibir("Opção inválida.");
            break;
        }
    }
}

void executarExploracao(IView& view, IController& ctrl)
{
    Jogador jogador = criarPersonagem(view, ctrl);

    view.exibir("Bem-vindo, " + jogador.getNome());
    view.exibir("Iniciando jornada... \n");

    int idCenaAtual = 1;

    while (idCenaAtual <= 7)
    {
        InfoCena dados = BancoCena::obterCena(idCenaAtual);
        Cena cena(dados, jogador);

        int estado = loopExploracaoCena(view, ctrl, jogador, cena);

        if (estado == 0)
            return;

        if (estado == 2)
            avancarCena(view, idCenaAtual);
    }

    exibirRelatorio(view, jogador);
    view.exibir("Pressione Enter para sair...");
    ctrl.lerTexto();
}
