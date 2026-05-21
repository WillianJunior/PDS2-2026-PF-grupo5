#include "TrechoMapa.hpp"

TrechoMapa::TrechoMapa(int id, std::string descricao):_id(id), _cena(nullptr),_descricao(descricao),_aberto(false){

}

void TrechoMapa::abrirTrecho(){
    _aberto = true;
}

void TrechoMapa::adicionarItem(Item* item){
    _itens.push_back(item);
}

void TrechoMapa::adicionarNPC(Personagem* npc){
    _npcs.push_back(npc);
}

std::vector<Item*> TrechoMapa::pegarItens() const{
    return _itens;
}

std::vector<Personagem*> TrechoMapa::pegarNPCs() const{
    return _npcs;
}

bool TrechoMapa::estaAberto() const{
    return _aberto;
}
