/**
 * @file Jogador.hpp
 * @brief Definição da classe Jogador, especialização de Personagem com inventário.
 */

#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagem.hpp"
#include "entities/items/Inventario.hpp"
#include "entities/items/Item.hpp"

/**
 * @class Jogador
 * @brief Personagem controlado pelo usuário, com capacidade de carregar itens.
 *
 * Herda todos os atributos e comportamentos de Personagem e acrescenta
 * o gerenciamento de um Inventario exclusivo do jogador.
 */
class Jogador : public Personagem {
private:
    Inventario _inventario;

public:
    using Personagem::Personagem;

    /**
     * @brief Adiciona um item ao inventário do jogador.
     * @param item Ponteiro para o item. O Inventario assume a posse e o deleta quando necessário.
     * @throw InventarioCheioException se o inventário estiver cheio.
     */
    void adicionarItem(Item* item);

    /**
     * @brief Usa o item na posição indicada sobre si mesmo e o remove do inventário.
     * @param posicao Índice do item no inventário.
     */
    void usarItem(int posicao);

    /** @return Referência ao inventário do jogador. */
    Inventario& getInventario();

    /** @return Referência constante ao inventário do jogador. */
    const Inventario& getInventario() const;
};

#endif
