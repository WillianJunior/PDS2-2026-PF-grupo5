/**
 * @file RegrasProgresso.hpp
 * @brief Encapsula as regras de progressão de personagem: XP, níveis e bônus.
 *
 * Esta classe é filha de `Regras` e expõe publicamente os métodos de progressão
 * que a classe pai define como `static protected`. Sua principal contribuição
 * própria é `verificarUpNivel()` — a lógica que decide se um personagem acumulou
 * XP suficiente para avançar de nível.
 *
 * @par Quem usa esta classe
 * - `Personagem::ganharXp()` → chama `verificarUpNivel()` para saber se sobe de nível
 * - `Batalha::definirRecompensa()` → chama `getXPParaProximoNivel()` para exibir progresso
 * - `ClassePersonagem` → chama `getBonusProficiencia()` para ataques que consomem PP
 *
 * @par O que NÃO é responsabilidade desta classe
 * - Modificar atributos do Personagem (isso é de Personagem::subirNivel()).
 * - Calcular dano ou CD (isso é de RegrasBatalha / RegrasAtaque).
 *
 * @see Regras.hpp        — classe pai com as tabelas e métodos protegidos
 * @see Personagem.hpp    — consome verificarUpNivel() e getBonusProficiencia()
 * @see Regras.md         — Seção 3 (Progressão)
 */

#ifndef REGRAS_PROGRESSO_HPP
#define REGRAS_PROGRESSO_HPP

#include "rules/Regras.hpp"

/**
 * @class RegrasProgresso
 * @brief Regras de progressão: verificação de level-up, XP por nível e bônus de proficiência.
 *
 * Todos os métodos são estáticos — a classe não tem estado próprio.
 *
 * @par Tabela de progressão (Regras.md — Seção 3.1)
 * | Nível | XP para avançar |
 * |-------|-----------------|
 * | 1°    | 300             |
 * | 2°    | 900             |
 * | 3°    | 2.700           |
 * | 4°    | 6.500           |
 * | 5°    | 14.000          |
 * | 6°    | 23.000          |
 * | 7°    | 34.000          |
 * | 8°    | 48.000          |
 * | 9°    | 64.000          |
 * | 10°   | — (máximo)      |
 *
 * @par Tabela de bônus de proficiência (Regras.md — Seção 3.2)
 * | Níveis  | Bônus |
 * |---------|-------|
 * | 1° – 3° | +2    |
 * | 4° – 6° | +3    |
 * | 7° – 9° | +4    |
 * | 10°     | +5    |
 */
class RegrasProgresso : public Regras {

public:

    // ── Level-up ──────────────────────────────────────────────────────────

    /**
     * @brief Verifica se o personagem acumulou XP suficiente para subir de nível.
     *
     * Compara `xpAtual` com o limiar retornado por `xpParaProximoNivel(nivelAtual)`.
     * Se `nivelAtual` já for o máximo (LV 10), retorna sempre `false`.
     *
     * @param xpAtual    XP acumulado pelo personagem no nível atual.
     * @param nivelAtual Nível atual do personagem (1 a 10).
     * @return true se xpAtual >= XP necessário para avançar.
     * @throw std::out_of_range Se nivelAtual < 1 ou nivelAtual > 10.
     *
     * @par Uso esperado em Personagem::ganharXp()
     * @code
     *   void Personagem::ganharXp(double quantidade) {
     *       _xp += quantidade;
     *       if (RegrasProgresso::verificarUpNivel(_xp, _nivel)) {
     *           _xp -= RegrasProgresso::getXPParaProximoNivel(_nivel);
     *           subirNivel();
     *       }
     *   }
     * @endcode
     *
     * @par Exemplos
     * @code
     *   verificarUpNivel(300.0, 1)  → true   (300 >= 300)
     *   verificarUpNivel(299.0, 1)  → false  (299 < 300)
     *   verificarUpNivel(9999.0, 10) → false  (nível máximo)
     * @endcode
     *
     * @see Regras.md — Seção 3.1
     */
    static bool verificarUpNivel(double xpAtual, int nivelAtual);

    // ── Wrappers públicos das tabelas da classe pai ───────────────────────

    /**
     * @brief Retorna o XP necessário para avançar do nível atual para o próximo.
     *
     * Wrapper público de `Regras::xpParaProximoNivel()`.
     * Retorna 0.0 se nivelAtual == 10 (nível máximo atingido).
     *
     * @param nivelAtual Nível atual do personagem (1 a 10).
     * @return XP necessário para subir de nível.
     * @throw std::out_of_range Se nivelAtual < 1 ou nivelAtual > 10.
     *
     * @par Exemplos
     * @code
     *   getXPParaProximoNivel(1)  → 300.0
     *   getXPParaProximoNivel(5)  → 14000.0
     *   getXPParaProximoNivel(10) → 0.0
     * @endcode
     */
    static double getXPParaProximoNivel(int nivelAtual);

    /**
     * @brief Retorna o bônus de proficiência para um determinado nível.
     *
     * Wrapper público de `Regras::bonusProficiencia()`.
     * Somado a rolagens de acerto em ataques que consomem PP e no Ataque Rápido.
     *
     * @param nivel Nível atual do personagem (1 a 10).
     * @return Bônus de proficiência: +2, +3, +4 ou +5.
     * @throw std::out_of_range Se nivel < 1 ou nivel > 10.
     *
     * @par Exemplos
     * @code
     *   getBonusProficiencia(1)  → 2
     *   getBonusProficiencia(5)  → 3
     *   getBonusProficiencia(10) → 5
     * @endcode
     *
     * @see Regras.md — Seção 3.2
     */
    static int getBonusProficiencia(int nivel);

    /**
     * @brief Retorna o nível máximo do jogo.
     * @return 10
     */
    static int getNivelMaximo();
};

#endif // REGRAS_PROGRESSO_HPP