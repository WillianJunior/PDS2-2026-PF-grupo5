/**
 * @file Regras.hpp
 * @brief Classe base que centraliza os métodos e tabelas compartilhados
 *        por todas as subclasses do sistema de regras do jogo.
 *
 * Hierarquia:
 * @code
 *   Regras  (esta classe)
 *     ├── RegrasBatalha
 *     ├── RegrasProgresso
 *     ├── RegrasPersonagem
 *     ├── RegrasAtaque           
 *     └── RegrasClassePersonagem 
 * @endcode
 *
 * Nenhuma filha deve reimplementar os métodos aqui definidos.
 */

#ifndef REGRAS_HPP
#define REGRAS_HPP

#include <stdexcept>
#include <array>

/**
 * @class Regras
 * @brief Classe pai abstrata do sistema de regras.
 *
 * Disponibiliza cinco métodos estáticos protegidos compartilhados entre
 * todas as filhas:
 *
 * | Método                  | Fórmula / Fonte              | Usada por                          |
 * |-------------------------|------------------------------|------------------------------------|
 * | calcularCoeficiente()   | y = 0,5x − 5                 | RegrasBatalha, RegrasPersonagem,   |
 * |                         |                              | RegrasAtaque, RegrasClassePersonagem|
 * | calcularCD()            | CD = 10 + coef_agilidade     | RegrasBatalha, RegrasPersonagem    |
 * | calcularPPTotal()       | PP = valorPoder × 5          | RegrasPersonagem, RegrasClassePersonagem|
 * | bonusProficiencia()     | tabela LV → bônus            | RegrasBatalha, RegrasAtaque        |
 * | xpParaProximoNivel()    | tabela LV → XP               | RegrasProgresso, RegrasBatalha     |
 */
class Regras {
public:

    // Tabelas internas (constexpr — zero custo em runtime)

    /**
     * @brief Bônus de proficiência por nível (índice 0 = LV 1).
     * LV 1–3 → +2 | LV 4–6 → +3 | LV 7–9 → +4 | LV 10 → +5
     */
    static constexpr std::array<int, 10> BONUS_PROFICIENCIA = {
        2, 2, 2,  // LV 1, 2, 3
        3, 3, 3,  // LV 4, 5, 6
        4, 4, 4,  // LV 7, 8, 9
        5         // LV 10
    };

    /**
     * @brief XP necessário para avançar do nível N para N+1 (índice 0 = LV 1).
     * Índice 9 (LV 10) = 0.0 pois é o nível máximo.
     */
    static constexpr std::array<double, 10> XP_POR_NIVEL = {
        300.0,    // LV 1 → 2
        900.0,    // LV 2 → 3
        2700.0,   // LV 3 → 4
        6500.0,   // LV 4 → 5
        14000.0,  // LV 5 → 6
        23000.0,  // LV 6 → 7
        34000.0,  // LV 7 → 8
        48000.0,  // LV 8 → 9
        64000.0,  // LV 9 → 10
        0.0       // LV 10 → máximo atingido
    };

    // Nível máximo 

    /** @brief Nível máximo atingível pelo jogador. */
    static constexpr int NIVEL_MAXIMO = 10;

    // Métodos compartilhados 

    /**
     * @brief Converte um valor de atributo em coeficiente: y = 0,5x − 5.
     *
     * Usado para calcular os modificadores de ATQ, DEF, AGI e Poder
     * que entram nas fórmulas de combate, vida, mana e CD.
     *
     * @param valorAtributo Valor bruto do atributo (ex: 17, 15, 12, 11).
     * @return Coeficiente resultante (pode ser negativo se valorAtributo < 10).
     *
     * @par Exemplos
     * @code
     *   calcularCoeficiente(17) → +3,5
     *   calcularCoeficiente(15) → +2,5
     *   calcularCoeficiente(12) → +1,0
     *   calcularCoeficiente(11) → +0,5
     *   calcularCoeficiente(10) →  0,0
     *   calcularCoeficiente(8)  → -1,0
     * @endcode
     */
    static double calcularCoeficiente(double valorAtributo);

    /**
     * @brief Calcula a Classe de Dificuldade (CD) a partir do atributo de Agilidade.
     *
     * Fórmula: CD = 10 + calcularCoeficiente(valorAgilidade)
     *
     * A CD define o valor mínimo que um atacante precisa SUPERAR (não igualar)
     * para que seu ataque acerte. Em empate de agilidade, o jogador age primeiro.
     *
     * @param valorAgilidade Valor bruto do atributo Agilidade.
     * @return CD calculada.
     *
     * @par Exemplos
     * @code
     *   calcularCD(15) → 10 + 2,5 = 12,5   (Mago do exemplo base)
     *   calcularCD(10) → 10 + 0,0 = 10,0
     *   calcularCD(8)  → 10 + (-1,0) = 9,0
     * @endcode
     */
    static double calcularCD(double valorAgilidade);

    /**
     * @brief Calcula o total de Pontos de Poder (PP / Mana) a partir do atributo Poder.
     *
     * Fórmula: PP Total = valorPoder × 5
     *
     * @param valorPoder Valor bruto do atributo Poder.
     * @return Total de PP disponível.
     *
     * @par Exemplos
     * @code
     *   calcularPPTotal(17) → 85 PP  (Mago do exemplo base)
     *   calcularPPTotal(11) → 55 PP  (Guerreiro do exemplo base)
     * @endcode
     */
    static double calcularPPTotal(double valorPoder);

    /**
     * @brief Retorna o bônus de proficiência para um determinado nível.
     *
     * Somado a rolagens de acerto em ataques que consomem PP,
     * e a rolagens de acerto do Ataque Rápido.
     *
     * @param nivel Nível atual do personagem (1 a 10).
     * @return Bônus de proficiência correspondente (+2, +3, +4 ou +5).
     * @throw std::out_of_range Se nivel < 1 ou nivel > 10.
     *
     * @par Tabela
     * @code
     *   LV 1–3 → +2  |  LV 4–6 → +3  |  LV 7–9 → +4  |  LV 10 → +5
     * @endcode
     */
    static int bonusProficiencia(int nivel);

    /**
     * @brief Retorna o XP necessário para avançar do nível atual para o próximo.
     *
     * @param nivelAtual Nível atual do personagem (1 a 10).
     * @return XP necessário. Retorna 0.0 se nivelAtual == NIVEL_MAXIMO.
     * @throw std::out_of_range Se nivelAtual < 1 ou nivelAtual > 10.
     *
     * @par Tabela
     * @code
     *   LV 1 → 300     LV 4 → 6.500   LV 7 → 34.000
     *   LV 2 → 900     LV 5 → 14.000  LV 8 → 48.000
     *   LV 3 → 2.700   LV 6 → 23.000  LV 9 → 64.000
     *                                  LV 10 → 0 (máximo)
     * @endcode
     */
    static double xpParaProximoNivel(int nivelAtual);

public:
    /** @brief Destrutor virtual — necessário para herança segura. */
    virtual ~Regras() = default;
};

#endif // REGRAS_HPP