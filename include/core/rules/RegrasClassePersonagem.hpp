/**
 * @file RegrasClassePersonagem.hpp
 * @brief Define toda a logica da inicialização de personagem conforme suas classes.
 *
 *  Utilizado por Criacao para inicializar um player.
 *
 *  @see regras.md
 *
 */
#ifndef REGRAS_CLASSE_PERSONAGEM_HPP
#define REGRAS_CLASSE_PERSONAGEM_HPP

#include <array>
#include <vector>
#include "core/rules/Regras.hpp"
#include "entities/character/ClassePersonagem.hpp"
#include "Dados.hpp"

/**
 * @class RegrasClassePersonagem
 * @brief Regras de criação e progressão de atributos por classe.
 *
 * Centraliza três decisões que dependem do arquétipo do personagem:
 * - Dado de vida (HP máximo do dado por classe)
 * - Prioridade de distribuição dos atributos rolados
 * - Fórmula de HP inicial e HP por nível
 *
 * Tabela de distribuição (1º = maior valor rolado):
 * | Classe    | Ataque | Defesa | Agilidade | Poder |
 * |-----------|--------|--------|-----------|-------|
 * | Guerreiro | 1º     | 2º     | 3º        | 4º    |
 * | Arqueiro  | 2º     | 4º     | 1º        | 3º    |
 * | Tank      | 2º     | 1º     | 4º        | 3º    |
 * | Mago      | 3º     | 4º     | 2º        | 1º    |
 */
class RegrasClassePersonagem : public Regras {
public:
    /**
     * @brief Retorna o valor máximo do dado de vida da classe.
     *
     * | Classe    | Dado | Máximo |
     * |-----------|------|--------|
     * | Guerreiro | 1d10 | 10     |
     * | Arqueiro  | 1d8  | 8      |
     * | Mago      | 1d6  | 6      |
     * | Tanque    | 1d12 | 12     |
     *
     * @param classe Arquétipo do personagem.
     * @return Valor máximo do dado de vida.
     */
    static int getDadoVida(TipoClasse classe);

    /**
     * @brief Distribui os valores rolados nos atributos conforme a prioridade da classe.
     *
     * @param classe Arquétipo do personagem.
     * @param valoresRolados 4 valores em ordem decrescente (saída de Dados::gerarAtributos).
     * @return Array {ataque, defesa, poder, agilidade} com os valores distribuídos.
     * @throw std::invalid_argument Se valoresRolados tiver menos de 4 elementos.
     */
    static std::array<double, 4> distribuirAtributos(
        TipoClasse classe,
        const std::vector<int>& valoresRolados
    );

    /**
     * @brief Calcula o HP inicial do personagem (nível 1).
     *
     * Fórmula: HP = getDadoVida(classe) + calcularCoeficiente(valorDefesa)
     *
     * @param classe Arquétipo do personagem.
     * @param valorDefesa Valor bruto do atributo Defesa após distribuição.
     * @return HP inicial.
     */
    static double calcularVidaInicial(TipoClasse classe, double valorDefesa);

    /**
     * @brief Calcula o incremento de HP ao subir de nível.
     *
     * Fórmula: incremento = rolagem(dado de vida) + calcularCoeficiente(valorDefesa)
     *
     * @param classe Arquétipo do personagem.
     * @param valorDefesa Valor bruto do atributo Defesa.
     * @param dados Instância de Dados para a rolagem.
     * @return Incremento de HP a ser somado ao total.
     */
    static double calcularVidaNovoNivel(TipoClasse classe, double valorDefesa, Dados& dados);
};

#endif
