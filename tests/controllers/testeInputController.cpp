#include "../doctest.h"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "controllers/InputController.hpp"

static std::string simularEntrada(const std::string& entrada, std::function<std::string()> fn) {
    std::istringstream buf(entrada);
    std::streambuf* antigo = std::cin.rdbuf(buf.rdbuf());
    std::string resultado = fn();
    std::cin.rdbuf(antigo);
    return resultado;
}

static int simularEntradaInt(const std::string& entrada, std::function<int()> fn) {
    std::istringstream buf(entrada);
    std::streambuf* antigo = std::cin.rdbuf(buf.rdbuf());
    int resultado = fn();
    std::cin.rdbuf(antigo);
    return resultado;
}

// ── lerTexto ──────────────────────────────────────────────────────────────────

TEST_CASE("lerTexto retorna a linha digitada") {
    InputController ctrl;
    std::string resultado = simularEntrada("ola mundo\n",
        [&]() { return ctrl.lerTexto(); });
    CHECK(resultado == "ola mundo");
}

TEST_CASE("lerTexto retorna string vazia para linha em branco") {
    InputController ctrl;
    std::string resultado = simularEntrada("\n",
        [&]() { return ctrl.lerTexto(); });
    CHECK(resultado == "");
}

TEST_CASE("lerTexto retorna apenas a primeira linha quando ha multiplas") {
    InputController ctrl;
    std::string resultado = simularEntrada("primeira\nsegunda\n",
        [&]() { return ctrl.lerTexto(); });
    CHECK(resultado == "primeira");
}

TEST_CASE("lerTexto preserva espacos e caracteres especiais") {
    InputController ctrl;
    std::string resultado = simularEntrada("  com espacos  \n",
        [&]() { return ctrl.lerTexto(); });
    CHECK(resultado == "  com espacos  ");
}

// ── lerInteiro ────────────────────────────────────────────────────────────────

TEST_CASE("lerInteiro retorna o inteiro digitado") {
    InputController ctrl;
    int resultado = simularEntradaInt("42\n",
        [&]() { return ctrl.lerInteiro(); });
    CHECK(resultado == 42);
}

TEST_CASE("lerInteiro funciona com numero negativo") {
    InputController ctrl;
    int resultado = simularEntradaInt("-7\n",
        [&]() { return ctrl.lerInteiro(); });
    CHECK(resultado == -7);
}

TEST_CASE("lerInteiro funciona com zero") {
    InputController ctrl;
    int resultado = simularEntradaInt("0\n",
        [&]() { return ctrl.lerInteiro(); });
    CHECK(resultado == 0);
}

TEST_CASE("lerInteiro consome o newline e nao interfere em leitura seguinte") {
    InputController ctrl;
    std::istringstream buf("3\nproximo\n");
    std::streambuf* antigo = std::cin.rdbuf(buf.rdbuf());

    int n = ctrl.lerInteiro();
    std::string texto = ctrl.lerTexto();

    std::cin.rdbuf(antigo);

    CHECK(n == 3);
    CHECK(texto == "proximo");
}
