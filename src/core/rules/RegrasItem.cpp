#include "core/rules/RegrasItem.hpp"
#include "utils/AtributoEnum.hpp"
#include "utils/TipoCondicaoEnum.hpp"

void RegrasItem::aplicarEfeito(const Item& item, Personagem& personagem) {

    if (item.pegarTipo() == Comida) {
        int valor = item.pegarValor();
        if (valor >= 0)
            personagem.recuperarVida(valor);
        else
            personagem.receberDano(-valor);
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
