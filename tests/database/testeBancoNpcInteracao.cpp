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

TEST_CASE("BancoNpcInteracao retorna NPC 4")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(4);

    CHECK(npc.id == 4);
}

TEST_CASE("BancoNpcInteracao retorna NPC 5")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(5);

    CHECK(npc.id == 5);
}

TEST_CASE("BancoNpcInteracao retorna NPC 6")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(6);

    CHECK(npc.id == 6);
}

TEST_CASE("BancoNpcInteracao retorna NPC 7")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(7);

    CHECK(npc.id == 7);
}

TEST_CASE("BancoNpcInteracao retorna NPC 8")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(8);

    CHECK(npc.id == 8);
}

TEST_CASE("BancoNpcInteracao retorna NPC 9")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(9);

    CHECK(npc.id == 9);
}

TEST_CASE("BancoNpcInteracao retorna NPC 10")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(10);

    CHECK(npc.id == 10);
}

TEST_CASE("BancoNpcInteracao retorna NPC 11")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(11);

    CHECK(npc.id == 11);
}

TEST_CASE("BancoNpcInteracao retorna NPC 12")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(12);

    CHECK(npc.id == 12);
}

TEST_CASE("BancoNpcInteracao retorna NPC 13")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(13);

    CHECK(npc.id == 13);
}

TEST_CASE("BancoNpcInteracao retorna NPC 14")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(14);

    CHECK(npc.id == 14);
}

TEST_CASE("BancoNpcInteracao retorna NPC 15")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(15);

    CHECK(npc.id == 15);
}

TEST_CASE("BancoNpcInteracao retorna NPC 16")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(16);

    CHECK(npc.id == 16);
}

TEST_CASE("BancoNpcInteracao retorna NPC 17")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(17);

    CHECK(npc.id == 17);
}

TEST_CASE("BancoNpcInteracao retorna NPC 18")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(18);

    CHECK(npc.id == 18);
}

TEST_CASE("BancoNpcInteracao retorna NPC 19")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(19);

    CHECK(npc.id == 19);
}

TEST_CASE("BancoNpcInteracao retorna NPC 20")
{
    InfoNPCInteracao npc = BancoNPCInteracao::obterNPC(20);

    CHECK(npc.id == 20);
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
        std::invalid_argument
    );
}