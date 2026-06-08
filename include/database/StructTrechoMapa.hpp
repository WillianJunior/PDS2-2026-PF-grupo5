#ifndef STRUCT_TRECHO_MAPA_HPP
#define STRUCT_TRECHO_MAPA_HPP
#include <string>
#include <vector>

struct InfoTrechoMapa{
    int id; //id do trecho

    std::string descricao;

    int npcInteracao; //id do npc de interação

    int quantidadeItens; //numero de itens presente no trecho
    int quantidadeInimigos; //numero de inimigos presente no trecho;

    int proximoTrecho; //id do proximo trecho

    int trechoAnterior; //id do trecho anterior
};


#endif