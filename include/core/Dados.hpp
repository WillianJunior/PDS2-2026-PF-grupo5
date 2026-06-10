/**
 * @file Dados.hpp
 * @brief Utilitário centralizado para rolagem de dados do RPG.
 *
 * Todos os módulos do jogo que precisam de aleatoriedade 
 * devem usar esta classe em vez de implementar
 * sua própria lógica de RNG.
 *
 * Uso básico:
 * @code
 *   Dados dados;               // construtor inicializa semente aleatória
 *   int resultado = dados.d20();
 *   int dano = dados.rolar(3, 6);        // 3d6
 *   int atributo = dados.rolar4d6();     // 4d6 descarte o menor
 * @endcode
 *
 * Para testes determinísticos, use o construtor com semente fixa:
 * @code
 *   Dados dados(42);           // semente fixa — resultados reproduzíveis
 * @endcode
 */

#ifndef DADOS_HPP
#define DADOS_HPP

#include <random>
#include <vector>
#include <stdexcept>

/**
 * @class Dados
 * @brief Encapsula a geração de números aleatórios para rolagem de dados.
 *
 * Internamente usa std::mt19937 (Mersenne Twister), um gerador de alta
 * qualidade estatística. A semente padrão vem de std::random_device,
 * garantindo resultados diferentes a cada execução.
 */
class Dados {
private:
    std::mt19937 _rng; ///< Motor de geração de números pseudoaleatórios.

    /**
     * @brief Rola um único dado com o número de lados especificado.
     * @param lados Número de lados do dado (deve ser >= 2).
     * @return Valor inteiro no intervalo [1, lados].
     * @throw std::invalid_argument Se lados < 2.
     */
    int _rolarUm(int lados);

public:

    /**
     * @brief Construtor padrão — semente aleatória via std::random_device.
     * Resultados variam a cada execução do programa.
     */
    Dados();

    /**
     * @brief Construtor com semente fixa — para testes determinísticos.
     * @param semente Valor da semente. Mesma semente → mesma sequência.
     */
    explicit Dados(unsigned int semente);

    // ── Dados individuais ─────────────────────────────────────────────────

    /** @brief Rola 1d4. @return Valor em [1, 4]. */
    int d4();

    /** @brief Rola 1d6. @return Valor em [1, 6]. */
    int d6();

    /** @brief Rola 1d8. @return Valor em [1, 8]. */
    int d8();

    /** @brief Rola 1d10. @return Valor em [1, 10]. */
    int d10();

    /** @brief Rola 1d12. @return Valor em [1, 12]. */
    int d12();

    /** @brief Rola 1d20. @return Valor em [1, 20]. */
    int d20();

    // ── Rolagens compostas ────────────────────────────────────────────────

    /**
     * @brief Rola múltiplos dados e retorna a soma.
     * @param quantidade Número de dados a rolar (deve ser >= 1).
     * @param lados Número de lados de cada dado (deve ser >= 2).
     * @return Soma dos resultados de todos os dados.
     * @throw std::invalid_argument Se quantidade < 1 ou lados < 2.
     *
     * @par Exemplo
     * @code
     *   dados.rolar(3, 6);   // 3d6 — soma de três d6
     *   dados.rolar(2, 10);  // 2d10
     *   dados.rolar(1, 20);  // equivalente a d20()
     * @endcode
     */
    int rolar(int quantidade, int lados);

    /**
     * @brief Rola 4d6 e descarta o menor valor (método D&D de geração de atributos).
     * @return Soma dos 3 maiores resultados entre os 4 dados rolados.
     *
     * @par Exemplo
     * @code
     *   // Rolagem: 3, 2, 5, 3 → descarta 2 → retorna 11
     *   int atributo = dados.rolar4d6();
     * @endcode
     */
    int rolar4d6();

    /**
     * @brief Gera o conjunto completo de 4 atributos para criação de personagem.
     * @return Vetor de 4 inteiros em ordem DECRESCENTE, cada um gerado por rolar4d6().
     *
     * @par Exemplo
     * @code
     *   // Possível retorno: {17, 15, 12, 11}
     *   std::vector<int> atributos = dados.gerarAtributos();
     * @endcode
     */
    std::vector<int> gerarAtributos();

    /**
     * @brief Rola 2d20 e retorna o maior (vantagem D&D).
     * @return O maior valor entre dois d20.
     */
    int d20Vantagem();

    /**
     * @brief Rola 2d20 e retorna o menor (desvantagem D&D).
     * @return O menor valor entre dois d20.
     */
    int d20Desvantagem();
};

#endif