#include "doctest.h"
#include "Batalha.hpp"
#include "Personagem.hpp"
#include "Cena.hpp"
#include "TrechoMapa.hpp"

TEST_CASE("Estado inicial de Batalha") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    CHECK(batalha.getTurno() == 0);
}

TEST_CASE("Iniciar Batalha") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();

    CHECK(batalha.getTurno() == 1);
}

TEST_CASE("Ataque Simples avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Rapido avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueRapido);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Forte avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueForte);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Defesa avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Defesa);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Esquiva avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Esquiva);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Usar Item avanca turno") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::UsarItem);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Finalizar Batalha") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);
    batalha.finalizarBatalha();

    CHECK(batalha.getTurno() == 0);
}

TEST_CASE("Processar Defesa sem dano - defesa maior que ataque") {
    Personagem player("Tank", 100, 25, 15, 10);
    Personagem inimigo("Fraco", 30, 10, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarDefesa();

    CHECK(player.getHP() == hpAntes);
}

TEST_CASE("Processar Defesa com dano parcial - razao entre 0.8 e 1.0") {
    Personagem player("Medio", 100, 15, 15, 10);
    Personagem inimigo("Orc", 30, 18, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarDefesa();

    CHECK(player.getHP() < hpAntes);
    CHECK(player.getHP() > hpAntes - inimigo.getAtaque());
}

TEST_CASE("Processar Defesa com dano total - razao abaixo de 0.8") {
    Personagem player("Fragil", 100, 5, 15, 10);
    Personagem inimigo("Forte", 30, 20, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarDefesa();

    CHECK(player.getHP() < hpAntes);
}

TEST_CASE("Processar Esquiva sem dano - agilidade maior que ataque") {
    Personagem player("Agil", 100, 15, 25, 10);
    Personagem inimigo("Lento", 30, 18, 5, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarEsquiva();

    CHECK(player.getHP() == hpAntes);
}

TEST_CASE("Processar Esquiva com dano total - agilidade menor que ataque") {
    Personagem player("Lento", 100, 15, 5, 10);
    Personagem inimigo("Agil", 30, 18, 25, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarEsquiva();

    CHECK(player.getHP() < hpAntes);
}

TEST_CASE("Processar Esquiva com dano parcial - agilidade igual ao ataque") {
    Personagem player("Medio", 100, 15, 18, 10);
    Personagem inimigo("Igual", 30, 18, 18, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    int hpAntes = player.getHP();
    batalha.processarEsquiva();

    CHECK(player.getHP() < hpAntes);
    CHECK(player.getHP() > hpAntes - inimigo.getAtaque());
}

TEST_CASE("Definir Recompensa") {
    TrechoMapa trecho(1, "Floresta");
    Cena cena(1, &trecho);
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.definirRecompensa(cena);

    CHECK(cena.explorando() == true);
    CHECK(cena.emBatalha() == false);
}

TEST_CASE("Acao invalida lanca excecao") {
    Personagem player("Heroi", 100, 20, 15, 10);
    Personagem inimigo("Orc", 30, 8, 6, 5);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();

    CHECK_THROWS_AS(batalha.realizarAcao(static_cast<AcaoBatalha>(999)), std::invalid_argument);
}