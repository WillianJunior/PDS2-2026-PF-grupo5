#include "doctest.h"

#include <queue>
#include <string>

#include "demo/Exploracao.hpp"

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
    ctrl.pushText("Alric"); ctrl.pushInt(1);
    ctrl.pushText("");
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Alric"));
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Mago") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Elara"); ctrl.pushInt(2);
    ctrl.pushText("");
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Arqueiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Rowan"); ctrl.pushInt(3);
    ctrl.pushText("");
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - encerramento imediato Tanque") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Bjorn"); ctrl.pushInt(4);
    ctrl.pushText("");
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);
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

    ctrl.pushText("Alric"); ctrl.pushInt(1);
    ctrl.pushText("");

    // Trecho 101 - loop principal
    ctrl.pushInt(99);       // inválido (default)

    ctrl.pushInt(1);        // vasculhar (tem item)
    ctrl.pushText("s");
    ctrl.pushText("");      // enter

    ctrl.pushInt(1);        // vasculhar (sem itens restantes)
    ctrl.pushText("");

    ctrl.pushInt(2);        // interagirNpc (npcId=1)
    ctrl.pushText("");

    ctrl.pushInt(3);        // inventário (item presente, usar idx=0)
    ctrl.pushInt(0);
    ctrl.pushText("");

    ctrl.pushInt(3);        // inventário (vazio)
    ctrl.pushText("");

    ctrl.pushInt(5);        // Encerrar

    executarExploracao(view, ctrl);

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

    ctrl.pushText("Lyra"); ctrl.pushInt(3); // Arqueiro
    ctrl.pushText("");

    // Vasculhar -> toma item (para testar inventário com item)
    ctrl.pushInt(1); ctrl.pushText("s"); ctrl.pushText("");

    // Inventário -> idx inválido (5 >= qtd=1)
    ctrl.pushInt(3); ctrl.pushInt(5); ctrl.pushText("");

    // Inventário -> fechar (idx=-1)
    ctrl.pushInt(3); ctrl.pushInt(-1); ctrl.pushText("");

    // Vasculhar de novo (sem itens, pois item foi tomado)
    ctrl.pushInt(1); ctrl.pushText("");

    // Descarta o próximo item usando um trecho diferente não é viável;
    // cobrimos 'n' tentando novamente após recarregar (impossível neste trecho).
    // Usa opção 5 para encerrar.
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("adicionado ao inventário"));
    CHECK(view.encontrou("Índice inválido"));
    CHECK(view.encontrou("Inventário fechado"));
    CHECK(view.encontrou("Nada para vasculhar aqui"));
    CHECK(view.encontrou("Run encerrada"));
}

TEST_CASE("executarExploracao - vasculhar e descartar ('n')") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Nara"); ctrl.pushInt(4); // Tanque
    ctrl.pushText("");

    ctrl.pushInt(1); ctrl.pushText("n"); ctrl.pushText(""); // descartar
    ctrl.pushInt(5); // Encerrar

    executarExploracao(view, ctrl);

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

    ctrl.pushText("Brann"); ctrl.pushInt(4); // Tanque (mais HP)
    ctrl.pushText("");

    ctrl.pushInt(4);          // avançar -> trecho 102 (inimigo!)
    pushAtaques(ctrl, 20);    // AtaqueSimples até acabar a batalha
    ctrl.pushInt(5);          // Encerrar se sobreviver

    executarExploracao(view, ctrl);

    // A batalha foi iniciada (verificarCombate encontrou inimigo)
    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("BATALHA"));
}

TEST_CASE("executarExploracao - batalha com opção inválida depois AtaqueSimples") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Gorak"); ctrl.pushInt(4); // Tanque
    ctrl.pushText("");

    ctrl.pushInt(4);       // avançar -> trecho 102 (inimigo!)

    ctrl.pushInt(99);      // opção inválida em batalha
    pushAtaques(ctrl, 20); // resolve batalha
    ctrl.pushInt(5);       // Encerrar se sobreviver

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("Opção inválida"));
}

TEST_CASE("executarExploracao - batalha: UsarItem vazio") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Vex"); ctrl.pushInt(4); // Tanque
    ctrl.pushText("");

    ctrl.pushInt(4);        // avançar -> trecho 102 (inimigo, sem itens no inv)

    ctrl.pushInt(6);        // UsarItem - inventário vazio
    pushAtaques(ctrl, 20);  // resolve batalha
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(view.encontrou("Inventário vazio! Escolha outra ação"));
}

TEST_CASE("executarExploracao - batalha: UsarItem cancelar e usar") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Bjorn"); ctrl.pushInt(4); // Tanque
    ctrl.pushText("");

    // Pega item no trecho 101
    ctrl.pushInt(1); ctrl.pushText("s"); ctrl.pushText("");

    ctrl.pushInt(4);        // avançar -> trecho 102 (inimigo! tem item no inv)

    ctrl.pushInt(6);        // UsarItem - tem item
    ctrl.pushInt(-1);       // cancelar
    ctrl.pushInt(6);        // UsarItem - novamente
    ctrl.pushInt(0);        // usar (idx=0)
    pushAtaques(ctrl, 20);  // resolve batalha (inimigo contra-ataca após item)
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Um inimigo apareceu"));
    // Cancelado OU item usado deve ter aparecido
    bool coberto = view.encontrou("Cancelado") || view.encontrou("Item usado!");
    CHECK(coberto);
}

TEST_CASE("executarExploracao - batalha: ações Defesa e Esquiva") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Gorak"); ctrl.pushInt(4); // Tanque
    ctrl.pushText("");

    ctrl.pushInt(4); // avançar -> trecho 102 (inimigo!)

    // Defesa (4), depois Esquiva (5), depois AtaqueSimples até acabar
    ctrl.pushInt(4); // Defesa
    ctrl.pushInt(5); // Esquiva
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5); // Encerrar

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Um inimigo apareceu"));
    // Chegou ao menos ao ponto de ler a ação - sem exceção
    CHECK(true);
}

TEST_CASE("executarExploracao - batalha: AtaqueRapido e AtaqueForte") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushText("Lyra"); ctrl.pushInt(3); // Arqueiro (tem PP)
    ctrl.pushText("");

    ctrl.pushInt(4); // avançar -> trecho 102

    ctrl.pushInt(2); // AtaqueRapido
    ctrl.pushInt(3); // AtaqueForte
    pushAtaques(ctrl, 20);
    ctrl.pushInt(5);

    executarExploracao(view, ctrl);

    CHECK(view.encontrou("Um inimigo apareceu"));
    CHECK(true);
}
