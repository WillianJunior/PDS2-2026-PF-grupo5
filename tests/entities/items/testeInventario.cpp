#include "../../doctest.h"

#include <stdexcept>

#include "entities/items/Item.hpp"
#include "entities/items/Inventario.hpp"
#include "entities/character/Personagem.hpp"

// TODO: substituir std::overflow_error por InventarioCheioException quando a exception customizada for implementada

// Manipulação de itens no inventário
TEST_CASE("Inventario inicia vazio") {
    Inventario inv;

    CHECK(inv.quantidadeItens() == 0);
    CHECK(inv.estaCheio() == false);
}

TEST_CASE("Adicionar um item aumenta a quantidade") {
    Inventario inv;
    Item item("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0);

    inv.adicionarItem(&item);

    CHECK(inv.quantidadeItens() == 1);
    CHECK(inv.estaCheio() == false);
}

TEST_CASE("Adicionar itens ate a capacidade maxima") {
    Inventario inv;
    Item itens[8] = {
        Item("Item1", "", Pocao, "", 0, 0),
        Item("Item2", "", Pocao, "", 0, 0),
        Item("Item3", "", Pocao, "", 0, 0),
        Item("Item4", "", Pocao, "", 0, 0),
        Item("Item5", "", Pocao, "", 0, 0),
        Item("Item6", "", Pocao, "", 0, 0),
        Item("Item7", "", Pocao, "", 0, 0),
        Item("Item8", "", Pocao, "", 0, 0)
    };

    for (int i = 0; i < 8; i++) {
        inv.adicionarItem(&itens[i]);
    }

    CHECK(inv.quantidadeItens() == 8);
    CHECK(inv.estaCheio() == true);
}

TEST_CASE("Adicionar item em inventario cheio lanca excecao") {
    Inventario inv;
    Item itens[9] = {
        Item("Item1", "", Pocao, "", 0, 0),
        Item("Item2", "", Pocao, "", 0, 0),
        Item("Item3", "", Pocao, "", 0, 0),
        Item("Item4", "", Pocao, "", 0, 0),
        Item("Item5", "", Pocao, "", 0, 0),
        Item("Item6", "", Pocao, "", 0, 0),
        Item("Item7", "", Pocao, "", 0, 0),
        Item("Item8", "", Pocao, "", 0, 0),
        Item("Item9", "", Pocao, "", 0, 0)
    };

    for (int i = 0; i < 8; i++) {
        inv.adicionarItem(&itens[i]);
    }

    // TODO: criar uma exceção custom para esse caso (algo como InventarioCheioException) e substituir a exception genérica utilizada
    CHECK_THROWS_AS(inv.adicionarItem(&itens[8]), std::overflow_error);
    CHECK(inv.quantidadeItens() == 8);
}

TEST_CASE("Remover item diminui a quantidade") {
    Inventario inv;
    Item item1("Pocao de Forca", "Acrescenta +10 de ataque durante 3 turnos", Pocao, "Ataque", 10, 3);
    Item item2("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0);

    inv.adicionarItem(&item1);
    inv.adicionarItem(&item2);
    inv.removerItem(0);

    CHECK(inv.quantidadeItens() == 1);
}

// Uso de itens no inventário 
TEST_CASE("Usar item remove do inventario") {
    Inventario inv;
    Item comida("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0);
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    inv.adicionarItem(&comida);
    inv.usarItem(0, heroi);

    CHECK(inv.quantidadeItens() == 0);
}
