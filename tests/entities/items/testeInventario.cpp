#include "../../doctest.h"

#include <memory>
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

    inv.adicionarItem(std::make_unique<Item>("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));

    CHECK(inv.quantidadeItens() == 1);
    CHECK(inv.estaCheio() == false);
}

TEST_CASE("Adicionar itens ate a capacidade maxima") {
    Inventario inv;

    for (int i = 0; i < 8; i++)
        inv.adicionarItem(std::make_unique<Item>("Item", "", Pocao, "", 0, 0));

    CHECK(inv.quantidadeItens() == 8);
    CHECK(inv.estaCheio() == true);
}

TEST_CASE("Adicionar item em inventario cheio lanca excecao") {
    Inventario inv;

    for (int i = 0; i < 8; i++)
        inv.adicionarItem(std::make_unique<Item>("Item", "", Pocao, "", 0, 0));

    // unique_ptr é destruído automaticamente quando a exceção propaga — sem vazamento
    CHECK_THROWS_AS(
        inv.adicionarItem(std::make_unique<Item>("Extra", "", Pocao, "", 0, 0)),
        InventarioCheioException);
    CHECK(inv.quantidadeItens() == 8);
}

TEST_CASE("Remover item diminui a quantidade") {
    Inventario inv;

    inv.adicionarItem(std::make_unique<Item>("Pocao de Forca", "Acrescenta +10 de ataque durante 3 turnos", Pocao, "Ataque", 10, 3));
    inv.adicionarItem(std::make_unique<Item>("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));
    inv.removerItem(0);

    CHECK(inv.quantidadeItens() == 1);
}

// Uso de itens no inventário
TEST_CASE("Usar item remove do inventario") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    inv.adicionarItem(std::make_unique<Item>("Pao", "Recupera 1d6 PV", Comida, "Cura", 1, 6));
    inv.usarItem(0, heroi);

    CHECK(inv.quantidadeItens() == 0);
}

TEST_CASE("Usar comida recupera vida do personagem") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    heroi.receberDano(30.0);

    inv.adicionarItem(std::make_unique<Item>("Pao", "Recupera 1d6 PV", Comida, "Cura", 1, 6));
    inv.usarItem(0, heroi);

    CHECK(heroi.getVidaAtual() > 70.0);   // herói estava a 70 HP, sempre cura algo
    CHECK(heroi.getVidaAtual() <= 100.0);
}

TEST_CASE("Usar comida negativa causa dano ao personagem") {
    Inventario inv;
    Personagem heroi("Heroi", "descrição do heroi", "fala do heroi", 10.0, 5.0, 100.0, 50.0, 8.0,
                     TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    inv.adicionarItem(std::make_unique<Item>("Cogumelo Toxico", "Causa 1d8 de dano", Comida, "Dano", -1, 8));
    inv.usarItem(0, heroi);

    CHECK(heroi.getVidaAtual() < 100.0);  // sempre recebe algum dano
    CHECK(heroi.getVidaAtual() >= 0.0);
}
