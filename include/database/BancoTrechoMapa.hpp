/**
 * @file BancoTrechoMapa.hpp
 * @brief Define o acesso estático aos dados de trechos de mapa.
 */

#ifndef INFO_TRECHO_MAPA_HPP
#define INFO_TRECHO_MAPA_HPP

#include "database/StructTrechoMapa.hpp"

/**
 * @class BancoTrechoMapa
 * @brief Recupera informações de um trecho do mapa pelo seu identificador.
 */
class BancoTrechoMapa {
public:
    /**
     * @brief Retorna os dados de um trecho de mapa.
     * @param id Identificador único do trecho.
     * @return Estrutura InfoTrechoMapa contendo os dados do trecho.
     */
    static InfoTrechoMapa obterTrechoMapa(int id);
};

#endif