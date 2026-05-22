#include "../../doctest.h"

#include "entities/map/Cena.hpp"
#include "entities/map/TrechoMapa.hpp"

TEST_CASE("Estado inicial de Cena") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() ==false);
    CHECK(cena.explorando() == true);
}

TEST_CASE("Iniciar Cena") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.iniciarCena();

    CHECK(cena.explorando() == true);
}

TEST_CASE("Andar") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.andar();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == true);
}

TEST_CASE("Vasculhar") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.vasculhar();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == true);
}

TEST_CASE("Interacao com NPCs") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.iniciarCena();
    cena.interagirNPCs();

    CHECK(cena.explorando() == true);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.emBatalha() == false);
}

TEST_CASE("Abrir Inventario") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.abrirInventario();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == true);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Inicair Batalha") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.iniciarBatalha();

    CHECK(cena.emBatalha() == true);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Finalizar Cena") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.finalizarCena();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == false);
}

TEST_CASE("Transicao de estados") {
    TrechoMapa trecho(1, "Inicio");
    Cena cena(1, &trecho);

    cena.iniciarBatalha();

    CHECK(cena.emBatalha() == true);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == false);

    cena.vasculhar();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == false);
    CHECK(cena.explorando() == true);

    cena.abrirInventario();

    CHECK(cena.emBatalha() == false);
    CHECK(cena.inventarioAberto() == true);
    CHECK(cena.explorando() == false);
   
}

