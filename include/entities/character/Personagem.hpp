/**
 * @file Personagem.hpp
 * @brief Definicao da classe Personagem, responsavel por gerenciar estados e atributos de individuos no jogo.
 */

#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include <vector>
#include "../character/ClassePersonagem.hpp"
#include "../battle/Condicao.hpp"
#include "utils/TipoArcanoEnum.hpp"
#include <cassert>
#include <array>

/**
 * @enum TipoPersonagem
 * @brief Define as categorias dos personagens do jogo.
 */
enum class TipoPersonagem {
    Jogador, ///< Personagem controlado pelo usuario.
    Inimigo, ///< Oponentes comuns encontrados em cenas.
    NPC,     ///< Personagens aliados encontrados em cena.
    BOSS     ///< Inimigos especiais especificos das Cenas.
};

/**
 * @enum XpNiveis
 * @brief Define todos os valores para subir de nivel ordenado
 */
constexpr std::array<double, 10> XpNiveis = {
    300,
    900,
    2700,
    6500,
    14000,
    23000,
    34000,
    48000,
    64000
};

/**
 * @class Personagem
 * @brief Representa um individuo unico no mundo do jogo.
 * Mantem os atributos (vida, mana, agilidade, ataque, defesa)
 * e a logica de progressao (nivel, experiencia) de cada personagem.
 */
class Personagem {
    private:
        std::string _nome;          ///< Nome unico do individuo.
        std::string _descricao;     ///< Breve historia (flavor) do personagem.
        std::string _fala;          ///< Fala do personagem em batalhas ou na cena.
        double _ataque;             ///< Pontuacao de ataque.
        double _defesa;             ///< Pontuacao de defesa.
        double _vidaAtual;          ///< Pontos de vida remanescentes.
        double _vidaTotal;          ///< Limite maximo de pontos de vida.
        double _ppAtual;            ///< Pontos de Poder (Mana) disponiveis.
        double _ppTotal;            ///< Capacidade maxima de mana.
        double _agilidade;          ///< Pontuacao de agilidade. Influencia a esquiva e velocidade.
        int _nivel;                 ///< Nivel atual de progressao.
        double _xp;                 ///< Pontos de experiencia acumulados.

        TipoPersonagem _tipo;                   ///< Categoria da entidade.
        ClassePersonagem _classe;               ///< Arquetipo que define as habilidades disponiveis.
        std::vector<Condicao> _condicoesAtivas; ///< Condicoes ativas aplicadas ao personagem.
        std::vector<TipoArcano> _arcanosAtivos; ///< Arcanos primordiais adquiridos pelo personagem.

    public:
        /**
         * @brief Construtor para inicializacao de um personagem individualizado.
         * @param nome Nome do personagem.
         * @param descricao Breve descricao/historia do personagem.
         * @param fala Fala do personagem em batalha ou cena.
         * @param ataque Pontos de ataque iniciais.
         * @param defesa Pontos de defesa iniciais.
         * @param vidaTotal Limite maximo de vida.
         * @param ppTotal Limite maximo de mana.
         * @param agilidade Pontos de agilidade iniciais.
         * @param tipoClasse Enum que define o arquetipo.
         * @param tipo Categoria (Jogador, Boss, etc).
         * @param nivel Nivel inicial (default = 1).
         */
        Personagem(
            std::string nome,
            std::string descricao,
            std::string fala,
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
         * @param dano Quantidade de dano a ser subtraida.
         */
        void receberDano(double dano);

        /**
         * @brief Incrementa a vida atual, respeitando o limite maximo.
         * @param cura Quantidade de pontos de vida recuperados.
         */
        void recuperarVida(double cura);

        /**
         * @brief Recupera pontos de mana.
         * @param quantidadeMana Valor a ser recuperado.
         */
        void recuperarMana(double quantidadeMana);

        /**
         * @brief Deduz pontos de mana para a execucao de ataques.
         * @param custoMana Valor de mana consumido.
         */
        void gastarMana(double custoMana);

        /**
         * @brief Adiciona experiencia e verifica condicoes para subir de nivel.
         * @param quantidadeXp Valor de experiencia recebido.
         */
        void ganharXp(double quantidadeXp);

        /**
         * @brief Incrementa o nivel e melhora os atributos base do personagem.
         */
        void subirNivel();

        /**
         * @brief Verifica se a vida atual e superior a zero.
         * @return true se o personagem estiver vivo, false caso nao esteja.
         */
        bool estaVivo() const;

        // Getters
        /** @return Nome do personagem */
        std::string getNome() const;
        /** @return Descricao do personagem */
        std::string getDescricao() const;
        /** @return Fala do personagem */
        std::string getFala() const;
        /** @return Vida atual do personagem. */
        double getVidaAtual() const;
        /** @return Limite maximo de vida. */
        double getVidaTotal() const;
        /** @return Valor do atributo de ataque. */
        double getAtaque() const;
        /** @return Valor do atributo de defesa. */
        double getDefesa() const;
        /** @return Valor do atributo de agilidade. */
        double getAgilidade() const;
        /** @return Mana Atual */
        double getManaAtual() const;
        /** @return Nivel atual do personagem. */
        int getNivel() const;
        /** @return Experiencia acumulada. */
        double getXp() const;
        /** @return Tipo (Jogador, Inimigo, etc). */
        TipoPersonagem getTipo() const;
        /** @return Referencia constante a classe/arquetipo. */
        const ClassePersonagem& getClasse() const;

        /**
         * @brief Aplica uma condicao ao personagem.
         * Para ModAtributo, modifica o atributo imediatamente e armazena para reverter depois.
         * Para outros tipos, apenas armazena (batalha processa por turno).
         */
        void aplicarCondicao(const Condicao& condicao);

        /**
         * @brief Remove e reverte a condicao na posicao indicada.
         * @param posicao Indice em _condicoesAtivas.
         */
        void removerCondicao(int posicao);

        /** @return Referencia constante as condicoes ativas. */
        const std::vector<Condicao>& getCondicoesAtivas() const;

        /**
         * @brief Altera o ataque forte do personagem.
         * Usado por outros para alterar o ataque sem precisar de acesso a classe.
         * Utiliza o nivel do personagem internamente.
         * @see ClassePersonagem.hpp - Implementacao interna da alteracao de ataque.
         */
        void alteraAtaqueForte();

        // Arcanos

        /**
         * @brief Concede um Arcano ao personagem.
         * @param arcano O Arcano a ser adquirido.
         * @note Arcanos duplicados sao ignorados (cada arcano pode ser obtido apenas uma vez).
         */
        void adicionarArcano(TipoArcano arcano);

        /**
         * @brief Verifica se o personagem possui um determinado Arcano.
         * @param arcano O Arcano a ser verificado.
         * @return true se o Arcano estiver ativo.
         */
        bool temArcano(TipoArcano arcano) const;

        /**
         * @brief Retorna a lista de Arcanos ativos do personagem.
         * @return Referencia constante ao vetor de arcanos.
         */
        const std::vector<TipoArcano>& getArcanos() const;
};

#endif
