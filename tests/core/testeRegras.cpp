#include "../doctest.h"

#include "core/rules/Regras.hpp"

TEST_CASE("calcularCoeficiente - formula 0.5x - 5") {
    CHECK(Regras::calcularCoeficiente(10.0) == doctest::Approx(0.0));
    CHECK(Regras::calcularCoeficiente(12.0) == doctest::Approx(1.0));
    CHECK(Regras::calcularCoeficiente(17.0) == doctest::Approx(3.5));
    CHECK(Regras::calcularCoeficiente(15.0) == doctest::Approx(2.5));
    CHECK(Regras::calcularCoeficiente(8.0)  == doctest::Approx(-1.0));
    CHECK(Regras::calcularCoeficiente(11.0) == doctest::Approx(0.5));
}

TEST_CASE("calcularCD - 10 mais coeficiente de agilidade") {
    CHECK(Regras::calcularCD(10.0) == doctest::Approx(10.0));
    CHECK(Regras::calcularCD(15.0) == doctest::Approx(12.5));
    CHECK(Regras::calcularCD(8.0)  == doctest::Approx(9.0));
}

TEST_CASE("calcularPPTotal - valorPoder vezes 5") {
    CHECK(Regras::calcularPPTotal(17.0) == doctest::Approx(85.0));
    CHECK(Regras::calcularPPTotal(11.0) == doctest::Approx(55.0));
    CHECK(Regras::calcularPPTotal(0.0)  == doctest::Approx(0.0));
}

TEST_CASE("bonusProficiencia - todos os niveis") {
    CHECK(Regras::bonusProficiencia(1)  == 2);
    CHECK(Regras::bonusProficiencia(2)  == 2);
    CHECK(Regras::bonusProficiencia(3)  == 2);
    CHECK(Regras::bonusProficiencia(4)  == 3);
    CHECK(Regras::bonusProficiencia(5)  == 3);
    CHECK(Regras::bonusProficiencia(6)  == 3);
    CHECK(Regras::bonusProficiencia(7)  == 4);
    CHECK(Regras::bonusProficiencia(8)  == 4);
    CHECK(Regras::bonusProficiencia(9)  == 4);
    CHECK(Regras::bonusProficiencia(10) == 5);
}

TEST_CASE("bonusProficiencia - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(Regras::bonusProficiencia(0),  std::out_of_range);
    CHECK_THROWS_AS(Regras::bonusProficiencia(11), std::out_of_range);
}

TEST_CASE("xpParaProximoNivel - valores corretos") {
    CHECK(Regras::xpParaProximoNivel(1)  == doctest::Approx(300.0));
    CHECK(Regras::xpParaProximoNivel(2)  == doctest::Approx(900.0));
    CHECK(Regras::xpParaProximoNivel(3)  == doctest::Approx(2700.0));
    CHECK(Regras::xpParaProximoNivel(5)  == doctest::Approx(14000.0));
    CHECK(Regras::xpParaProximoNivel(9)  == doctest::Approx(64000.0));
    CHECK(Regras::xpParaProximoNivel(10) == doctest::Approx(0.0));
}

TEST_CASE("xpParaProximoNivel - nivel invalido lanca excecao") {
    CHECK_THROWS_AS(Regras::xpParaProximoNivel(0),  std::out_of_range);
    CHECK_THROWS_AS(Regras::xpParaProximoNivel(11), std::out_of_range);
}
