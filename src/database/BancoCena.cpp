/**
 * @file BancoCena.cpp
 * @brief Repositório estático de cenas do jogo (7 cenas — 7 arcanos).
 * Retorna InfoCena por ID; lança std::invalid_argument para IDs inválidos.
 */

#include "database/BancoCena.hpp"
#include <stdexcept>

InfoCena BancoCena::obterCena(int id){

    if(id <= 0){
    throw std::invalid_argument(
        "ID de cena invalido"
    );
    }

    switch (id)
    {
    case 1:
        return{
            1,  //id
            "Poder do primeiro arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            101, //id do trechoMapa inicial da cena
            {101,102,103} //vetor com os ids dos trechos de mapa que compões a cena

        };
    
    case 2:
        return{
            2,  //id
            "Poder do segundo arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            201, //id do trechoMapa inicial da cena
            {201,202,203} //vetor com os ids dos trechos de mapa que compões a cena

        };

    case 3:
        return{
            3,  //id
            "Poder do terceiro arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            301, //id do trechoMapa inicial da cena
            {301,302,303} //vetor com os ids dos trechos de mapa que compões a cena

        };

    case 4:
        return{
            4,  //id
            "Poder do quarto arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            401, //id do trechoMapa inicial da cena
            {401,402,403} //vetor com os ids dos trechos de mapa que compões a cena

        };

    case 5:
        return{
            5,  //id
            "Poder do quinto arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            501, //id do trechoMapa inicial da cena
            {501,502,503} //vetor com os ids dos trechos de mapa que compões a cena

        };

    case 6:
        return{
            6,  //id
            "Poder do sexto arcano", //arcano
            "", //recompensa entregue no final da cena
            "", //descricao da cena
            601, //id do trechoMapa inicial da cena
            {601,602,603} //vetor com os ids dos trechos de mapa que compões a cena

        };

    case 7:
        return{
            7,  //id
            "Poder de todos os arcanos", //arcano
            "", //recompensa entregue no final da cena
            "Cena final", //descricao da cena
            701, //id do trechoMapa inicial da cena
            {701,702,703} //vetor com os ids dos trechos de mapa que compões a cena

        };

    default:
        throw std::invalid_argument("Cena com id desconhecido: " + std::to_string(id));
    }
}