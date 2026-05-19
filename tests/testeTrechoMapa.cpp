#include "doctest.h"
#include "TrechoMapa.hpp"
#include "Item.hpp"
#include "Personagem.hpp"

TEST_CASE("Construtor de TrechoMapa"){
    TrechoMapa trecho(1, "Floresta");

    CHECK(trecho.pegarItens().size()==0);
    CHECK(trecho.pegarNPCs().size()==0);
    CHECK(trecho.estaAberto() == false);
}

TEST_CASE("Funcao abrirTrecho ") {
    TrechoMapa trecho(1, "Floresta");

    trecho.abrirTrecho();

    CHECK(trecho.estaAberto() == true);
}

TEST_CASE("Adicionar item") {
    TrechoMapa trecho(1, "Floresta");

    Item* item = new Item("Poção", "cura", TipoItem::Pocao, "cura", 10, 0);

    trecho.adicionarItem(item);

    CHECK(trecho.pegarItens().size() == 1);
    CHECK(trecho.pegarItens()[0] == item);

    delete item;
}

TEST_CASE("Varios itens") {
    TrechoMapa trecho(1, "Floresta");

    Item* item1 = new Item("Item1", "Item 1 eh uma pocao", TipoItem::Pocao, "defesa", 5, 0);
    Item* item2 = new Item("Item2", "item 2 eh uma comida", TipoItem::Comida, "cura", 20, 0);

    trecho.adicionarItem(item1);
    trecho.adicionarItem(item2);

    CHECK(trecho.pegarItens()[0] == item1);
    CHECK(trecho.pegarItens()[1] == item2);

    delete item1;
    delete item2;
}

TEST_CASE("Adicionar NPC") {
    TrechoMapa trecho(1, "Floresta");

    Personagem* npc = nullptr;

    trecho.adicionarNPC(npc);

    CHECK(trecho.pegarNPCs().size() == 1);
    CHECK(trecho.pegarNPCs()[0] == npc);
}

TEST_CASE("Varios NPCs") {
    TrechoMapa trecho(1, "Floresta");

    Personagem* npc1 = nullptr;
    Personagem* npc2 = nullptr;
    Personagem* npc3 = nullptr;

    trecho.adicionarNPC(npc1);
    trecho.adicionarNPC(npc2);
    trecho.adicionarNPC(npc3);

    auto npcs = trecho.pegarNPCs();

    CHECK(npcs.size() == 3);
    CHECK(npcs[0] == npc1);
    CHECK(npcs[1] == npc2);
    CHECK(npcs[2] == npc3);
}

TEST_CASE("Coeistencia de Itens e NPCs") {
    TrechoMapa trecho(1, "Floresta");

    Item* item = new Item("Poção", "Essa pocao melhora seu ataque.", TipoItem::Pocao, "Ataque", 10, 0);
    Personagem* npc = nullptr;

    trecho.adicionarItem(item);
    trecho.adicionarNPC(npc);

    CHECK(trecho.pegarItens().size() == 1);
    CHECK(trecho.pegarNPCs().size() == 1);

    CHECK(trecho.pegarItens()[0] == item);
    CHECK(trecho.pegarNPCs()[0] == npc);

    delete item;
}
