#include "tests/doctest.h"

#include "include/database/BancoNpcInteracao.hpp"

#include <stdexcept>

TEST_CASE("BancoNpcInteracao retorna NPC 1")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(1);

    CHECK(npc.id == 1);
}

TEST_CASE("BancoNpcInteracao retorna NPC 2")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(2);

    CHECK(npc.id == 2);
}

TEST_CASE("BancoNpcInteracao retorna NPC 3")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(3);

    CHECK(npc.id == 3);
}

TEST_CASE("BancoNPCInteracao lanca excecao para id negativo")
{
    CHECK_THROWS_AS(
        BancoNPCInteracao::obterNPC(-1),
        std::invalid_argument
    );
}

TEST_CASE("BancoNPCInteracao lanca excecao para id inexistente")
{
    CHECK_THROWS_AS(
        BancoNPCInteracao::obterNPC(999),
        std::runtime_error
    );
}