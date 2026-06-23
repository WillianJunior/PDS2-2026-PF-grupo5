#include "doctest.h"
#include "demo/UI.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>

class ViewFake : public IView {
public:
    mutable std::stringstream buffer;

    void exibir(const std::string& msg) const override {
        buffer << msg << "\n";
    }

    void exibirLinha() const override {}
};

TEST_CASE("Teste exibirCentrado") {
    ViewFake view;

    exibirCentrado(view, "ola");

    CHECK(view.buffer.str().find("ola") != std::string::npos);
}

TEST_CASE("ascii arquivo inexistente") {
    ViewFake view;

    exibirAsciiArtArquivo(view, "arquivo_que_nao_existe.txt");

    CHECK(view.buffer.str().empty());
}

TEST_CASE("UI - ascii arquivo valido") {
    ViewFake view;

    std::ofstream file("ascii_test.txt");
    file << "linha1\nlinha2\n";
    file.close();

    exibirAsciiArtArquivo(view, "ascii_test.txt");

    std::string saida = view.buffer.str();

    CHECK(saida.find("linha1") != std::string::npos);
    CHECK(saida.find("linha2") != std::string::npos);

    std::remove("ascii_test.txt");
}

TEST_CASE("UI - ascii aplica prefixo") {
    ViewFake view;

    std::ofstream file("ascii_test2.txt");
    file << "abc\n";
    file.close();

    exibirAsciiArtArquivo(view, "ascii_test2.txt");

    std::string saida = view.buffer.str();

    CHECK(saida.find("abc") != std::string::npos);

    // se centralizou, normalmente terá espaços antes
    CHECK(saida[0] == ' ');

    std::remove("ascii_test2.txt");
}
