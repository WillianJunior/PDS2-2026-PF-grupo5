/**
 * @file Dados.cpp
 * @brief Implementação da classe Dados.
 */

#include "core/Dados.hpp"
#include <algorithm>
#include <random>
#include <vector>
#include <stdexcept>

//Construtores

Dados::Dados()
    : _rng(std::random_device{}()) {}

Dados::Dados(unsigned int semente)
    : _rng(semente) {}

//Privado

int Dados::_rolarUm(int lados) {
    if (lados < 2)
        throw std::invalid_argument("Dado precisa ter pelo menos 2 lados.");

    std::uniform_int_distribution<int> dist(1, lados);
    return dist(_rng);
}

//Dados individuais

int Dados::d4()  { return _rolarUm(4);  }
int Dados::d6()  { return _rolarUm(6);  }
int Dados::d8()  { return _rolarUm(8);  }
int Dados::d10() { return _rolarUm(10); }
int Dados::d12() { return _rolarUm(12); }
int Dados::d20() { return _rolarUm(20); }

//Rolagens compostas

int Dados::rolar(int quantidade, int lados) {
    if (quantidade < 1)
        throw std::invalid_argument("Quantidade de dados deve ser >= 1.");
    if (lados < 2)
        throw std::invalid_argument("Dado precisa ter pelo menos 2 lados.");

    int soma = 0;
    for (int i = 0; i < quantidade; i++)
        soma += _rolarUm(lados);

    return soma;
}

int Dados::rolar4d6() {
    // Rola os 4 dados
    std::vector<int> resultados;
    for (int i = 0; i < 4; i++)
        resultados.push_back(_rolarUm(6));

    // Descarta o menor
    std::sort(resultados.begin(), resultados.end()); // [menor, ..., maior]

    int soma = 0;
    for (int i = 1; i < 4; i++) // ignora o índice 0 (o menor)
        soma += resultados[i];

    return soma;
}

std::vector<int> Dados::gerarAtributos() {
    std::vector<int> atributos;
    for (int i = 0; i < 4; i++)
        atributos.push_back(rolar4d6());

    // Ordena em ordem DECRESCENTE para distribuição por classe
    std::sort(atributos.begin(), atributos.end(), std::greater<int>());

    return atributos;
}

int Dados::d20Vantagem() {
    int a = _rolarUm(20);
    int b = _rolarUm(20);
    return std::max(a, b);
}

int Dados::d20Desvantagem() {
    int a = _rolarUm(20);
    int b = _rolarUm(20);
    return std::min(a, b);
}