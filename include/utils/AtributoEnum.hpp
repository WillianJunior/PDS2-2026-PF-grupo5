/**
 * @file AtributoEnum.hpp
 * @brief Enum tipado para os atributos do personagem.
 *
 * Atributos definidos em regras.md seção 1.5.
 * Utilizado em classes variadas para evitar comparações por string.
 */

#ifndef ATRIBUTO_ENUM_HPP
#define ATRIBUTO_ENUM_HPP

/**
 * @enum Atributo
 * @brief Identifica um atributo de Personagem.
 */
enum class Atributo {
    Nenhum,    ///< Valor default
    Ataque,    ///< Pontuação de ataque — afeta rolagens de acerto e dano.
    Defesa,    ///< Pontuação de defesa — determina PV base por nível.
    Agilidade, ///< Pontuação de agilidade — determina iniciativa e CD.
    Poder      ///< Pontos de Poder (PP) — recursos para habilidades especiais.
};

#endif
