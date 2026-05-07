/**
 * @file TrechoMapa.hpp
 * @brief Definição da classe TrechoMapa, que representa uma área específica do mundo do jogo.
 */

#ifndef TRECHOMAPA_HPP
#define TRECHOMAPA_HPP

#include <string>
#include <vector>

#include "Item.hpp"
#include "Personagem.hpp"

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
    int _id;                 ///< Identificador único do trecho do mapa.
    Cena* _cena;             ///< Ponteiro para a Cena à qual este trecho pertence.
    std::string _descricao;  ///< Descrição da área, contendo detalhes do cenário.

    /**
     * @brief Lista de ponteiros para itens presentes no chão deste trecho.
     */
    std::vector<Item*> _itens; 

    /**
     * @brief Lista de ponteiros para NPCs (inimigos ou aliados) localizados nesse trecho.
     */
    std::vector<Personagem*> _npcs; 

public:
    /**
     * @brief Construtor da classe TrechoMapa.
     * @param id Identificador numérico.
     * @param descricao Descrição da área.
     */
    TrechoMapa(int id, std::string descricao);

    /**
     * @brief Ativa o trecho, exibindo a descrição e tornando NPCs e itens acessíveis ao jogador.
     */
    void abrirTrecho();

    /**
     * @brief Adiciona um novo item à lista de objetos espalhados pelo trecho.
     * @param item Ponteiro para o item a ser depositado.
     */
    void adicionarItem(Item* item);

    /**
     * @brief Insere um NPC na lista de personagens presentes na área.
     * @param npc Ponteiro para o personagem (NPC ou Boss).
     */
    void adicionarNPC(Personagem* npc);

    /**
     * @brief Recupera a lista de itens disponíveis para coleta.
     * @return Vetor de ponteiros para os itens.
     */
    std::vector<Item*> pegarItens() const;

    /**
     * @brief Recupera a lista de NPCs presentes para interação ou batalha.
     * @return Vetor de ponteiros para os NPCs.
     */
    std::vector<Personagem*> pegarNPCs() const;

};

#endif