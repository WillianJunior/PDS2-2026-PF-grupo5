/**
 * @file RegrasBatalha.hpp
 * @brief Encapsula toda a lógica de regras do sistema de combate.
 *
 * Esta classe é filha de Regras e concentra exclusivamente os cálculos
 * e tabelas que Batalha precisa.
 *
 * @par Responsabilidades
 * - Classificar o confronto (Trivial → Impossível) com base no ND do inimigo
 *   e no nível do jogador.
 * - Calcular o XP ganho após o combate (com redução proporcional para Trivial).
 * - Determinar se a fuga está disponível.
 * - Calcular o multiplicador de dano para Defesa e Esquiva.
 *
 * @par O que NÃO é responsabilidade desta classe
 * - Conhecer _player ou _inimigo.
 * - Rolar dados (isso é de Dados).
 * - Calcular dano de ataque (isso é de RegrasAtaque).
 *
 * @see Batalha.hpp  — orquestra o fluxo usando esta classe
 * @see Regras.hpp   — classe pai com métodos compartilhados
 * @see Regras.md    — Seção 4 (Dificuldade de Encontros)
 */

#ifndef REGRAS_BATALHA_HPP
#define REGRAS_BATALHA_HPP

#include "Regras.hpp"
#include <map>
#include <array>
#include <string>

/**
 * @class RegrasBatalha
 * @brief Regras de combate: dificuldade, XP, fuga, defesa e esquiva.
 *
 * Todos os métodos são estáticos — a classe não tem estado próprio.
 * Batalha instancia um ponteiro para RegrasBatalha apenas para injeção
 * de dependência (permite mocking nos testes).
 */
class RegrasBatalha : public Regras {

public:

    // Enum de classificação

    /**
     * @enum Dificuldade
     * @brief Resultado da classificação de um confronto.
     *
     * | Classificação | XP ganho              | Fuga       |
     * |---------------|-----------------------|------------|
     * | Trivial       | Reduzido proporcional | Disponível |
     * | Facil         | 100%                  | Disponível |
     * | Medio         | 100%                  | Disponível |
     * | Dificil       | 100%                  | Disponível |
     * | Boss          | 100%                  | Bloqueada  |
     * | Impossivel    | 100%                  | Bloqueada* |
     *
     * *Impossível: a fuga é oferecida ANTES do combate começar.
     *
     * @see Regras.md — Seção 4.4 e 4.6
     */
    enum class Dificuldade {
        Trivial,    ///< XP do inimigo < limiar Fácil do jogador.
        Facil,      ///< limiar Fácil ≤ XP < limiar Médio.
        Medio,      ///< limiar Médio ≤ XP < limiar Difícil.
        Dificil,    ///< limiar Difícil ≤ XP < limiar Boss.
        Boss,       ///< XP ≥ limiar Boss.
        Impossivel  ///< XP ≥ 2× limiar Boss (caso extremo).
    };

private:

    // Tabelas internas

    /**
     * @brief Tabela de XP concedido por ND de inimigo.
     *
     * Chaves fracionárias: 0.125 = ND 1/8 | 0.25 = ND 1/4 | 0.5 = ND 1/2.
     * NDs acima de 10 constam como referência (provavelmente não usados).
     *
     * Fonte: SRD 5.1 — "Experience Points by Challenge Rating".
     */
    static const std::map<double, double> TABELA_XP_ND;

    /**
     * @brief Limiares de dificuldade por nível do jogador.
     *
     * LIMIARES[nivel - 1] = { Fácil, Médio, Difícil, Boss }
     *
     * Fonte: D&D 5e DMG Cap.3 — adaptado para combate solo (valores menores).
     */
    static const std::array<std::array<double, 4>, 10> LIMIARES;

public:

    // Consultas às tabelas

    /**
     * @brief Retorna o XP base de um inimigo pelo seu ND.
     * @param ndInimigo ND do inimigo (ex: 0.125, 0.25, 0.5, 1.0, 2.0 ...).
     * @return XP correspondente ao ND.
     * @throw std::invalid_argument Se o ND não existir na tabela.
     *
     * @par Exemplos
     * @code
     *   getXPporND(0.125) → 25.0   (ND 1/8)
     *   getXPporND(0.5)   → 100.0  (ND 1/2)
     *   getXPporND(5.0)   → 1800.0
     * @endcode
     */
    static double getXPporND(double ndInimigo);

    /**
     * @brief Retorna um limiar de dificuldade para um nível e categoria.
     * @param nivel            Nível do jogador (1 a 10).
     * @param indiceDificuldade 0=Fácil | 1=Médio | 2=Difícil | 3=Boss.
     * @return Valor do limiar em XP.
     * @throw std::out_of_range Se nivel < 1, nivel > 10 ou índice inválido.
     */
    static double getLimiar(int nivel, int indiceDificuldade);

    // Classificação de encontro

    /**
     * @brief Classifica o confronto com base no ND do inimigo e no nível do jogador.
     *
     * Fluxo: ND → XP do inimigo → compara com limiares do nível → Dificuldade.
     *
     * @param lvJogador Nível atual do jogador (1 a 10).
     * @param ndInimigo ND do inimigo (ex: 0.5, 1.0, 4.0).
     * @return Enum Dificuldade com a classificação do confronto.
     * @throw std::invalid_argument Se ndInimigo não existir na tabela.
     * @throw std::out_of_range    Se lvJogador for inválido.
     *
     * @par Exemplos (mesma luta, perspectivas diferentes)
     * @code
     *   classificarConfronto(3, 2.0) → Boss      (450 XP ≥ limiar Boss LV3=400)
     *   classificarConfronto(5, 2.0) → Medio     (250 ≤ 450 < 500)
     *   classificarConfronto(8, 2.0) → Facil     (450 = limiar Fácil LV8=450)
     * @endcode
     *
     * @see Regras.md — Seção 4.4
     */
    static Dificuldade ClassificarConfronto(int lvJogador, double ndInimigo);

    /**
     * @brief Converte o enum Dificuldade para string (uso em View/log).
     * @param d Classificação.
     * @return String legível: "Trivial", "Fácil", "Médio", "Difícil", "Boss" ou "Impossível".
     */
    static std::string DificuldadeParaString(Dificuldade d);

    // XP e fuga

    /**
     * @brief Calcula o XP ganho após vencer o combate.
     *
     * Para encontros Triviais, aplica redução proporcional:
     * @code
     *   xpGanho = xpBase × (xpBase / limiarFacil)
     * @endcode
     * Para todos os outros: 100% do XP base.
     *
     * @param ndInimigo ND do inimigo derrotado.
     * @param lvJogador Nível do jogador.
     * @return XP a ser entregue ao jogador.
     *
     * @par Exemplo (Trivial)
     * @code
     *   // LV 6 (limiar Fácil=300) vs ND 1/8 (25 XP):
     *   calcularXPGanho(0.125, 6) → 25 × (25/300) ≈ 2.08
     * @endcode
     *
     * @see Regras.md — Seção 4.5
     */
    static double CalcularXPGanho(double ndInimigo, int lvJogador);

    /**
     * @brief Verifica se a opção de Fugir está disponível para o jogador.
     *
     * Fuga bloqueada em: Boss e Impossível.
     * Fuga disponível em: Trivial, Fácil, Médio e Difícil.
     *
     * @note Para Impossível, a fuga é oferecida ANTES do combate começar
     *       (via IView::exibirMensagem). Uma vez iniciado, está bloqueada.
     *
     * @param lvJogador Nível do jogador.
     * @param ndInimigo ND do inimigo.
     * @return true se fugir está disponível no turno atual.
     *
     * @see Regras.md — Seção 4.6
     */
    static bool FugirDisponivel(int lvJogador, double ndInimigo);

    // Cálculos de combate defensivo

    /**
     * @brief Calcula o multiplicador de dano quando o jogador se Defende.
     *
     * Compara o atributo de Defesa do player com o de Ataque do inimigo:
     * - defPlayer > ataqueInimigo      → 0%   de dano (0.00)
     * - 0.8 ≤ def/atq < 1.0           → 75%  de dano (0.75)
     * - def/atq < 0.8                  → 100% de dano (1.00)
     *
     * @param defPlayer      Atributo de Defesa do player  (raw, ex: 17.0).
     * @param ataqueInimigo  Atributo de Ataque do inimigo (raw, ex: 15.0).
     * @return Multiplicador de dano em [0.0, 0.75, 1.0].
     *
     * @note Batalha aplica: danoFinal = danoRolado × multiplicador.
     *
     * @par Exemplos
     * @code
     *   processarDefesa(18.0, 15.0) → 0.00  (DEF > ATQ)
     *   processarDefesa(13.0, 15.0) → 0.75  (13/15 = 0.87 ≥ 0.8)
     *   processarDefesa(8.0,  15.0) → 1.00  (8/15 = 0.53 < 0.8)
     * @endcode
     *
     * @see Regras.md — Seção 2.6
     */
    static double ProcessarDefesa(double defPlayer, double ataqueInimigo);

    /**
     * @brief Calcula o multiplicador de dano quando o jogador Esquiva.
     *
     * Compara o atributo de Agilidade do player com o de Ataque do inimigo:
     * - agiPlayer > ataqueInimigo  → 0%   de dano (0.00)
     * - agiPlayer < ataqueInimigo  → 100% de dano (1.00)
     * - agiPlayer == ataqueInimigo → 50%  de dano (0.50)
     *
     * @param agiPlayer      Atributo de Agilidade do player  (raw, ex: 15.0).
     * @param ataqueInimigo  Atributo de Ataque do inimigo    (raw, ex: 12.0).
     * @return Multiplicador de dano em [0.0, 0.50, 1.0].
     *
     * @note Batalha aplica: danoFinal = danoRolado × multiplicador.
     *
     * @par Exemplos
     * @code
     *   processarEsquiva(15.0, 12.0) → 0.00  (AGI > ATQ)
     *   processarEsquiva(10.0, 12.0) → 1.00  (AGI < ATQ)
     *   processarEsquiva(12.0, 12.0) → 0.50  (AGI == ATQ)
     * @endcode
     *
     * @see Regras.md — Seção 2.7
     */
    static double ProcessarEsquiva(double agiPlayer, double ataqueInimigo);
};

#endif