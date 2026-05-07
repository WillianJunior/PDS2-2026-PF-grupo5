#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Item.hpp"
#include "Personagem.hpp"

class Inventario {
private:
    struct No {
        Item* _item;
        No* _proximo;
    };
    
    No* _inicio;
    int _quantidade;
    static const int _capacidadeMax = 8; //quantidade maxima de slots (8)

public:
    Inventario();
    ~Inventario();

    bool adicionarItem(Item* item); //retorna se foi possível adicionar, ou se o inventário está cheio
    void usarItem(int posicao, Personagem& personagem); //usa o item da posição indicada no personagem informado
    void removerItem(int posicao); 

    bool estaCheio() const;  //para testes
    int quantidadeItens() const;
    void listarItens() const;
    void fecharInventario();
};

#endif