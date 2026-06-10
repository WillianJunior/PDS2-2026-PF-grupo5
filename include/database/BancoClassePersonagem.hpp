#ifndef BANCOCLASSEPERSONAGEM_HPP
#define BANCOCLASSEPERSONAGEM_HPP

#include "entities/character/ClassePersonagem.hpp"

class BancoClassePersonagem {
    public: 
    static void defineClasse(TipoClasse tipo, ClassePersonagem& classePersonagem);
    static std::array<Ataque,3>  defineAtaques(TipoClasse tipo);
    static std::array<Ataque, 4> getAtaquesFortesPossiveis(TipoClasse tipo);
};

#endif