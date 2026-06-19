#include "../doctest.h"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "views/TerminalView.hpp"

static std::string capturarSaida(std::function<void()> fn) {
    std::ostringstream buf;
    std::streambuf* antigo = std::cout.rdbuf(buf.rdbuf());
    fn();
    std::cout.rdbuf(antigo);
    return buf.str();
}

TEST_CASE("exibir imprime mensagem seguida de newline") {
    TerminalView view;
    std::string saida = capturarSaida([&]() { view.exibir("Ola mundo"); });
    CHECK(saida == "Ola mundo\n");
}

TEST_CASE("exibir com mensagem vazia imprime apenas newline") {
    TerminalView view;
    std::string saida = capturarSaida([&]() { view.exibir(""); });
    CHECK(saida == "\n");
}

TEST_CASE("exibir preserva caracteres especiais") {
    TerminalView view;
    std::string saida = capturarSaida([&]() { view.exibir("Acao: +4 ATQ!"); });
    CHECK(saida == "Acao: +4 ATQ!\n");
}

TEST_CASE("exibirLinha imprime exatamente 55 hifens seguidos de newline") {
    TerminalView view;
    std::string saida = capturarSaida([&]() { view.exibirLinha(); });
    CHECK(saida == std::string(55, '-') + "\n");
    CHECK(saida.size() == 56); // 55 hifens + '\n'
}

TEST_CASE("exibir chamado multiplas vezes acumula saidas independentes") {
    TerminalView view;
    std::string saida = capturarSaida([&]() {
        view.exibir("linha 1");
        view.exibir("linha 2");
    });
    CHECK(saida == "linha 1\nlinha 2\n");
}
