#include "../../doctest.h"

#include "entities/character/ClassePersonagem.hpp"

/*
Ordem dos ataques:
0.Simples
1.Rapido      
2.Forte
*/

//Testes de Construtor de ClassePersonagem
TEST_CASE("Construtor de ClassePersonagem para Arqueiro") {
        ClassePersonagem p(TipoClasse::Arqueiro);

        CHECK(p.getNome() == "Arqueiro");
        CHECK(p.getTipo() == TipoClasse::Arqueiro);
        CHECK(p.getDescricao() == "Velocidade e precisão, ataques múltiplos");
        CHECK(p.getArma() == "Arco");
}

TEST_CASE("Construtor de ClassePersonagem para Guerreiro") {
        ClassePersonagem p(TipoClasse::Guerreiro);

        CHECK(p.getNome() == "Guerreiro");
        CHECK(p.getTipo() == TipoClasse::Guerreiro);
        CHECK(p.getDescricao() == "Alto dano, resistente, combate direto");
        CHECK(p.getArma() == "Espada");
}

TEST_CASE("Construtor de ClassePersonagem para Mago") {
        ClassePersonagem p(TipoClasse::Mago);

        CHECK(p.getNome() == "Mago");
        CHECK(p.getTipo() == TipoClasse::Mago);
        CHECK(p.getDescricao() == "Dano mágico elevado, baixa defesa");
        CHECK(p.getArma() == "Magia");
}


TEST_CASE("Construtor de ClassePersonagem para Tanque") {
        ClassePersonagem p(TipoClasse::Tanque);

        CHECK(p.getNome() == "Tanque");
        CHECK(p.getTipo() == TipoClasse::Tanque);
        CHECK(p.getDescricao() == "Máxima resistência, dano baseado em Defesa");
        CHECK(p.getArma() == "Escudo");
}

//Teste de Ataques
TEST_CASE("Todas as classes possuem ataques ordenados corretamente") {

    std::array<TipoClasse, 4> classes = {
        TipoClasse::Arqueiro,
        TipoClasse::Guerreiro,
        TipoClasse::Mago,
        TipoClasse::Tanque
    };

    for (const auto& tipoClasse : classes) {
        ClassePersonagem p(tipoClasse);
        const auto& ataques = p.getAtaques();

        CHECK(ataques[0].tipo == TipoAtaque::Simples);
        CHECK(ataques[1].tipo == TipoAtaque::Rapido);
        CHECK(ataques[2].tipo == TipoAtaque::Forte);
    }
}

TEST_CASE("Detalhes de ataques definidos corretamente") {
        ClassePersonagem p(TipoClasse::Arqueiro);

        CHECK(p.getAtaque(TipoAtaque::Simples).nome == "Flecha");
        CHECK(p.getAtaque(TipoAtaque::Simples).descricao == "Fraco porém não gasta mana.");
        CHECK(p.getAtaque(TipoAtaque::Simples).custoPP == 0);

        CHECK(p.getAtaque(TipoAtaque::Rapido).nome == "Tiro Rápido");
        CHECK(p.getAtaque(TipoAtaque::Rapido).descricao == "Saca e solta duas flechas em sequência.");
        CHECK(p.getAtaque(TipoAtaque::Rapido).custoPP == 10);

        CHECK(p.getAtaque(TipoAtaque::Forte).nome == "Flecha Explosiva");
        CHECK(p.getAtaque(TipoAtaque::Forte).descricao == "A flecha detona ao impactar, espalhando fogo nos pés do inimigo.");
        CHECK(p.getAtaque(TipoAtaque::Forte).custoPP == 30);
}

TEST_CASE("alteraAtaqueForte - ataque forte inicial do Guerreiro") {
    ClassePersonagem g(TipoClasse::Guerreiro);
    CHECK(g.getAtaque(TipoAtaque::Forte).nome == "Fúria Berserker");
}

TEST_CASE("alteraAtaqueForte - nivel 3 muda ataque forte do Guerreiro") {
    ClassePersonagem g(TipoClasse::Guerreiro);
    g.alteraAtaqueForte(3);
    CHECK(g.getAtaque(TipoAtaque::Forte).nome == "Golpe Devastador");
}

TEST_CASE("alteraAtaqueForte - nivel 5 muda ataque forte do Guerreiro") {
    ClassePersonagem g(TipoClasse::Guerreiro);
    g.alteraAtaqueForte(5);
    CHECK(g.getAtaque(TipoAtaque::Forte).nome == "Perfuração");
}

TEST_CASE("alteraAtaqueForte - nivel 7 muda ataque forte do Guerreiro") {
    ClassePersonagem g(TipoClasse::Guerreiro);
    g.alteraAtaqueForte(7);
    CHECK(g.getAtaque(TipoAtaque::Forte).nome == "Golpe do Abismo");
}

TEST_CASE("alteraAtaqueForte - nivel nao reconhecido nao altera ataque forte") {
    ClassePersonagem g(TipoClasse::Guerreiro);
    std::string nomeOriginal = g.getAtaque(TipoAtaque::Forte).nome;
    g.alteraAtaqueForte(2);
    CHECK(g.getAtaque(TipoAtaque::Forte).nome == nomeOriginal);
}