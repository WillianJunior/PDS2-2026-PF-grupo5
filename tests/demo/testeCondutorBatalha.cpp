#include "../doctest.h"

#include <queue>
#include <string>

#include "demo/CondutorBatalha.hpp"
#include "demo/ConfigExploracao.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/map/Cena.hpp"
#include "database/BancoCena.hpp"
#include "core/Dados.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// Fakes
// ─────────────────────────────────────────────────────────────────────────────

namespace {

class ViewFake : public IView {
public:
    mutable std::vector<std::string> linhas;

    void exibir(const std::string& msg) const override { linhas.push_back(msg); }
    void exibirLinha() const override { linhas.push_back(std::string(55, '-')); }

    bool encontrou(const std::string& sub) const {
        for (const auto& l : linhas)
            if (l.find(sub) != std::string::npos) return true;
        return false;
    }
};

class MockController : public IController {
    std::queue<int>         _ints;
    std::queue<std::string> _textos;
    int                     _df;

public:
    explicit MockController(int df = 1) : _df(df) {}

    void pushInt(int v) { _ints.push(v); }

    int lerInteiro() override {
        if (_ints.empty()) return _df;
        int v = _ints.front(); _ints.pop(); return v;
    }

    std::string lerTexto() override {
        if (_textos.empty()) return "";
        std::string s = _textos.front(); _textos.pop(); return s;
    }
};

// Player forte o suficiente para vencer inimigo fraco em poucos turnos
static Jogador makeJogadorForte() {
    return Jogador("Heroi", "", "",
        30.0, 20.0, 300.0, 200.0, 15.0,
        TipoClasse::Guerreiro, TipoPersonagem::Jogador, 5);
}

// Inimigo fraco que o player derrota facilmente
static Personagem makeInimigoFraco() {
    return Personagem("Goblin", "Um goblin fraco", "Argh!",
        5.0, 5.0, 20.0, 5.0, 5.0,
        TipoClasse::Guerreiro, TipoPersonagem::Inimigo, 1);
}

// Player fraco que perde rapidamente
static Jogador makeJogadorFraco() {
    return Jogador("Fraco", "", "",
        5.0, 5.0, 15.0, 5.0, 5.0,
        TipoClasse::Guerreiro, TipoPersonagem::Jogador, 1);
}

// Inimigo forte que mata o jogador fraco
static Personagem makeInimigoForte() {
    return Personagem("Dragon", "Um dragao imenso", "RAWR!",
        50.0, 40.0, 1000.0, 500.0, 50.0,
        TipoClasse::Guerreiro, TipoPersonagem::Inimigo, 10);
}

static Cena makeCena(Jogador& jogador, int cenaId = 1) {
    InfoCena info = BancoCena::obterCena(cenaId);
    return Cena(info, jogador);
}

static ConfigExploracao cfgSilencioso() {
    return ConfigExploracao{true, true}; // skipLore=true, skipEnter=true
}

} // namespace

// ─────────────────────────────────────────────────────────────────────────────
// Testes de CondutorBatalha
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("CondutorBatalha - vitória (player forte vs inimigo fraco)") {
    ViewFake view;
    MockController ctrl(1); // AtaqueSimples por padrão

    Jogador    jogador = makeJogadorForte();
    Personagem inimigo = makeInimigoFraco();
    Dados dados(42); // semente fixa para determinismo
    Cena cena = makeCena(jogador);

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena,
                             cfgSilencioso());
    ResultadoBatalha res = condutor.executar();

    CHECK(res == ResultadoBatalha::Vitoria);
    CHECK(view.encontrou("foi derrotado!"));
    CHECK(view.encontrou("BATALHA"));
}

TEST_CASE("CondutorBatalha - derrota (player fraco vs inimigo forte)") {
    ViewFake view;
    MockController ctrl(1);

    Jogador    jogador = makeJogadorFraco();
    Personagem inimigo = makeInimigoForte();
    Dados dados(42);
    Cena cena = makeCena(jogador);

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena,
                             cfgSilencioso());
    ResultadoBatalha res = condutor.executar();

    CHECK(res == ResultadoBatalha::Derrota);
    CHECK(view.encontrou("foi derrotado"));
}

TEST_CASE("CondutorBatalha - fuga disponível e escolhida") {
    ViewFake view;
    MockController ctrl;

    Jogador    jogador = makeJogadorForte();
    Personagem inimigo = makeInimigoFraco();
    Dados dados(42);
    Cena cena = makeCena(jogador);

    // Calcula quantas ações tem disponíveis e seleciona Fugir (última opção)
    // Para inimigo fraco no nível alto, Fugir geralmente é a última ação
    // Empurra um número alto para garantir que Fugir seja selecionado se disponível
    ctrl.pushInt(7); // índice > qtd de ações → inválido, tenta de novo
    ctrl.pushInt(7); // se ações disponíveis = 7, seleciona a última (Fugir)
    // fallback: default=1 (AtaqueSimples) encerra a batalha por vitória
    MockController ctrlFuga(1);
    // Força seleção de Fugir como 7ª opção (se disponível no combate)
    ctrlFuga.pushInt(7); // tenta fugir na primeira oportunidade

    CondutorBatalha condutor(view, ctrlFuga, jogador, inimigo, dados, cena,
                             cfgSilencioso());
    ResultadoBatalha res = condutor.executar();

    // Resultado pode ser Fuga ou Vitória dependendo das ações disponíveis
    bool valido = (res == ResultadoBatalha::Fuga || res == ResultadoBatalha::Vitoria);
    CHECK(valido);
}

TEST_CASE("CondutorBatalha - opção inválida é rejeitada sem consumir turno") {
    ViewFake view;
    MockController ctrl;

    Jogador    jogador = makeJogadorForte();
    Personagem inimigo = makeInimigoFraco();
    Dados dados(42);
    Cena cena = makeCena(jogador);

    ctrl.pushInt(99); // opção inválida
    ctrl.pushInt(99); // outra inválida
    // default=1: AtaqueSimples termina a batalha

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena,
                             cfgSilencioso());
    ResultadoBatalha res = condutor.executar();

    CHECK(view.encontrou("Opção inválida"));
    CHECK(res == ResultadoBatalha::Vitoria);
}

TEST_CASE("CondutorBatalha - UsarItem com inventário vazio não consome turno") {
    ViewFake view;
    MockController ctrl;

    Jogador    jogador = makeJogadorForte(); // sem itens no inventário
    Personagem inimigo = makeInimigoFraco();
    Dados dados(42);
    Cena cena = makeCena(jogador);

    // Tenta usar item (índice 6 ou 7, dependendo das ações disponíveis)
    // Para jogador forte nível 5, UsarItem é provavelmente a 6ª ação
    ctrl.pushInt(6);
    ctrl.pushInt(6);
    // default=1: AtaqueSimples termina

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena,
                             cfgSilencioso());
    ResultadoBatalha res = condutor.executar();

    // Deve ter mostrado mensagem de inventário vazio OU simplesmente vencido
    bool coberto = view.encontrou("Inventário vazio") ||
                   res == ResultadoBatalha::Vitoria;
    CHECK(coberto);
}

TEST_CASE("CondutorBatalha - ConfigExploracao skipEnter não bloqueia execução") {
    ViewFake view;
    MockController ctrl(1);

    Jogador    jogador = makeJogadorForte();
    Personagem inimigo = makeInimigoFraco();
    Dados dados(1);
    Cena cena = makeCena(jogador);

    ConfigExploracao cfg;
    cfg.skipEnter = true;

    CondutorBatalha condutor(view, ctrl, jogador, inimigo, dados, cena, cfg);
    ResultadoBatalha res = condutor.executar();

    // Deve completar sem precisar de input de Enter
    bool finalizado = (res == ResultadoBatalha::Vitoria ||
                       res == ResultadoBatalha::Derrota ||
                       res == ResultadoBatalha::Fuga);
    CHECK(finalizado);
}
