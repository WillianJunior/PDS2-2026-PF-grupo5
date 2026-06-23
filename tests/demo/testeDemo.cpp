// TODO: avaliar se é necessário manter a demo (e o teste)
#include "doctest.h"

#include <queue>
#include <string>

#include "demo/Demo.hpp"

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

class MockController : public IController {
    std::queue<int>         _ints;
    std::queue<std::string> _textos;

public:
    void pushInt(int v)                 { _ints.push(v); }
    void pushText(const std::string& s) { _textos.push(s); }

    int lerInteiro() override {
        if (_ints.empty()) return -1;
        int v = _ints.front(); _ints.pop(); return v;
    }

    std::string lerTexto() override {
        if (_textos.empty()) return "";
        std::string s = _textos.front(); _textos.pop(); return s;
    }
};

} // namespace

// ─────────────────────────────────────────────────────────────────────────────
// Teste 1 — caminho mínimo: avança direto no primeiro turno
// Cobre: aguardarEnter × 3, loopAcoesTrecho → opção 4, exibirRelatorio vazio
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarDemo - caminho mínimo (avança imediatamente)") {
    ViewFake view;
    MockController ctrl;

    // loopAcoesTrecho: avança
    ctrl.pushInt(4);
    // aguardarEnter × 3 (antes batalha, depois batalha, encerrar)
    ctrl.pushText("");
    ctrl.pushText("");
    ctrl.pushText("");

    executarDemo(view, ctrl);

    CHECK(view.encontrou("THE DARK AGE"));
    CHECK(view.encontrou("Alric"));
    CHECK(view.encontrou("Relatório de Validação"));
    CHECK(view.encontrou("Inventário vazio."));
}

// ─────────────────────────────────────────────────────────────────────────────
// Teste 2 — cobertura completa de loopAcoesTrecho e interagirInventario
//
// Sequência em trecho 101 (NPC=1, items=[1]):
//   99 → inválido (default)
//    1 → vasculhar + "s" (toma item; inventário passa a ter 1 item)
//    3 → inventário: idx=5 (inválido, 5 >= qtd=1)
//    3 → inventário: idx=-1 (fechar sem usar)
//    3 → inventário: idx=0  (usa item; inventário fica vazio)
//    1 → vasculhar (sem itens)
//    2 → NPC (temNpc=true, id=1)
//    3 → inventário vazio
//    4 → avançar → trecho 102 (encerra loopAcoesTrecho)
//
// Depois: batalha mockada + relatório + encerrar
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarDemo - cobertura completa de loopAcoesTrecho") {
    ViewFake view;
    MockController ctrl;

    // loopAcoesTrecho (trecho 101)
    ctrl.pushInt(99); // inválido
    ctrl.pushInt(1);  // vasculhar (tem item)
    ctrl.pushText("s"); // pegar item
    ctrl.pushInt(3);  // inventário — idx inválido
    ctrl.pushInt(5);
    ctrl.pushInt(3);  // inventário — fechar (idx=-1)
    ctrl.pushInt(-1);
    ctrl.pushInt(3);  // inventário — usar (idx=0)
    ctrl.pushInt(0);
    ctrl.pushInt(1);  // vasculhar (sem itens)
    ctrl.pushInt(2);  // NPC
    ctrl.pushInt(3);  // inventário vazio
    ctrl.pushInt(4);  // avançar → sai do loop

    // aguardarEnter × 3
    ctrl.pushText("");
    ctrl.pushText("");
    ctrl.pushText("");

    executarDemo(view, ctrl);

    CHECK(view.encontrou("Opção inválida"));
    CHECK(view.encontrou("adicionado ao inventário"));
    CHECK(view.encontrou("Índice inválido"));
    CHECK(view.encontrou("Item usado!"));
    CHECK(view.encontrou("Não há nada para vasculhar"));
    CHECK(view.encontrou("Um inimigo bloqueia o caminho"));
    CHECK(view.encontrou("Relatório de Validação"));
    CHECK(view.encontrou("Inventário vazio."));
}

// ─────────────────────────────────────────────────────────────────────────────
// Teste 3 — descarta item + relatório com inventário não vazio
//
// Pega item, NÃO usa, avança → relatório chama listarItens()
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarDemo - relatório com inventário não vazio") {
    ViewFake view;
    MockController ctrl;

    // Vasculhar e pegar item
    ctrl.pushInt(1);
    ctrl.pushText("s");
    // Avançar
    ctrl.pushInt(4);
    // aguardarEnter × 3
    ctrl.pushText("");
    ctrl.pushText("");
    ctrl.pushText("");

    executarDemo(view, ctrl);

    CHECK(view.encontrou("adicionado ao inventário"));
    CHECK(view.encontrou("Relatório de Validação"));
    // inventário não-vazio → listarItens (não exibe "Inventário vazio.")
    CHECK_FALSE(view.encontrou("Inventário vazio."));
}

// ─────────────────────────────────────────────────────────────────────────────
// Teste 4 — vasculhar e descartar ("n")
// ─────────────────────────────────────────────────────────────────────────────
TEST_CASE("executarDemo - vasculhar e descartar item") {
    ViewFake view;
    MockController ctrl;

    ctrl.pushInt(1);    // vasculhar (tem item)
    ctrl.pushText("n"); // não pegar
    ctrl.pushInt(4);    // avançar
    ctrl.pushText("");
    ctrl.pushText("");
    ctrl.pushText("");

    executarDemo(view, ctrl);

    CHECK(view.encontrou("deixou o item para trás"));
    // inventário permanece vazio
    CHECK(view.encontrou("Inventário vazio."));
}
