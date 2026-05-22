#include "doctest.h"
#include "Batalha.hpp"
#include "Personagem.hpp"
#include "Cena.hpp"
#include "TrechoMapa.hpp"

TEST_CASE("Estado inicial de Batalha") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    CHECK(batalha.getTurno() == 0);
}

TEST_CASE("Iniciar Batalha") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();

    CHECK(batalha.getTurno() == 1);
}

TEST_CASE("Ataque Simples avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Rapido avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueRapido);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Forte avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueForte);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Defesa avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Defesa);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Esquiva avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Esquiva);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Usar Item avanca turno") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::UsarItem);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Finalizar Batalha") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);
    batalha.finalizarBatalha();

    CHECK(batalha.getTurno() == 0);
}

TEST_CASE("Processar Defesa sem dano - defesa maior que ataque") {
    Personagem player("Tank", "Tank resistente", "Nao me atinja!", 10, 25, 100, 50, 10, TipoClasse::Tanque, TipoPersonagem::Jogador);
    Personagem inimigo("Fraco", "Inimigo fraco", "Grr!", 10, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() == vidaAntes);
}

TEST_CASE("Processar Defesa com dano parcial - razao entre 0.8 e 1.0") {
    Personagem player("Medio", "Guerreiro medio", "Vamos!", 10, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc bruto", "Raargh!", 18, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() < vidaAntes);
    CHECK(player.getVidaAtual() > vidaAntes - inimigo.getAtaque());
}

TEST_CASE("Processar Defesa com dano total - razao abaixo de 0.8") {
    Personagem player("Fragil", "Mago fragil", "Nao!", 10, 5, 100, 50, 10, TipoClasse::Mago, TipoPersonagem::Jogador);
    Personagem inimigo("Forte", "Inimigo forte", "Raargh!", 20, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() < vidaAntes);
}

TEST_CASE("Processar Esquiva sem dano - agilidade maior que ataque") {
    Personagem player("Agil", "Arqueiro agil", "Nunca me acertaras!", 15, 10, 100, 50, 25, TipoClasse::Arqueiro, TipoPersonagem::Jogador);
    Personagem inimigo("Lento", "Inimigo lento", "Grr!", 18, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() == vidaAntes);
}

TEST_CASE("Processar Esquiva com dano total - agilidade menor que ataque") {
    Personagem player("Lento", "Guerreiro lento", "Vou te pegar!", 15, 10, 100, 50, 5, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Agil", "Inimigo agil", "Grr!", 18, 6, 30, 20, 25, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() < vidaAntes);
}

TEST_CASE("Processar Esquiva com dano parcial - agilidade igual ao ataque") {
    Personagem player("Medio", "Guerreiro medio", "Vamos!", 15, 10, 100, 50, 18, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Igual", "Inimigo igual", "Grr!", 18, 6, 30, 20, 18, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() < vidaAntes);
    CHECK(player.getVidaAtual() > vidaAntes - inimigo.getAtaque());
}

TEST_CASE("Definir Recompensa") {
    TrechoMapa trecho(1, "Floresta");
    Cena cena(1, &trecho);
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();
    batalha.definirRecompensa(cena);

    CHECK(cena.explorando() == true);
    CHECK(cena.emBatalha() == false);
}

TEST_CASE("Acao invalida lanca excecao") {
    Personagem player("Heroi", "Heroi corajoso", "Vou te vencer!", 20, 15, 100, 50, 10, TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc cruel", "Grr!", 8, 6, 30, 20, 5, TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo);

    batalha.iniciarBatalha();

    CHECK_THROWS_AS(batalha.realizarAcao(static_cast<AcaoBatalha>(999)), std::invalid_argument);
}