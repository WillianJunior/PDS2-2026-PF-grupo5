#include "../../doctest.h"

#include "entities/map/Cena.hpp"
#include "entities/map/TrechoMapa.hpp"

TEST_CASE("Estado inicial de Cena") {
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,3}
    };

    Cena cena(dados);

    CHECK(cena.pegarId() == 1);
    CHECK(cena.pegarArcano() == "Primeiro arcano");

    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.emBatalha() == false);
    CHECK(cena.explorando() == false);


}

TEST_CASE("Iniciar Cena") {
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,3}
    };

    Cena cena(dados);

    cena.iniciarCena();

    CHECK(cena.explorando() == true);
    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
}

TEST_CASE("Abrir Inventario") {
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,3}
    };

    Cena cena(dados);

    cena.abrirInventario();

    CHECK(cena.inventarioAberto() == true);
}

TEST_CASE("Iniciar Batalha") {
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,3}
    };

    Cena cena(dados);

    cena.iniciarBatalha();

    CHECK(cena.emBatalha() == true);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Finalizar Cena") {
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,3}
    };

    Cena cena(dados);

    cena.iniciarCena();

    cena.finalizarCena();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Mudar trecho"){
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,}
    };

    Cena cena(dados);
    cena.mudarTrecho(2);

    CHECK(cena.pegarTrechoAtual().pegarId()==2);
}

TEST_CASE("Andar para o proximo trecho"){
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1,2,}
    };

    Cena cena(dados);

    cena.iniciarCena();
    int trechoInicial = cena.pegarTrechoAtual().pegarId();

    cena.andar();

    CHECK(cena.pegarTrechoAtual().pegarId() != trechoInicial);

}

TEST_CASE("Pegar trecho atual"){
    InfoCena dados{
        1,
        "Primeiro arcano", 
        "recompensa", 
        "descricao", 
        1, 
        {1}
    };

    Cena cena(dados);
    cena.iniciarCena();

    CHECK(cena.pegarTrechoAtual().pegarId() == 1);
}
