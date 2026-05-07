/**
 * @file Cena.hpp
 * @brief Definição da classe Cena, responsável por iniciar e gerenciar a exploração e os eventos de uma cena (um "capítulo") do jogo.
 */

#ifndef CENA_HPP
#define CENA_HPP

#include "TrechoMapa.hpp"
#include "Batalha.hpp"

/**
 * @class Cena
 * @brief Gerencia o fluxo de jogo em um capítulo específico.
 * A classe Cena controla a interação do jogador com o mapa, NPCs e a transição para o motor de batalha. 
 */
class Cena {
private:
    /** 
     * @brief Nível da cena atual.
     */
    int _nivel;

    /** 
     * @brief Ponteiro para o trecho do mapa que está sendo explorado.
     * @note A Cena colabora com TrechoMapa para gerenciar o cenário atual.
     */
    TrechoMapa* _trechoAtual;

public:
    /**
     * @brief Construtor da classe Cena.
     * @param nivel O nível inicial da cena.
     * @param trecho Ponteiro para o trecho do mapa que será explorado.
     */
    Cena(int nivel, TrechoMapa* trecho);

    /**
     * @brief Inicializa os recursos da cena (mapa, NPCs e eventos).
     */
    void iniciarCena();

    /**
     * @brief Finaliza a cena e libera os recursos alocados.
     */
    void finalizarCena();

    /**
     * @brief Verifica se o jogador ainda pode progredir na cena atual.
     * @return true se houver continuidade, false se a cena deve ser encerrada.
     * @note O jogador pode progredir se ainda houver interações com itens e/ou 
     * NPCs no trecho de mapa atual ou outros trechos de mapa ainda não explorados.
     */
    bool verificarContinuidade() const;

    /**
     * @brief Gerencia a movimentação do personagem pelo trecho do mapa.
     */
    void andar();

    /**
     * @brief Permite ao jogador buscar itens ou decobrir NPCs no cenário.
     */
    void vasculhar();

    /**
     * @brief Inicia o diálogo ou interação com os NPCs presentes no trecho.
     */
    void interagirNPCs();

    /**
     * @brief Abre a interface de gerenciamento de itens do jogador.
     */
    void abrirInventario();

    /**
     * @brief Migra o fluxo de jogo para o combate em turnos.
     */
    void iniciarBatalha();

};

#endif