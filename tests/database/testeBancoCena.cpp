#include "tests/doctest.h"

#include "include/database/BancoCena.hpp"

#include <stdexcept>

TEST_CASE("BancoCena retorna Cena 1")
{
    CHECK(BancoCena::obterCena(1).id == 1);
}

TEST_CASE("BancoCena retorna Cena 2")
{
    CHECK(BancoCena::obterCena(2).id == 2);
}

TEST_CASE("BancoCena retorna Cena 3")
{
    CHECK(BancoCena::obterCena(3).id == 3);
}

TEST_CASE("BancoCena retorna Cena 4")
{
    CHECK(BancoCena::obterCena(4).id == 4);
}

TEST_CASE("BancoCena retorna Cena 5")
{
    CHECK(BancoCena::obterCena(5).id == 5);
}

TEST_CASE("BancoCena retorna Cena 6")
{
    CHECK(BancoCena::obterCena(6).id == 6);
}

TEST_CASE("BancoCena retorna Cena 7")
{
    CHECK(BancoCena::obterCena(7).id == 7);
}

TEST_CASE("BancoCena rejeita id negativo")
{
    CHECK_THROWS_AS(
        BancoCena::obterCena(-1),
        std::invalid_argument
    );
}

TEST_CASE("BancoCena rejeita id inexistente")
{
    CHECK_THROWS_AS(
        BancoCena::obterCena(999),
        std::invalid_argument
    );
}