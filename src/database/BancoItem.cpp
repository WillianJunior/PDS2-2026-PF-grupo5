/**
 * @file BancoItem.cpp
 * @brief Repositório estático de itens do jogo, organizados por cena.
 *
 * Cada cena possui 4 itens: 2 comidas (positiva/negativa), 1 poção e 1 cristal.
 *
 * Comidas seguem as categorias do Regras.md (Seção 5.2).
 * O efeito é **aleatório** (rolagem de dado no uso via RegrasItem + Dados):
 *   - Fruta       → ±1d6  | qtdDados=±1, ladosDado=6
 *   - Carne       → ±2d6  | qtdDados=±2, ladosDado=6
 *   - Cogumelo/Erva → ±2d8 | qtdDados=±2, ladosDado=8
 *
 * Para Comidas: Item._valor = qtdDados (+cura/-dano), Item._duracao = ladosDado.
 *
 * Poções seguem o Regras.md (Seção 5.3): bônus fixo +4, duração fixa por tipo,
 * sem variação entre cenas. Nomes temáticos diferentes, mesmas estatísticas.
 *
 * @see Regras.md — Seção 5
 */

#include <stdexcept>
#include <string>

#include "database/BancoItem.hpp"

// ── Factories ────────────────────────────────────────────────────────────────

Item BancoItem::criarComidaPositiva(int cenaId, std::string nome, std::string desc,
                                    int qtdDados, int ladosDado)
{
    // _valor = +qtdDados (cura), _duracao = ladosDado
    return {nome, desc, Comida, "Cura", qtdDados, ladosDado, cenaId};
}

Item BancoItem::criarComidaNegativa(int cenaId, std::string nome, std::string desc,
                                    int qtdDados, int ladosDado)
{
    // _valor = -qtdDados (dano), _duracao = ladosDado
    return {nome, desc, Comida, "Dano", -qtdDados, ladosDado, cenaId};
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


// ── Lookup ────────────────────────────────────────────────────────────────────

Item BancoItem::obterItem(int cenaId, int itemId)
{
    (void)cenaId;
    switch (itemId)
    {
    // ── Cena 1 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Fruta → ±1d6 | Regras.md §5.2
    case 1:
        return criarComidaPositiva(1, "Fruta Fresca",
            "Uma maca docinha.", 1, 6);
    case 2:
        return criarComidaNegativa(1, "Fruta Podre",
            "Uma pera amolecida e cheirando mal.", 1, 6);
    // Pocao de Forca: Ataque +4, 3 turnos | Regras.md §5.3
    case 3:
        return criarPocaoAtaque(1, "Pocao de Forca",
            "Aumenta o Ataque em +4 por 3 turnos.", 4);
    // Cristal de Agressao: Berserk 3 turnos | Regras.md §5.4
    case 4:
        return criarCristal(1, "Cristal de Agressao",
            "Entra em Berserk ao iniciar batalha: vantagem no acerto, -1d4 PV/turno.", 3, "Berserk", 3);

    // ── Cena 2 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Carne → ±2d6 | Regras.md §5.2
    case 10:
        return criarComidaPositiva(2, "Carne Preparada",
            "Cozido de coelhos bem temperado.", 2, 10);
    case 11:
        return criarComidaNegativa(2, "Carne Crua",
            "Carne crua de procedencia duvidosa.", 2, 8);
    // Pocao de Resistencia: Defesa +4, 4 turnos | Regras.md §5.3
    case 12:
        return criarPocaoDefesa(2, "Pocao de Resistencia",
            "Aumenta a Defesa em +4 por 4 turnos.", 17);
    // Cristal de Protecao: +5 CD permanente na cena | Regras.md §5.4
    case 13:
        return criarCristal(2, "Cristal de Protecao",
            "Concede +5 na Classe de Dificuldade durante todos os combates da cena.", 5, "CD", 0);

    // ── Cena 3 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Cogumelo → ±2d8 | Regras.md §5.2
    case 20:
        return criarComidaPositiva(3, "Cogumelo Medicinal",
            "Cogumelo simples de aroma suave.", 2, 8);
    case 21:
        return criarComidaNegativa(3, "Cogumelo Vermelho com Pintinhas",
            "Cogumelo de cor vivida e aspecto suspeito.", 2, 8);
    // Pocao de Velocidade: Agilidade +4, 3 turnos | Regras.md §5.3
    case 22:
        return criarPocaoVelocidade(3, "Pocao de Velocidade",
            "Aumenta a Agilidade em +4 por 3 turnos.", 4);
    // Cristal de Veneno: envenena alvo 3 turnos (-2d6/turno) | Regras.md §5.4
    case 23:
        return criarCristal(3, "Cristal de Veneno",
            "Primeiro ataque bem-sucedido envenena o alvo por 3 turnos (-2d6 PV/turno).", 3, "Envenenado", 3);

    // ── Cena 4 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Fruta → ±1d6 | Regras.md §5.2
    case 30:
        return criarComidaPositiva(4, "Coco Silvestre",
            "Coco verde encontrado na mata.", 5, 6);
    case 31:
        return criarComidaNegativa(4, "Coquinho Venenoso",
            "Coquinho de uma palmeira desconhecida.", 1, 6);
    // Pocao de Mana: Poder +4, 4 turnos | Regras.md §5.3
    case 32:
        return criarPocaoMana(4, "Pocao de Mana",
            "Aumenta o Poder em +4 por 4 turnos.", 4);
    // Cristal de Velocidade: +3 iniciativa e +2 CD nos 2 primeiros turnos | Regras.md §5.4
    case 33:
        return criarCristal(4, "Cristal de Velocidade",
            "Concede +3 na iniciativa e +2 na CD durante os 2 primeiros turnos do combate.", 3, "Iniciativa", 2);

    // ── Cena 5 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Cogumelo/Erva → ±2d8 | Regras.md §5.2
    case 40:
        return criarComidaPositiva(5, "Raiz Curativa",
            "Raiz amarga com propriedades medicinais.", 2, 8);
    case 41:
        return criarComidaNegativa(5, "Raiz Podre",
            "Raiz deteriorada com cheiro forte.", 2, 8);
    // Elixir de Batalha: Ataque +4, 3 turnos | Regras.md §5.3 (mesmo bônus, nome tematico)
    case 42:
        return criarPocaoAtaque(5, "Elixir de Batalha",
            "Aumenta o Ataque em +4 por 3 turnos.", 9);
    // Cristal de Drenagem: recupera 1d4 PV ao acertar | Regras.md §5.4
    case 43:
        return criarCristal(5, "Cristal de Drenagem",
            "Recupera 1d4 PV ao fim de cada turno em que acertar pelo menos um ataque.", 1, "Drenagem", 0);

    // ── Cena 6 ───────────────────────────────────────────────────────────────
    // Comidas: categoria Fruta → ±1d6 | Regras.md §5.2
    case 50:
        return criarComidaPositiva(6, "Mel Silvestre",
            "Mel coletado de colmeias da floresta.", 3, 15);
    case 51:
        return criarComidaNegativa(6, "Mel Fermentado",
            "Mel com bolhas e odor azedo.", 1, 6);
    // Pocao de Escudo: Defesa +4, 4 turnos | Regras.md §5.3 (mesmo bônus, nome tematico)
    case 52:
        return criarPocaoDefesa(6, "Pocao de Escudo",
            "Aumenta a Defesa em +4 por 4 turnos.", 4);
    // Cristal Sombrio: variante tematica do Cristal de Agressao | Regras.md §5.4
    case 53:
        return criarCristal(6, "Cristal Sombrio",
            "Entra em Berserk ao iniciar batalha: vantagem no acerto, -1d4 PV/turno.", 6, "Berserk", 3);

    // ── Cena 7 (Final) ───────────────────────────────────────────────────────
    // Comidas: categoria Fruta → ±1d6 | Regras.md §5.2
    case 60:
        return criarComidaPositiva(7, "Amoras Silvestres",
            "Amoras docinhas encontradas na entrada do santuario.", 1, 6);
    case 61:
        return criarComidaNegativa(7, "Goiaba com Bicho",
            "Tinha mais bicho que goiaba.", 1, 6);
    // Elixir Arcano: Ataque +4, 3 turnos | Regras.md §5.3 (mesmo bônus, nome tematico)
    case 62:
        return criarPocaoAtaque(7, "Elixir Arcano",
            "Aumenta o Ataque em +4 por 3 turnos.", 4);
    // Cristal Arcano: variante tematica do Cristal de Agressao | Regras.md §5.4
    case 63:
        return criarCristal(7, "Cristal Arcano",
            "Entra em Berserk ao iniciar batalha: vantagem no acerto, -1d4 PV/turno.", 3, "Berserk", 3);

    default:
        throw std::invalid_argument("BancoItem: id desconhecido: " + std::to_string(itemId));
    }
}
