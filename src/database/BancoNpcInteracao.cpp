/**
 * @file BancoNpcInteracao.cpp
 * @brief Repositório estático de NPCs de diálogo (20 entradas).
 *
 * NPCs de diálogo são personagens não-combatentes encontrados nos trechos de mapa.
 * IDs 1–3  → Cena 1 (um por trecho)
 * IDs 4–6  → Cena 2
 * IDs 7–9  → Cena 3
 * IDs 10–12 → Cena 4
 * IDs 13–15 → Cena 5
 * IDs 16–18 → Cena 6
 * IDs 19–20 → Cena 7 (cena final — 2 NPCs de apoio)
 *
 * @note Nomes e falas são placeholders; substituir pelo conteúdo narrativo definitivo.
 */

#include "database/BancoNpcInteracao.hpp"
#include <stdexcept>

InfoNPCInteracao BancoNPCInteracao::obterNPC(int id)
{
    if (id <= 0)
        throw std::invalid_argument("ID de NPC invalido: deve ser maior que zero.");

    switch (id)
    {
        // ── Cena 1 ───────────────────────────────────────────────────────────
        case 1:
            return { 1, "Aldeao", "Um fazendeiro assustado.", "Cuidado com as criaturas na floresta!" };
        case 2:
            return { 2, "Viajante", "Um mercador de passagem.", "Encontrei algo estranho mais adiante..." };
        case 3:
            return { 3, "Anciao", "Um velho sábio da aldeia.", "O primeiro arcano desperta. Seja prudente." };

        // ── Cena 2 ───────────────────────────────────────────────────────────
        case 4:
            return { 4, "Guarda", "Um soldado ferido.", "Fugi das ruinas. Nao volte por la." };
        case 5:
            return { 5, "Herborista", "Uma mulher colhendo plantas.", "Estas ervas podem te ajudar na batalha." };
        case 6:
            return { 6, "Fantasma", "Uma presenca etérea e silenciosa.", "Liberte-nos deste lugar amaldicoado..." };

        // ── Cena 3 ───────────────────────────────────────────────────────────
        case 7:
            return { 7, "Druida", "Um guardiao da floresta.", "A natureza esta perturbada. Algo avanca." };
        case 8:
            return { 8, "Crianca Perdida", "Uma crianca sozinha e assustada.", "Eu vi um monstro enorme passar por aqui!" };
        case 9:
            return { 9, "Ermitao", "Um recluso que vive na mata.", "Tres arcanos revelados, quatro restam." };

        // ── Cena 4 ───────────────────────────────────────────────────────────
        case 10:
            return { 10, "Cavaleiro", "Um cavaleiro em armadura enferrujada.", "Minha lanca se quebrou. Tome meu escudo." };
        case 11:
            return { 11, "Maga Exilada", "Uma arquimaga afastada da ordem.", "O quarto arcano corrompe quem o toca." };
        case 12:
            return { 12, "Mercenario", "Um lutador contratado.", "Paguei caro para chegar ate aqui. Voce tambem vai." };

        // ── Cena 5 ───────────────────────────────────────────────────────────
        case 13:
            return { 13, "Sacerdote", "Um clerigo em oracoes.", "Que os deuses guiem seu caminho." };
        case 14:
            return { 14, "Espirito", "Uma alma que nao encontrou descanso.", "Eu tentei chegar ao arcano. Fracassei." };
        case 15:
            return { 15, "Sobrevivente", "Um aventureiro exausto.", "Os outros do grupo nao voltaram. Fui o unico." };

        // ── Cena 6 ───────────────────────────────────────────────────────────
        case 16:
            return { 16, "Oraculo", "Uma figura que enxerga alem do tempo.", "Voce chegara ao fim. Mas a que custo?" };
        case 17:
            return { 17, "Arauto", "Um mensageiro do além.", "O sexto arcano foi selado por uma razao." };
        case 18:
            return { 18, "Feiticeiro", "Um mago corrompido pelo poder.", "Desista enquanto pode. Eu nao desisti e olhe o que restou." };

        // ── Cena 7 (Final) ───────────────────────────────────────────────────
        case 19:
            return { 19, "Eco do Passado", "Uma visao de um heroi anterior.", "Muitos tentaram. Voce sera diferente?" };
        case 20:
            return { 20, "Guardiao Silencioso", "Uma entidade que protege o arcano final.", "Apenas o digno avanca. Prove seu valor." };

        default:
            throw std::invalid_argument(
                "NPC de interacao nao encontrado: id " + std::to_string(id));
    }
}
