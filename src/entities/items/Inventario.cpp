/**
 * @file Inventario.cpp
 * @brief Implementação da classe Inventario.
 *
 * Gestão de memória 100% via RAII: os nós e itens são donos de si mesmos
 * através de std::unique_ptr. O destrutor padrão é suficiente — nenhum
 * delete manual é necessário.
 */

#include <stdexcept>
#include <iostream>

#include "entities/items/Inventario.hpp"
#include "entities/character/Personagem.hpp"
#include "core/rules/RegrasItem.hpp"

// Construtor e destrutor
Inventario::Inventario() : _inicio(nullptr), _quantidade(0) {}

// Destrutor usa o padrão: unique_ptr encadeia a destruição dos nós.
// Com capacidade máxima de 8 itens, não há risco de stack overflow.
Inventario::~Inventario() = default;

// Manipulação de itens

void Inventario::adicionarItem(Item* item) {
    if (_quantidade >= _capacidadeMax)
        throw InventarioCheioException();

    auto novoNo = std::make_unique<No>();
    novoNo->_item    = std::unique_ptr<Item>(item); // assume ownership
    novoNo->_proximo = nullptr;

    if (_inicio == nullptr) {
        _inicio = std::move(novoNo);
    } else {
        No* atual = _inicio.get();
        while (atual->_proximo != nullptr)
            atual = atual->_proximo.get();
        atual->_proximo = std::move(novoNo);
    }
    _quantidade++;
}

void Inventario::usarItem(int posicao, Personagem& personagem) {
    if (posicao < 0 || posicao >= _quantidade)
        throw std::out_of_range("Posicao de item invalida no inventario.");

    No* atual = _inicio.get();
    for (int i = 0; i < posicao; i++)
        atual = atual->_proximo.get();

    RegrasItem::aplicarEfeito(*atual->_item, personagem);
    removerItem(posicao);
}

void Inventario::removerItem(int posicao) {
    if (_inicio == nullptr || posicao < 0 || posicao >= _quantidade)
        throw std::out_of_range("Posicao de item invalida no inventario.");

    if (posicao == 0) {
        // Move o _proximo para fora antes de destruir o nó raiz
        std::unique_ptr<No> removido = std::move(_inicio);
        _inicio = std::move(removido->_proximo);
        // removido sai do escopo e destrói apenas o nó e seu item
        _quantidade--;
        return;
    }

    No* anterior = _inicio.get();
    for (int i = 0; i < posicao - 1; i++) {
        if (anterior->_proximo == nullptr)
            throw std::out_of_range("Posicao de item invalida no inventario.");
        anterior = anterior->_proximo.get();
    }

    std::unique_ptr<No> removido = std::move(anterior->_proximo);
    anterior->_proximo = std::move(removido->_proximo);
    // removido sai do escopo e destrói apenas o nó e seu item
    _quantidade--;
}

bool Inventario::estaCheio() const { return _quantidade >= _capacidadeMax; }

int Inventario::quantidadeItens() const { return _quantidade; }

// Listagem e interface
void Inventario::listarItens() const {
    No* atual = _inicio.get();
    int i = 0;
    while (atual != nullptr) {
        std::cout << i << ": " << atual->_item->pegarNome()
                  << " — " << atual->_item->pegarDescricao() << "\n";
        atual = atual->_proximo.get();
        i++;
    }
}

void Inventario::fecharInventario() {}
