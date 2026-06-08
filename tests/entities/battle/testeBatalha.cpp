#include "../../doctest.h"

#include <algorithm>
#include <stdexcept>

#include "entities/battle/Batalha.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/map/Cena.hpp"
#include "entities/map/TrechoMapa.hpp"

// Helpers

static Personagem makePlayer() {
    return Personagem("Heroi", "Heroi das montanhas", "Pra você é sr. Eremita!",
                      20, 15, 100, 50, 10,
                      TipoClasse::Guerreiro, TipoPersonagem::Jogador);
}

static Personagem makeInimigo() {
    return Personagem("Orc", "Orc pirata", "Grr!",
                      8, 6, 30, 20, 5,
                      TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
}

// Estado inicial

TEST_CASE("Estado inicial de Batalha") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    CHECK(batalha.getTurno() == 0);
}

// Iniciar batalha

TEST_CASE("Iniciar Batalha avanca turno para 1") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK(batalha.getTurno() == 1);
}

TEST_CASE("Iniciar Batalha preenche acoes disponiveis") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK(!batalha.getAcoesDisponiveis().empty());
}

TEST_CASE("Iniciar Batalha define fator dificuldade positivo") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK(batalha.getFatorDificuldade() >= 0.0);
}

// Avanço de turno por ação

TEST_CASE("Ataque Simples avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Rapido avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueRapido);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Ataque Forte avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueForte);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Defesa avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Defesa);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Esquiva avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::Esquiva);

    CHECK(batalha.getTurno() == 2);
}

TEST_CASE("Usar Item avanca turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::UsarItem);

    CHECK(batalha.getTurno() == 2);
}

// Ação inválida

TEST_CASE("Acao invalida lanca excecao") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK_THROWS_AS(batalha.realizarAcao(static_cast<AcaoBatalha>(999)),
                    std::invalid_argument);
}

// Finalizar batalha

TEST_CASE("Finalizar Batalha reseta turno para 0") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.realizarAcao(AcaoBatalha::AtaqueSimples);
    batalha.finalizarBatalha();

    CHECK(batalha.getTurno() == 0);
}

// Processar defesa

TEST_CASE("Processar Defesa sem dano - defesa maior que ataque") {
    Dados dados(42);
    Personagem player("Tank", "Tank resistente", "Sai fora!",
                      10, 25, 100, 50, 10,
                      TipoClasse::Tanque, TipoPersonagem::Jogador);
    Personagem inimigo("Fraco", "Inimigo fraco", "Grr!",
                       10, 6, 30, 20, 5,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() == vidaAntes);
}

TEST_CASE("Processar Defesa com dano parcial - razao entre 0.8 e 1.0") {
    Dados dados(42);
    Personagem player("Medio", "Guerreiro medio", "Vamos!",
                      10, 15, 100, 50, 10,
                      TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Orc", "Orc bruto", "Raargh!",
                       18, 6, 30, 20, 5,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() < vidaAntes);
    CHECK(player.getVidaAtual() > vidaAntes - inimigo.getAtaque());
}

TEST_CASE("Processar Defesa com dano total - razao abaixo de 0.8") {
    Dados dados(42);
    Personagem player("Fragil", "Mago fragil", "Eita!",
                      10, 5, 100, 50, 10,
                      TipoClasse::Mago, TipoPersonagem::Jogador);
    Personagem inimigo("Forte", "Inimigo forte", "Raargh!",
                       20, 6, 30, 20, 5,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarDefesa();

    CHECK(player.getVidaAtual() < vidaAntes);
}

// Processar esquiva

TEST_CASE("Processar Esquiva sem dano - agilidade maior que ataque") {
    Dados dados(42);
    Personagem player("Agil", "Arqueiro agil", "Jamais conseguirá me acertar!",
                      15, 10, 100, 50, 25,
                      TipoClasse::Arqueiro, TipoPersonagem::Jogador);
    Personagem inimigo("Lento", "Inimigo lento", "Grr!",
                       18, 6, 30, 20, 5,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() == vidaAntes);
}

TEST_CASE("Processar Esquiva com dano total - agilidade menor que ataque") {
    Dados dados(42);
    Personagem player("Lento", "Guerreiro lento", "Vou te pegar!",
                      15, 10, 100, 50, 5,
                      TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Agil", "Inimigo agil", "Grr!",
                       18, 6, 30, 20, 25,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() < vidaAntes);
}

TEST_CASE("Processar Esquiva com dano parcial - agilidade igual ao ataque") {
    Dados dados(42);
    Personagem player("Medio", "Guerreiro medio", "Vamos!",
                      15, 10, 100, 50, 18,
                      TipoClasse::Guerreiro, TipoPersonagem::Jogador);
    Personagem inimigo("Igual", "Inimigo igual", "Grr!",
                       18, 6, 30, 20, 18,
                       TipoClasse::Guerreiro, TipoPersonagem::Inimigo);
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    batalha.processarEsquiva();

    CHECK(player.getVidaAtual() < vidaAntes);
    CHECK(player.getVidaAtual() > vidaAntes - inimigo.getAtaque());
}

// Definir recompensa

TEST_CASE("Definir Recompensa") {
    InfoCena infoCena{1, "O Louco", "espada_arcana", "Primeira cena", 1, {1}};
    Cena cena(infoCena);
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    batalha.definirRecompensa(cena);

    CHECK(cena.explorando() == true);
    CHECK(cena.emBatalha() == false);
}

// Aplicar condição

TEST_CASE("Aplicar condicao Envenenado ao player nao lanca excecao") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    Condicao envenenado{TipoCondicao::Envenenado, "Envenenado", 3, 5.0, ""};
    CHECK_NOTHROW(batalha.aplicarCondicao(envenenado, true));
}

TEST_CASE("Aplicar condicao Atordoado ao inimigo nao lanca excecao") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    Condicao atordoado{TipoCondicao::Atordoado, "", 2, 0.0, ""};
    CHECK_NOTHROW(batalha.aplicarCondicao(atordoado, false));
}

TEST_CASE("Paralisado remove todas as acoes disponiveis") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    Condicao paralisado{TipoCondicao::Paralisado, "", 1, 0.0, ""};
    batalha.aplicarCondicao(paralisado, true);

    CHECK(batalha.getAcoesDisponiveis().empty());
}

TEST_CASE("Atordoado remove AtaqueRapido e AtaqueForte das acoes") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    Condicao atordoado{TipoCondicao::Atordoado, "", 1, 0.0, ""};
    batalha.aplicarCondicao(atordoado, true);

    const auto& acoes = batalha.getAcoesDisponiveis();
    bool temRapido = std::find(acoes.begin(), acoes.end(), AcaoBatalha::AtaqueRapido) != acoes.end();
    bool temForte  = std::find(acoes.begin(), acoes.end(), AcaoBatalha::AtaqueForte)  != acoes.end();
    CHECK(!temRapido);
    CHECK(!temForte);
}

// Processar condições ativas

TEST_CASE("Processar condicoes ativas nao lanca excecao com lista vazia") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK_NOTHROW(batalha.processarCondicoesAtivas());
}

TEST_CASE("Envenenado causa dano ao player por turno") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    double vidaAntes = player.getVidaAtual();
    Condicao envenenado{TipoCondicao::Envenenado, "Envenenado", 2, 6.0, ""};
    batalha.aplicarCondicao(envenenado, true);
    batalha.processarCondicoesAtivas();

    CHECK(player.getVidaAtual() < vidaAntes);
}

TEST_CASE("Condicao expira apos duracao zerada") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();
    Condicao berserk{TipoCondicao::Berserk, "", 1, 3.0, ""};
    batalha.aplicarCondicao(berserk, true);
    batalha.processarCondicoesAtivas(); // expira após 1 turno

    // apos expirar, novo processamento não deve causar dano adicional
    double vidaAposExpiracao = player.getVidaAtual();
    batalha.processarCondicoesAtivas();
    CHECK(player.getVidaAtual() == vidaAposExpiracao);
}

// Verificar fuga

TEST_CASE("Verificar fuga em combate normal") {
    Dados dados(42);
    Personagem player = makePlayer();
    Personagem inimigo = makeInimigo();
    Batalha batalha(&player, &inimigo, dados);

    batalha.iniciarBatalha();

    CHECK(batalha.verificarFuga() == true);
}
