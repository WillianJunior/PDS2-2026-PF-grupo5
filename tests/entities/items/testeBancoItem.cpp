#include "../../doctest.h"

#include <stdexcept>

#include "entities/items/Item.hpp"
#include "database/BancoItem.hpp"

TEST_CASE("BancoItem retorna comida pelo id") {
    Item item = BancoItem::obterItem(1, 1);

    CHECK(item.pegarTipo() == Comida);
    CHECK(item.pegarValor() > 0);
    CHECK(item.pegarDuracao() == 0);
    CHECK(item.getCenaId() == 1);
}

TEST_CASE("BancoItem retorna pocao pelo id") {
    Item item = BancoItem::obterItem(1, 3);

    CHECK(item.pegarTipo() == Pocao);
    CHECK(item.pegarEfeito() == "Ataque");
    CHECK(item.pegarValor() == 4);
    CHECK(item.pegarDuracao() == 3);
    CHECK(item.getCenaId() == 1);
}

TEST_CASE("BancoItem retorna cristal pelo id") {
    Item item = BancoItem::obterItem(1, 4);

    CHECK(item.pegarTipo() == Cristal);
    CHECK(item.pegarEfeito() == "Berserk");
    CHECK(item.pegarValor() == 3);
    CHECK(item.getCenaId() == 1);
}

TEST_CASE("BancoItem retorna item de cena 2") {
    Item item = BancoItem::obterItem(2, 12);

    CHECK(item.pegarTipo() == Pocao);
    CHECK(item.pegarEfeito() == "Defesa");
    CHECK(item.getCenaId() == 2);
}

TEST_CASE("BancoItem lanca excecao para id invalido") {
    CHECK_THROWS_AS(BancoItem::obterItem(1, 99), std::invalid_argument);
}
