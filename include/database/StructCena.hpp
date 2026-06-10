#ifndef STRUCT_CENA_HPP
#define STRUCT_CENA_HPP

#include <string>
#include <vector>

/**
 * @struct InfoCena
 * @brief Representa os dados de uma cena do jogo.
 */
struct InfoCena {
    int id;                     ///< Identificador único da cena.
    std::string arcano;         ///< Nome do Arcano concedido ao concluir a cena.
    std::string recompensa;     ///< Descrição da recompensa da cena.
    std::string descricao;      ///< Texto descritivo da cena.
    int trechoInicial;          ///< ID do trecho inicial dessa cena.
    std::vector<int> trechos;   ///< IDs dos trechos que pertencem à cena.
};

#endif