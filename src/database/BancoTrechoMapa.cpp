#include "include/database/BancoTrechoMapa.hpp"

InfoTrechoMapa BancoTrechoMapa::obterTrechoMapa(int id){

    switch (id)
    {
    case 101:
        return{
            101, //id
            "", //descrição
            {}, //vetor de id dos NPCs de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            {}, //vetor de id dos proximos trechos
            101, //id do trecho anterior
        };
        break;
    
    case 102:
        return{
            102, //id
            "", //descrição
            {}, //vetor de id dos NPCs de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            {}, //vetor de id dos proximos trechos
            101, //id do trecho anterior
        };
        break;

    case 103:
        return{
            103, //id
            "", //descrição
            {}, //vetor de id dos NPCs de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            {}, //vetor de id dos proximos trechos
            102, //id do trecho anterior
        };
        break;

    default:
        break;
    }




}