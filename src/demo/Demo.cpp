#include <string>

#include "demo/Demo.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "database/BancoNpcInteracao.hpp"
#include "database/BancoItem.hpp"

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

// Exibe o menu de ações e processa a escolha do jogador num trecho
// Retorna quando o jogador escolher "Avançar"
static void loopAcoesTrecho(IView& view, IController& ctrl, Jogador& jogador, Cena& cena) {
    while (true) {
        view.exibirLinha();
        view.exibir("[Localização] " + cena.pegarTrechoAtual().pegarDescricao());
        view.exibir("\nO que deseja fazer?");

        bool temItens = cena.pegarTrechoAtual().possuiItensRestantes();
        bool temNpc   = cena.pegarTrechoAtual().pegarNPCInteracao() > 0;

        view.exibir("  [1] Vasculhar o local" + std::string(temItens ? "" : " (nada a vasculhar)"));
        view.exibir("  [2] Interagir com NPCs" + std::string(temNpc  ? "" : " (nenhum NPC aqui)"));
        view.exibir("  [3] Abrir inventário");
        view.exibir("  [4] Avançar para o próximo trecho");

        int opcao = ctrl.lerInteiro();

        switch (opcao) {
        case 1:
            if (temItens) {
                int itemId = cena.pegarTrechoAtual().sortearItem();
                Item preview = BancoItem::obterItem(cena.pegarId(), itemId);
                view.exibir("\nVocê encontrou: " + preview.pegarNome() +
                            " — " + preview.pegarDescricao());
                view.exibir("Deseja pegar o item? [s/n]  (se não, o item será perdido)");
                std::string resp = ctrl.lerTexto();
                if (!resp.empty() && (resp[0] == 's' || resp[0] == 'S')) {
                    cena.vasculhar();
                    view.exibir("-> " + preview.pegarNome() + " adicionado ao inventário!");
                } else {
                    cena.descartarItem();
                    view.exibir("Você deixou o item para trás. Ele foi perdido.");
                }
            } else {
                view.exibir("Não há nada para vasculhar aqui.");
            }
            break;

        case 2:
            if (temNpc) {
                int npcId = cena.pegarTrechoAtual().pegarNPCInteracao();
                InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(npcId);
                view.exibir("\n" + npc.nome + ": \"" + npc.fala + "\"");
            } else {
                view.exibir("Não há NPCs para interagir aqui.");
            }
            break;

        case 3:
            interagirInventario(view, ctrl, jogador);
            break;

        case 4:
            cena.andar();
            return;

        default:
            view.exibir("Opção inválida. Escolha entre 1 e 4.");
            break;
        }
    }
}

// Exibe o relatório de validação ao final da demo
static void exibirRelatorio(IView& view, Jogador& jogador, const Cena& cena) {
    view.exibirLinha();
    view.exibir("=== Relatório de Validação ===");
    view.exibir("Cena atual  : " + std::to_string(cena.pegarId()) +
                " | Trecho: " + std::to_string(cena.pegarTrechoAtual().pegarId()));
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

void executarDemo(IView& view, IController& ctrl) {
    // ── Apresentação ──────────────────────────────────────────────────────────
    view.exibirLinha();
    view.exibir("  THE DARK AGE — THE ARCANUM QUEST  [Demo de Validação]");
    view.exibirLinha();

    // ── Criar jogador com dados pré-setados ───────────────────────────────────
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
    view.exibir("Bem-vindo, " + jogador.getNome() + "!\n");

    // ── Carregar Cena 1 ───────────────────────────────────────────────────────
    InfoCena infoCena = BancoCena::obterCena(1);
    Cena cena(infoCena, jogador);
    cena.iniciarCena(); // carrega trecho 101

    // ── Trecho 101 — NPC + Item ───────────────────────────────────────────────
    view.exibirLinha();
    view.exibir("[Localização] " + cena.pegarTrechoAtual().pegarDescricao());

    loopAcoesTrecho(view, ctrl, jogador, cena); // move para trecho 102 ao escolher [4]

    // ── Trecho 102 — Batalha mockada ──────────────────────────────────────────
    view.exibirLinha();
    view.exibir("[Localização] " + cena.pegarTrechoAtual().pegarDescricao());

    if (cena.pegarTrechoAtual().possuiInimigo()) {
        view.exibir("\nUm inimigo bloqueia o caminho!");
        aguardarEnter(view, ctrl, "[Pressione Enter para batalhar...]");

        // Lore mockado
        view.exibir("\n*** A batalha foi iniciada. O jogador se esforçou muito");
        view.exibir("    e ganhou! Uhul! ***");

        aguardarEnter(view, ctrl, "\n[Pressione Enter para continuar...]");

        cena.iniciarBatalha();
        jogador.ganharXp(10.0);
        view.exibir("Você ganhou 10 XP!");
    }

    // ── Relatório final ───────────────────────────────────────────────────────
    exibirRelatorio(view, jogador, cena);
    aguardarEnter(view, ctrl, "[Pressione Enter para encerrar...]");
}
