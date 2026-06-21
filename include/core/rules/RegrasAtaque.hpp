/**
 * @file RegrasAtaque.hpp
 * @brief Define toda a logica do Calculo de Ataques.
 *
 *  Utilizado por Batalha para Calcular o Dano de um Ataque.
 *  O Dano de um Ataque e calculado a partir do seu tipo e IdAtaque.
 *
 *  @see regras.md - Secao 2.2, 2.3 e 2.4
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
 * @brief Calcula o dano dos ataques, considerando comportamento unico.
 */
class RegrasAtaque : public Regras {
    public:
        static double calcularDano(const Personagem& personagem, const Ataque& ataque,
            std::optional<unsigned int> seed = std::nullopt);

        static int getExecucoes(const Personagem& personagem, const Ataque& ataque);

    private:
        static double calcularCoeficiente(const Personagem& personagem, AtributoCoef atributoCoef);

        static int regraPorNivel(int nivel, std::array<int, 4> faixas);
};

#endif
