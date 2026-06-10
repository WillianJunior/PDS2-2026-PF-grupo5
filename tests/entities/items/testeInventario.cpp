#include "../../doctest.h"

#include <stdexcept>

#include "entities/items/Item.hpp"
#include "entities/items/Inventario.hpp"
#include "entities/character/Personagem.hpp"

// Manipulação de itens no inventário
TEST_CASE("Inventario inicia vazio") {
    Inventario inv;

    CHECK(inv.quantidadeItens() == 0);
    CHECK(inv.estaCheio() == false);
}

TEST_CASE("Adicionar um item aumenta a quantidade") {
    Inventario inv;

    inv.adicionarItem(new Item("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));

    CHECK(inv.quantidadeItens() == 1);
    CHECK(inv.estaCheio() == false);
}

TEST_CASE("Adicionar itens ate a capacidade maxima") {
    Inventario inv;

    for (int i = 0; i < 8; i++)
        inv.adicionarItem(new Item("Item", "", Pocao, "", 0, 0));

    CHECK(inv.quantidadeItens() == 8);
    CHECK(inv.estaCheio() == true);
}

TEST_CASE("Adicionar item em inventario cheio lanca excecao") {
    Inventario inv;

    for (int i = 0; i < 8; i++)
        inv.adicionarItem(new Item("Item", "", Pocao, "", 0, 0));

    Item* extra = new Item("Extra", "", Pocao, "", 0, 0);
    CHECK_THROWS_AS(inv.adicionarItem(extra), InventarioCheioException);
    CHECK(inv.quantidadeItens() == 8);
    delete extra;
}

TEST_CASE("Remover item diminui a quantidade") {
    Inventario inv;

    inv.adicionarItem(new Item("Pocao de Forca", "Acrescenta +10 de ataque durante 3 turnos", Pocao, "Ataque", 10, 3));
    inv.adicionarItem(new Item("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));
    inv.removerItem(0);

    CHECK(inv.quantidadeItens() == 1);
}

// Uso de itens no inventário
TEST_CASE("Usar item remove do inventario") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    inv.adicionarItem(new Item("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));
    inv.usarItem(0, heroi);

    CHECK(inv.quantidadeItens() == 0);
}

TEST_CASE("Usar comida recupera vida do personagem") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    heroi.receberDano(30.0);

    inv.adicionarItem(new Item("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));
    inv.usarItem(0, heroi);

    CHECK(heroi.getVidaAtual() == 90.0);
}

TEST_CASE("Usar comida negativa causa dano ao personagem") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    inv.adicionarItem(new Item("Cogumelo Toxico", "Causa 10 de dano", Comida, "Dano", -10, 0));
    inv.usarItem(0, heroi);

    CHECK(heroi.getVidaAtual() == 90.0);
}
