/**
 * @file BancoDadosAtaque.hpp
 * @brief Repositório estático definindo os dados de um Ataque para calculo do Dano.
 * Usado por RegrasAtaque.
 * @see regras.md 2.2, 2.3 e 2.4 - Define os dados, coeficientes e multiplicações.
 * @see IdAtaque.hpp - Define todos os Ataques possiveis.
 * @see StructDadosAtaque.hpp - Define a estrutura dos dados necessario de um Ataque.
 */

#ifndef BANCODADOSATAQUE_HPP
#define BANCODADOSATAQUE_HPP

#include "StructDadosAtaques.hpp"
#include "utils/AtaqueEnum.hpp"
#include <stdexcept>
#include <map>


/**
 * @class BancoDadosAtaque
 * @brief Fornece dados sobre o calculo do dano dos Ataques.
 *
 */
class BancoDadosAtaque {
    public:
        /**
         * @brief Retorna os dados de um Ataque para calculo de dano.
         * @param id ID do Ataque.
         * @return Estrutura contendo os dados do Ataque.
         * @throw std::runtime_error Caso o Ataque não exista.
         */
        static const DadosAtaque& getDadosAtaque(IdAtaque id);

    private:
        /**
         * @brief Contêm todos os dados de um Ataque para calculo de dano.
         * IdAtaque como chave para procura.
         * DadosAtaque possui todos os dados do Ataque.
         */
        static const std::map<IdAtaque, DadosAtaque> ataques;
};

#endif