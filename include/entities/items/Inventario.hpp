/**
 * @file Inventario.hpp
 * @brief Definição da classe Inventario para gestão de itens dos personagens.
 */

#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Item.hpp"
#include "Personagem.hpp"

/**
 * @class Inventario
 * @brief Classe responsável pelo armazenamento e gerenciamento de itens.
 * Possui uma capacidade limitada e permite que o personagem armazene, use ou remova itens coletados durante o jogo.
 * @todo Revisitar essa estrutura, pois pode ser interessante usarmos uma estrutura mais eficiente de dados, como um vetor ou um array.
 */
class Inventario {
private:
    struct No {
        Item* _item;    ///< Ponteiro para o item armazenado neste nó.
        No* _proximo;   ///< Ponteiro para o próximo item armazenado na lista.
    };
    
    No* _inicio;
    int _quantidade;    ///< Contador de itens atualmente armazenados.
    static const int _capacidadeMax = 8; ///< Capacidade máxima do inventário.

public:
    /**
     * @brief Construtor padrão da classe Inventario.
     */
    Inventario();

    /**
     * @brief Destrutor da classe Inventario.
     */
    ~Inventario();

    /**
     * @brief Tenta adicionar um item ao primeiro slot disponível.
     * @param item Ponteiro para o item a ser adicionado.
     * @throw InventarioCheioException quando a quantidade de itens atinge a capacidade máxima permitida (8).
     * @note Se a exceção for lançada, o chamador deverá ser responsável por liberar a memória do item.
     */
    void adicionarItem(Item* item);

    /**
     * @brief Realiza o uso de um item em um personagem alvo.
     * @param posicao Índice do item no inventário.
     * @param personagem Referência do personagem que receberá o efeito.
     */
    void usarItem(int posicao, Personagem& personagem);

    /**
     * @brief Remove permanentemente um item do inventário.
     * @param posicao Índice do item a ser removido.
     */
    void removerItem(int posicao); 

    /**
     * @brief Verifica se a capacidade máxima foi atingida.
     * @return true se cheio, false caso contrário.
     */
    bool estaCheio() const;

    /**
     * @brief Retorna o número atual de itens armazenados.
     * @return Inteiro representando a quantidade.
     */
    int quantidadeItens() const;

    /**
     * @brief Exibe no console a lista de itens e suas descrições.
     */
    void listarItens() const;

    /**
     * @brief Finaliza as operações do inventário e limpa a interface.
     */
    void fecharInventario();
};

#endif