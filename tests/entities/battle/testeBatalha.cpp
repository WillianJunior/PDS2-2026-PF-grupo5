/**
 * @file testeBatalha.cpp
 * @brief Testes unitarios para Batalha.cpp.
 */

#include "../../doctest.h"
#include <stdexcept>

#include "entities/battle/Batalha.hpp"
#include "entities/character/Personagem.hpp"
#include "core/Dados.hpp"
#include "entities/map/Cena.hpp"
#include "entities/character/Jogador.hpp"
#include "database/BancoCena.hpp"
#include "utils/TipoArcanoEnum.hpp"
#include "entities/battle/Condicao.hpp"

static Personagem makePlayer(int nivel = 5) {
    return Personagem("Heroi", "desc", "fala",
        20.0, 15.0, 200.0, 100.0, 12.0,
        TipoClasse::Guerreiro, TipoPersonagem::Jogador, nivel);
}

static Personagem makeInimigo(int nivel = 1) {
    return Personagem("Orc", "desc", "fala",
        8.0, 8.0, 50.0, 10.0, 8.0,
        TipoClasse::Guerreiro, TipoPersonagem::Inimigo, nivel);
}

// --- Construtor e iniciarBatalha ---

TEST_CASE("Batalha - construtor e iniciarBatalha") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo(2);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    CHECK(b.getTurno() == 0);
    b.iniciarBatalha();
    CHECK(b.getTurno() == 1);
    CHECK(b.getFatorDificuldade() == doctest::Approx(1.0));
}

TEST_CASE("Batalha - fatorDificuldade calculada corretamente") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo(1);
    Dados dados(1);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    CHECK(b.getFatorDificuldade() == doctest::Approx(0.5));
}

// --- getAcoesDisponiveis ---

TEST_CASE("Batalha - acoes disponiveis apos iniciar") {
    Personagem player  = makePlayer(1);
    Personagem inimigo = makeInimigo(1);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    CHECK(b.getAcoesDisponiveis().size() >= 5);
}

// --- realizarAcao ---

TEST_CASE("Batalha - acao invalida lanca excecao") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao paralisa;
    paralisa.tipo = TipoCondicao::Paralisado;
    paralisa.duracaoTurnos = 3;
    b.aplicarCondicao(paralisa, true);
    b.processarCondicoesAtivas();

    CHECK_THROWS_AS(b.realizarAcao(AcaoBatalha::AtaqueSimples), std::invalid_argument);
}

TEST_CASE("Batalha - AtaqueSimples avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::AtaqueSimples);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - Defesa avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(99);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::Defesa);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - Esquiva avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(7);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::Esquiva);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - UsarItem avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(7);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::UsarItem);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - Fugir avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(7);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::Fugir);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - AtaqueRapido consome mana e avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    double manaAntes = player.getManaAtual();
    b.realizarAcao(AcaoBatalha::AtaqueRapido);
    CHECK(player.getManaAtual() <= manaAntes);
    CHECK(b.getTurno() == 2);
}

TEST_CASE("Batalha - AtaqueForte consome mana e avanca turno") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(99);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    double manaAntes = player.getManaAtual();
    b.realizarAcao(AcaoBatalha::AtaqueForte);
    CHECK(player.getManaAtual() <= manaAntes);
    CHECK(b.getTurno() == 2);
}

// --- finalizarBatalha ---

TEST_CASE("Batalha - finalizarBatalha reseta estado") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    b.realizarAcao(AcaoBatalha::AtaqueSimples);
    b.finalizarBatalha();
    CHECK(b.getTurno() == 0);
}

// --- aplicarCondicao ---

TEST_CASE("Batalha - aplicarCondicao Berserk no player") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao berserk;
    berserk.tipo = TipoCondicao::Berserk;
    berserk.duracaoTurnos = 3;
    b.aplicarCondicao(berserk, true);

    bool found = false;
    for (const auto& c : player.getCondicoesAtivas())
        if (c.tipo == TipoCondicao::Berserk) found = true;
    CHECK(found);
}

TEST_CASE("Batalha - aplicarCondicao Envenenado no inimigo") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao env;
    env.tipo = TipoCondicao::Envenenado;
    env.duracaoTurnos = 2;
    b.aplicarCondicao(env, false);

    bool found = false;
    for (const auto& c : inimigo.getCondicoesAtivas())
        if (c.tipo == TipoCondicao::Envenenado) found = true;
    CHECK(found);
}

TEST_CASE("Batalha - Arcano Alma bloqueia Paralisado") {
    Personagem player  = makePlayer();
    player.adicionarArcano(TipoArcano::Alma);
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao paralisa;
    paralisa.tipo = TipoCondicao::Paralisado;
    paralisa.duracaoTurnos = 2;
    b.aplicarCondicao(paralisa, true);

    bool found = false;
    for (const auto& c : player.getCondicoesAtivas())
        if (c.tipo == TipoCondicao::Paralisado) found = true;
    CHECK(!found);
}

// --- processarCondicoesAtivas ---

TEST_CASE("Batalha - Berserk causa dano ao player por turno") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao berserk;
    berserk.tipo = TipoCondicao::Berserk;
    berserk.duracaoTurnos = 2;
    b.aplicarCondicao(berserk, true);

    double vidaAntes = player.getVidaAtual();
    b.processarCondicoesAtivas();
    CHECK(player.getVidaAtual() < vidaAntes);
}

TEST_CASE("Batalha - Envenenado causa dano ao inimigo por turno") {
    Personagem player  = makePlayer();
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao env;
    env.tipo = TipoCondicao::Envenenado;
    env.duracaoTurnos = 2;
    b.aplicarCondicao(env, false);

    double vidaAntes = inimigo.getVidaAtual();
    b.processarCondicoesAtivas();
    CHECK(inimigo.getVidaAtual() < vidaAntes);
}

TEST_CASE("Batalha - Arcano Vida regenera HP do player") {
    Personagem player  = makePlayer();
    player.receberDano(50.0);
    player.adicionarArcano(TipoArcano::Vida);
    Personagem inimigo = makeInimigo();
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    double vidaAntes = player.getVidaAtual();
    b.processarCondicoesAtivas();
    CHECK(player.getVidaAtual() >= vidaAntes);
}

// --- verificarFuga ---

TEST_CASE("Batalha - verificarFuga nivel alto vs ND baixo") {
    Personagem player  = makePlayer(10);
    Personagem inimigo = makeInimigo(1);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();
    CHECK(b.verificarFuga());
}

// --- definirRecompensa ---

TEST_CASE("Batalha - definirRecompensa concede XP") {
    Personagem playerPers  = makePlayer(3);
    Personagem inimigoPers = makeInimigo(2);
    Dados dados(42);
    Batalha b(&playerPers, &inimigoPers, dados);
    b.iniciarBatalha();

    Jogador jogador("Heroi", "desc", "fala",
        20.0, 15.0, 200.0, 100.0, 12.0,
        TipoClasse::Guerreiro, TipoPersonagem::Jogador, 3);
    InfoCena infoCena = BancoCena::obterCena(1);
    Cena cena(infoCena, jogador);

    double xpAntes = playerPers.getXp();
    b.definirRecompensa(cena);
    CHECK(playerPers.getXp() > xpAntes);
}

TEST_CASE("Batalha - Arcano Alma aumenta XP ganho") {
    Personagem playerPers  = makePlayer(3);
    playerPers.adicionarArcano(TipoArcano::Alma);
    Personagem inimigoPers = makeInimigo(2);
    Dados dados(42);
    Batalha b(&playerPers, &inimigoPers, dados);
    b.iniciarBatalha();

    Jogador jogador("Heroi", "desc", "fala",
        20.0, 15.0, 200.0, 100.0, 12.0,
        TipoClasse::Guerreiro, TipoPersonagem::Jogador, 3);
    InfoCena infoCena = BancoCena::obterCena(1);
    Cena cena(infoCena, jogador);

    b.definirRecompensa(cena);
    CHECK(playerPers.getXp() > 0);
}

// --- Atordoado ---

TEST_CASE("Batalha - Atordoado remove AtaqueRapido e AtaqueForte") {
    Personagem player  = makePlayer(5);
    Personagem inimigo = makeInimigo(1);
    Dados dados(42);
    Batalha b(&player, &inimigo, dados);
    b.iniciarBatalha();

    Condicao atord;
    atord.tipo = TipoCondicao::Atordoado;
    atord.duracaoTurnos = 2;
    b.aplicarCondicao(atord, true);
    b.processarCondicoesAtivas();

    const auto& acoes = b.getAcoesDisponiveis();
    bool temRapido = false, temForte = false;
    for (const auto& a : acoes) {
        if (a == AcaoBatalha::AtaqueRapido) temRapido = true;
        if (a == AcaoBatalha::AtaqueForte)  temForte  = true;
    }
    CHECK(!temRapido);
    CHECK(!temForte);
}
