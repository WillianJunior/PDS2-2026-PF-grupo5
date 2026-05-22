#include "entities/character/Personagem.hpp"

Personagem::Personagem(
    std::string nome,
    std::string descricao,
    std::string fala,
    double ataque, 
    double defesa, 
    double vidaTotal, 
    double ppTotal, 
    double agilidade, 
    TipoClasse tipoClasse,
    TipoPersonagem tipo,
    int nivel)
    : _nome(nome),
      _descricao(descricao),
      _fala(fala),
      _ataque(ataque),
      _defesa(defesa),
      _vidaTotal(vidaTotal),
      _vidaAtual(vidaTotal),
      _ppTotal(ppTotal),
      _ppAtual(ppTotal),
      _agilidade(agilidade),
      _xp(0),
      _classe(tipoClasse),
      _tipo(tipo),
      _nivel(nivel)
{}

void Personagem::receberDano(double dano) {

}

void Personagem::recuperarVida(double cura) {

}

void Personagem::recuperarMana(double quantidadeMana) {

}

void Personagem::gastarMana(double custoMana) {

}

void Personagem::ganharXp(double quantidadeXp) {

}

void Personagem::subirNivel() {

}

bool Personagem::estaVivo() const {
    if(_vidaAtual == 0)
        return false;
    else
        return true;
}

void Personagem::cenaAtual() {

}

std::string Personagem::getNome() const {
    return _nome;
}

std::string Personagem::getDescricao() const {
    return _descricao;
}

std::string Personagem::getFala() const {
    return _fala;
}

double Personagem::getVidaAtual() const {
    return _vidaAtual;
}

double Personagem::getAtaque() const {
    return _ataque;
}

double Personagem::getDefesa() const {
    return _defesa;
}

double Personagem::getAgilidade() const {
    return _agilidade;
}

double Personagem::getManaAtual() const {
    return _ppAtual;
}

int Personagem::getNivel() const {
    return _nivel;
}

double Personagem::getXp() const {
    return _xp;
}

TipoPersonagem Personagem::getTipo() const {
    return _tipo;
}

const ClassePersonagem& Personagem::getClasse() const {
    return _classe;
}