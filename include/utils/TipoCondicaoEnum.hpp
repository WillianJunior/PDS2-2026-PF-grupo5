/**
 * @file TipoCondicaoEnum.hpp
 * @brief Enum tipado para os tipos de condição de combate.
 *
 * Condições definidas em regras.md seção 2.5.
 * Utilizado em classes variadas para evitar comparações por string.
 */

#ifndef TIPO_CONDICAO_ENUM_HPP
#define TIPO_CONDICAO_ENUM_HPP

/**
 * @enum TipoCondicao
 * @brief Categorias de condições de combate disponíveis no jogo.
 *
 * Condições marcadas com (*) são genéricas: possuem um campo nomeCustom
 * em Condicao para exibição na lore, mas a mecânica subjacente é idêntica.
 */
enum class TipoCondicao {
    SemCondicao,       ///< Sem efeito adicional.
    Berserk,           ///< Sofre 1d4/turno; vantagem em acerto (2d20, melhor).
    ModAtributo,       ///< (*) Modifica X pontos de um atributo por N turnos.
                       ///<     valorParametro positivo = reduz; negativo = aumenta.
                       ///<     Ex lore: "Enfraquecido", "Amaldiçoado", "Fortalecido".
    CemPorcentoAcerto, ///< (*) Força AGI = -10 → CD = 0; próximo ataque não pode errar.
                       ///<     Ex lore: "Vulnerável", "Exposto", "Marcado".
    Paralisado,        ///< Nenhuma ação disponível por N turnos.
    Atordoado,         ///< Sem Ataque Rápido nem Ataque Forte no próximo turno.
    Envenenado         ///< (*) Sofre 2d6/turno por N turnos.
                       ///<     Ex lore: "Sangrando", "Em Chamas", "Amaldiçoado".
};

#endif
