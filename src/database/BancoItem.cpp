#include <stdexcept>
#include <string>

#include "database/BancoItem.hpp"

// Factories 

Item BancoItem::criarComidaPositiva(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Comida, "Cura", valor, 0, cenaId};
}

Item BancoItem::criarComidaNegativa(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Comida, "Dano", valor, 0, cenaId};
}

Item BancoItem::criarPocaoAtaque(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Pocao, "Ataque", valor, 3, cenaId};
}

Item BancoItem::criarPocaoDefesa(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Pocao, "Defesa", valor, 4, cenaId};
}

Item BancoItem::criarPocaoVelocidade(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Pocao, "Agilidade", valor, 3, cenaId};
}

Item BancoItem::criarPocaoMana(int cenaId, std::string nome, std::string desc, int valor)
{
    return {nome, desc, Pocao, "Poder", valor, 4, cenaId};
}

Item BancoItem::criarCristal(int cenaId, std::string nome, std::string desc, int valor,
                             std::string efeito, int duracao)
{
    return {nome, desc, Cristal, efeito, valor, duracao, cenaId};
}


// Lookup 
// TODO: gerar todos os itens organizados por cena (cada qual com seu flavor)

Item BancoItem::obterItem(int cenaId, int itemId)
{
    switch (itemId)
    {
    // ── Cena 1 (IDs 1–9) ─────────────────────────────────────────────
    case 1:
        return criarComidaPositiva(1, "Fruta Fresca", "Uma maçã docinha.", 3);
    case 2:
        return criarComidaNegativa(1, "Fruta Podre", "Uma pera amolecida e cheirando mal.", -3);
    case 3:
        return criarPocaoAtaque(1, "Pocao de Forca", "Aumenta o Ataque por 3 turnos.", 4);
    case 4:
        return criarCristal(1, "Cristal de Agressao", "Entra em Berserk por 3 turnos ao iniciar batalha.", 3, "Berserk", 3);

    // ── Cena 2 (IDs 10–19) ───────────────────────────────────────────
    case 10:
        return criarComidaPositiva(2, "Carne Preparada", "Cozido de coelhos bem temperado.", 7);
    case 11:
        return criarComidaNegativa(2, "Carne Crua", "Carne crua de procedencia duvidosa.", -7);
    case 12:
        return criarPocaoDefesa(2, "Pocao de Resistencia", "Aumenta a Defesa por 4 turnos.", 4);
    case 13:
        return criarCristal(2, "Cristal de Protecao", "Concede +5 na CD durante todos os combates da cena.", 5, "CD", 0);

    // ── Cena 3 (IDs 20–29) ───────────────────────────────────────────
    case 20:
        return criarComidaPositiva(3, "Cogumelo Medicinal", "Cogumelo simples de aroma suave.", 9);
    case 21:
        return criarComidaNegativa(3, "Cogumelo Vermelho com Pintinhas", "Cogumelo de cor vívida e aspecto suspeito.", -9);
    case 22:
        return criarPocaoVelocidade(3, "Pocao de Velocidade", "Aumenta a Agilidade por 3 turnos.", 4);
    case 23:
        return criarCristal(3, "Cristal de Veneno", "Primeiro ataque envenena o alvo por 3 turnos.", 3, "Envenenado", 3);

    // ── Cena 4 (IDs 30–39) ───────────────────────────────────────────
    case 30:
        return criarComidaPositiva(4, "Coco Silvestre", "Coco verde encontrado na mata.", 5);
    case 31:
        return criarComidaNegativa(4, "Coquinho Venenoso", "Coquinho de uma palmeira desconhecida.", -5);
    case 32:
        return criarPocaoMana(4, "Pocao de Mana", "Aumenta o Poder por 4 turnos.", 4);
    case 33:
        return criarCristal(4, "Cristal de Velocidade", "Concede +3 iniciativa e +2 CD nos 2 primeiros turnos.", 3, "Iniciativa", 2);

    // ── Cena 5 (IDs 40–49) ───────────────────────────────────────────
    case 40:
        return criarComidaPositiva(5, "Raiz Curativa", "Raiz amarga com propriedades medicinais.", 6);
    case 41:
        return criarComidaNegativa(5, "Raiz Podre", "Raiz deteriorada com cheiro forte.", -6);
    case 42:
        return criarPocaoAtaque(5, "Elixir de Batalha", "Aumenta o Ataque por 3 turnos.", 5);
    case 43:
        return criarCristal(5, "Cristal de Drenagem", "Recupera 1d4 PV ao fim de cada turno com acerto.", 1, "Drenagem", 0);

    // ── Cena 6 (IDs 50–59) ───────────────────────────────────────────
    case 50:
        return criarComidaPositiva(6, "Mel Silvestre", "Mel coletado de colmeias da floresta.", 4);
    case 51:
        return criarComidaNegativa(6, "Mel Fermentado", "Mel com bolhas e odor azedo.", -4);
    case 52:
        return criarPocaoDefesa(6, "Pocao de Escudo", "Aumenta a Defesa por 4 turnos.", 5);
    case 53:
        return criarCristal(6, "Cristal Sombrio", "Entra em Berserk por 3 turnos ao iniciar batalha.", 4, "Berserk", 3);

    // ── Cena 7 (IDs 60–69) ───────────────────────────────────────────
    case 60:
        return criarComidaPositiva(7, "Amoras silvestres", "Amoras docinhas hummm", 10);
    case 61:
        return criarComidaNegativa(7, "Goiaba com bicho", "Tinha mais bicho que goiaba", -10);
    case 62:
        return criarPocaoAtaque(7, "Elixir Arcano", "Aumenta o Ataque por 3 turnos.", 6);
    case 63:
        return criarCristal(7, "Cristal Arcano", "Entra em Berserk e drena PV por 3 turnos.", 5, "Berserk", 3);

    default:
        throw std::invalid_argument("BancoItem: id desconhecido: " + std::to_string(itemId));
    }
}
