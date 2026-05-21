#include "doctest.h"
#include "Personagem.hpp"

/*
    ANOTAÇÕES IMPORTANTES
 Personagem
 (Nome,
 Descricao, 
 Fala,
 Ataque, 
 Defesa, 
 VidaTotal, 
 PPTotal, 
 Agilidade, 
 TipoClasse, 
 TipoPersonagem, 
 Nivel(Opcional))

 Nível        Quantidade de Xp
 1                   300
 2                   900
 3                   2.700
 4                   6.500
 5                   14.000
 6                   23.000
 7                   34.000
 8                   48.000
 9                   64.000
 10                            
*/

//Testes de Construtor de Personagem
TEST_CASE("Construtor de Personagem")  {
    Personagem p("John Doe", "Descricao", "Fala", 
        17, 20, 100, 50, 20, 
        TipoClasse::Guerreiro, 
        TipoPersonagem::Jogador);

    CHECK(p.getNome() == "John Doe");
    CHECK(p.getDescricao() == "Descricao");
    CHECK(p.getFala() == "Fala");
    CHECK(p.getAtaque() == 17);
    CHECK(p.getDefesa() == 20);
    CHECK(p.getVidaAtual() == 100);
    CHECK(p.getManaAtual() == 50);
    CHECK(p.getAgilidade() == 20);
    CHECK(p.getClasse().getTipo() == TipoClasse::Guerreiro);
    CHECK(p.getTipo() == TipoPersonagem::Jogador);
}


//Testes de Dano
TEST_CASE("Recebeu dano corretamente") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::NPC);

    p.receberDano(20);
    CHECK(p.getVidaAtual() == 80);
}

TEST_CASE("Recebeu dano acima da vida atual") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::NPC);

    p.receberDano(500);
    CHECK(p.getVidaAtual() == 0);
}

//Testes de Recuperar Vida
TEST_CASE("Recuperou vida") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Mago, 
        TipoPersonagem::NPC);

    p.receberDano(20);
    p.recuperarVida(15);
    CHECK(p.getVidaAtual() == 95);
}

TEST_CASE("Recuperou vida acima do total") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.recuperarVida(100);
    CHECK(p.getVidaAtual() == 100);
}


//Testes de Mana
TEST_CASE("Gastou mana") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.gastarMana(20);
    CHECK(p.getManaAtual() == 30);
}

TEST_CASE("Gastou mana acima do valor maximo") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 

    p.gastarMana(100);
    CHECK(p.getManaAtual() == 0);
}

TEST_CASE("Recuperou mana") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.gastarMana(20);
    p.recuperarMana(15);
    CHECK(p.getManaAtual() == 45);
}

TEST_CASE("Recuperou mana acima do maximo") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.recuperarMana(100);
    CHECK(p.getManaAtual() == 50);
}
//Testes de Experiencia 
TEST_CASE("Ganhou experiencia") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.ganharXp(20);
    CHECK(p.getXp() == 20);
}

TEST_CASE("Ganhou experiencia e Subiu de nivel") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.ganharXp(300);
    CHECK(p.getXp() == 0);
    CHECK(p.getNivel() == 2);
}


TEST_CASE("Ganhou experiencia acima da quantidade para subir de nivel") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Tanque, 
        TipoPersonagem::NPC); 
    
    p.ganharXp(320);
    CHECK(p.getXp() == 20);
    CHECK(p.getNivel() == 2);
}

//Teste de Vivo ou Morto
TEST_CASE("Recebeu dano ate morrer") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::NPC);

    p.receberDano(100);
    CHECK(p.getVidaAtual() == 0);
    CHECK(p.estaVivo() == false);
}

TEST_CASE("Recebeu dano mas continua vivo") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::NPC);

    p.receberDano(90);
    CHECK(p.getVidaAtual() == 10);
    CHECK(p.estaVivo() == true);
}

TEST_CASE("Recebeu dano, morreu e voltou a vida") {
    Personagem p("Nome", "Desc", "Fala",
        17, 20, 100, 50, 20, 
        TipoClasse::Arqueiro, 
        TipoPersonagem::NPC);

    p.receberDano(100);
    p.recuperarVida(20);
    CHECK(p.estaVivo() == true);
}