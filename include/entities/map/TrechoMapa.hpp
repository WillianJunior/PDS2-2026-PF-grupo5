/**
 * @file TrechoMapa.hpp
 * @brief Definição da classe TrechoMapa, que representa uma área específica do mundo do jogo.
 */

#ifndef TRECHOMAPA_HPP
#define TRECHOMAPA_HPP

#include <string>
#include <vector>

#include "database/StructTrechoMapa.hpp"

// Evita a dependência circular com Cena (Forward Declaration).
class Cena;

/**
 * @class TrechoMapa
 * @brief Representa um segmento geográfico do mapa contendo itens e NPCs.
 * É responsável por armazenar os itens e os NPCs de uma área específica, 
 * permitindo a interação do jogador com o ambiente.
 */
class TrechoMapa {
private:

    /**
     * @brief Dados fixos do trecho carregados do banco.
     */
    InfoTrechoMapa _dados;

     /**
     * @brief Indica se o trecho está aberto.
     */
    bool _aberto;

    int _itensEncontrados;

    int _inimigosDerrotados;

public:
     /**
     * @brief Construtor.
     * @param dados Informações do trecho.
     */
    TrechoMapa(const InfoTrechoMapa& dados);

    /**
     * @brief Marca o trecho como aberto.
     */
    void abrirTrecho();

    bool estaAberto() const;

    bool possuiItensRestantes() const;

    bool possuiInimigosRestantes() const;

    void registrarItemEncontrado();

    void registrarInimigoDerrotado();

    int pegarItensRestantes() const;

    int pegarInimigosRestantes() const;

    /**
     * @brief Retorna o ID do trecho.
     */
    int pegarId() const;

    /**
     * @brief Retorna a descrição.
     */
    std::string pegarDescricao() const;

    /**
     * @brief Retorna os NPCs de interação.
     */
    int pegarNPCInteracao() const;

    /**
     * @brief Retorna os próximos trechos.
     */
    int pegarProximoTrecho() const;

    /**
     * @brief Retorna o trecho anterior.
     */
    int pegarTrechoAnterior() const;
};

#endif