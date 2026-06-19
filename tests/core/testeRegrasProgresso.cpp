#include "../doctest.h"

#include "core/rules/RegrasProgresso.hpp"
#include <stdexcept>

// ── verificarUpNivel ──────────────────────────────────────────────────────────

TEST_CASE("verificarUpNivel - retorna true no limiar exato de cada nivel") {
    CHECK(RegrasProgresso::verificarUpNivel(300.0,   1) == true);
    CHECK(RegrasProgresso::verificarUpNivel(900.0,   2) == true);
    CHECK(RegrasProgresso::verificarUpNivel(2700.0,  3) == true);
    CHECK(RegrasProgresso::verificarUpNivel(6500.0,  4) == true);
    CHECK(RegrasProgresso::verificarUpNivel(14000.0, 5) == true);
    CHECK(RegrasProgresso::verificarUpNivel(23000.0, 6) == true);
    CHECK(RegrasProgresso::verificarUpNivel(34000.0, 7) == true);
    CHECK(RegrasProgresso::verificarUpNivel(48000.0, 8) == true);
    CHECK(RegrasProgresso::verificarUpNivel(64000.0, 9) == true);
}

TEST_CASE("verificarUpNivel - retorna true acima do limiar") {
    CHECK(RegrasProgresso::verificarUpNivel(301.0,   1) == true);
    CHECK(RegrasProgresso::verificarUpNivel(64001.0, 9) == true);
}

TEST_CASE("verificarUpNivel - retorna false abaixo do limiar") {
    CHECK(RegrasProgresso::verificarUpNivel(299.0,   1) == false);
    CHECK(RegrasProgresso::verificarUpNivel(0.0,     1) == false);
    CHECK(RegrasProgresso::verificarUpNivel(63999.0, 9) == false);
}

TEST_CASE("verificarUpNivel - nivel maximo nunca sobe independente do XP") {
    CHECK(RegrasProgresso::verificarUpNivel(0.0,      10) == false);
    CHECK(RegrasProgresso::verificarUpNivel(999999.0, 10) == false);
}

TEST_CASE("verificarUpNivel - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasProgresso::verificarUpNivel(1000.0, 0),  std::out_of_range);
    CHECK_THROWS_AS(RegrasProgresso::verificarUpNivel(1000.0, 11), std::out_of_range);
}

// ── getXPParaProximoNivel ────────────────────────────────────────────────────

TEST_CASE("getXPParaProximoNivel - valores corretos para todos os niveis") {
    CHECK(RegrasProgresso::getXPParaProximoNivel(1)  == doctest::Approx(300.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(2)  == doctest::Approx(900.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(3)  == doctest::Approx(2700.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(4)  == doctest::Approx(6500.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(5)  == doctest::Approx(14000.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(6)  == doctest::Approx(23000.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(7)  == doctest::Approx(34000.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(8)  == doctest::Approx(48000.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(9)  == doctest::Approx(64000.0));
    CHECK(RegrasProgresso::getXPParaProximoNivel(10) == doctest::Approx(0.0));
}

TEST_CASE("getXPParaProximoNivel - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasProgresso::getXPParaProximoNivel(0),  std::out_of_range);
    CHECK_THROWS_AS(RegrasProgresso::getXPParaProximoNivel(11), std::out_of_range);
}

// ── getBonusProficiencia ──────────────────────────────────────────────────────

TEST_CASE("getBonusProficiencia - bonus correto por faixa de nivel") {
    CHECK(RegrasProgresso::getBonusProficiencia(1)  == 2);
    CHECK(RegrasProgresso::getBonusProficiencia(2)  == 2);
    CHECK(RegrasProgresso::getBonusProficiencia(3)  == 2);
    CHECK(RegrasProgresso::getBonusProficiencia(4)  == 3);
    CHECK(RegrasProgresso::getBonusProficiencia(5)  == 3);
    CHECK(RegrasProgresso::getBonusProficiencia(6)  == 3);
    CHECK(RegrasProgresso::getBonusProficiencia(7)  == 4);
    CHECK(RegrasProgresso::getBonusProficiencia(8)  == 4);
    CHECK(RegrasProgresso::getBonusProficiencia(9)  == 4);
    CHECK(RegrasProgresso::getBonusProficiencia(10) == 5);
}

TEST_CASE("getBonusProficiencia - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(RegrasProgresso::getBonusProficiencia(0),  std::out_of_range);
    CHECK_THROWS_AS(RegrasProgresso::getBonusProficiencia(11), std::out_of_range);
}

// ── getNivelMaximo ────────────────────────────────────────────────────────────

TEST_CASE("getNivelMaximo retorna 10") {
    CHECK(RegrasProgresso::getNivelMaximo() == 10);
}
