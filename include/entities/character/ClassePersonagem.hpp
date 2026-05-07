#ifndef CLASSEPERSONAGEM_HPP
#define CLASSEPERSONAGEM_HPP
#include <string>
#include <array>

    //Define o perfil do ataque, 
    //usado pela Batalha para cálculo de dano.
    enum class TipoAtaque {
        Fraco,
        Rapido,
        Forte
    };

    struct Ataque {
        std::string nome;
        std::string descricao;
        TipoAtaque tipo;
        double custoPP;
    };
    
    //Identifica o tipo de classe, 
    //que será usado para construir a ClassePersonagem com atributos e ataques específicos.
    enum class TipoClasse {
        Arqueiro,
        Guerreiro,
        Mago,
        Escudeiro
    };

    //Representa um conjunto de ataques que uma Classe de Personagem possui 
    //e armazena detalhes do tipo da Classe de Personagem.
    class ClassePersonagem {
        private:
            std::string nome;
            std::string descricao;
            std::string arma;
            std::array<Ataque, 3> ataques;

        public:
            ClassePersonagem(TipoClasse tipo);
            std::string getNome() const;
            std::string getDescricao() const;
            std::string getArma() const;
            const std::array<Ataque, 3>& getAtaques() const;
    };

#endif
