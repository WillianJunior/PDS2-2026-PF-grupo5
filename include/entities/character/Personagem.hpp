/**
 * @file Personagem.hpp
 * @brief Definição da classe Personagem, responsável por gerenciar estados e atributos de indivíduos no jogo.
 */

#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include "ClassePersonagem.hpp"

/**
 * @enum TipoPersonagem
 * @brief Define as categorias dos personagens do jogo.
 */
enum class TipoPersonagem { 
    Jogador, ///< Personagem controlado pelo usuário.
    Inimigo, ///< Oponentes comuns encontrados em cenas.
    NPC,     ///< Personagens aliados encontrados em cena.
    BOSS     ///< Inimigos especiais específicos das Cenas.
};

/**
 * @class Personagem
 * @brief Representa um indivíduo único no mundo do jogo.
 * Mantém os atributos (vida, mana, agilidade, ataque, defesa)
 * e a lógica de progressão (nível, experiência) de cada personagem.
 */
class Personagem {
    private:
        std::string _nome;          ///< Nome único do indivíduo.
        double _ataque;             ///< Pontuação de ataque.
        double _defesa;             ///< Pontuação de defesa.
        double _vidaAtual;          ///< Pontos de vida remanescentes.
        double _vidaTotal;          ///< Limite máximo de pontos de vida.
        double _ppAtual;            ///< Pontos de Poder (Mana) disponíveis.
        double _ppTotal;            ///< Capacidade máxima de mana.
        double _agilidade;          ///< Pontuação de agilidade. Influencia a esquiva e velocidade.
        int _nivel;                 ///< Nível atual de progressão.
        double _xp;                 ///< Pontos de experiência acumulados.

        TipoPersonagem _tipo;       ///< Categoria da entidade.
        ClassePersonagem _classe;   ///< Arquétipo que define as habilidades disponíveis.

    public:
    /**
         * @brief Construtor para inicialização de um personagem individualizado.
         * @param nome Nome do personagem.
         * @param ataque Pontos de ataque iniciais.
         * @param defesa Pontos de defesa iniciais.
         * @param vidaTotal Limite máximo de vida.
         * @param ppTotal Limite máximo de mana.
         * @param agilidade Pontos de agilidade iniciais.
         * @param tipoClasse Enum que define o arquétipo.
         * @param tipo Categoria (Jogador, Boss, etc).
         * @param nivel Nível inicial (default = 1).
         */
        Personagem(
            std::string nome, 
            double ataque, 
            double defesa, 
            double vidaTotal, 
            double ppTotal, 
            double agilidade, 
            TipoClasse tipoClasse,
            TipoPersonagem tipo,
            int nivel = 1);

        /**
         * @brief Reduz a vida atual do personagem com base em um ataque.
         * @param dano Quantidade de dano a ser subtraída.
         */
        void receberDano(double dano);

        /**
         * @brief Incrementa a vida atual, respeitando o limite máximo.
         * @param cura Quantidade de pontos de vida recuperados.
         */
        void recuperarVida(double cura); 

        /**
         * @brief Recupera pontos de mana.
         * @param quantidadeMana Valor a ser recuperado.
         */
        void recuperarMana(double quantidadeMana);

        /**
         * @brief Deduz pontos de mana para a execução de ataques.
         * @param custoMana Valor de mana consumido.
         */
        void gastarMana(double custoMana); 

        /**
         * @brief Adiciona experiência e verifica condições para subir de nível.
         * @param quantidadeXp Valor de experiência recebido.
         */
        void ganharExperiencia(double quantidadeXp);

        /**
         * @brief Incrementa o nível e melhora os atributos base do personagem.
         */
        void subirNivel();

        /**
         * @brief Verifica se a vida atual é superior a zero.
         * @return true se o personagem estiver vivo, false caso não esteja.
         */
        bool estaVivo() const;

        // Getters
        /** @return Vida atual do personagem. */
        double getVidaAtual() const;
        /** @return Valor do atributo de ataque. */
        double getAtaque() const;
        /** @return Valor do atributo de defesa. */
        double getDefesa() const;
        /** @return Valor do atributo de agilidade. */
        double getAgilidade() const;
        /** @return Nível atual do personagem. */
        int getNivel() const;
        /** @return Experiência acumulada. */
        double getXp() const;
        /** @return Tipo (Jogador, Inimigo, etc). */
        TipoPersonagem getTipo() const;
        /** @return Referência constante à classe/arquétipo. */
        const ClassePersonagem& getClasse() const;   

        
};

#endif