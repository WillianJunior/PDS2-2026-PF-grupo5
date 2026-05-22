#include "../../doctest.h"

#include "entities/items/Item.hpp"

// Construtor
TEST_CASE("Construção de item do tipo Pocao") {
    Item item("Pocao de Forca", "Acrescenta +10 de força durante 3 turnos de batalha", Pocao, "Aumenta ataque", 10, 3);

    CHECK(item.pegarNome() == "Pocao de Forca");
    CHECK(item.pegarDescricao() == "Acrescenta +10 de força durante 3 turnos de batalha");
    CHECK(item.pegarTipo() == Pocao);
    CHECK(item.pegarEfeito() == "Aumenta ataque");
    CHECK(item.pegarValor() == 10);
    CHECK(item.pegarDuracao() == 3);
}

TEST_CASE("Construção de item do tipo Comida") {
    Item item("Pao", "Recupera vida", Comida, "Cura", 20, 0);

    CHECK(item.pegarNome() == "Pao");
    CHECK(item.pegarDescricao() == "Recupera vida");
    CHECK(item.pegarTipo() == Comida);
    CHECK(item.pegarEfeito() == "Cura");
    CHECK(item.pegarValor() == 20);
    CHECK(item.pegarDuracao() == 0);
}

TEST_CASE("Construção de item do tipo Cristal") {
    Item item("Cristal de Mana", "Acrescenta +15 de mana durante 2 turnos de batalha", Cristal, "Mana", 15, 2);

    CHECK(item.pegarNome() == "Cristal de Mana");
    CHECK(item.pegarDescricao() == "Acrescenta +15 de mana durante 2 turnos de batalha");
    CHECK(item.pegarTipo() == Cristal);
    CHECK(item.pegarEfeito() == "Mana");
    CHECK(item.pegarValor() == 15);
    CHECK(item.pegarDuracao() == 2);
}

// Enum
TEST_CASE("Verificação dos tipos do enum TipoItem") {
    Item pocao("Pocao", "", Pocao, "", 0, 0);
    Item comida("Comida", "", Comida, "", 0, 0);
    Item cristal("Cristal", "", Cristal, "", 0, 0);

    CHECK(pocao.pegarTipo() == Pocao);
    CHECK(comida.pegarTipo() == Comida);
    CHECK(cristal.pegarTipo() == Cristal);

    CHECK(pocao.pegarTipo() != Comida);
    CHECK(pocao.pegarTipo() != Cristal);
    CHECK(comida.pegarTipo() != Cristal);
}

// Edge cases 
TEST_CASE("Item com valor zero") {
    Item item("Item Neutro", "Não causa efeito ao personagem", Pocao, "Nenhum", 0, 0);

    CHECK(item.pegarValor() == 0);
    CHECK(item.pegarDuracao() == 0);
}

TEST_CASE("Item com valor negativo") {
    Item item("Maldição", "Reduz em -5 o ataque do personagem durante 2 turnos de batalha", Pocao, "Penalidade", -5, 2);

    CHECK(item.pegarValor() == -5);
    CHECK(item.pegarDuracao() == 2);
}
