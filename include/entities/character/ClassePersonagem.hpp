/**
 * @file ClassePersonagem.hpp
 * @brief Definição das estruturas de arquétipos e ataques do jogo.
 */

#ifndef CLASSEPERSONAGEM_HPP
#define CLASSEPERSONAGEM_HPP

#include <string>
#include <array>
#include "utils/AtaqueEnum.hpp"
#include "battle/Condicao.hpp"

/**
 * @enum TipoAtaque
 * @brief Define o perfil do ataque para cálculos de dano na Batalha.
 */
enum class TipoAtaque {
    Simples,  ///< Baseado apenas nos pontos de ataque.
    Rapido,   ///< Usa agilidade e consome mana.
    Forte     ///< Dano massivo, alto consumo de mana, reduz defesa inimiga.
};

/**
 * @enum TimingEfeito
 * @brief Define se um efeito é aplicado antes ou depois do ataque.
 */
enum class TimingEfeito {
    AntesDoAcerto,
    DepoisDoAcerto
};

/**
 * @struct Ataque
 * @brief Estrutura que armazena os dados do efeito que um ataque possui.
 */
struct EfeitoAtaque {
    TimingEfeito timing = TimingEfeito::AntesDoAcerto; //< Quando o efeito é considerado
    Condicao condicao;                                 //< Condição que o efeito causa
    int chance = 0;                                    //< Probabilidade do Efeito ser causado
    int hit = 1;                                       //< Qual hit o efeito deve ser considerado
    bool afetaProprio = false;                         //< Efeito afeta o próprio personagem.
};

/**
 * @struct Ataque
 * @brief Estrutura que armazena os dados brutos de um golpe específico.
 */
struct Ataque {
    IdAtaque id;           ///< Identificador do ataque.
    std::string nome;      ///< Nome do ataque.
    std::string descricao; ///< Descrição do ataque.
    TipoAtaque tipo;       ///< Categoria (Simples, Rapido ou Forte).
    double custoPP;        ///< Custo de Mana (Pontos de Poder) para execução.
    EfeitoAtaque efeito;   ///< Efeito que o ataque aplica ao ser usado.
};
/**
 * @enum TipoClasse
 * @brief Identificadores para os tipos de heróis disponíveis.
 */
enum class TipoClasse {
    Arqueiro,
    Guerreiro,
    Mago,
    Tanque
};

/**
 * @class ClassePersonagem
 * @brief Representa o arquétipo de um personagem, definindo seus ataques e armas, e
 * fornece os dados necessários para que a Batalha e o Personagem 
 * saibam quais habilidades estão disponíveis conforme a escolha do jogador.
 */
class ClassePersonagem {
private:
    TipoClasse _tipo;                ///< Tipo da classe (ex: "Mago").
    std::string _descricao;          ///< Breve história (flavor) da classe.
    std::string _arma;               ///< Tipo de arma utilizada (flavor).
    std::array<Ataque, 3> _ataques;  ///< Lista fixa de 3 ataques por classe.

public:
    /**
     * @brief Construtor que inicializa a classe com seus atributos básicos.
     * @param tipo O enumerador que define qual classe será construída.
     */
    ClassePersonagem(TipoClasse tipo);

    //Getters
    /** @return Nome da classe. */
    std::string getNome() const;

    /** @return Descrição das características da classe. */
    std::string getDescricao() const;

    /** @return Nome da arma padrão da classe. */
    std::string getArma() const;

    /** @return Nome da arma padrão da classe. */
    TipoClasse getTipo() const;

    /**
     * @brief Retorna a lista de ataques disponíveis.
     * @return Referência constante para o array de ataques.
     */
    const std::array<Ataque, 3>& getAtaques() const;

    /**
     *  @return  Devolve um Ataque
     *  @param tipo O tipo do Ataque para devolver. 
    */
    const Ataque& getAtaque(TipoAtaque tipo) const;

    /**
     * @brief Altera o Ataque forte.
     * @param nivel O nivel atual do Personagem.
     */
    void alteraAtaqueForte(int nivel);

    //Setters
    /**
     * @brief Altera a Descrição do Personagem.
     * @param descricao O texto definido para ser a Descrição.
     */
    void setDescricao(std::string descricao);

    /**
     * @brief Altera a Arma do Personagem (flavor).
     * @param nomeArma O texto definido para ser a o nome da Arma.
     */
    void setArma(std::string nomeArma);
};

#endif