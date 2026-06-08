#include "include/database/BancoTrechoMapa.hpp"

InfoTrechoMapa BancoTrechoMapa::obterTrechoMapa(int id){

    switch (id)
    {
    case 101:
        return{
            101, //id
            "", //descrição
            1, //id do NPC de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            102, //id do proximo trecho
            101, //id do trecho anterior
        };
        break;
    
    case 102:
        return{
            102, //id
            "", //descrição
            2, //id dos NPC de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            103, //id do proximo trecho
            101, //id do trecho anterior
        };
        break;

    case 103:
        return{
            103, //id
            "", //descrição
            3, // id do NPC de interação
            3, //quantidade de itens no trecho
            2, //quantidade de inimigosno trecho
            104, //id do proximo trecho
            102, //id do trecho anterior
        };
        break;

    default:
        break;
    }




}