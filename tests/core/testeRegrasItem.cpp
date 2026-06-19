#include "../doctest.h"

#include "entities/items/Item.hpp"
#include "entities/character/Personagem.hpp"
#include "core/rules/RegrasItem.hpp"
#include "utils/AtributoEnum.hpp"
#include "utils/TipoCondicaoEnum.hpp"

static Personagem criarHeroi() {
    return Personagem("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                      TipoClasse::Guerreiro, TipoPersonagem::Jogador);
}

// ── Comida ────────────────────────────────────────────────────────────────

TEST_CASE("Comida positiva recupera vida do personagem") {
    Item comida("Fruta Fresca", "Recupera 1d6 PV", Comida, "Cura", 1, 6);
    Personagem heroi = criarHeroi();
    heroi.receberDano(20.0);

    RegrasItem::aplicarEfeito(comida, heroi);

    CHECK(heroi.getVidaAtual() > 80.0);   // herói estava a 80 HP, sempre cura algo
    CHECK(heroi.getVidaAtual() <= 100.0);
}

TEST_CASE("Comida negativa causa dano ao personagem") {
    Item comidaRuim("Cogumelo Toxico", "Causa 1d8 de dano", Comida, "Dano", -1, 8);
    Personagem heroi = criarHeroi();

    RegrasItem::aplicarEfeito(comidaRuim, heroi);

    CHECK(heroi.getVidaAtual() < 100.0);  // sempre recebe algum dano
    CHECK(heroi.getVidaAtual() >= 0.0);
}

TEST_CASE("Comida nao ultrapassa limite maximo de PV") {
    Item comida("Carne Preparada", "Recupera 7d6 PV", Comida, "Cura", 7, 6);
    Personagem heroi = criarHeroi();
    heroi.receberDano(5.0);

    RegrasItem::aplicarEfeito(comida, heroi);

    CHECK(heroi.getVidaAtual() == 100.0); // 7d6 mínimo = 7 > 5 de dano → sempre atinge o máximo
}

// ── Poção ─────────────────────────────────────────────────────────────────

TEST_CASE("Pocao de Forca aumenta ataque e armazena condicao") {
    Item pocao("Pocao de Forca", "Boost de Ataque", Pocao, "Ataque", 4, 3);
    Personagem heroi = criarHeroi();
    double ataqueOriginal = heroi.getAtaque();

    RegrasItem::aplicarEfeito(pocao, heroi);

    CHECK(heroi.getAtaque() == ataqueOriginal + 4.0);
    CHECK(heroi.getCondicoesAtivas().size() == 1);
    CHECK(heroi.getCondicoesAtivas()[0].tipo == TipoCondicao::ModAtributo);
    CHECK(heroi.getCondicoesAtivas()[0].atributoAlvo == Atributo::Ataque);
    CHECK(heroi.getCondicoesAtivas()[0].duracaoTurnos == 3);
}

TEST_CASE("Remover condicao de Pocao reverte o ataque") {
    Item pocao("Pocao de Forca", "Boost de Ataque", Pocao, "Ataque", 4, 3);
    Personagem heroi = criarHeroi();
    double ataqueOriginal = heroi.getAtaque();

    RegrasItem::aplicarEfeito(pocao, heroi);
    heroi.removerCondicao(0);

    CHECK(heroi.getAtaque() == ataqueOriginal);
    CHECK(heroi.getCondicoesAtivas().empty());
}

TEST_CASE("Pocao de Resistencia aumenta defesa") {
    Item pocao("Pocao de Resistencia", "Boost de Defesa", Pocao, "Defesa", 4, 4);
    Personagem heroi = criarHeroi();
    double defesaOriginal = heroi.getDefesa();

    RegrasItem::aplicarEfeito(pocao, heroi);

    CHECK(heroi.getDefesa() == defesaOriginal + 4.0);
}

// ── Cristal ───────────────────────────────────────────────────────────────

TEST_CASE("Cristal de Agressao armazena condicao Berserk") {
    Item cristal("Cristal de Agressao", "Berserk por 3 turnos", Cristal, "Berserk", 3, 3);
    Personagem heroi = criarHeroi();

    RegrasItem::aplicarEfeito(cristal, heroi);

    CHECK(heroi.getCondicoesAtivas().size() == 1);
    CHECK(heroi.getCondicoesAtivas()[0].tipo == TipoCondicao::Berserk);
    CHECK(heroi.getCondicoesAtivas()[0].duracaoTurnos == 3);
}

TEST_CASE("Cristal de Protecao boost de defesa via ModAtributo") {
    Item cristal("Cristal de Protecao", "+5 CD", Cristal, "CD", 5, 0);
    Personagem heroi = criarHeroi();
    double defesaOriginal = heroi.getDefesa();

    RegrasItem::aplicarEfeito(cristal, heroi);

    CHECK(heroi.getDefesa() == defesaOriginal + 5.0);
    CHECK(heroi.getCondicoesAtivas()[0].tipo == TipoCondicao::ModAtributo);
    CHECK(heroi.getCondicoesAtivas()[0].atributoAlvo == Atributo::Defesa);
}

TEST_CASE("Cristal de Veneno armazena condicao Envenenado") {
    Item cristal("Cristal de Veneno", "Envenena alvo", Cristal, "Envenenado", 3, 3);
    Personagem heroi = criarHeroi();

    RegrasItem::aplicarEfeito(cristal, heroi);

    CHECK(heroi.getCondicoesAtivas()[0].tipo == TipoCondicao::Envenenado);
}
