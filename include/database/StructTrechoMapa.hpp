#ifndef STRUCT_TRECHO_MAPA_HPP
#define STRUCT_TRECHO_MAPA_HPP
#include <string>
#include <vector>

struct InfoTrechoMapa{
    int id; //id do trecho

    std::string descricao;

    std::vector<int> NPCsInteracao; //vetor de id dos npcs de interação do trecho

    int quantidadeItens; //numero de itens presente no trecho
    int quantidadeInimigos; //numero de inimigos presente no trecho;

    std::vector<int> proximosTrechos; //trechos que este trecho libera

    int trechoAnterior; //id do trecho anterior
};


#endif