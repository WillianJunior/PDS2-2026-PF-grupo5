/**
 * @file testeBancoInimigo.cpp
 * @brief Testes unitarios para BancoInimigo -- cobertura de todos os IDs.
 */

#include "../doctest.h"
#include <stdexcept>
#include "database/BancoInimigo.hpp"

// --- Helpers -----------------------------------------------------------------

static void checkInimigo(int id, TipoPersonagem tipoEsperado) {
    Personagem p = BancoInimigo::obterInimigo(id);
    CHECK(!p.getNome().empty());
    CHECK(p.getVidaAtual() > 0);
    CHECK(p.getTipo() == tipoEsperado);
}

// --- ID invalido --------------------------------------------------------------

TEST_CASE("BancoInimigo - ID zero lanca excecao") {
    CHECK_THROWS_AS(BancoInimigo::obterInimigo(0),  std::invalid_argument);
}

TEST_CASE("BancoInimigo - ID negativo lanca excecao") {
    CHECK_THROWS_AS(BancoInimigo::obterInimigo(-5), std::invalid_argument);
}

TEST_CASE("BancoInimigo - ID desconhecido lanca excecao") {
    CHECK_THROWS_AS(BancoInimigo::obterInimigo(9999), std::invalid_argument);
}

// --- Fase I (Magisk, LV 1-2) -------------------------------------------------

TEST_CASE("BancoInimigo - Fase I inimigos comuns (1, 2, 3)") {
    checkInimigo(1, TipoPersonagem::Inimigo);
    checkInimigo(2, TipoPersonagem::Inimigo);
    checkInimigo(3, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase I: Device (101)") {
    checkInimigo(101, TipoPersonagem::BOSS);
    Personagem p = BancoInimigo::obterInimigo(101);
    CHECK(p.getNivel() >= 1);
}

// --- Fase II (Mantuu, LV 3-4) ------------------------------------------------

TEST_CASE("BancoInimigo - Fase II inimigos comuns (11, 12, 13)") {
    checkInimigo(11, TipoPersonagem::Inimigo);
    checkInimigo(12, TipoPersonagem::Inimigo);
    checkInimigo(13, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase II: Vaelthor (102)") {
    checkInimigo(102, TipoPersonagem::BOSS);
}

// --- Fase III (Xantares, LV 5-6) ---------------------------------------------

TEST_CASE("BancoInimigo - Fase III inimigos comuns (21, 22, 23)") {
    checkInimigo(21, TipoPersonagem::Inimigo);
    checkInimigo(22, TipoPersonagem::Inimigo);
    checkInimigo(23, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase III: Malphas (103)") {
    checkInimigo(103, TipoPersonagem::BOSS);
}

// --- Fase IV (Kenyrock, LV 7-8) ----------------------------------------------

TEST_CASE("BancoInimigo - Fase IV inimigos comuns (31, 32, 33)") {
    checkInimigo(31, TipoPersonagem::Inimigo);
    checkInimigo(32, TipoPersonagem::Inimigo);
    checkInimigo(33, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase IV: N'baki D'Itris (104)") {
    checkInimigo(104, TipoPersonagem::BOSS);
}

// --- Fase V (Skyprout, LV 9-10) ----------------------------------------------

TEST_CASE("BancoInimigo - Fase V inimigos comuns (41, 42, 43)") {
    checkInimigo(41, TipoPersonagem::Inimigo);
    checkInimigo(42, TipoPersonagem::Inimigo);
    checkInimigo(43, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase V: Livies (105)") {
    checkInimigo(105, TipoPersonagem::BOSS);
}

// --- Fase VI (Retorno Magisk) -------------------------------------------------

TEST_CASE("BancoInimigo - Fase VI inimigos comuns (51, 52, 53)") {
    checkInimigo(51, TipoPersonagem::Inimigo);
    checkInimigo(52, TipoPersonagem::Inimigo);
    checkInimigo(53, TipoPersonagem::Inimigo);
}

TEST_CASE("BancoInimigo - Arauto Fase VI: Nyriel (106)") {
    checkInimigo(106, TipoPersonagem::BOSS);
}

// --- Boss Final --------------------------------------------------------------

TEST_CASE("BancoInimigo - Boss Final: Sonath (999)") {
    Personagem p = BancoInimigo::obterInimigo(999);
    CHECK(!p.getNome().empty());
    CHECK(p.getVidaAtual() > 0);
    CHECK(p.getTipo() == TipoPersonagem::BOSS);
    CHECK(p.getNivel() == 10);
}

// --- Atributos basicos -------------------------------------------------------

TEST_CASE("BancoInimigo - atributos crescem por fase") {
    Personagem fase1 = BancoInimigo::obterInimigo(1);
    Personagem fase6 = BancoInimigo::obterInimigo(52);
    CHECK(fase6.getVidaTotal() > fase1.getVidaTotal());
}
