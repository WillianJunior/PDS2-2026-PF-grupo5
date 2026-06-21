#include "../doctest.h"

#include <iostream>
#include "Dados.hpp"
#include "core/rules/RegrasAtaque.hpp"
#include "entities/character/Personagem.hpp"
/**
 * Calculo de Dano: 
 * Normal: dado(s) + coeficiente.
 * Nivel: (nivel, face) + coeficiente.
 * 
 * Calculo de Coeficiente: (valorAtributo * 0.5) - 5.0
 * 
 * Execucoes Ataque:
 * Normal: execucoes x (dado(s) + coeficiente).
 * Nivel: execucoes x ((nivel, face) + coeficiente)
 * 
 * 
 * Dado(1):
 * (1,8) = 4
 * (1, 4) = 2
 * (1, 6) = 3
 * (4, 6) = 20
 * (2, 8) = 12
 * (1, 10) = 5
 */

TEST_CASE("Dano de ataque simples de personagem") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefAtaque + dado) -> 5 + 4 = 9
    CHECK(dano == 9);
}

TEST_CASE("Dano de ataque simples de personagem com ataque com valor baixo") {
    Personagem p("John Doe", "Descricao", "Fala", 
        1, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefAtaque + dado) -> -4.5 + 4 = -0.5
    // -0.5 vira 0
    CHECK(dano == 0);
}

TEST_CASE("Dano de multi ataques simples de Guerreiro em nivel 5") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 5);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 2 x (CoefAtaque + dado) -> 2 x (5 + 4) = 18
    CHECK(dano == 18);
}

TEST_CASE("Dano de ataque simples de Arqueiro em nivel 3") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::Jogador, 3);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefAtaque + dado) -> 5 + 4 = 9
    CHECK(dano == 9);
}

TEST_CASE("Dano de ataque simples de Mago em nivel 10") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Mago, 
        TipoPersonagem::Jogador, 10);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefAtaque + dado) -> 5 + 33 = 38
    Dados dados(1);
    CHECK(dados.rolar(4,10) == 33);
    CHECK(dano == 38);
}

TEST_CASE("Dano de ataque rapido de Guerreiro") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Rapido);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 2 x (CoefAtaque + dado) -> 2 x (5 + 4) = 18
    CHECK(dano == 14);
}

TEST_CASE("Dano de ataque forte que usa CoefAgilidade e usa Nivel de Arqueiro nivel 7") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 40, 100, 50, 30, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::Jogador, 7);

    p.alteraAtaqueForte();
    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Forte);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefAgil + (nivel, face)) -> (10 + 24) +  = 34
    CHECK(ataque.id == IdAtaque::TiroFinal);
    CHECK(dano == 34);
}

TEST_CASE("Dano de ataque forte que usa CoefDefesa") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 40, 100, 50, 32, 
        TipoClasse::Tanque, 
        TipoPersonagem::Jogador, 7);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Forte);
    double dano = 0;
    for(int i = 0; i < RegrasAtaque::getExecucoes(p, ataque); i++)
        dano += RegrasAtaque::calcularDano(p, ataque, 1);
    // 1 x (CoefDefesa + dado) -> 15 + 5 = 20
    CHECK(ataque.id == IdAtaque::PancadaDeEscudo);
    CHECK(dano == 20);
}

TEST_CASE("Dano de ataque abaixo ou igual ao valor maximo/minimo") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    // CoefAtaque + dado -> 5 + 8 = 13
    // CoefAtaque + dado -> 5 + 1 = 6
    double dano = RegrasAtaque::calcularDano(p, ataque);
    CHECK(dano >= 6);
    CHECK(dano <= 13);
    dano = RegrasAtaque::calcularDano(p, ataque);
    CHECK(dano >= 6);
    CHECK(dano <= 13);
    dano = RegrasAtaque::calcularDano(p, ataque);
    CHECK(dano >= 6);
    CHECK(dano <= 13);
    dano = RegrasAtaque::calcularDano(p, ataque);
    CHECK(dano >= 6);
    CHECK(dano <= 13);
}
