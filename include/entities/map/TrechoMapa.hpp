/**
 * @file TrechoMapa.hpp
 * @brief Definição da classe TrechoMapa, que representa uma área específica do mundo do jogo.
 */

#ifndef TRECHOMAPA_HPP
#define TRECHOMAPA_HPP

#include <string>
#include <vector>

#include "database/StructTrechoMapa.hpp"
#include "entities/items/Item.hpp"

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

    int sortearItem() const;

    /**
     * @brief Gera o próximo item do trecho, incrementando a contagem.
     * Delega a criação do item a Item::gerarItem usando o cenaId do trecho.
     * @return Item gerado.
     * @throw std::runtime_error se não houver itens restantes.
     */
    Item gerarItem();

    void registrarItemEncontrado();

    int pegarItensRestantes() const;

    bool possuiInimigo() const;
    int pegarIdInimigo() const;

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