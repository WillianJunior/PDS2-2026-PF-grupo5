#include "../../doctest.h"

#include "entities/map/TrechoMapa.hpp"
#include "entities/items/Item.hpp"
#include "entities/character/Personagem.hpp"

TEST_CASE("Construtor de TrechoMapa"){
    InfoTrechoMapa dados{
        1,
        "Floresta",
        10, //id no nps
        3, //quantidade de item
        2, //quantidade de inimigo
        2, //id do proximo trecho
        -1 //id do trecho anterior

    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarId() == 1);
    CHECK(trecho.pegarDescricao() == "Floresta");
    CHECK(trecho.pegarNPCInteracao() == 10);
    CHECK(trecho.pegarProximoTrecho() == 2);
    CHECK(trecho.pegarTrechoAnterior() == -1);

}


TEST_CASE("TrechoMapa inicia fechado")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.estaAberto() == false);
}

TEST_CASE("abrirTrecho altera estado")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.abrirTrecho();

    CHECK(trecho.estaAberto() == true);
}

TEST_CASE("TrechoMapa possui itens restantes inicialmente")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        3,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.possuiItensRestantes() == true);
}

TEST_CASE("registrarItemEncontrado reduz itens restantes")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        3,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarItemEncontrado();

    CHECK(trecho.pegarItensRestantes() == 2);
}

TEST_CASE("Nao possui itens restantes apos encontrar todos")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        2,
        0,
        -1
    };

    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        2,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarItemEncontrado();
    trecho.registrarItemEncontrado();

    CHECK(trecho.possuiItensRestantes() == false);
}

TEST_CASE("Nao registra itens acima do limite")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        1,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarItemEncontrado();
    trecho.registrarItemEncontrado();

    CHECK(trecho.pegarItensRestantes() == 0);
}

TEST_CASE("Possui inimigos restantes inicialmente")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        2,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.possuiInimigosRestantes() == true);
}

TEST_CASE("registrarInimigoDerrotado reduz quantidade")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        3,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarInimigoDerrotado();

    CHECK(trecho.pegarInimigosRestantes() == 2);
}

TEST_CASE("Nao possui inimigos restantes apos derrotar todos")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        2,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarInimigoDerrotado();
    trecho.registrarInimigoDerrotado();

    CHECK(trecho.possuiInimigosRestantes() == false);
}

TEST_CASE("Nao derrota inimigos acima do limite")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        1,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    trecho.registrarInimigoDerrotado();
    trecho.registrarInimigoDerrotado();

    CHECK(trecho.pegarInimigosRestantes() == 0);
}

TEST_CASE("Retorna NPC de interacao")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        15,
        0,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarNPCInteracao() == 15);
}

TEST_CASE("Trecho sem NPC retorna menos um")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        0,
        -1,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarNPCInteracao() == -1);
}

TEST_CASE("Retorna proximo trecho")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        0,
        0,
        2,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarProximoTrecho() == 2);
}

TEST_CASE("Retorna trecho anterior")
{
    InfoTrechoMapa dados{
        2,
        "Interior da floresta",
        -1,
        0,
        0,
        3,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarTrechoAnterior() == 1);
}

TEST_CASE("Primeiro trecho nao possui anterior")
{
    InfoTrechoMapa dados{
        1,
        "Entrada da floresta",
        -1,
        0,
        0,
        2,
        -1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarTrechoAnterior() == -1);
}

