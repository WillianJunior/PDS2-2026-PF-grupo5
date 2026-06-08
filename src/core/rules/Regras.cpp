/**
 * @file Regras.cpp
 * @brief Implementação da classe base Regras.
 */

#include "Regras.hpp"

double Regras::calcularCoeficiente(double valorAtributo) {
    return (0.5 * valorAtributo) - 5.0;
}

double Regras::calcularCD(double valorAgilidade) {
    return 10.0 + calcularCoeficiente(valorAgilidade);
}

double Regras::calcularPPTotal(double valorPoder) {
    return valorPoder * 5.0;
}

int Regras::bonusProficiencia(int nivel) {
    if (nivel < 1 || nivel > NIVEL_MAXIMO)
        throw std::out_of_range("Nivel deve estar entre 1 e 10.");

    return BONUS_PROFICIENCIA[nivel - 1];
}

double Regras::xpParaProximoNivel(int nivelAtual) {
    if (nivelAtual < 1 || nivelAtual > NIVEL_MAXIMO)
        throw std::out_of_range("Nivel deve estar entre 1 e 10.");

    return XP_POR_NIVEL[nivelAtual - 1];
}