#include "doctest.h"
#include "ClassePersonagem.hpp"

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
        CHECK(p.getDescricao() == "Alta agilidade e ataques à distância");
        CHECK(p.getArma() == "Arco");
}

TEST_CASE("Construtor de ClassePersonagem para Guerreiro") {
        ClassePersonagem p(TipoClasse::Guerreiro);

        CHECK(p.getNome() == "Guerreiro");
        CHECK(p.getTipo() == TipoClasse::Guerreiro);
        CHECK(p.getDescricao() == "Alta resistência física");
        CHECK(p.getArma() == "Espada");
}

TEST_CASE("Construtor de ClassePersonagem para Mago") {
        ClassePersonagem p(TipoClasse::Mago);

        CHECK(p.getNome() == "Mago");
        CHECK(p.getTipo() == TipoClasse::Mago);
        CHECK(p.getDescricao() == "Uso ampliado de habilidades mágicas");
        CHECK(p.getArma() == "Magia");
}


TEST_CASE("Construtor de ClassePersonagem para Tanque") {
        ClassePersonagem p(TipoClasse::Tanque);

        CHECK(p.getNome() == "Tanque");
        CHECK(p.getTipo() == TipoClasse::Tanque);
        CHECK(p.getDescricao() == "Bloqueio e redução de dano");
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

        CHECK(p.getAtaque(TipoAtaque::Simples).nome == "Ataque Simples");
        CHECK(p.getAtaque(TipoAtaque::Simples).descricao == "-");
        CHECK(p.getAtaque(TipoAtaque::Simples).custoPP == 0);

        CHECK(p.getAtaque(TipoAtaque::Rapido).nome == "Tiro Rápido");
        CHECK(p.getAtaque(TipoAtaque::Rapido).descricao == "Saca e solta duas flechas em sequência.");
        CHECK(p.getAtaque(TipoAtaque::Rapido).custoPP == 10);

        CHECK(p.getAtaque(TipoAtaque::Forte).nome == "Flecha Explosiva");
        CHECK(p.getAtaque(TipoAtaque::Forte).descricao == "A flecha detona no alvo.");
        CHECK(p.getAtaque(TipoAtaque::Forte).custoPP == 30);
}