/**
 * @file TipoArcanoEnum.hpp
 * @brief Enum tipado para os seis Arcanos primordiais do jogo.
 *
 * Arcanos sao poderes permanentes concedidos pelos Lordes da criacao a
 * portadores mortais. Cada Arcano produz efeitos passivos em combate e
 * bonus narrativos de exploracao.
 *
 * @see Regras.md - Secao 6 (Sistema de Arcanos)
 * @see Personagem::adicionarArcano, Personagem::temArcano
 */

#ifndef TIPO_ARCANO_ENUM_HPP
#define TIPO_ARCANO_ENUM_HPP

/**
 * @enum TipoArcano
 * @brief Identifica cada um dos seis Arcanos primordiais.
 *
 * A ordem segue a hierarquia lore dos Lordes (Talos -> Azuth -> Glaron ->
 * Eldath -> Lathander -> Asmodeus).
 *
 * | Arcano   | Deus      | Efeito resumido em combate                    |
 * |----------|-----------|-----------------------------------------------|
 * | Alma     | Talos     | +50 % XP ganho; imunidade a Paralisado        |
 * | Mente    | Azuth     | -25 % custo de PP em ataques que gastam PP    |
 * | Elementos| Glaron    | +20 % de dano em todos os ataques             |
 * | Natureza | Eldath    | Bonus de exploracao (itens e encontros raros) |
 * | Vida     | Lathander | Regen +1d4 PV/turno; curas recebidas x1,5    |
 * | Caos     | Asmodeus  | 25 % do dano causado convertido em PV         |
 */
enum class TipoArcano {
    Nenhum,     ///< Sem arcano equipado (estado padrao).
    Alma,       ///< Talos   - XP amplificado e imunidade a paralisia.
    Mente,      ///< Azuth   - Eficiencia de mana aumentada.
    Elementos,  ///< Glaron  - Dano fisico e elemental fortalecido.
    Natureza,   ///< Eldath  - Recursos raros e encontros favoraveis.
    Vida,       ///< Lathander - Regeneracao e cura potencializadas.
    Caos        ///< Asmodeus - Roubo de vida (lifesteal) em ataques.
};

#endif
