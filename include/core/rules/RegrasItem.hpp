/**
 * @file RegrasItem.hpp
 * @brief Encapsula a lógica de aplicação de efeitos de itens sobre personagens.
 *
 * Filha de Regras. Concentra os cálculos de efeito de cada categoria de item
 * (Comida, Poção, Cristal) sem conhecer Inventario ou Batalha.
 */

#ifndef REGRAS_ITEM_HPP
#define REGRAS_ITEM_HPP

#include "Regras.hpp"
#include "entities/items/Item.hpp"
#include "entities/character/Personagem.hpp"

/**
 * @class RegrasItem
 * @brief Calcula e aplica o efeito de um item sobre um Personagem.
 *
 * Todos os métodos são estáticos; a classe não possui estado próprio.
 */
class RegrasItem : public Regras {
public:
    /**
     * @brief Aplica o efeito do item sobre o personagem alvo.
     *
     * - Comida com valor positivo: chama recuperarVida().
     * - Comida com valor negativo: chama receberDano().
     * - Poção e Cristal: TODO; pendentes de refatoração em Personagem (Condicao / slot de equipamento).
     *
     * @param item   Item a ser aplicado.
     * @param personagem Personagem que receberá o efeito.
     */
    static void aplicarEfeito(const Item& item, Personagem& personagem);
};

#endif
