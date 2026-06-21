#include "core/rules/RegrasAtaque.hpp"

double RegrasAtaque::calcularDano(const Personagem& personagem, const Ataque& ataque, std::optional<unsigned int> seed) {
    Dados dados = seed.has_value()
    ? Dados(*seed)
    : Dados();
    const DadosAtaque& dadosAtaque = BancoDadosAtaque::getDadosAtaque(ataque.id);

    double coeficiente = RegrasAtaque::calcularCoeficiente(personagem, dadosAtaque.atributoCoef);
    double valorDados = dados.rolar(dadosAtaque.quantidadeDados, dadosAtaque.faces);

    double dano = dadosAtaque.multiplicador * (valorDados + coeficiente);
    if(dano < 0)
        dano = 0;

    if(dadosAtaque.escalaComNivel)
        return personagem.getNivel() * dano;
    else
        return dano;
}

double RegrasAtaque::calcularCoeficiente(const Personagem& personagem, AtributoCoef atributoCoef) {
    switch(atributoCoef) {
        case AtributoCoef::Ataque:
        return Regras::calcularCoeficiente(personagem.getAtaque());

        case AtributoCoef::Agilidade:
        return Regras::calcularCoeficiente(personagem.getAgilidade());

        case AtributoCoef::Defesa:
        return Regras::calcularCoeficiente(personagem.getDefesa());

    }
    throw std::invalid_argument("AtributoCoef inválido");
}

