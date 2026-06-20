#include "../../doctest.h"

#include <stdexcept>
#include "entities/map/TrechoMapa.hpp"
#include "entities/items/Item.hpp"
#include "entities/character/Personagem.hpp"

TEST_CASE("Construtor de TrechoMapa")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        10,
        {},
        true,
        20,
        2,
        -1,
        1
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
        {},
        false,
        -1,
        -1,
        -1,
        1
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
        {},
        false,
        -1,
        -1,
        -1,
        1
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
        {1,2,3},
        false,
        -1,
        -1,
        -1,
        1
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
        {1, 3, 5}, 
        false, 
        -1, 
        -1, 
        -1,
        1
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
        {1, 3}, 
        false, 
        -1, 
        -1, 
        -1,
        1
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
        {1}, 
        false,
        0, 
        -1, 
        -1,
        1
    };

    TrechoMapa trecho(dados);
    trecho.registrarItemEncontrado();
    trecho.registrarItemEncontrado();

    CHECK(trecho.pegarItensRestantes() == 0);
}

TEST_CASE("sortearItem retorna ID do proximo item")
{
    InfoTrechoMapa dados{ 
        1, 
        "Floresta", 
        -1, 
        {1, 3, 5}, 
        false, 
        0, 
        -1, 
        -1,
        1 
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.sortearItem() == 1);
    trecho.registrarItemEncontrado();
    CHECK(trecho.sortearItem() == 3);
    trecho.registrarItemEncontrado();
    CHECK(trecho.sortearItem() == 5);
}

TEST_CASE("sortearItem retorna -1 quando nao ha itens restantes")
{
    InfoTrechoMapa dados{ 
        1, 
        "Floresta", 
        -1, 
        {}, 
        false, 
        0, 
        -1, 
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.sortearItem() == -1);
}

TEST_CASE("Retorna NPC de interacao")
{
    InfoTrechoMapa dados{ 
        1, 
        "Floresta", 
        15, 
        {}, 
        false, 
        0, 
        -1, 
        -1,
        1
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
        {},
        false,
        -1,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarNPCInteracao() == -1);
}

TEST_CASE("Retorna proximo trecho")
{
    InfoTrechoMapa dados{
        101,
        "Floresta",
        -1,
        {},
        false,
        -1,
        102,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarProximoTrecho() == 102);
}

TEST_CASE("Retorna trecho anterior")
{
    InfoTrechoMapa dados{
        102,
        "Interior da floresta",
        -1,
        {},
        false,
        -1,
        103,
        101,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarTrechoAnterior() == 101);
}

TEST_CASE("Primeiro trecho nao possui anterior")
{
    InfoTrechoMapa dados{
        101,
        "Entrada da floresta",
        -1,
        {},
        false,
        -1,
        102,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarTrechoAnterior() == -1);
}

TEST_CASE("gerarItem retorna item e registra encontro")
{
    InfoTrechoMapa dados{ 101, "Floresta", -1, {1, 3}, false, 0, -1, -1, 1 };

    TrechoMapa trecho(dados);
    Item item = trecho.gerarItem();

    CHECK(item.getCenaId() == 1);
    CHECK(trecho.pegarItensRestantes() == 1);
}

TEST_CASE("gerarItem sequencial esgota itens do trecho")
{
    InfoTrechoMapa dados{ 101, "Floresta", -1, {1, 3}, false, 0, -1, -1, 1 };

    TrechoMapa trecho(dados);
    trecho.gerarItem();
    trecho.gerarItem();

    CHECK(trecho.possuiItensRestantes() == false);
}

TEST_CASE("gerarItem lanca excecao quando sem itens restantes")
{
    InfoTrechoMapa dados{ 101, "Floresta", -1, {}, false, 0, -1, -1, 1 };

    TrechoMapa trecho(dados);

    CHECK_THROWS_AS(trecho.gerarItem(), std::runtime_error);
}

TEST_CASE("Trecho possui inimigo")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        50,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.possuiInimigo() == true);
}

TEST_CASE("Trecho nao possui inimigo")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        false,
        -1,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.possuiInimigo() == false);
}

TEST_CASE("Retorna ID do inimigo")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        42,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK(trecho.pegarIdInimigo() == 42);
}

TEST_CASE("ID negativo do trecho lança exceção")
{
    InfoTrechoMapa dados{
        -1,
        "Floresta",
        -1,
        {},
        true,
        42,
        -1,
        -1,
        1
    };

    CHECK_THROWS_AS(TrechoMapa trecho(dados), std::invalid_argument);
}

TEST_CASE("Lança exceção para id inválido de cena")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        42,
        -1,
        -1,
        0
    };

    CHECK_THROWS_AS(TrechoMapa trecho(dados), std::invalid_argument);
}

TEST_CASE("Lança exceção para id inválido do inimigo")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        0,
        -1,
        -1,
        1
    };

    CHECK_THROWS_AS(TrechoMapa trecho(dados), std::invalid_argument);
}

TEST_CASE("Lança exceção para id inválido do inimigo")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        0,
        -1,
        -1,
        1
    };

    CHECK_THROWS_AS(TrechoMapa trecho(dados), std::invalid_argument);
}

TEST_CASE("Não permite abrir o mesmo trecho duas vezes")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        true,
        42,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    trecho.abrirTrecho();

    CHECK_THROWS_AS(trecho.abrirTrecho(), std::logic_error);
}

TEST_CASE("Não retorna id do inimigo quando ele não existe")
{
    InfoTrechoMapa dados{
        1,
        "Floresta",
        -1,
        {},
        false,
        -1,
        -1,
        -1,
        1
    };

    TrechoMapa trecho(dados);

    CHECK_THROWS_AS(trecho.pegarIdInimigo(), std::logic_error);
}