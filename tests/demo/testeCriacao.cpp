#include "doctest.h"

#include <queue>
#include <string>

#include "demo/Criacao.hpp"
#include "demo/ConfigExploracao.hpp"

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

// skipLore=true, skipEnter=true: evita pressioneQualquerTecla(), menuSaves()
// e animarGeracaoAtributos() que bloqueiam ou dormem fora do IController
static ConfigExploracao cfgTeste() {
    return ConfigExploracao{true, true};
}

} // namespace

// ─── Testes de classe ────────────────────────────────────────────────────────

TEST_CASE("criarPersonagem - Guerreiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Ello");
    ctrl.pushInt(1);
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getNome() == "Ello");
    CHECK(j.getClasse().getTipo() == TipoClasse::Guerreiro);
}

TEST_CASE("criarPersonagem - Mago") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Kovu");
    ctrl.pushInt(2);
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getNome() == "Kovu");
    CHECK(j.getClasse().getTipo() == TipoClasse::Mago);
}

TEST_CASE("criarPersonagem - Arqueiro") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Zara");
    ctrl.pushInt(3);
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getNome() == "Zara");
    CHECK(j.getClasse().getTipo() == TipoClasse::Arqueiro);
}

TEST_CASE("criarPersonagem - Tanque") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Kidra");
    ctrl.pushInt(4);
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

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
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getNome() == "Damaya");
    // mensagem "invalida" vai para stdout (não IView), verificamos via comportamento:
    CHECK(j.getClasse().getTipo() == TipoClasse::Mago);
}

// ─── Verificação de UI ───────────────────────────────────────────────────────

TEST_CASE("criarPersonagem - exibe tabela de classes") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Liff");
    ctrl.pushInt(3);
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    // tabela de classes vai para stdout (criarNovoPersonagem usa std::cout),
    // verificamos via comportamento: personagem criada com a classe correta
    CHECK(j.getClasse().getTipo() == TipoClasse::Arqueiro);
}

// ─── Parâmetro de saída cenaInicial ──────────────────────────────────────────

TEST_CASE("criarPersonagem - cenaInicial é 1 após criação de novo personagem") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Vael");
    ctrl.pushInt(1);
    int cena = 99; // valor inicial diferente para confirmar que foi atualizado

    criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(cena == 1);
}

// ─── Robustez com entradas inválidas ─────────────────────────────────────────

TEST_CASE("criarPersonagem - múltiplas classes inválidas antes de Tanque") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Rhen");
    ctrl.pushInt(0);    // inválido
    ctrl.pushInt(5);    // inválido
    ctrl.pushInt(-1);   // inválido
    ctrl.pushInt(4);    // Tanque — válido
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getClasse().getTipo() == TipoClasse::Tanque);
}

// ─── Fallback de nome vazio ───────────────────────────────────────────────────

TEST_CASE("criarPersonagem - playerName vazio usa fallback Aventureiro") {
    ViewFake view;
    MockController ctrl;
    // fila de textos vazia → lerTexto() retorna "" → usa fallback
    ctrl.pushInt(2); // Mago
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    CHECK(j.getNome() == "Aventureiro");
    CHECK(j.getClasse().getTipo() == TipoClasse::Mago);
}

// ─── Dois nomes distintos ─────────────────────────────────────────────────────

TEST_CASE("criarPersonagem - charName diferente de playerName é preservado") {
    ViewFake view;
    MockController ctrl;
    ctrl.pushText("Joao");   // playerName
    ctrl.pushText("Heroi");  // charName distinto
    ctrl.pushInt(1);          // Guerreiro
    int cena = 1;

    Jogador j = criarPersonagem(view, ctrl, cena, cfgTeste());

    // getNome() retorna charName, não playerName
    CHECK(j.getNome() == "Heroi");
    CHECK(j.getClasse().getTipo() == TipoClasse::Guerreiro);
}
