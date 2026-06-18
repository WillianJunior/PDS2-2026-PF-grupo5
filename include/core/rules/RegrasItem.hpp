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
     * - **Comida**: rola dados conforme categoria (Regras.md §5.2):
     *   - _valor = qtdDados (positivo = cura, negativo = dano)
     *   - _duracao = ladosDado (6 ou 8)
     *   - Cria Dados internamente com semente aleatória.
     * - **Poção**: aplica ModAtributo temporário (Regras.md §5.3).
     * - **Cristal**: aplica condição de combate (Regras.md §5.4).
     *
     * @param item       Item a ser aplicado.
     * @param personagem Personagem que receberá o efeito.
     */
    static void aplicarEfeito(const Item& item, Personagem& personagem);
};

#endif
