/**
 * @file AtributoEnum.hpp
 * @brief Enum para identificar atributos de personagem.
 */

#ifndef ATRIBUTO_ENUM_HPP
#define ATRIBUTO_ENUM_HPP

enum class Atributo {
    Nenhum,
    Ataque,    ///< Pontuação de ataque.
    Defesa,    ///< Pontuação de defesa.
    Agilidade, ///< Pontuação de agilidade — determina iniciativa e CD.
    Poder      ///< Pontos de Poder (PP) — recursos para habilidades especiais.
};

#endif // ATRIBUTO_ENUM_HPP
