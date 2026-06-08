/**
 * @file Condicao.hpp
 * @brief Define os tipos e a estrutura de condições de combate do jogo.
 *
 * Condições são efeitos aplicados a um Personagem durante o combate — por
 * ataques do jogador, do inimigo, ou como efeito colateral de uma ação.
 * Toda condição possui duração em turnos e altera ao menos um campo
 * mecânico do personagem afetado.
 *
 * Este header é incluído tanto por Batalha quanto por Personagem para
 * evitar duplicação da definição.
 *
 * @see Batalha, Personagem
 */

#ifndef CONDICAO_HPP
#define CONDICAO_HPP

#include <string>

/**
 * @enum TipoCondicao
 * @brief Categorias de condições de combate disponíveis no jogo.
 *
 * Algumas condições são genéricas (marcadas com *) e possuem um campo
 * `nomeCustom` na struct Condicao para que apareçam na lore com nomes
 * diferentes, mas com a mesma mecânica subjacente.
 */
enum class TipoCondicao {
    SemCondicao,      ///< Sem efeito adicional.

    Berserk,          ///< Sofre 1d4/turno; vantagem em acerto (2d20, melhor).

    ReducAtributo,    ///< (*) Reduz X pontos de um atributo específico por N turnos.
                      ///<     Ex lore: "Amaldiçoado", "Corroído", "Lentidão".

    CemPorcentoAcerto,///< (*) Força AGI = -10 → CD = 0; próximo ataque não pode errar.
                      ///<     Ex lore: "Vulnerável", "Exposto", "Marcado".

    Paralisado,       ///< Nenhuma ação disponível por N turnos.

    Atordoado,        ///< Sem Ataque Rápido nem Ataque Forte no próximo turno.

    Envenenado        ///< (*) Sofre 2d6/turno por N turnos.
                      ///<     Ex lore: "Sangrando", "Em Chamas", "Amaldiçoado".
};

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
 * | ATQ/DEF/AGI/PP  | `personagem.atributo += valorParametro` (neg) |
 * | Rolagem acerto  | Vantagem: 2d20 maior / Desvantagem: 2d20 menor|
 * | Ações           | Flag booleana: `podeAtacarForte`, `podeAgir`  |
 */
struct Condicao {
    TipoCondicao tipo = TipoCondicao::SemCondicao;

    /**
     * @brief Nome exibido ao jogador (lore).
     * Usado em condições genéricas (ReducAtributo, CemPorcentoAcerto, Envenenado)
     * para personalizar o nome sem alterar a mecânica.
     * Ex: "Amaldiçoado", "Em Chamas", "Exposto".
     */
    std::string nomeCustom = "";

    /** @brief Quantos turnos a condição ainda permanece ativa. 0 = expirada. */
    int duracaoTurnos = 0;

    /**
     * @brief Valor numérico do efeito (dependente do tipo):
     * - ReducAtributo: quanto reduz (valor positivo → subtrai do atributo)
     * - Envenenado:    dano por turno (normalmente 2d6 já rolado)
     * - Berserk:       dano por turno (normalmente 1d4 já rolado)
     * - Outros tipos:  ignorado
     */
    double valorParametro = 0.0;

    /**
     * @brief Identifica qual atributo é afetado (apenas para ReducAtributo).
     * Valores válidos: "ATQ", "DEF", "AGI", "Poder".
     */
    std::string atributoAlvo = "";
};

#endif // CONDICAO_HPP
