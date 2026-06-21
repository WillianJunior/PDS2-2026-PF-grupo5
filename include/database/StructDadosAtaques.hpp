/**
 * @file StructDadosAtaques.hpp
 * @brief Enums para definir os calculos do Dano de um Ataque.
 *
 * Utilizado em RegrasAtaque e Batalha.
 */

#ifndef STRUCT_DADOS_ATAQUE_HPP
#define STRUCT_DADOS_ATAQUE_HPP

/**
 * @class AtributoCoef
 * @brief Define os tipos de Coeficientes que um Ataque utiliza em seu calculo.
 */
enum class AtributoCoef {
    Ataque,
    Defesa,
    Agilidade
};

/**
 * @struct DadosAtaque
 * @brief Define todos os dados que um Ataque precisa para calcular seu Dano.
 */
struct DadosAtaque {
    int quantidadeDados;          //< A quantidade de dados usados no calculo.
    int faces;                    //< A quantidade de faces que o dado(s) possuem.
    AtributoCoef atributoCoef;    //< O tipo de Coeficiente que esse Ataque utiliza.
    bool dadosPorNivel = false;   //< Define se o calculo utiliza o nivel como a quantidade dados.
    int numeroDeExecucoes = 1;    //< Define quantas vezes o ataque e executado.
};

#endif
