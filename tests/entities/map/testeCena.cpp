#include "../../doctest.h"

#include <memory>

#include "entities/map/Cena.hpp"
#include "entities/map/TrechoMapa.hpp"
#include "entities/character/Jogador.hpp"

static Jogador criarJogadorTeste() {
    return Jogador("Heroi", "", "", 10.0, 5.0, 100.0, 50.0, 8.0,
                   TipoClasse::Guerreiro, TipoPersonagem::Jogador);
}

TEST_CASE("Estado inicial de Cena") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 1, {1,2,3} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK(cena.pegarId() == 1);
    CHECK(cena.pegarArcano() == "Primeiro arcano");
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.emBatalha() == false);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Iniciar Cena") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101,102,103} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();

    CHECK(cena.explorando() == true);
    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
}

TEST_CASE("Abrir Inventario") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 1, {1,2,3} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.abrirInventario();

    CHECK(cena.inventarioAberto() == true);
}

TEST_CASE("Iniciar Batalha") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 1, {1,2,3} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarBatalha();

    CHECK(cena.emBatalha() == true);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Finalizar Cena") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101,102,103} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();
    cena.finalizarCena();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Mudar trecho") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101,102} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.mudarTrecho(102);

    CHECK(cena.pegarTrechoAtual().pegarId() == 102);
}

TEST_CASE("Andar para o proximo trecho") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101,102} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();
    int trechoInicial = cena.pegarTrechoAtual().pegarId();

    cena.andar();

    CHECK(cena.pegarTrechoAtual().pegarId() != trechoInicial);
}

TEST_CASE("Pegar trecho atual") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();

    CHECK(cena.pegarTrechoAtual().pegarId() == 101);
}

TEST_CASE("Pegar trecho atual sem iniciar cena gera excecao")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};
    Jogador jogador = criarJogadorTeste();

    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.pegarTrechoAtual(), std::runtime_error);
}

TEST_CASE("Vasculhar adiciona item ao inventario do jogador") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();

    int itensTrecho = cena.pegarTrechoAtual().pegarItensRestantes();
    cena.vasculhar();

    CHECK(cena.pegarTrechoAtual().pegarItensRestantes() == itensTrecho - 1);
    CHECK(jogador.getInventario().quantidadeItens() == 1);
}

TEST_CASE("Vasculhar nao adiciona item se inventario cheio") {
    InfoCena dados{ 1, "Primeiro arcano", "recompensa", "descricao", 101, {101} };
    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    cena.iniciarCena();
    for (int i = 0; i < 8; i++)
        jogador.adicionarItem(std::make_unique<Item>("Item", "", Pocao, "", 0, 0));

    int itensTrecho = cena.pegarTrechoAtual().pegarItensRestantes();
    cena.vasculhar();

    CHECK(cena.pegarTrechoAtual().pegarItensRestantes() == itensTrecho);
    CHECK(jogador.getInventario().quantidadeItens() == 8);
}

TEST_CASE("Andar em trecho final nao muda trecho")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",103,{103}};
    Jogador jogador = criarJogadorTeste();

    Cena cena(dados,jogador);

    cena.iniciarCena();

    int idAntes = cena.pegarTrechoAtual().pegarId();

    cena.andar();

    CHECK(cena.pegarTrechoAtual().pegarId() == idAntes);
}

TEST_CASE("Exceção lançada com id incorreto de cena")
{
    InfoCena dados{0,"Arcano","recompensa","descricao",101, {101}};

    Jogador jogador = criarJogadorTeste();

    CHECK_THROWS_AS(Cena(dados, jogador),std::invalid_argument);
}

TEST_CASE("Andar sem trecho carregado gera excecao")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.andar(),std::runtime_error);
}

TEST_CASE("Vasculhar sem trecho carregado gera excecao")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.vasculhar(),std::runtime_error);
}

TEST_CASE("Interagir NPC sem trecho carregado gera excecao")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.interagirNPCs(),std::runtime_error);
}

TEST_CASE("Descartar item sem trecho carregado gera excecao")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.descartarItem(),std::runtime_error);
}

TEST_CASE("Mudar trecho rejeita id invalido")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK_THROWS_AS(cena.mudarTrecho(0),std::invalid_argument);
}

TEST_CASE("Pegar descricao da cena")
{
    InfoCena dados{1,"Arcano","recompensa","Descricao de teste",101,{101}};

    Jogador jogador = criarJogadorTeste();
    Cena cena(dados, jogador);

    CHECK(cena.pegarDescricao() == "Descricao de teste");
}

TEST_CASE("Interagir NPCs sem NPC no trecho")
{
    InfoCena dados{2,"Arcano","recompensa","descricao",201,{201,202,203}};

    Jogador jogador = criarJogadorTeste();

    Cena cena(dados, jogador);

    cena.iniciarCena();

    CHECK_NOTHROW(cena.interagirNPCs());
}

TEST_CASE("Descartar item quando nao ha itens restantes")
{
    InfoCena dados{1,"Arcano","recompensa","descricao",101,{101}};

    Jogador jogador = criarJogadorTeste();

    Cena cena(dados, jogador);

    cena.iniciarCena();

    while(cena.pegarTrechoAtual().possuiItensRestantes()){
        cena.descartarItem();
    }

    CHECK_NOTHROW(cena.descartarItem());

    CHECK(cena.pegarTrechoAtual().pegarItensRestantes() == 0);
}