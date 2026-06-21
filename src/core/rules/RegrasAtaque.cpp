#include "core/rules/RegrasAtaque.hpp"

double RegrasAtaque::calcularDano(const Personagem& personagem, const Ataque& ataque) {
    Dados dados;
    const DadosAtaque& dadosAtaque = BancoDadosAtaque::getDadosAtaque(ataque.id);
    double coeficiente = RegrasAtaque::calcularCoeficiente(personagem, dadosAtaque.atributoCoef);

    if(dadosAtaque.escalaComNivel)
        return personagem.getNivel() * 
        (dados.rolar(dadosAtaque.quantidadeDados,dadosAtaque.faces) 
        + coeficiente * dadosAtaque.multiplicador); 
    else
        return dados.rolar(dadosAtaque.quantidadeDados,dadosAtaque.faces) 
        + coeficiente * dadosAtaque.multiplicador;
}

double RegrasAtaque::calcularCoeficiente(const Personagem& personagem, AtributoCoef atributoCoef) {
    switch(atributoCoef) {
        case AtributoCoef::Ataque:
        return Regras::calcularCoeficiente(personagem.getAtaque());

        case AtributoCoef::Agilidade:
        return Regras::calcularCoeficiente(personagem.getAgilidade());

        case AtributoCoef::Defesa:
        return Regras::calcularCoeficiente(personagem.getDefesa());

        case AtributoCoef::Nenhum:
        return 0.0;
    }
    throw std::invalid_argument("AtributoCoef inválido");
}

