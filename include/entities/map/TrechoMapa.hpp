#ifndef TRECHOMAPA_HPP
#define TRECHOMAPA_HPP

#include <string>
#include <vector>

#include "Item.hpp"
#include "Personagem.hpp"
#include "Cena.hpp"

class TrechoMapa{
private:
    int _id;
    Cena* _cena;
    std::string _descricao;


    std::vector<Item*> _itens; //lista dos itens da cena
    std::vector<Personagem*> _npcs; //lista dos NPCs da cena
public:
    TrechoMapa(int id, std::string descricao);

    void abrirTrecho();

    void adicionarItem(Item* item);
    void adicionarNPC(Personagem* npc);

    std::vector<Item*> pegarItens() const; //retorna os itens do trecho
    std::vector<Personagem*> pegarNPCs() const; //retorna os NPCs do trecho

};

#endif