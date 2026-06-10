#include <stdexcept>
#include <iostream>

#include "entities/items/Inventario.hpp"
#include "entities/character/Personagem.hpp"
#include "core/rules/RegrasItem.hpp"

// Construtor e destrutor
Inventario::Inventario() : _inicio(nullptr), _quantidade(0) {}

Inventario::~Inventario() {
    No* atual = _inicio;
    while (atual != nullptr) {
        No* proximo = atual->_proximo;
        delete atual->_item;
        delete atual;
        atual = proximo;
    }
}

// Manipulação de itens
void Inventario::adicionarItem(Item* item) {
    if (_quantidade >= _capacidadeMax)
        throw InventarioCheioException();

    No* novo = new No{item, nullptr};

    if (_inicio == nullptr) {
        _inicio = novo;
    } else {
        No* atual = _inicio;
        while (atual->_proximo != nullptr)
            atual = atual->_proximo;
        atual->_proximo = novo;
    }
    _quantidade++;
}

void Inventario::usarItem(int posicao, Personagem& personagem) {
    No* atual = _inicio;
    for (int i = 0; i < posicao; i++) {
        if (atual == nullptr) return;
        atual = atual->_proximo;
    }
    if (atual == nullptr) return;

    Item* item = atual->_item;
    RegrasItem::aplicarEfeito(*item, personagem);
    removerItem(posicao);
}

void Inventario::removerItem(int posicao) {
    if (_inicio == nullptr)
        return;

    if (posicao == 0) {
        No* removido = _inicio;
        _inicio = _inicio->_proximo;
        delete removido->_item;
        delete removido;
        _quantidade--;
        return;
    }

    No* anterior = _inicio;
    for (int i = 0; i < posicao - 1; i++) {
        if (anterior->_proximo == nullptr)
            return;
        anterior = anterior->_proximo;
    }

    No* removido = anterior->_proximo;
    if (removido == nullptr)
        return;
    anterior->_proximo = removido->_proximo;
    delete removido->_item;
    delete removido;
    _quantidade--;
}

bool Inventario::estaCheio() const { return _quantidade >= _capacidadeMax; }

int Inventario::quantidadeItens() const { return _quantidade; }

// Listagem e interface
void Inventario::listarItens() const {
    No* atual = _inicio;
    int i = 0;
    while (atual != nullptr) {
        std::cout << i << ": " << atual->_item->pegarNome()
                  << " — " << atual->_item->pegarDescricao() << "\n";
        atual = atual->_proximo;
        i++;
    }
}

void Inventario::fecharInventario() {}
