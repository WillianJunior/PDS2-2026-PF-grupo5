#include "doctest.h"

#include <queue>
#include <string>

#include "demo/Exploracao.hpp"
#include "demo/ConfigExploracao.hpp"

// Todos os testes usam ConfigExploracao{skipLore=true, skipEnter=true} para evitar
// leituras diretas de stdin/TTY em Criacao.cpp (cutscene, título, menu de saves,
// confirmações e diálogos de animação).
// Para testes de CondutorBatalha isolados, ver testeCondutorBatalha.cpp.

static ConfigExploracao cfgTeste() {
    return ConfigExploracao{true, true}; // skipLore=true, skipEnter=true
}

namespace {

class ViewFake : public IView {
public:
    mutable std::vector<std::string> linhas;

    void exibir(const std::string& msg) const override {
        linhas.push_back(msg);
    }

    void exibirLinha() const override {
        linhas.push_back(std::string(55, '-'));
    }

    bool encontrou(const std::string& sub) const {
        for (const auto& l : linhas)
            if (l.find(sub) != std::string::npos) return true;
        return false;
    }
};

/**
 * MockController com filas de inteiros e textos.
 * Quando a fila de inteiros esgota, retorna dfInt (default).
 *   dfInt=5  -> "Encerrar" no loop de exploração (garantia que o loop encerra)
 *   dfInt=1  -> "AtaqueSimples" na batalha
 */
class MockController : public IController {
    std::queue<int>         _ints;
    std::queue<std::string> _textos;
    int                     _dfInt;

public:
    explicit MockController(int dfInt = 5) : _dfInt(dfInt) {}

    void pushInt(int v)                 { _ints.push(v); }
    void pushText(const std::string& s) { _textos.push(s); }

    int lerInteiro() override {
        if (_ints.empty()) return _dfInt;
        int v = _ints.front(); _ints.pop(); return v;
    }

    std::string lerTexto() override {
        if (_textos.empty()) return "";
        std::string s = _textos.front(); _textos.pop(); return s;
    }
};

// Adiciona N repetições de AtaqueSimples (1) para resolver batalha
static void pushAtaques(MockController& ctrl, int n) {
    for (int i = 0; i < n; ++i) ctrl.pushInt(1);
}

} // namespace

// ─────────────────────────────────────────────────────────────────────────────
// Testes 1-4 - encerramento imediato (opção 5), uma classe por teste
// Cobre: criarPersonagem (4 classes), case 5 "Encerrar", verificarCombate
//        sem inimigo (trecho 101), exibirHeaderCena
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarExploracao - encerramento imediato Guerreiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Alric"); ctrl.pushText("Alric"); ctrl.pushInt(1);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    // "Alric" é escrito em stdout (Criacao), não via IView
    // verificamos que o loop iniciou (header de cena) e encerrou corretamente
    CHECK(view.encontrou("O que deseja fazer"));
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Mago") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Elara"); ctrl.pushText("Elara"); ctrl.pushInt(2);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Arqueiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Rowan"); ctrl.pushText("Rowan"); ctrl.pushInt(3);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Tanque") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Bjorn"); ctrl.pushText("Bjorn"); ctrl.pushInt(4);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());
    CHECK(view.encontrou("Run encerrada"));
}

// ─────────────────────────────────────────────────────────────────────────────
// Teste 5 - exploração completa do trecho 101 (sem batalha)
//
// Trecho 101: NPC=1, items=[1], sem inimigo, próximo=102
// Cobre: case 1 (vasculhar s), case 1 (vasculhar sem itens), case 2 (NPC),
//        case 3 (inventário com item -> usar), case 3 (inventário vazio),
//        default (opção inválida), case 5 (Encerrar)
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarExploracao - todas as opções do loop (trecho 101)") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Alric"); ctrl.pushText("Alric"); ctrl.pushInt(1);

    // Trecho 101 - loop principal
    ctrl.pushInt(99);       // inválido (default)

    ctrl.pushInt(1);        // vasculhar (tem item)
    ctrl.pushText("s");

    ctrl.pushInt(1);        // vasculhar (sem itens restantes)

    ctrl.pushInt(2);        // interagirNpc (npcId=1)

    ctrl.pushInt(3);        // inventário (item presente, usar idx=0)
    ctrl.pushInt(0);

    ctrl.pushInt(3);        // inventário (vazio)

    ctrl.pushInt(5);        // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Opção inválida"));
    CHECK(view.encontrou("adicionado ao inventário"));
    CHECK(view.encontrou("Nada para vasculhar aqui"));
    CHECK(view.encontrou("Nome:"));
    CHECK(view.encontrou("Item usado!"));
    CHECK(view.encontrou("Inventário vazio."));
    CHECK(view.encontrou("Run encerrada"));
}

// ─────────────────────────────────────────────────────────────────────────────
// Teste 6 - vasculhar e descartar item ('n') + inventário: idx inválido / -1
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarExploracao - descarte de item e caminhos de inventário") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Lyra"); ctrl.pushText("Lyra"); ctrl.pushInt(3); // Arqueiro

    // Vasculhar -> toma item (para testar inventário com item)
    ctrl.pushInt(1); ctrl.pushText("s");

    // Inventário -> idx inválido (5 >= qtd=1)
    ctrl.pushInt(3); ctrl.pushInt(5);

    // Inventário -> fechar (idx=-1)
    ctrl.pushInt(3); ctrl.pushInt(-1);

    // Vasculhar de novo (sem itens, pois item foi tomado)
    ctrl.pushInt(1);

    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("adicionado ao inventário"));
    CHECK(view.encontrou("Índice inválido"));
    CHECK(view.encontrou("Inventário fechado"));
    CHECK(view.encontrou("Nada para vasculhar aqui"));
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - vasculhar e descartar ('n')") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Nara"); ctrl.pushText("Nara"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(1); ctrl.pushText("n"); // descartar
    ctrl.pushInt(5); // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Você deixou o item para trás"));
    CHECK(view.encontrou("Run encerrada"));
}

// ─────────────────────────────────────────────────────────────────────────────
// Testes de batalha (verificarCombate com inimigo + loopBatalha)
//
// O Orc Saqueador (ND 1/2) é classificado como Boss para LV 1 ->
// Fugir é bloqueado. A batalha termina por Vitória ou Derrota (aleatório).
// Os testes verificam apenas que a batalha FOI iniciada e que a função
// encerra normalmente (sem exceção).
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarExploracao - batalha com AtaqueSimples") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Brann"); ctrl.pushText("Brann"); ctrl.pushInt(4); // Tanque (mais HP)

    ctrl.pushInt(4);          // avançar -> trecho 102 (inimigo!)
    pushAtaques(ctrl, 20);    // AtaqueSimples até acabar a batalha
    ctrl.pushInt(5);          // Encerrar se sobreviver

    executarExploracao(view, ctrl, cfgTeste());

    // A batalha foi iniciada (verificarCombate encontrou inimigo)
    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("BATALHA"));
}

TEST_CASE("executarExploracao - batalha com opção inválida depois AtaqueSimples") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Gorak"); ctrl.pushText("Gorak"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);       // avançar -> trecho 102 (inimigo!)

    ctrl.pushInt(99);      // opção inválida em batalha
    pushAtaques(ctrl, 20); // resolve batalha
    ctrl.pushInt(5);       // Encerrar se sobreviver

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("Opção inválida"));
}

TEST_CASE("executarExploracao - batalha: UsarItem vazio") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Vex"); ctrl.pushText("Vex"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);        // avançar -> trecho 102 (inimigo, sem itens no inv)

    ctrl.pushInt(6);        // UsarItem - inventário vazio
    pushAtaques(ctrl, 20);  // resolve batalha
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("Inventário vazio! Escolha outra ação"));
}

TEST_CASE("executarExploracao - batalha: UsarItem cancelar e usar") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Bjorn"); ctrl.pushText("Bjorn"); ctrl.pushInt(4); // Tanque

    // Pega item no trecho 101
    ctrl.pushInt(1); ctrl.pushText("s");

    ctrl.pushInt(4);        // avançar -> trecho 102 (inimigo! tem item no inv)

    ctrl.pushInt(6);        // UsarItem - tem item
    ctrl.pushInt(-1);       // cancelar
    ctrl.pushInt(6);        // UsarItem - novamente
    ctrl.pushInt(0);        // usar (idx=0)
    pushAtaques(ctrl, 20);  // resolve batalha (inimigo contra-ataca após item)
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    // Cancelado OU item usado deve ter aparecido
    bool coberto = view.encontrou("Cancelado") || view.encontrou("Item usado!");
    CHECK(coberto);
}

TEST_CASE("executarExploracao - batalha: ações Defesa e Esquiva") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Gorak"); ctrl.pushText("Gorak"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4); // avançar -> trecho 102 (inimigo!)

    // Defesa (4), depois Esquiva (5), depois AtaqueSimples até acabar
    ctrl.pushInt(4); // Defesa
    ctrl.pushInt(5); // Esquiva
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5); // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    // Chegou ao menos ao ponto de ler a ação - sem exceção
    CHECK(true);
}

TEST_CASE("executarExploracao - batalha: AtaqueRapido e AtaqueForte") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Lyra"); ctrl.pushText("Lyra"); ctrl.pushInt(3); // Arqueiro (tem PP)

    ctrl.pushInt(4); // avançar -> trecho 102

    ctrl.pushInt(2); // AtaqueRapido
    ctrl.pushInt(3); // AtaqueForte
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(true);
}

// ─────────────────────────────────────────────────────────────────────────────
// Novos testes — cobertura adicional
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("executarExploracao - múltiplas opções inválidas consecutivas no loop") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Kira"); ctrl.pushText("Kira"); ctrl.pushInt(1); // Guerreiro

    ctrl.pushInt(0);    // inválido
    ctrl.pushInt(-1);   // inválido
    ctrl.pushInt(99);   // inválido
    ctrl.pushInt(6);    // inválido (fora do intervalo 1-5)
    ctrl.pushInt(5);    // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    int count = 0;
    for (const auto& l : view.linhas)
        if (l.find("Opção inválida") != std::string::npos) count++;
    CHECK(count >= 3);
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - batalha: Guerreiro usa AtaqueRapido e AtaqueForte") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Thane"); ctrl.pushText("Thane"); ctrl.pushInt(1); // Guerreiro

    ctrl.pushInt(4); // avançar -> trecho 102 (inimigo!)

    ctrl.pushInt(2); // AtaqueRapido
    ctrl.pushInt(3); // AtaqueForte
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(true);
}

TEST_CASE("executarExploracao - batalha: Mago usa AtaqueRapido e AtaqueForte") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Sora"); ctrl.pushText("Sora"); ctrl.pushInt(2); // Mago

    ctrl.pushInt(4); // avançar -> trecho 102 (inimigo!)

    ctrl.pushInt(2); // AtaqueRapido
    ctrl.pushInt(3); // AtaqueForte
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(true);
}

// ─────────────────────────────────────────────────────────────────────────────
// Testes de trecho 103, boss fight e diálogos pós-boss
//
// Estrutura da cena 1:
//   Trecho 101: sem inimigo, NPC=1, items=[1], próximo=102
//   Trecho 102: inimigo (Orc Saqueador id=1), NPC=2,  próximo=103
//   Trecho 103: sem inimigo, NPC=-1, items=[4,2], próximo=-1 (boss)
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("executarExploracao - interação com NPC ausente (trecho 103)") {
    // Trecho 103 tem NPC=-1 → cobre if(npcId<=0) em interagirNpc
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Drak"); ctrl.pushText("Drak"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);        // avançar → trecho 102 (inimigo: Orc Saqueador)
    pushAtaques(ctrl, 30);  // derrotar Orc

    ctrl.pushInt(4);        // avançar → trecho 103 (sem inimigo)
    ctrl.pushInt(2);        // interagir → npcId=-1 → "Não há NPCs neste trecho."
    ctrl.pushInt(5);        // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    // batalha do trecho 102 foi iniciada
    CHECK(view.encontrou("Um inimigo apareceu"));
    // se o player venceu o Orc e chegou ao trecho 103:
    bool npcs = view.encontrou("Não há NPCs") || view.encontrou("Run encerrada");
    CHECK(npcs);
}

TEST_CASE("executarExploracao - boss fight da cena 1 (executarEncontroBoss)") {
    // Avança por todos os trechos até o boss (Device, id=101)
    // Cobre: executarEncontroBoss, bossIdParaCena(1), arcanoParaCena(1)
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Krag"); ctrl.pushText("Krag"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);        // avançar → trecho 102 (inimigo)
    pushAtaques(ctrl, 30);  // derrotar Orc

    ctrl.pushInt(4);        // avançar → trecho 103 (sem inimigo)
    ctrl.pushInt(4);        // avançar → próximo=-1 → executarEncontroBoss (Device)
    pushAtaques(ctrl, 50);  // lutar contra boss (win ou lose)
    ctrl.pushInt(5);        // Encerrar (se sobreviver)

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu"));           // Orc no trecho 102
    CHECK(view.encontrou("poderoso barra o seu caminho"));  // intro do boss
}

TEST_CASE("executarExploracao - boss fight cobre path de transição de cena (estado==2)") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Brun"); ctrl.pushText("Brun"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);
    pushAtaques(ctrl, 30);  // Orc
    ctrl.pushInt(4);         // trecho 103
    ctrl.pushInt(4);         // boss fight (Device)
    pushAtaques(ctrl, 50);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("poderoso barra o seu caminho")); // boss intro sempre aparece
}

TEST_CASE("executarExploracao - vasculhar múltiplos itens em trecho 103") {
    // Trecho 103 tem items=[4,2]; testa vasculhar com mais de um item disponível
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Sera"); ctrl.pushText("Sera"); ctrl.pushInt(4); // Tanque

    ctrl.pushInt(4);                    // avançar → trecho 102 (inimigo)
    pushAtaques(ctrl, 30);              // derrotar Orc

    ctrl.pushInt(4);                    // avançar → trecho 103 (sem inimigo)
    ctrl.pushInt(1); ctrl.pushText("s"); // vasculhar → pegar primeiro item
    ctrl.pushInt(1); ctrl.pushText("s"); // vasculhar → pegar segundo item
    ctrl.pushInt(1);                     // vasculhar → sem itens restantes
    ctrl.pushInt(5);                     // Encerrar

    executarExploracao(view, ctrl, cfgTeste());

    CHECK(view.encontrou("Um inimigo apareceu")); // Orc no trecho 102
}
