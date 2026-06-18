#include "tests/doctest.h"

#include "include/database/BancoTrechoMapa.hpp"

TEST_CASE("BancoTrechoMapa retorna trecho 101")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(101).id == 101
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 102")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(102).id == 102
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 103")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(103).id == 103
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 201")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(201).id == 201
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 202")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(202).id == 202
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 203")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(203).id == 203
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 301")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(301).id == 301
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 302")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(302).id == 302
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 303")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(303).id == 303
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 401")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(401).id == 401
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 402")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(402).id == 402
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 403")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(403).id == 403
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 501")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(501).id == 501
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 502")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(502).id == 502
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 503")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(503).id == 503
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 601")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(601).id == 601
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 602")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(602).id == 602
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 603")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(603).id == 603
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 701")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(701).id == 701
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 702")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(702).id == 702
    );
}

TEST_CASE("BancoTrechoMapa retorna trecho 703")
{
    CHECK(
        BancoTrechoMapa::obterTrechoMapa(703).id == 703
    );
}

TEST_CASE("BancoTrechoMapa lanca excecao para ID invalido")
{
    CHECK_THROWS(
        BancoTrechoMapa::obterTrechoMapa(-1)
    );
}