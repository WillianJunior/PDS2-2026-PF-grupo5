/**
 * @file TrechoMapa.cpp
 * @brief Implementação da classe TrechoMapa
 */

#include "TrechoMapa.hpp"

/**
 * @brief Construtor da classe TrechoMapa.
 * Inicializa os atributos básicos do trecho
 */
TrechoMapa::TrechoMapa(int id, std::string descricao):_id(id), _cena(nullptr),_descricao(descricao),_aberto(false){

}
/**
 * @brief Marca o trecho como aberto.
 */
void TrechoMapa::abrirTrecho(){
    
}

/**
 * @brief Adiciona um item ao trecho.
 */
void TrechoMapa::adicionarItem(Item* item){
    
}

/**
 * @brief Adiciona um NPC ao trecho
 */
void TrechoMapa::adicionarNPC(Personagem* npc){
    
}

/**
 * @brief Retorna os itens presentes no trecho
 */
std::vector<Item*> TrechoMapa::pegarItens() const{
    return {};
}

/**
 * @brief Retorna os NPCs presentes no trecho.
 */
std::vector<Personagem*> TrechoMapa::pegarNPCs() const{
    return {};
}

/**
 * @brief Verifica se o trecho já foi aberto.
 */
bool TrechoMapa::estaAberto() const{
    return {};
}
