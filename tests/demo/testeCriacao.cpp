#include "doctest.h"

#include <queue>
#include <string>

#include "demo/Criacao.hpp"

namespace {

class ViewFake : public IView {
public:
    mutable std::string saida;

    void exibir(const std::string& msg) const override {
        saida += msg + "\n";
    }

    void exibirLinha() const override {
        saida += std::string(55, '-') + "\n";
    }
};

class MockController : public IController {
    std::queue<int>         _ints;
    std::queue<std::string> _textos;

public:
    void pushInt(int v)              { _ints.push(v); }
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

// ─── Testes de classe ────────────────────────────────────────────────────────

TEST_CASE("criarPersonagem - Guerreiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Ello");
    ctrl.pushInt(1);

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Ello");
    CHECK(j.getClasse().getTipo() == TipoClasse::Guerreiro);
}

TEST_CASE("criarPersonagem - Mago") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Kovu");
    ctrl.pushInt(2);

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Kovu");
    CHECK(j.getClasse().getTipo() == TipoClasse::Mago);
}

TEST_CASE("criarPersonagem - Arqueiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Zara");
    ctrl.pushInt(3);

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Zara");
    CHECK(j.getClasse().getTipo() == TipoClasse::Arqueiro);
}

TEST_CASE("criarPersonagem - Tanque") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Kidra");
    ctrl.pushInt(4);

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Kidra");
    CHECK(j.getClasse().getTipo() == TipoClasse::Tanque);
}

// ─── Escolhas inválidas antes da válida ─────────────────────────────────────

TEST_CASE("criarPersonagem - classe inválida depois válida") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Damaya");
    ctrl.pushInt(0);   // inválido
    ctrl.pushInt(99);  // inválido
    ctrl.pushInt(2);   // Mago — válido

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Damaya");
    CHECK(view.saida.find("invalida") != std::string::npos);
}

// ─── Verificação de UI ───────────────────────────────────────────────────────

TEST_CASE("criarPersonagem - exibe tabela de classes") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Liff");
    ctrl.pushInt(3);

    criarPersonagem(view, ctrl);

    CHECK(view.saida.find("Classe") != std::string::npos);
    CHECK(view.saida.find("Guerreiro") != std::string::npos);
}
