#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP
#include <string>
#include "ClassePersonagem.hpp"

    //Define os tipos de personagens possiveis
    enum class TipoPersonagem { 
        Jogador,
        Inimigo,
        NPC,
        BOSS,
    };

    //Representar um indivíduo do jogo, mantém seu estado (vida, mana, ataque).
    //Responde a eventos como dano, cura e progressão, alterando seu estado.
    class Personagem {
        private:
        //Atributos que todo personagem possui.
            std::string nome;
            double ataque;
            double defesa;
            double vidaAtual;
            double vidaTotal;
            double ppAtual;
            double ppTotal; 
            double agilidade;
            int nivel;
            double xp;

            TipoPersonagem tipo;
            ClassePersonagem classe; //Define quais ataques o Personagem possui.

        public:
            //Todas as ações possiveis que um personagem pode ser afetado.
            void receberDano(double dano);
            void recuperarVida(double cura); 
            void recuperarMana(double quantidadeMana);
            void gastarMana(double custoMana); 
            void ganharExperiencia(double quantidadeXp);
            void subirNivel();
            bool estaVivo() const; //Facilita saber se o Personagem esta vivo ou não.

            //Getters
            double getVidaAtual() const;
            double getAtaque() const;
            double getDefesa() const;
            double getAgilidade() const;
            int getNivel() const;
            double getXp() const;
            TipoPersonagem getTipo() const;
            const ClassePersonagem& getClasse() const;   

            //Construtor que mantêm o conceito que todo personagem é individual 
            //e precisa ter seus atributos deifnidos
            Personagem(
                std::string nome, 
                double ataque, 
                double defesa, 
                double vidaTotal, 
                double ppTotal, 
                double agilidade, 
                TipoClasse tipoClasse,
                TipoPersonagem tipo,
                int nivel = 1); //Nível inicia 1 mas pode ser escolhido com outro valor inicial. 
    };
#endif