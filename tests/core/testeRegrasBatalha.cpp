#include "../doctest.h"

#include "core/rules/RegrasBatalha.hpp"

// getXPporND

TEST_CASE("getXPporND - NDs validos") {
    CHECK(RegrasBatalha::getXPporND(0.125) == doctest::Approx(25.0));
    CHECK(RegrasBatalha::getXPporND(0.25)  == doctest::Approx(50.0));
    CHECK(RegrasBatalha::getXPporND(0.5)   == doctest::Approx(100.0));
    CHECK(RegrasBatalha::getXPporND(1.0)   == doctest::Approx(200.0));
    CHECK(RegrasBatalha::getXPporND(5.0)   == doctest::Approx(1800.0));
    CHECK(RegrasBatalha::getXPporND(10.0)  == doctest::Approx(5900.0));
}

TEST_CASE("getXPporND - ND invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasBatalha::getXPporND(0.0),  std::invalid_argument);
    CHECK_THROWS_AS(RegrasBatalha::getXPporND(11.0), std::invalid_argument);
}

// getLimiar

TEST_CASE("getLimiar - valores corretos") {
    CHECK(RegrasBatalha::getLimiar(1,  0) == doctest::Approx(25.0));   // LV1 Facil
    CHECK(RegrasBatalha::getLimiar(1,  1) == doctest::Approx(50.0));   // LV1 Medio
    CHECK(RegrasBatalha::getLimiar(1,  2) == doctest::Approx(75.0));   // LV1 Dificil
    CHECK(RegrasBatalha::getLimiar(1,  3) == doctest::Approx(100.0));  // LV1 Boss
    CHECK(RegrasBatalha::getLimiar(10, 3) == doctest::Approx(2800.0)); // LV10 Boss
}

TEST_CASE("getLimiar - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasBatalha::getLimiar(0,  0), std::out_of_range);
    CHECK_THROWS_AS(RegrasBatalha::getLimiar(11, 0), std::out_of_range);
}

TEST_CASE("getLimiar - indice invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasBatalha::getLimiar(1, -1), std::out_of_range);
    CHECK_THROWS_AS(RegrasBatalha::getLimiar(1,  4), std::out_of_range);
}

// ClassificarConfronto
// LV1: Facil=25, Medio=50, Dificil=75, Boss=100
// LV4: Facil=125, Medio=250, Dificil=375, Boss=500
// LV5: Facil=250

TEST_CASE("ClassificarConfronto - Trivial") {
    // LV5: limFacil=250. ND 0.125 = 25 XP < 250 → Trivial
    auto d = RegrasBatalha::ClassificarConfronto(5, 0.125);
    CHECK(d == RegrasBatalha::Dificuldade::Trivial);
}

TEST_CASE("ClassificarConfronto - Facil") {
    // LV1: limFacil=25. ND 0.125 = 25 XP >= 25, < 50 → Facil
    auto d = RegrasBatalha::ClassificarConfronto(1, 0.125);
    CHECK(d == RegrasBatalha::Dificuldade::Facil);
}

TEST_CASE("ClassificarConfronto - Medio") {
    // LV1: limMedio=50. ND 0.25 = 50 XP >= 50, < 75 → Medio
    auto d = RegrasBatalha::ClassificarConfronto(1, 0.25);
    CHECK(d == RegrasBatalha::Dificuldade::Medio);
}

TEST_CASE("ClassificarConfronto - Dificil") {
    // LV4: limDificil=375, limBoss=500. ND 2.0 = 450 XP >= 375, < 500 → Dificil
    auto d = RegrasBatalha::ClassificarConfronto(4, 2.0);
    CHECK(d == RegrasBatalha::Dificuldade::Dificil);
}

TEST_CASE("ClassificarConfronto - Boss") {
    // LV1: limBoss=100. ND 0.5 = 100 XP >= 100, < 200 (2*limBoss) → Boss
    auto d = RegrasBatalha::ClassificarConfronto(1, 0.5);
    CHECK(d == RegrasBatalha::Dificuldade::Boss);
}

TEST_CASE("ClassificarConfronto - Impossivel") {
    // LV1: 2*limBoss=200. ND 1.0 = 200 XP >= 200 → Impossivel
    auto d = RegrasBatalha::ClassificarConfronto(1, 1.0);
    CHECK(d == RegrasBatalha::Dificuldade::Impossivel);
}

// DificuldadeParaString

TEST_CASE("DificuldadeParaString - todos os valores") {
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Trivial)    == "Trivial");
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Facil)      == "Fácil");
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Medio)      == "Médio");
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Dificil)    == "Difícil");
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Boss)       == "Boss");
    CHECK(RegrasBatalha::DificuldadeParaString(RegrasBatalha::Dificuldade::Impossivel) == "Impossível");
}

// CalcularXPGanho

TEST_CASE("CalcularXPGanho - nao trivial retorna xp base") {
    // LV1, ND 0.125: xpBase=25, limFacil=25. 25 >= 25 → retorna 25.0
    double xp = RegrasBatalha::CalcularXPGanho(0.125, 1);
    CHECK(xp == doctest::Approx(25.0));
}

TEST_CASE("CalcularXPGanho - trivial aplica reducao proporcional") {
    // LV5, ND 0.125: xpBase=25, limFacil=250. 25 < 250 → xpReduzido = 25*(25/250) = 2.5
    double xp = RegrasBatalha::CalcularXPGanho(0.125, 5);
    CHECK(xp == doctest::Approx(25.0 * 25.0 / 250.0));
}

// FugirDisponivel

TEST_CASE("FugirDisponivel - disponivel em confronto nao-boss") {
    CHECK(RegrasBatalha::FugirDisponivel(5, 0.125) == true);  // Trivial
    CHECK(RegrasBatalha::FugirDisponivel(1, 0.125) == true);  // Facil
}

TEST_CASE("FugirDisponivel - bloqueado em Boss") {
    // LV1, ND 0.5 → Boss
    CHECK(RegrasBatalha::FugirDisponivel(1, 0.5) == false);
}

TEST_CASE("FugirDisponivel - bloqueado em Impossivel") {
    // LV1, ND 1.0 → Impossivel
    CHECK(RegrasBatalha::FugirDisponivel(1, 1.0) == false);
}

// ProcessarDefesa

TEST_CASE("ProcessarDefesa - defesa supera ataque bloqueia totalmente") {
    CHECK(RegrasBatalha::ProcessarDefesa(18.0, 15.0) == doctest::Approx(0.0));
    CHECK(RegrasBatalha::ProcessarDefesa(10.0,  5.0) == doctest::Approx(0.0));
}

TEST_CASE("ProcessarDefesa - ratio 0.8 ou mais reduz para 75 porcento") {
    // ratio = 12/15 = 0.8 → 0.75
    CHECK(RegrasBatalha::ProcessarDefesa(12.0, 15.0) == doctest::Approx(0.75));
    // ratio = 13/15 ≈ 0.867 → 0.75
    CHECK(RegrasBatalha::ProcessarDefesa(13.0, 15.0) == doctest::Approx(0.75));
}

TEST_CASE("ProcessarDefesa - ratio abaixo de 0.8 causa dano total") {
    CHECK(RegrasBatalha::ProcessarDefesa(8.0, 15.0) == doctest::Approx(1.0));
    CHECK(RegrasBatalha::ProcessarDefesa(5.0, 10.0) == doctest::Approx(1.0));
}

TEST_CASE("ProcessarDefesa - inimigo sem ataque causa zero dano") {
    CHECK(RegrasBatalha::ProcessarDefesa(0.0, 0.0) == doctest::Approx(0.0));
    CHECK(RegrasBatalha::ProcessarDefesa(5.0, 0.0) == doctest::Approx(0.0));
}

// ProcessarEsquiva

TEST_CASE("ProcessarEsquiva - agilidade supera ataque esquiva total") {
    CHECK(RegrasBatalha::ProcessarEsquiva(15.0, 12.0) == doctest::Approx(0.0));
}

TEST_CASE("ProcessarEsquiva - agilidade menor que ataque sem esquiva") {
    CHECK(RegrasBatalha::ProcessarEsquiva(10.0, 12.0) == doctest::Approx(1.0));
}

TEST_CASE("ProcessarEsquiva - empate resulta em 50 porcento de dano") {
    CHECK(RegrasBatalha::ProcessarEsquiva(12.0, 12.0) == doctest::Approx(0.5));
}
