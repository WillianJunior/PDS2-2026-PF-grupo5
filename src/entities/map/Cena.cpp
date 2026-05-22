/**
 * @file Cena.cpp
 * @brief Implementação da classe Cena
 */
#include "entities/map/Cena.hpp"

/**
 * @brief Construtor da classe Cena.
 */
Cena::Cena(int nivel, TrechoMapa* trecho):_nivel(nivel),_trechoAtual(trecho), _inventarioAberto(false),_emBatalha(false),_explorando(true){

}

/**
 * @brief Inicializa a cena
 */
void Cena::iniciarCena(){
}

/**
 * @brief Finaliza a cena.
 */
void Cena::finalizarCena(){
}

/**
 * @brief Verifica a continuidade da cena
 */
bool Cena::verificarContinuidade() const{
    return false;
}

/**
 * @brief Gerencia a movimentação no mapa.
 */
void Cena::andar(){

}

/**
 * @brief Permite vasculhar o trecho atual do mapa.
 */
void Cena::vasculhar(){

}

/**
 * @brief Realiza as interações com os NPCs de diálogo
 */
void Cena::interagirNPCs(){

}

/**
 * @brief Abre o inventário do jogador
 */
void Cena::abrirInventario(){

}

/**
 * @brief Inicializa uma batalha
 */
void Cena::iniciarBatalha(){

}

/**
 * @brief Retorna se o inventário está aberto.
 */
bool Cena::inventarioAberto() const{
    return _inventarioAberto;
}

/**
 * @brief Retorna se o player está em batalha.
 */
bool Cena::emBatalha() const{
    return _emBatalha;
}

/**
 * @brief Retorna se o jogador está explorando (vasculhando, andando, interagindo com NPCs)
 */
bool Cena::explorando() const{
    return _explorando;
}