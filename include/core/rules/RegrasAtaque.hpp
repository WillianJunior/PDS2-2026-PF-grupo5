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
#include "database/BancoDadosAtaque.hpp"
#include "core/Dados.hpp"
#include "Regras.hpp"
#include <optional>

/**
 * @class RegrasAtaque
 * @brief Calcula o dano dos ataques, considerando comportamento único.
 *
 */
class RegrasAtaque : public Regras {
    public:
        /**
         * @brief Calcula o dano baseado no Ataque e na Classe do Personagem.
         * @param personagem O Personagem que atacou.
         * @param ataque O Ataque que o Personagem utilizou.
         * @param seed Usado apenas para testes.
         * @return O dano do Ataque baseado em seu comportamento e influencias de nível, atributos e classe.
         *
        */
        static double calcularDano(const Personagem& personagem, const Ataque& ataque, std::optional<unsigned int> seed = std::nullopt); 

    private:
        /**
         * @brief Calcula o coeficiente baseado no AtributoCoef de um Ataque.
         * @param personagem O Personagem.
         * @param atributoCoef O Ataque que o Personagem utilizou.
         * @return O coeficiente a ser usado para calcular o Dano do ataque.
         * 
         * Utilizado internamente para separar a lógica de calcular dano e coeficiente.
         * Apenas usado por calcularDano().
         *
        */
        static double calcularCoeficiente(const Personagem& personagem, AtributoCoef atributoCoef);
};

#endif