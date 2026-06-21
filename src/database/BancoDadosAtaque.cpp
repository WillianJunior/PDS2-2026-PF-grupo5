#include "database/BancoDadosAtaque.hpp"

const std::map<IdAtaque, DadosAtaque>
BancoDadosAtaque::ataques = {
    //Ataque Simples
    { IdAtaque::Flecha, {1, 8, AtributoCoef::Ataque} },
    { IdAtaque::Espada, {1, 8, AtributoCoef::Ataque} },
    { IdAtaque::Truque, {1, 10, AtributoCoef::Ataque}},
    { IdAtaque::Escudo, {1, 6, AtributoCoef::Ataque}},

    //Ataque Rapido
    { IdAtaque::TiroRapido, {1, 4, AtributoCoef::Ataque, false, 2} },
    { IdAtaque::GolpeRelampago, {1, 4, AtributoCoef::Ataque, false, 2} },
    { IdAtaque::ProjetilArcano, {1, 6, AtributoCoef::Ataque} },
    { IdAtaque::Investida, {1, 6, AtributoCoef::Defesa} },

    //Ataque Forte - Arqueiro
    { IdAtaque::FlechaExplosiva, {2, 8, AtributoCoef::Ataque} },
    { IdAtaque::TiroCerteiro, {2, 10, AtributoCoef::Ataque} },
    { IdAtaque::Saraivada, {5, 4, AtributoCoef::Ataque} },
    { IdAtaque::TiroFinal, {1, 6, AtributoCoef::Agilidade, true} },

    //Ataque Forte - Guerreiro
    { IdAtaque::FuriaBerserker, {3, 6, AtributoCoef::Ataque} },
    { IdAtaque::GolpeDevastador, {2, 10, AtributoCoef::Ataque} },
    { IdAtaque::Perfuracao, {2, 8, AtributoCoef::Ataque} },
    { IdAtaque::GolpeDoAbismo, {1, 10, AtributoCoef::Ataque, true} },

    //Ataque Forte - Mago
    { IdAtaque::BolaDeFogo, {4, 6, AtributoCoef::Ataque} },
    { IdAtaque::Raio, {2, 10, AtributoCoef::Ataque} },
    { IdAtaque::DrenoDaMagia, {1, 8, AtributoCoef::Ataque} },
    { IdAtaque::VorticeArcano, {1, 6, AtributoCoef::Ataque, true} },

    //Ataque Forte - Tanque
    { IdAtaque::PancadaDeEscudo, {1, 10, AtributoCoef::Defesa} },
    { IdAtaque::Terremoto, {2, 6, AtributoCoef::Defesa} },
    { IdAtaque::BarreiraDeEspinhos, {1, 8, AtributoCoef::Defesa} },
    { IdAtaque::Martirio, {1, 8, AtributoCoef::Defesa, true} },
};

const DadosAtaque& BancoDadosAtaque::getDadosAtaque(IdAtaque id) {
    auto it = ataques.find(id);
    if (it == ataques.end()) {
        throw std::runtime_error("Ataque nao encontrado");
    }
    return it->second;
}
