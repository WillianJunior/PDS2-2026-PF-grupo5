#include "include/database/BancoDadosAtaque.hpp"

/**
 * Estrutura:
 * {IdAtaque, {quantidadeDeDados, quantidadeDeLados, AtributoCoef, escalaComNivel*, multiplicador*}}
 * * - Opcional
 */

const std::map<IdAtaque, DadosAtaque>
BancoDadosAtaque::ataques = {
    //Ataque Simples
    { IdAtaque::Flecha, {1, 8, AtributoCoef::Nenhum} },               //< Arqueiro
    { IdAtaque::Espada, {1, 8, AtributoCoef::Nenhum} },               //< Guerreiro
    { IdAtaque::Truque, {1, 6, AtributoCoef::Nenhum} },               //< Mago
    { IdAtaque::Escudo, {1, 10, AtributoCoef::Nenhum}},               //< Tank


    //Ataque Rapido
    { IdAtaque::TiroRapido, {1, 4, AtributoCoef::Ataque, 2.0} },      //< Arqueiro
    { IdAtaque::GolpeRelampago, {1, 4, AtributoCoef::Ataque, 2.0} },  //< Guerreiro
    { IdAtaque::ProjetilArcano, {1, 6, AtributoCoef::Ataque} },       //< Mago
    { IdAtaque::Investida, {1, 6, AtributoCoef::Defesa} },            //< Tank
    
    //Ataque Forte
    //Arqueiro
    { IdAtaque::FlechaExplosiva, {2, 8, AtributoCoef::Ataque} },      //< Ataque Forte 1
    { IdAtaque::TiroCerteiro, {2, 10, AtributoCoef::Ataque} },        //< Ataque Forte 2
    { IdAtaque::Saraivada, {5, 4, AtributoCoef::Ataque} },            //< Ataque Forte 3
    { IdAtaque::TiroFinal, {1, 6, AtributoCoef::Agilidade, true}, },  //< Ataque Forte 4
    
    //Guerreiro
    { IdAtaque::FuriaBerserker, {3, 6, AtributoCoef::Ataque} },       //< Ataque Forte 1
    { IdAtaque::GolpeDevastador, {2, 10, AtributoCoef::Ataque} },     //< Ataque Forte 2
    { IdAtaque::Perfuracao, {2, 8, AtributoCoef::Ataque} },           //< Ataque Forte 3
    { IdAtaque::GolpeDoAbismo, {1, 10, AtributoCoef::Ataque, true} }, //< Ataque Forte 4

    //Mago
    { IdAtaque::BolaDeFogo, {4, 6, AtributoCoef::Ataque} },           //< Ataque Forte 1
    { IdAtaque::Raio, {2, 10, AtributoCoef::Ataque} },                //< Ataque Forte 2
    { IdAtaque::DrenoDaMagia, {1, 8, AtributoCoef::Ataque} },         //< Ataque Forte 3
    { IdAtaque::VorticeArcano, {1, 6, AtributoCoef::Ataque, true} },  //< Ataque Forte 4

    //Tanque
    { IdAtaque::PancadaDeEscudo, {1, 10, AtributoCoef::Defesa} },     //< Ataque Forte 1
    { IdAtaque::Terremoto, {2, 6, AtributoCoef::Defesa} },            //< Ataque Forte 2
    { IdAtaque::BarreiraDeEspinhos, {1, 8, AtributoCoef::Defesa} },   //< Ataque Forte 3
    { IdAtaque::Martirio, {1, 8, AtributoCoef::Defesa, true} },       //< Ataque Forte 4
    
};

const DadosAtaque& BancoDadosAtaque::getDadosAtaque(IdAtaque id) {
    auto it = ataques.find(id);
    if (it == ataques.end()) {
        throw std::runtime_error("Ataque não encontrado");
    }

    return it->second;
}
