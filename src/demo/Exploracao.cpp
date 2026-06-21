#include <string>

#include "demo/Exploracao.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "database/BancoNpcInteracao.hpp"
#include "database/BancoItem.hpp"

static void verificarCombate(
    IView& view,
    const Cena& cena
)
{
    if(!cena.pegarTrechoAtual().possuiInimigo())
    {
        return;
    }

    view.exibirLinha();
    view.exibir("Um inimigo apareceu!");
    view.exibir("Batalha em desenvolvimento.");
    view.exibirLinha();
}

static void avancarCena(
    IView& view,
    int& idCenaAtual
)
{
    view.exibirLinha();

    view.exibir(
        "Chefe da cena encontrado!"
    );

    view.exibir(
        "Batalha do chefe em desenvolvimento."
    );

    view.exibir(
        "Chefe derrotado!"
    );

    view.exibirLinha();

    idCenaAtual++;
}

static bool processarAndar(
    IView& view,
    Cena& cena
)
{
    int proximo =
        cena.pegarTrechoAtual()
            .pegarProximoTrecho();

    if(proximo == -1)
    {
        return false;
    }

    cena.andar();

    verificarCombate(
        view,
        cena
    );
    view.exibir("DEBUG: indo para trecho " + std::to_string(proximo));
    return true;
}

static void interagirNpc(
    IView& view,
    const Cena& cena
)
{
    int npcId =
        cena.pegarTrechoAtual()
        .pegarNPCInteracao();

    if(npcId <= 0)
    {
        view.exibir(
            "Nao ha NPCs neste trecho."
        );

        return;
    }

    InfoNPCInteracao npc =
        BancoNPCInteracao::obterNPC(npcId);

    view.exibirLinha();

    view.exibir(
        "Nome: " + npc.nome
    );

    view.exibir(
        "Descricao: "
        + npc.descricaoFisica
    );

    view.exibir(
        npc.fala
    );

    view.exibirLinha();
}

//---------------------------------------------------------------------------------------------------------------------


// Aguarda o usuário pressionar Enter
static void aguardarEnter(IView& view, IController& ctrl, const std::string& msg) {
    view.exibir(msg);
    ctrl.lerTexto();
}

// Exibe o inventário e oferece ao jogador a opção de usar um item
static void interagirInventario(IView& view, IController& ctrl, Jogador& jogador) {
    view.exibir("\n--- Inventário ---");
    int qtd = jogador.getInventario().quantidadeItens();
    if (qtd == 0) {
        view.exibir("O inventário está vazio.");
        return;
    }
    jogador.getInventario().listarItens();
    view.exibir("Usar item? [índice / -1 para pular]");
    int idx = ctrl.lerInteiro();
    if (idx >= 0 && idx < qtd) {
        jogador.usarItem(idx);
        view.exibir("Item usado!  HP atual: " + std::to_string(static_cast<int>(jogador.getVidaAtual())));
    } else if (idx != -1) {
        view.exibir("Índice inválido. Nenhum item foi usado.");
    }
}

// Exibe o relatório de validação ao final da demo
static void exibirRelatorio(IView& view, Jogador& jogador) {
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

static bool loopExploracaoCena(
    IView& view,
    IController& ctrl,
    Jogador& jogador,
    Cena& cena
)
{
    cena.iniciarCena();

    view.exibirLinha();
    view.exibir("=== NOVA CENA ===");
    view.exibir("[Entrada] " + cena.pegarDescricao());
    view.exibirLinha();

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
        bool temNpc   = cena.pegarTrechoAtual().pegarNPCInteracao() > 0;

        view.exibir("O que deseja fazer?");
        view.exibir("  [1] Vasculhar o local");
        view.exibir("  [2] Interagir com NPCs");
        view.exibir("  [3] Abrir inventário");
        view.exibir("  [4] Avançar");

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
        {
            int npcId = cena.pegarTrechoAtual().pegarNPCInteracao();

            if (npcId <= 0)
            {
                view.exibir("Não há NPCs aqui.");
            }
            else
            {
                InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(npcId);

                view.exibir("Nome: " + npc.nome);
                view.exibir("Descrição: " + npc.descricaoFisica);
                view.exibir(npc.fala);
            }
            break;
        }

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
        {
            if (!processarAndar(view, cena))
            {
                return false; // acabou a cena
            }

            view.exibirLinha();
            view.exibir("[Novo trecho] " + cena.pegarTrechoAtual().pegarDescricao());
            break;
        }

        default:
            view.exibir("Opção inválida.");
            break;
        }
    }
}

void executarExploracao(IView& view, IController& ctrl)
{
    Jogador jogador(
        "Alric",
        "Um guerreiro experiente das Florestas de Edhen.",
        "Pelo Arcano, lutarei, uai!",
        12.0,   // ataque
        8.0,    // defesa
        100.0,  // vidaTotal
        40.0,   // ppTotal
        10.0,   // agilidade
        TipoClasse::Guerreiro,
        TipoPersonagem::Jogador
    );

    view.exibir("Bem-vindo, " + jogador.getNome());

    int idCenaAtual = 1;

    while (idCenaAtual <= 7)
    {
        InfoCena dados = BancoCena::obterCena(idCenaAtual);
        Cena cena(dados, jogador);

        bool continua = loopExploracaoCena(view, ctrl, jogador, cena);

        if (!continua)
        {
            avancarCena(view, idCenaAtual);
        }
    }

    exibirRelatorio(view, jogador);
    aguardarEnter(view, ctrl, "Pressione Enter para sair...");
}


