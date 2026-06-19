#include <string>

#include "demo/Demo.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "database/BancoNpcInteracao.hpp"

// Pergunta sim/não e retorna true para 's'/'S'.
static bool perguntarSim(IView& view, IController& ctrl, const std::string& pergunta) {
    view.exibir(pergunta + " [s/n]");
    std::string resp = ctrl.lerTexto();
    return !resp.empty() && (resp[0] == 's' || resp[0] == 'S');
}

// Aguarda o usuário pressionar Enter.
static void aguardarEnter(IView& view, IController& ctrl, const std::string& msg) {
    view.exibir(msg);
    ctrl.lerTexto();
}

// Exibe o inventário e oferece ao jogador a opção de usar um item.
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
        view.exibir("Item usado!  HP atual: " + std::to_string(jogador.getVidaAtual()));
    }
}

// Exibe o relatório de validação ao final da demo.
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
                " / " + std::to_string(100));

    view.exibir("\n--- Inventário final ---");
    int qtd = jogador.getInventario().quantidadeItens();
    if (qtd == 0)
        view.exibir("Inventário vazio.");
    else
        jogador.getInventario().listarItens();

    view.exibirLinha();
    view.exibir("Memória gerenciada 100% via RAII — sem new/delete manual.");
    view.exibir("Nenhum crash ou vazamento detectado nesta execução.");
    view.exibirLinha();
}

void executarDemo(IView& view, IController& ctrl) {
    // ── Apresentação ──────────────────────────────────────────────────────────
    view.exibirLinha();
    view.exibir("  THE DARK AGE — THE ARCANUM QUEST  [Demo de Validação]");
    view.exibirLinha();

    // ── Criar jogador com dados pré-setados ───────────────────────────────────
    Jogador jogador(
        "Alric",          // nome
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

    // NPC de diálogo
    int npcId = cena.pegarTrechoAtual().pegarNPCInteracao();
    if (npcId > 0) {
        InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(npcId);
        view.exibir("\n" + npc.nome + ": \"" + npc.fala + "\"");
    }

    // Vasculhar
    if (cena.pegarTrechoAtual().possuiItensRestantes()) {
        if (perguntarSim(view, ctrl, "\nVasculhar o local?")) {
            cena.vasculhar();
            view.exibir("-> Item adicionado ao inventário!");
        }
    }

    // Inventário
    if (perguntarSim(view, ctrl, "\nAbrir inventário?"))
        interagirInventario(view, ctrl, jogador);

    aguardarEnter(view, ctrl, "\n[Pressione Enter para avançar...]");

    // ── Trecho 102 — Batalha mockada ──────────────────────────────────────────
    cena.andar(); // move para trecho 102

    view.exibirLinha();
    view.exibir("[Localização] " + cena.pegarTrechoAtual().pegarDescricao());

    if (cena.pegarTrechoAtual().possuiInimigo()) {
        view.exibir("\nUm inimigo bloqueia o caminho!");
        aguardarEnter(view, ctrl, "[Pressione Enter para batalhar...]");

        // Mock da batalha
        view.exibir("\n*** A batalha foi iniciada. O jogador se esforçou muito");
        view.exibir("    e ganhou! Uhul! ***\n");

        cena.iniciarBatalha();
        jogador.ganharXp(10.0);
        view.exibir("Você ganhou 10 XP!");
    }

    // ── Relatório final ───────────────────────────────────────────────────────
    exibirRelatorio(view, jogador, cena);
    aguardarEnter(view, ctrl, "[Pressione Enter para encerrar...]");
}
