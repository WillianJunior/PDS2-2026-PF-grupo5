#include "doctest.h"
#include "demo/UI.hpp"

#include <fstream> // manipulação de arquivos
#include <sstream> // stringstream para capturar saída
#include <string>
#include <cstdio> // std::remove para apagar arquivos temporários

// escopo local para o ViewFake
namespace {

class ViewFake : public IView {
public:
    // mutable permite modificação em métodos const
    mutable std::stringstream buffer;

    void exibir(const std::string& msg) const override {
        buffer << msg << "\n";
    }

    void exibirLinha() const override {}
};

} 

TEST_CASE("UI - exibirCentrado insere texto na saída") {
    ViewFake view;
    exibirCentrado(view, "ola");
    CHECK(view.buffer.str().find("ola") != std::string::npos);
}

TEST_CASE("UI - exibirCentrado com string longa não adiciona prefixo negativo") {
    ViewFake view;
    std::string longa(200, 'x');
    exibirCentrado(view, longa);
    CHECK(view.buffer.str().find(longa) != std::string::npos);
}

TEST_CASE("UI - ascii arquivo inexistente não produz saída") {
    ViewFake view;
    exibirAsciiArtArquivo(view, "arquivo_que_nao_existe.txt");
    CHECK(view.buffer.str().empty());
}

TEST_CASE("UI - ascii arquivo válido exibe conteúdo") {
    ViewFake view;

    std::ofstream file("ascii_test_ui.txt");
    file << "linha1\nlinha2\n";
    file.close();

    exibirAsciiArtArquivo(view, "ascii_test_ui.txt");

    std::string saida = view.buffer.str();
    CHECK(saida.find("linha1") != std::string::npos);
    CHECK(saida.find("linha2") != std::string::npos);

    std::remove("ascii_test_ui.txt");
}

TEST_CASE("UI - ascii aplica prefixo para centralização") {
    ViewFake view;

    std::ofstream file("ascii_test_prefixo.txt");
    file << "abc\n";
    file.close();

    exibirAsciiArtArquivo(view, "ascii_test_prefixo.txt");

    std::string saida = view.buffer.str();
    CHECK(saida.find("abc") != std::string::npos);
    // Terminal fallback é 80 colunas; "abc" tem 3 → pad = (80-3)/2 = 38 espaços
    CHECK(!saida.empty());
    CHECK(saida[0] == ' ');

    std::remove("ascii_test_prefixo.txt");
}

TEST_CASE("UI - ascii arquivo vazio não produz saída") {
    ViewFake view;

    std::ofstream file("ascii_test_vazio.txt");
    file.close();

    exibirAsciiArtArquivo(view, "ascii_test_vazio.txt");

    CHECK(view.buffer.str().empty());

    std::remove("ascii_test_vazio.txt");
}
