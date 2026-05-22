#include "entities/character/ClassePersonagem.hpp"

ClassePersonagem::ClassePersonagem(TipoClasse tipo) : _tipo(tipo) {
    _descricao = "";
    _arma = "";
};

std::string ClassePersonagem::getNome() const {
    switch(_tipo) {
        case TipoClasse::Arqueiro:
            return "Arqueiro";

        case TipoClasse::Guerreiro:
            return "Guerreiro";

        case TipoClasse::Mago:
            return "Mago";

        case TipoClasse::Tanque:
            return "Tanque";
    }
    return "";
}

std::string ClassePersonagem::getDescricao() const {
    return _descricao;
}

std::string ClassePersonagem::getArma() const {
    return _arma;
}


TipoClasse ClassePersonagem::getTipo() const {
    return _tipo;
}

const std::array<Ataque, 3>& ClassePersonagem::getAtaques() const {
    return _ataques;
}

const Ataque& ClassePersonagem::getAtaque(TipoAtaque tipo) const {
    switch(tipo) {
        case TipoAtaque::Simples:
            return _ataques[0];
        case TipoAtaque::Rapido:
            return _ataques[1];
        case TipoAtaque::Forte:
            return _ataques[2];
    }
    return _ataques[0];
}

