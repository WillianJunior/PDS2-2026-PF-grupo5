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
#include <string>

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
     * @throw std::invalid_argument Caso os dados da cena sejam inválidos.
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
     * @brief Gerencia a movimentação do personagem pelo trecho do mapa.
     * @throw std::runtime_error Caso não exista trecho carregado.
     */
    void andar();

    /**
     * @brief Permite ao jogador buscar itens ou decobrir NPCs no cenário.
     * @throw std::runtime_error Caso não exista trecho carregado.
     */
    void vasculhar();

    /**
     * @brief Descarta o próximo item do trecho sem adicioná-lo ao inventário.
     * Avança o contador de itens encontrados sem entregar o item ao jogador.
     * @throw std::runtime_error Caso não exista trecho carregado.
     */
    void descartarItem();

    /**
     * @brief Inicia o diálogo ou interação com os NPCs presentes no trecho.
     * @throw std::runtime_error Caso não exista trecho carregado.
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
     * @throw std::invalid_argument Caso o ID do trecho seja inválido.
     */
    void mudarTrecho(int idTrecho);

    /**
     * @brief Retorna o ID da cena.
     * @return Identificador único da cena.
     */
    int pegarId() const;

    /**
     * @brief Retorna o arcano associado à cena.
     * @return Nome do arcano da cena.
     */
    std::string pegarArcano() const;

    /**
     * @brief Retorna o trecho atual.
     * @return Referência para o trecho atual.
     * @throw std::runtime_error Caso nenhum trecho tenha sido carregado.
     */
    const TrechoMapa& pegarTrechoAtual() const;

    /**
     * @brief Retorna se o inventário está aberto.
     * @return true se o inventário estiver aberto, false caso contrário.
     */
    bool inventarioAberto() const;

    /**
     * @brief Retorna se o jogador está em batalha.
     * @return true se a cena estiver em batalha, false caso contrário.
     */
    bool emBatalha() const;

    /**
     * @brief Retorna se o jogador está explorando.
     * @return true se a cena estiver em modo de exploração, false caso contrário.
     */
    bool explorando() const;

};

#endif