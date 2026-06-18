/**
 * @file BancoNpcInteracao.hpp
 * @brief Banco estático contendo os NPCs de interação do jogo.
 */

#ifndef BANCO_NPC_INTERACAO_HPP
#define BANCO_NPC_INTERACAO_HPP

#include "database/StructNpcInteracao.hpp"

/**
 * @class BancoNPCInteracao
 * @brief Banco estático contendo todos os NPCs de interação do jogo.
 */
class BancoNPCInteracao {
public:

    /**
     * @brief Retorna os dados de um NPC.
     * @param id ID do NPC.
     * @return Estrutura contendo os dados do NPC.
     * @throw std::runtime_error Caso o NPC não exista.
     */
    static InfoNPCInteracao obterNPC(int id);
};

#endif