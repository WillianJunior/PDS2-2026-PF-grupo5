#include "core/rules/RegrasAtaque.hpp"

double RegrasAtaque::calcularDano(const Personagem& personagem, const Ataque& ataque,
    std::optional<unsigned int> seed) {

    Dados dados = seed.has_value()
    ? Dados(*seed)
    : Dados();
    const DadosAtaque& dadosAtaque = BancoDadosAtaque::getDadosAtaque(ataque.id);

    double coeficiente = RegrasAtaque::calcularCoeficiente(personagem, dadosAtaque.atributoCoef);
    double dano = 0;
    double valorDados = 0;

    if(dadosAtaque.dadosPorNivel) {
        valorDados = dados.rolar(personagem.getNivel(), dadosAtaque.faces);
    } else if (ataque.tipo == TipoAtaque::Simples &&
    personagem.getClasse().getTipo() == TipoClasse::Mago) {
    int quantidadeDados = regraPorNivel(personagem.getNivel(), {1, 2, 3, 4});
        valorDados = dados.rolar(quantidadeDados, dadosAtaque.faces);
    } else
        valorDados = dados.rolar(dadosAtaque.quantidadeDados, dadosAtaque.faces);

    dano = valorDados + coeficiente;

    if(dano < 0)
        dano = 0;

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
    throw std::invalid_argument("AtributoCoef invalido");
}

int RegrasAtaque::regraPorNivel(int nivel, std::array<int, 4> faixas){
    if(nivel <= 2) return faixas[0];
    if(nivel <= 4) return faixas[1];
    if(nivel <= 6) return faixas[2];
    return faixas[3];
}

int RegrasAtaque::getExecucoes(const Personagem& personagem, const Ataque& ataque) {
    int nivel = personagem.getNivel();

    if(ataque.tipo == TipoAtaque::Simples)
    switch(personagem.getClasse().getTipo()) {
        case TipoClasse::Arqueiro:
            return regraPorNivel(nivel, {1,1,2,3});

        case TipoClasse::Guerreiro:
            return regraPorNivel(nivel, {1,2,2,3});

        case TipoClasse::Mago:
            return regraPorNivel(nivel, {1,1,1,1});

        case TipoClasse::Tanque:
            return regraPorNivel(nivel, {1,1,2,3});
    } else
        return BancoDadosAtaque::getDadosAtaque(ataque.id).numeroDeExecucoes;

    throw std::invalid_argument("Tipo de ataque invalido");
}
