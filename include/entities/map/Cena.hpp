/**
 * @file Cena.hpp
 * @brief Definição da classe Cena, responsável por iniciar e gerenciar a exploração e os eventos de uma cena (um "capítulo") do jogo.
 */

#ifndef CENA_HPP
#define CENA_HPP

#include "../map/TrechoMapa.hpp"
#include "../battle/Batalha.hpp"
#include "../character/Jogador.hpp"
#include "../../database/StructCena.hpp"

#include <memory>

/**
 * @class Cena
 * @brief Gerencia o fluxo de jogo em um capítulo específico.
 * A classe Cena controla a interação do jogador com o mapa, NPCs e a transição para o motor de batalha. 
 */
class Cena {
private:
    /**
     * @brief Dados permanentes da cena.
     */
    InfoCena _dadosCena;

    /**
     * @brief Referência ao jogador que está explorando a cena.
     */
    Jogador& _jogador;

    /**
     * @brief Trecho atualmente explorado pelo jogador.
     */
    std::unique_ptr<TrechoMapa> _trechoAtual;

     /** 
     * @brief Indica se o inventário está aberto.
     */
    bool _inventarioAberto;

    /** 
     * @brief Indica se o jogador está em batalha.
     */
    bool _emBatalha;

    /** 
     * @brief Indica se o jogador está explorando o mapa.
     */
    bool _explorando;

public:
     /**
     * @brief Construtor da cena.
     * @param dados Estrutura contendo as informações da cena.
     * @param jogador Referência ao jogador que explorará a cena.
     */
    Cena(const InfoCena& dados, Jogador& jogador);

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

     /**
     * @brief Troca o trecho atual.
     * @param idTrecho ID do novo trecho.
     */
    void mudarTrecho(int idTrecho);

    /**
     * @brief Retorna o ID da cena.
     */
    int pegarId() const;

    /**
     * @brief Retorna o arcano associado à cena.
     */
    std::string pegarArcano() const;

    /**
     * @brief Retorna o trecho atual.
     */
    const TrechoMapa& pegarTrechoAtual() const;

    /**
     * @brief Retorna se o inventário está aberto.
     */
    bool inventarioAberto() const;

    /**
     * @brief Retorna se o jogador está em batalha.
     */
    bool emBatalha() const;

    /**
     * @brief Retorna se o jogador está explorando.
     */
    bool explorando() const;

};

#endif