/**
 * @file RegrasItem.cpp
 * @brief Implementação das regras de uso de itens (Comida, Poção e Cristal).
 * @see Regras.md — Seção 5
 */

#include <cstdlib>

#include "core/rules/RegrasItem.hpp"
#include "core/Dados.hpp"
#include "utils/AtributoEnum.hpp"
#include "utils/TipoCondicaoEnum.hpp"

void RegrasItem::aplicarEfeito(const Item& item, Personagem& personagem) {

    if (item.pegarTipo() == Comida) {
        // _valor = qtdDados (+ = cura, - = dano) | _duracao = ladosDado
        // Regras.md §5.2: Fruta=1d6, Carne=2d6, Cogumelo/Erva=2d8
        int qtd   = item.pegarValor();
        int lados = item.pegarDuracao();
        Dados d;
        int total = d.rolar(std::abs(qtd), lados);
        if (qtd >= 0)
            personagem.recuperarVida(total);
        else
            personagem.receberDano(total);
        return;
    }

    if (item.pegarTipo() == Pocao) {
        std::string efeito = item.pegarEfeito();
        Atributo alvo = Atributo::Nenhum;
        if      (efeito == "Ataque")    alvo = Atributo::Ataque;
        else if (efeito == "Defesa")    alvo = Atributo::Defesa;
        else if (efeito == "Agilidade") alvo = Atributo::Agilidade;
        else if (efeito == "Poder")     alvo = Atributo::Poder;
        else return;

        Condicao c;
        c.tipo           = TipoCondicao::ModAtributo;
        c.atributoAlvo   = alvo;
        c.valorParametro = -(double)item.pegarValor(); // negativo = boost
        c.duracaoTurnos  = item.pegarDuracao();
        personagem.aplicarCondicao(c);
        return;
    }

    if (item.pegarTipo() == Cristal) {
        std::string efeito = item.pegarEfeito();
        Condicao c;
        c.duracaoTurnos  = item.pegarDuracao();
        c.valorParametro = (double)item.pegarValor();

        if (efeito == "Berserk") {
            c.tipo = TipoCondicao::Berserk;
        } else if (efeito == "Envenenado") {
            c.tipo = TipoCondicao::Envenenado;
        } else if (efeito == "CD") {
            c.tipo           = TipoCondicao::ModAtributo;
            c.atributoAlvo   = Atributo::Defesa;
            c.valorParametro = -(double)item.pegarValor();
        } else if (efeito == "Iniciativa") {
            c.tipo           = TipoCondicao::ModAtributo;
            c.atributoAlvo   = Atributo::Agilidade;
            c.valorParametro = -(double)item.pegarValor();
        } else if (efeito == "Drenagem") {
            c.tipo       = TipoCondicao::Berserk;
            c.nomeCustom = "Drenagem";
        } else {
            return;
        }

        personagem.aplicarCondicao(c);
        return;
    }
}
