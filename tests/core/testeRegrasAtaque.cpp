#include "../doctest.h"

#include <iostream>
#include "Dados.hpp"
#include "core/rules/RegrasAtaque.hpp"
#include "entities/character/Personagem.hpp"
/**
 * Calculo de Dano: 
 * Normal: dado(s) + coeficiente.
 * Multiplicador: (dado(s) + coeficiente) * multiplicador.
 * Nivel: nivel + dado(s) + coeficiente.
 * Com Tudo: (nivel + dado(s) + coeficiente) * multiplicador
 * 
 * Calculo de Coeficiente: (valorAtributo * 0.5) - 5.0
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

TEST_CASE("Calcula dano de ataque fraco de personagem") {
    Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    // CoefAtaque + dado -> 5 + 4 = 9
    CHECK(dano == 9);
}

TEST_CASE("Calcula dano de ataque fraco de personagem com ataque com valor baixo") {
    Personagem p("John Doe", "Descricao", "Fala", 
        1, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Simples);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    // CoefAtaque + dado -> -4.5 + 4 = -0.5
    // -0.5 vira 0
    CHECK(dano == 0);
}

TEST_CASE("Calcula dano de ataque rapido de Guerreiro") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Rapido);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    Dados dados(1);
    // 2*(CoefAtaque + dado) -> 2*(15 + 2) = 14
    CHECK(dano == 14);
}

TEST_CASE("Calcula dano de ataque forte de Tanque") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 40, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::Jogador, 1);

    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Forte);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    Dados dados(1);
    // CoefDefesa + dado -> (15 + 5) = 20
    CHECK(ataque.id == IdAtaque::PancadaDeEscudo);
    CHECK(dano == 20);
}


TEST_CASE("Calcula dano de ataque forte que escalaNivel de Mago nivel 7") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Mago, 
        TipoPersonagem::Jogador, 7);

    p.alteraAtaqueForte();
    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Forte);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    
    // Nivel * (CoefAtaque + dado) -> 7*(5 + 3) = 56
    CHECK(dano == 56);
}

/**
 * TEST_CASE("Calcula dano de ataque forte que escalaNivel de Mago nivel 7") {
   Personagem p("John Doe", "Descricao", "Fala", 
        20, 20, 100, 50, 20, 
        TipoClasse::Mago, 
        TipoPersonagem::Jogador, 7);

    p.alteraAtaqueForte();
    Ataque ataque = p.getClasse().getAtaque(TipoAtaque::Forte);
    double dano = RegrasAtaque::calcularDano(p, ataque, 1);
    
    // Nivel * (CoefAtaque + dado) -> 7*(5 + 3) = 56
    CHECK(ataque.id == IdAtaque::VorticeArcano);
}
 */



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
