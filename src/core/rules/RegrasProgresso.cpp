/**
 * @file RegrasProgresso.cpp
 * @brief Implementação da classe RegrasProgresso.
 */

#include "RegrasProgresso.hpp"

bool RegrasProgresso::verificarUpNivel(double xpAtual, int nivelAtual) {
    // Nível inválido — delega a validação para o método da classe pai
    // (lança std::out_of_range para < 1 ou > 10)
    if (nivelAtual < 1 || nivelAtual > NIVEL_MAXIMO)
        xpParaProximoNivel(nivelAtual); // dispara a exceção do pai

    // Nível máximo — nunca sobe mais
    if (nivelAtual == NIVEL_MAXIMO)
        return false;

    return xpAtual >= xpParaProximoNivel(nivelAtual);
}

double RegrasProgresso::getXPParaProximoNivel(int nivelAtual) {
    return xpParaProximoNivel(nivelAtual);
}

int RegrasProgresso::getBonusProficiencia(int nivel) {
    return bonusProficiencia(nivel);
}

int RegrasProgresso::getNivelMaximo() {
    return NIVEL_MAXIMO;
}