/**
 * @file Condicao.hpp
 * @brief Define a estrutura de condições de combate do jogo.
 *
 * Condições são efeitos aplicados a um Personagem durante o combate — por
 * ataques do jogador, do inimigo, ou como efeito colateral de uma ação.
 * Toda condição possui duração em turnos e altera ao menos um campo
 * mecânico do personagem afetado.
 *
 * Os enums TipoCondicao e Atributo são definidos em utils/ e incluídos aqui
 * para que qualquer arquivo que inclua Condicao.hpp acesse os dois enums.
 *
 * @see Batalha, Personagem
 */

#ifndef CONDICAO_HPP
#define CONDICAO_HPP

#include <string>
#include "utils/AtributoEnum.hpp"
#include "utils/TipoCondicaoEnum.hpp"

/**
 * @struct Condicao
 * @brief Representa uma condição ativa aplicada a um Personagem.
 *
 * Cada instância descreve um único efeito em vigor, com sua duração restante
 * e os parâmetros necessários para aplicá-lo e revertê-lo corretamente.
 *
 * @par Como cada campo é alterado em runtime
 * | Campo alterado  | Operação                                      |
 * |-----------------|-----------------------------------------------|
 * | PV atual        | `personagem.hp -= valorParametro` /turno      |
 * | PP atual        | `personagem.pp -= valorParametro` /turno      |
 * | ATQ/DEF/AGI/PP  | `_atributo -= valorParametro` (neg = boost)   |
 * | Rolagem acerto  | Vantagem: 2d20 maior / Desvantagem: 2d20 menor|
 * | Ações           | Flag booleana: `podeAtacarForte`, `podeAgir`  |
 */
struct Condicao {
    TipoCondicao tipo = TipoCondicao::SemCondicao;

    /**
     * @brief Nome exibido ao jogador (lore).
     * Usado em condições genéricas (ModAtributo, CemPorcentoAcerto, Envenenado)
     * para personalizar o nome sem alterar a mecânica.
     * Ex: "Amaldiçoado", "Em Chamas", "Exposto".
     */
    std::string nomeCustom = "";

    /** @brief Quantos turnos a condição ainda permanece ativa. 0 = expirada. */
    int duracaoTurnos = 0;

    /**
     * @brief Valor numérico do efeito (dependente do tipo):
     * - ModAtributo: positivo = reduz o atributo; negativo = aumenta (boost).
     * - Envenenado:  dano por turno (normalmente 2d6 já rolado).
     * - Berserk:     dano por turno (normalmente 1d4 já rolado).
     * - Outros:      ignorado.
     */
    double valorParametro = 0.0;

    /**
     * @brief Atributo afetado pela condição.
     * Relevante apenas para ModAtributo; ignorado nos demais tipos.
     * Valores válidos: Atributo::Ataque, Defesa, Agilidade, Poder.
     */
    Atributo atributoAlvo = Atributo::Nenhum;
};

#endif
