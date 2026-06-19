#include "../../doctest.h"

#include <memory>

#include "entities/character/Jogador.hpp"
#include "entities/items/Item.hpp"
#include "entities/items/Inventario.hpp"

TEST_CASE("Jogador inicia com inventario vazio") {
    Jogador jogador("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                    TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    CHECK(jogador.getInventario().quantidadeItens() == 0);
    CHECK(jogador.getInventario().estaCheio() == false);
}

TEST_CASE("Jogador adicionar item aumenta quantidade no inventario") {
    Jogador jogador("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                    TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    jogador.adicionarItem(std::make_unique<Item>("Pao", "Recupera 20 PV", Comida, "Cura", 20, 0));

    CHECK(jogador.getInventario().quantidadeItens() == 1);
}

TEST_CASE("Jogador usar comida aplica efeito e remove item") {
    Jogador jogador("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                    TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    jogador.receberDano(30.0);

    jogador.adicionarItem(std::make_unique<Item>("Pao", "Recupera 1d6 PV", Comida, "Cura", 1, 6));
    jogador.usarItem(0);

    CHECK(jogador.getInventario().quantidadeItens() == 0);
    CHECK(jogador.getVidaAtual() > 70.0);   // jogador estava a 70 HP, sempre cura algo
    CHECK(jogador.getVidaAtual() <= 100.0);
}

TEST_CASE("Jogador lanca excecao ao adicionar item com inventario cheio") {
    Jogador jogador("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                    TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    for (int i = 0; i < 8; i++)
        jogador.adicionarItem(std::make_unique<Item>("Item", "", Pocao, "", 0, 0));

    // unique_ptr é destruído automaticamente quando a exceção propaga — sem vazamento
    CHECK_THROWS_AS(
        jogador.adicionarItem(std::make_unique<Item>("Extra", "", Pocao, "", 0, 0)),
        InventarioCheioException);
}
