#include "../doctest.h"

#include "core/rules/RegrasClassePersonagem.hpp"

// ── getDadoVida ────────────────────────────────────────────────────────────

TEST_CASE("getDadoVida - retorna o maximo do dado de vida por classe") {
    CHECK(RegrasClassePersonagem::getDadoVida(TipoClasse::Guerreiro) == 10);
    CHECK(RegrasClassePersonagem::getDadoVida(TipoClasse::Arqueiro)  == 8);
    CHECK(RegrasClassePersonagem::getDadoVida(TipoClasse::Mago)      == 6);
    CHECK(RegrasClassePersonagem::getDadoVida(TipoClasse::Tanque)    == 12);
}

// ── distribuirAtributos ────────────────────────────────────────────────────
// Exemplo canônico do §1.3 de regras.md: {17, 15, 12, 11}
// Retorno: {ataque, defesa, poder, agilidade}

TEST_CASE("distribuirAtributos - Guerreiro prioriza ATQ>DEF>AGI>POD") {
    std::vector<int> vals = {17, 15, 12, 11};
    auto a = RegrasClassePersonagem::distribuirAtributos(TipoClasse::Guerreiro, vals);
    CHECK(a[0] == doctest::Approx(17)); // ataque  = 1º
    CHECK(a[1] == doctest::Approx(15)); // defesa  = 2º
    CHECK(a[2] == doctest::Approx(11)); // poder   = 4º
    CHECK(a[3] == doctest::Approx(12)); // agilidade = 3º
}

TEST_CASE("distribuirAtributos - Arqueiro prioriza AGI>ATQ>POD>DEF") {
    std::vector<int> vals = {17, 15, 12, 11};
    auto a = RegrasClassePersonagem::distribuirAtributos(TipoClasse::Arqueiro, vals);
    CHECK(a[0] == doctest::Approx(15)); // ataque  = 2º
    CHECK(a[1] == doctest::Approx(11)); // defesa  = 4º
    CHECK(a[2] == doctest::Approx(12)); // poder   = 3º
    CHECK(a[3] == doctest::Approx(17)); // agilidade = 1º
}

TEST_CASE("distribuirAtributos - Tanque prioriza DEF>ATQ>POD>AGI") {
    std::vector<int> vals = {17, 15, 12, 11};
    auto a = RegrasClassePersonagem::distribuirAtributos(TipoClasse::Tanque, vals);
    CHECK(a[0] == doctest::Approx(15)); // ataque  = 2º
    CHECK(a[1] == doctest::Approx(17)); // defesa  = 1º
    CHECK(a[2] == doctest::Approx(12)); // poder   = 3º
    CHECK(a[3] == doctest::Approx(11)); // agilidade = 4º
}

TEST_CASE("distribuirAtributos - Mago prioriza POD>AGI>ATQ>DEF") {
    std::vector<int> vals = {17, 15, 12, 11};
    auto a = RegrasClassePersonagem::distribuirAtributos(TipoClasse::Mago, vals);
    CHECK(a[0] == doctest::Approx(12)); // ataque  = 3º
    CHECK(a[1] == doctest::Approx(11)); // defesa  = 4º
    CHECK(a[2] == doctest::Approx(17)); // poder   = 1º
    CHECK(a[3] == doctest::Approx(15)); // agilidade = 2º
}

TEST_CASE("distribuirAtributos - vetor com menos de 4 elementos lanca excecao") {
    std::vector<int> curto = {17, 15, 12};
    CHECK_THROWS_AS(
        RegrasClassePersonagem::distribuirAtributos(TipoClasse::Guerreiro, curto),
        std::invalid_argument
    );
}

// ── calcularVidaInicial ────────────────────────────────────────────────────
// HP = getDadoVida(classe) + calcularCoeficiente(defesa)
// calcularCoeficiente(x) = 0.5x - 5

TEST_CASE("calcularVidaInicial - Guerreiro com defesa 15") {
    // 10 + (0.5*15 - 5) = 10 + 2.5 = 12.5
    CHECK(RegrasClassePersonagem::calcularVidaInicial(TipoClasse::Guerreiro, 15.0)
          == doctest::Approx(12.5));
}

TEST_CASE("calcularVidaInicial - Mago com defesa 11") {
    // 6 + (0.5*11 - 5) = 6 + 0.5 = 6.5
    CHECK(RegrasClassePersonagem::calcularVidaInicial(TipoClasse::Mago, 11.0)
          == doctest::Approx(6.5));
}

TEST_CASE("calcularVidaInicial - Arqueiro com defesa 11") {
    // 8 + (0.5*11 - 5) = 8 + 0.5 = 8.5
    CHECK(RegrasClassePersonagem::calcularVidaInicial(TipoClasse::Arqueiro, 11.0)
          == doctest::Approx(8.5));
}

TEST_CASE("calcularVidaInicial - Tanque com defesa 17") {
    // 12 + (0.5*17 - 5) = 12 + 3.5 = 15.5
    CHECK(RegrasClassePersonagem::calcularVidaInicial(TipoClasse::Tanque, 17.0)
          == doctest::Approx(15.5));
}

// ── calcularVidaNovoNivel ──────────────────────────────────────────────────
// Com semente fixa os resultados são determinísticos

TEST_CASE("calcularVidaNovoNivel - resultado dentro do intervalo esperado") {
    Dados dados(42);
    // incremento = rolar(1, dado) + coef(defesa)
    // Para Guerreiro (1d10) com defesa=15: coef=2.5, mínimo=1+2.5=3.5, máximo=10+2.5=12.5
    double inc = RegrasClassePersonagem::calcularVidaNovoNivel(
        TipoClasse::Guerreiro, 15.0, dados);
    CHECK(inc >= 3.5);
    CHECK(inc <= 12.5);
}

TEST_CASE("calcularVidaNovoNivel - resultado deterministico com mesma semente") {
    Dados d1(99);
    Dados d2(99);
    double inc1 = RegrasClassePersonagem::calcularVidaNovoNivel(TipoClasse::Mago, 11.0, d1);
    double inc2 = RegrasClassePersonagem::calcularVidaNovoNivel(TipoClasse::Mago, 11.0, d2);
    CHECK(inc1 == doctest::Approx(inc2));
}
