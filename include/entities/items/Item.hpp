/**
 * @file Item.hpp
 * @brief Definição da classe base Item e do enumerador de tipos de itens.
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

/**
 * @enum TipoItem
 * @brief Categorias de itens disponíveis no jogo.
 */
enum TipoItem {
    Pocao,  ///< Itens que modificam atributos (ataque, defesa, esquiva e mapa).
    Comida, ///< Itens que recuperam vida.
    Cristal ///< Itens que dão vantagens ao jogador durante uma batalha.
};

/**
 * @class Item
 * @brief Representa um objeto genérico que pode ser coletado e utilizado.
 * A classe armazena informações básicas de identificação, além dos modificadores que afetam os atributos do Personagem quando o item é consumido.
 */
class Item {
private: 
    std::string _nome;      ///< Nome identificador do item.
    std::string _descricao; ///< Texto descritivo para a interface do jogador.
    TipoItem _tipo;         ///< Categoria do item (Pocao, Comida ou Cristal).

    std::string _efeito;    ///< Descrição do efeito aplicado (ex: "Cura", "Dano").
    int _valor;             ///< Intensidade do efeito (ex: +20 de HP).
    int _duracao;           ///< Tempo de duração do efeito em turnos (0 para imediato).

public:
    /**
     * @brief Construtor da classe Item.
     * @param nome Nome do item.
     * @param descricao Breve descrição do que o item faz.
     * @param tipo Categoria do item conforme o enum TipoItem.
     * @param efeito Descrição do efeito aplicado.
     * @param valor Valor numérico da alteração no atributo.
     * @param duracao Quantidade de turnos que o efeito persiste.
     */
    Item(std::string nome, std::string descricao, TipoItem tipo, std::string efeito, int valor, int duracao);

    /** @return O nome do item. */
    std::string pegarNome() const;

    /** @return A descrição detalhada do item. */
    std::string pegarDescricao() const;

    /** @return O tipo do item (Pocao, Comida ou Cristal). */
    TipoItem pegarTipo() const;

    /** @return A string que identifica o efeito. */
    std::string pegarEfeito() const;

    /** @return O valor numérico do modificador. */
    int pegarValor() const;

    /** @return A duração do efeito em turnos. */
    int pegarDuracao() const;
};

#endif