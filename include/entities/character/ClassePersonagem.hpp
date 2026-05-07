/**
 * @file ClassePersonagem.hpp
 * @brief Definição das estruturas de arquétipos e ataques do jogo.
 */

#ifndef CLASSEPERSONAGEM_HPP
#define CLASSEPERSONAGEM_HPP

#include <string>
#include <array>

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
 * @struct Ataque
 * @brief Estrutura que armazena os dados brutos de um golpe específico.
 */
struct Ataque {
    std::string nome;      ///< Nome identificador do ataque.
    std::string descricao; ///< Descrição do ataque.
    TipoAtaque tipo;       ///< Categoria (Simples, Rapido ou Forte).
    double custoPP;        ///< Custo de Mana (Pontos de Poder) para execução.
};

/**
 * @enum TipoClasse
 * @brief Identificadores para os tipos de heróis disponíveis.
 */
enum class TipoClasse {
    Arqueiro,
    Guerreiro,
    Mago,
    Escudeiro
};

/**
 * @class ClassePersonagem
 * @brief Representa o arquétipo de um personagem, definindo seus ataques e armas, e
 * fornece os dados necessários para que a Batalha e o Personagem 
 * saibam quais habilidades estão disponíveis conforme a escolha do jogador.
 */
class ClassePersonagem {
private:
    std::string _nome;               ///< Nome da classe (ex: "Mago").
    std::string _descricao;          ///< Breve história (flavor) da classe.
    std::string _arma;               ///< Tipo de arma utilizada (flavor).
    std::array<Ataque, 3> _ataques;  ///< Lista fixa de 3 ataques por classe.

public:
    /**
     * @brief Construtor que inicializa a classe com seus atributos básicos.
     * @param nome Nome da classe.
     * @param tipo O enumerador que define qual classe será construída.
     */
    ClassePersonagem(std::string nome, TipoClasse tipo);

    /** @return Nome da classe. */
    std::string getNome() const;

    /** @return Descrição das características da classe. */
    std::string getDescricao() const;

    /** @return Nome da arma padrão da classe. */
    std::string getArma() const;

    /**
     * @brief Retorna a lista de ataques disponíveis.
     * @return Referência constante para o array de ataques.
     */
    const std::array<Ataque, 3>& getAtaques() const;

    /** @brief Inclui a descrição da classe. */
    void setDescricao(std::string descricao);

    /** @brief Inclui a arma da classe. */
    void setArma(std::string arma);

    /** @brief Inclui a lista de ataques da classe. */
    void setAtaques(std::array<Ataque, 3> ataques);

};

#endif