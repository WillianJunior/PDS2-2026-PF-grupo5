#include "../../doctest.h"

#include <stdexcept>

#include "entities/items/Item.hpp"
#include "database/BancoItem.hpp"

TEST_CASE("BancoItem retorna comida pelo id") {
    Item item = BancoItem::obterItem(1, 1);

    CHECK(item.pegarTipo() == Comida);
    CHECK(item.pegarValor() > 0);
    CHECK(item.pegarDuracao() == 6);  // Fruta Fresca → 1d6, ladosDado=6
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

// ── Comida negativa ───────────────────────────────────────────────────────────

TEST_CASE("BancoItem retorna comida negativa pelo id") {
    Item item = BancoItem::obterItem(1, 2); // Fruta Podre

    CHECK(item.pegarTipo() == Comida);
    CHECK(item.pegarEfeito() == "Dano");
    CHECK(item.pegarValor() < 0);       // qtdDados negativo = dano
    CHECK(item.pegarDuracao() == 6);    // 1d6
    CHECK(item.getCenaId() == 1);
}

// ── Itens por cena ────────────────────────────────────────────────────────────

TEST_CASE("BancoItem retorna itens da cena 3") {
    Item comida  = BancoItem::obterItem(3, 20); // Cogumelo Medicinal
    Item pocao   = BancoItem::obterItem(3, 22); // Pocao de Velocidade
    Item cristal = BancoItem::obterItem(3, 23); // Cristal de Veneno

    CHECK(comida.pegarTipo()  == Comida);
    CHECK(comida.pegarDuracao() == 8);           // 2d8
    CHECK(comida.pegarValor()   == 2);

    CHECK(pocao.pegarTipo()   == Pocao);
    CHECK(pocao.pegarEfeito() == "Agilidade");
    CHECK(pocao.pegarValor()  == 4);
    CHECK(pocao.pegarDuracao() == 3);

    CHECK(cristal.pegarTipo()   == Cristal);
    CHECK(cristal.pegarEfeito() == "Envenenado");
}

TEST_CASE("BancoItem retorna itens da cena 4") {
    Item pocao   = BancoItem::obterItem(4, 32); // Pocao de Mana
    Item cristal = BancoItem::obterItem(4, 33); // Cristal de Velocidade

    CHECK(pocao.pegarTipo()    == Pocao);
    CHECK(pocao.pegarEfeito()  == "Poder");
    CHECK(pocao.pegarValor()   == 4);
    CHECK(pocao.pegarDuracao() == 4);
    CHECK(pocao.getCenaId()    == 4);

    CHECK(cristal.pegarTipo()   == Cristal);
    CHECK(cristal.pegarEfeito() == "Iniciativa");
}

TEST_CASE("BancoItem retorna itens da cena 5") {
    Item comida  = BancoItem::obterItem(5, 40); // Raiz Curativa
    Item cristal = BancoItem::obterItem(5, 43); // Cristal de Drenagem

    CHECK(comida.pegarTipo()    == Comida);
    CHECK(comida.pegarDuracao() == 8);   // 2d8

    CHECK(cristal.pegarEfeito() == "Drenagem");
    CHECK(cristal.getCenaId()   == 5);
}

TEST_CASE("BancoItem retorna itens da cena 6") {
    Item pocao   = BancoItem::obterItem(6, 52); // Pocao de Escudo
    Item cristal = BancoItem::obterItem(6, 53); // Cristal Sombrio

    CHECK(pocao.pegarEfeito()  == "Defesa");
    CHECK(pocao.pegarValor()   == 4);
    CHECK(pocao.pegarDuracao() == 4);

    CHECK(cristal.pegarEfeito()    == "Berserk");
    CHECK(cristal.pegarDuracao()   == 3);
}

TEST_CASE("BancoItem retorna itens da cena 7") {
    Item comida  = BancoItem::obterItem(7, 60); // Amoras Silvestres
    Item pocao   = BancoItem::obterItem(7, 62); // Elixir Arcano
    Item cristal = BancoItem::obterItem(7, 63); // Cristal Arcano

    CHECK(comida.getCenaId()    == 7);
    CHECK(comida.pegarTipo()    == Comida);
    CHECK(comida.pegarDuracao() == 6);

    CHECK(pocao.pegarEfeito()  == "Ataque");
    CHECK(pocao.pegarValor()   == 4);
    CHECK(pocao.pegarDuracao() == 3);

    CHECK(cristal.pegarEfeito() == "Berserk");
    CHECK(cristal.getCenaId()   == 7);
}

// ── Atributos dos tipos de pocao ──────────────────────────────────────────────

TEST_CASE("BancoItem pocao de velocidade tem efeito Agilidade e duracao 3") {
    Item item = BancoItem::obterItem(3, 22);
    CHECK(item.pegarTipo()    == Pocao);
    CHECK(item.pegarEfeito()  == "Agilidade");
    CHECK(item.pegarDuracao() == 3);
    CHECK(item.pegarValor()   == 4);
}

TEST_CASE("BancoItem pocao de mana tem efeito Poder e duracao 4") {
    Item item = BancoItem::obterItem(4, 32);
    CHECK(item.pegarTipo()    == Pocao);
    CHECK(item.pegarEfeito()  == "Poder");
    CHECK(item.pegarDuracao() == 4);
    CHECK(item.pegarValor()   == 4);
}

// ── Cristal CD (Classe de Dificuldade) ───────────────────────────────────────

TEST_CASE("BancoItem cristal de protecao tem efeito CD e duracao 0") {
    Item item = BancoItem::obterItem(2, 13);
    CHECK(item.pegarTipo()    == Cristal);
    CHECK(item.pegarEfeito()  == "CD");
    CHECK(item.pegarValor()   == 5);
    CHECK(item.pegarDuracao() == 0); // permanente na cena
    CHECK(item.getCenaId()    == 2);
}
