/**
 * @file BancoCena.hpp
 * @brief Fábrica estática de definições de cena e informações por ID.
 */

#ifndef INFO_CENA_HPP
#define INFO_CENA_HPP

#include "database/StructCena.hpp"

/**
 * @brief Classe de acesso aos dados da tabela de cenas
 *
 * Encapsula a lógica de obtenção de informações de cena a partir do ID.
 */
class BancoCena {
public:
    /**
     * @brief Recupera os dados de uma cena pelo seu identificador
     * @param id Identificador único da cena
     * @return Estrutura InfoCena com os dados da cena
     */
    static InfoCena obterCena(int id);
};

#endif