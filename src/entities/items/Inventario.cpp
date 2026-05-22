#include <stdexcept>

#include "entities/items/Inventario.hpp"
#include "entities/character/Personagem.hpp"

// Construtor e destrutor
Inventario::Inventario() : _inicio(nullptr), _quantidade(0) {}

Inventario::~Inventario() {}

// Manipulação de itens 
void Inventario::adicionarItem(Item* item) {}

void Inventario::usarItem(int posicao, Personagem& personagem) {}

void Inventario::removerItem(int posicao) {}

bool Inventario::estaCheio() const { return false; }

int Inventario::quantidadeItens() const { return 0; }

// Listagem e interface
void Inventario::listarItens() const {}

void Inventario::fecharInventario() {}
