/**
 * @file RegrasAtaque.hpp
 * @brief Define toda a lógica do Calculo de Ataques.
 * 
 *  Utilizado por Batalha para Calcular o Dano de um Ataque.
 *  O Dano de um Ataque é calculado a partir do seu tipo e IdAtaque.
 * 
 *  @see regras.md - Seção 2.2, 2.3 e 2.4
 * 
 */
#ifndef REGRASATAQUE_HPP
#define REGRASATAQUE_HPP

#include "entities/character/ClassePersonagem.hpp"
#include "entities/character/Personagem.hpp"
#include "database/BancoClassePersonagem.hpp"
#include "core/Dados.hpp"
#include "Regras.hpp"

/**
 * @class RegrasAtaque
 * @brief Calcula o dano dos ataques, considerando comportamento único.
 *
 */
class RegrasAtaque : public Regras {
    public:

        static double calcularDano(const Personagem& personagem, const Ataque& ataque);
        
    private:
        static double calcularDanoSimples(const Personagem& personagem, const Ataque& ataque);
        static double calcularDanoRapido(const Personagem& personagem, const Ataque& ataque);
        static double calcularDanoForte(const Personagem& personagem, const Ataque& ataque);
};

#endif