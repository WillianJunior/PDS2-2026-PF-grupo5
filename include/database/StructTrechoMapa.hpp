/**
 * @file StructTrechoMapa.hpp
 * @brief Estrutura que armazena os dados de um trecho do mapa.
 */

#ifndef STRUCT_TRECHO_MAPA_HPP
#define STRUCT_TRECHO_MAPA_HPP
#include <string>
#include <vector>

/**
 * @struct InfoTrechoMapa
 * @brief Representa os dados de um trecho do mapa.
 */
struct InfoTrechoMapa {
    int id;                      ///< Identificador único do trecho.
    std::string descricao;       ///< Descrição narrativa do trecho.
    int npcInteracao;            ///< ID do NPC com o qual o jogador pode interagir.
    std::vector<int> idsItens;   ///< IDs dos itens disponíveis no trecho (BancoItem).
    bool existeInimigo;          ///< Bool que define se tem algum inimigo no trecho.
    int idInimigo;               ///< ID do inimigo caso presente no trecho.
    int proximoTrecho;           ///< ID do próximo trecho.
    int trechoAnterior;          ///< ID do trecho anterior.
    int cenaId;                  ///< ID da cena à qual este trecho pertence.
};

#endif