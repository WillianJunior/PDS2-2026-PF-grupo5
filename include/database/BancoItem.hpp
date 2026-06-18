/**
 * @file BancoItem.hpp
 * @brief Fábrica estática de instâncias de Item predefinidos por cena.
 */

#ifndef BANCO_ITEM_HPP
#define BANCO_ITEM_HPP

#include "entities/items/Item.hpp"
#include <string>

/**
 * @class BancoItem
 * @brief Retorna itens predefinidos por cena e ID sequencial.
 *
 * IDs são globais e sequenciais, agrupados em faixas por cena (TODO: atualizar faixas futuramente com os itens finais):
 * - Cena 1:  1 –  9
 * - Cena 2: 10 – 19
 * - Cena 3: 20 – 29
 * - Cena 4: 30 – 39
 * - Cena 5: 40 – 49
 * - Cena 6: 50 – 59
 * - Cena 7: 60 – 69
 *
 * Métodos factory privados encapsulam tipo/efeito/duracao (fixos por arquétipo);
 * nome, descricao e valor variam por cena e são declarados no switch.
 */
class BancoItem
{
public:
    /**
     * @brief Retorna o item correspondente à cena e ao ID fornecidos.
     * @param cenaId ID da cena solicitante.
     * @param itemId Identificador global sequencial do item.
     * @return Item com os atributos definidos nas regras.
     * @throw std::invalid_argument se o itemId não for reconhecido.
     */
    static Item obterItem(int cenaId, int itemId);

private:
    /// @param qtdDados  Quantidade de dados (ex: 1 para 1d6, 2 para 2d8).
    /// @param ladosDado Lados do dado (ex: 6 para d6, 8 para d8).
    static Item criarComidaPositiva(int cenaId, std::string nome, std::string desc,
                                    int qtdDados, int ladosDado);
    static Item criarComidaNegativa(int cenaId, std::string nome, std::string desc,
                                    int qtdDados, int ladosDado);
    static Item criarPocaoAtaque(int cenaId, std::string nome, std::string desc, int valor);
    static Item criarPocaoDefesa(int cenaId, std::string nome, std::string desc, int valor);
    static Item criarPocaoVelocidade(int cenaId, std::string nome, std::string desc, int valor);
    static Item criarPocaoMana(int cenaId, std::string nome, std::string desc, int valor);
    static Item criarCristal(int cenaId, std::string nome, std::string desc, int valor,
                             std::string efeito, int duracao);
};

#endif
