#include "doctest.h"
#include "demo/UI.hpp"
#include "demo/ConfigExploracao.hpp"
#include "entities/character/Jogador.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

namespace {

class ViewFake : public IView {
public:
    mutable std::stringstream buffer;

    void exibir(const std::string& msg) const override {
        buffer << msg << "\n";
    }

    void exibirLinha() const override {
        buffer << std::string(55, '-') << "\n";
    }
};

class MockCtrl : public IController {
public:
    int lerInteiro() override { return 0; }
    std::string lerTexto() override { return ""; }
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

// ─── aguardarEnter ───────────────────────────────────────────────────────────

TEST_CASE("UI - aguardarEnter skipEnter=true não produz saída nem consome entrada") {
    ViewFake view;
    MockCtrl ctrl;
    ConfigExploracao cfg;
    cfg.skipEnter = true;

    aguardarEnter(view, ctrl, "Pressione Enter...", cfg);

    CHECK(view.buffer.str().empty());
}

TEST_CASE("UI - aguardarEnter skipEnter=false exibe mensagem personalizada") {
    ViewFake view;
    MockCtrl ctrl;
    ConfigExploracao cfg;
    cfg.skipEnter = false;

    aguardarEnter(view, ctrl, "Continuar?", cfg);

    CHECK(view.buffer.str().find("Continuar?") != std::string::npos);
}

// ─── exibirRelatorio ─────────────────────────────────────────────────────────

TEST_CASE("UI - exibirRelatorio exibe nome, classe e inventário vazio") {
    ViewFake view;
    Jogador j("Eron", "", "", 10.0, 8.0, 100.0, 30.0, 12.0,
              TipoClasse::Mago, TipoPersonagem::Jogador);

    exibirRelatorio(view, j);

    std::string saida = view.buffer.str();
    CHECK(saida.find("Eron")               != std::string::npos);
    CHECK(saida.find("Mago")               != std::string::npos);
    CHECK(saida.find("Relatório")          != std::string::npos);
    CHECK(saida.find("Inventário vazio.")  != std::string::npos);
    CHECK(saida.find("Fim da demo")        != std::string::npos);
}

// ─── exibirDialogo ───────────────────────────────────────────────────────────

TEST_CASE("UI - exibirDialogo arquivo inexistente não produz saída") {
    ViewFake view;
    exibirDialogo(view, "dialogo_inexistente_xyz.txt");
    CHECK(view.buffer.str().empty());
}

TEST_CASE("UI - exibirDialogo exibe linhas do arquivo com recuo de dois espaços") {
    ViewFake view;
    std::ofstream f("dialogo_test_ui.txt");
    f << "Ola mundo\n";
    f << "Segunda linha\n";
    f.close();

    exibirDialogo(view, "dialogo_test_ui.txt");

    std::string saida = view.buffer.str();
    CHECK(saida.find("  Ola mundo")      != std::string::npos);
    CHECK(saida.find("  Segunda linha")  != std::string::npos);

    std::remove("dialogo_test_ui.txt");
}
