#include "entities/character/Jogador.hpp"

void Jogador::adicionarItem(Item* item) {
    _inventario.adicionarItem(item);
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
