#ifndef STRUCT_NPC_INTERACAO_HPP
#define STRUCT_NPC_INTERACAO_HPP

#include <string>

/**
 * @struct InfoNPCInteracao
 * @brief Representa os dados de um NPC de interação.
 */
struct InfoNPCInteracao {
    int id;                         ///< Identificador único do NPC.
    std::string nome;               ///< Nome do NPC.
    std::string descricaoFisica;    ///< Aparência física do NPC.
    std::string fala;               ///< Texto falado durante a interação.
};

#endif