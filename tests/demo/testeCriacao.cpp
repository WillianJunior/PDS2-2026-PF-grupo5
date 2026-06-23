#include "doctest.h"

#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "InputController.hpp"

#include <sstream>
#include <string>
#include <iostream>

class ViewFake : public IView {
public:
    mutable std::string output;

    void exibir(const std::string& msg) const override {
        output += msg + "\n";
    }

    void exibirLinha() const override {
        output += "-----\n";
    }
};

TEST_CASE("criarPersonagem - fluxo normal") {
    ViewFake view;

    std::stringstream input;
    input << "Ello\n"; // nome
    input << "1\n";    // guerreiro

    auto oldCin = std::cin.rdbuf(input.rdbuf());

    InputController ctrl;

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Ello");

    std::cin.rdbuf(oldCin);
}

TEST_CASE("criarPersonagem - classe invalida depois valida") {
    ViewFake view;

    std::stringstream input;
    input << "Kovu\n";
    input << "99\n"; 
    input << "2\n";  

    auto oldCin = std::cin.rdbuf(input.rdbuf());

    InputController ctrl;

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Kovu");

    std::cin.rdbuf(oldCin);
}

TEST_CASE("criarPersonagem - multiplas tentativas invalidas") {
    ViewFake view;

    std::stringstream input;
    input << "Kidra\n";
    input << "0\n";
    input << "-1\n";
    input << "abc\n"; 
    input << "4\n";

    auto oldCin = std::cin.rdbuf(input.rdbuf());

    InputController ctrl;

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(j.getNome() == "Kidra");

    std::cin.rdbuf(oldCin);
}

TEST_CASE("criarPersonagem - executa UI completa") {
    ViewFake view;

    std::stringstream input;
    input << "Zara\n";
    input << "3\n";

    auto oldCin = std::cin.rdbuf(input.rdbuf());

    InputController ctrl;

    Jogador j = criarPersonagem(view, ctrl);

    CHECK(view.output.find("Classe") != std::string::npos);

    std::cin.rdbuf(oldCin);
}