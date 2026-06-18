/**
 * @file ClassePersonagem.cpp
 * @brief Implementação da classe ClassePersonagem.
 * Define os ataques, arma e descrição de cada arquétipo via BancoClassePersonagem.
 * @see Regras.md — Seções 1.1, 2.2, 2.3 e 2.4
 */

#include "entities/character/ClassePersonagem.hpp"
#include "database/BancoClassePersonagem.hpp"

ClassePersonagem::ClassePersonagem(TipoClasse tipo) : _tipo(tipo) {
    BancoClassePersonagem::defineClasse(tipo, *this);
    _ataques = BancoClassePersonagem::defineAtaques(tipo);
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

void ClassePersonagem::setDescricao(std::string descricao) {
    _descricao = descricao;
} 

void ClassePersonagem::setArma(std::string nomeArma) {
    _arma = nomeArma;
}

void ClassePersonagem::alteraAtaqueForte(int nivel) {
    std::array<Ataque,4> opcoesAtaque 
    = BancoClassePersonagem::getAtaquesFortesPossiveis(_tipo);
    switch(nivel) {
        case 3:
            _ataques[2] = opcoesAtaque[1];
            break;

        case 5:
            _ataques[2] = opcoesAtaque[2];
            break;
        
        case 7:
            _ataques[2] = opcoesAtaque[3];
            break;
    }
}

const Condicao& ClassePersonagem::getEfeitoAtaque(TipoAtaque tipo) const {
    switch(tipo) {
        case TipoAtaque::Simples:
            return _ataques[0].efeito;
        case TipoAtaque::Rapido:
            return _ataques[1].efeito;
        case TipoAtaque::Forte:
            return _ataques[2].efeito;
    }
    return _ataques[0].efeito;
};

