/**
 * @file Jogador.cpp
 * @brief Implementação da classe Jogador — extensão de Personagem com inventário.
 */

#include "entities/character/Jogador.hpp"

void Jogador::adicionarItem(std::unique_ptr<Item> item) {
    _inventario.adicionarItem(std::move(item));
}

void Jogador::usarItem(int posicao) {
    _inventario.usarItem(posicao, *this);
}

Inventario& Jogador::getInventario() {
    return _inventario;
}

const Inventario& Jogador::getInventario() const {
    return _inventario;
}
