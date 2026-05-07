/**
 * @file Batalha.hpp
 * @brief Gerenciador do motor de combate por turnos do RPG.
 */

#ifndef BATALHA_HPP
#define BATALHA_HPP

#include <vector>
#include <string>

#include "Personagem.hpp"
#include "Item.hpp"

// Evita a dependência circular com Cena (Forward Declaration).
class Cena;

/**
 * @enum AcaoBatalha
 * @brief Define as ações possíveis que o jogador ou NPC podem tomar.
 */
enum class AcaoBatalha {
    AtaqueSimples, ///< Baseado apenas nos pontos de ataque.
    AtaqueRapido,  ///< Usa agilidade e consome mana.
    AtaqueForte,   ///< Dano massivo, alto consumo de mana, reduz defesa inimiga.
    Defesa,        ///< Tenta reduzir o dano recebido.
    Esquiva,       ///< Tenta anular o dano baseado em agilidade.
    UsarItem,      ///< Abre o inventário para consumir um item.
    Fugir          ///< Tenta encerrar a batalha prematuramente.
};

/**
 * @class Batalha
 * @brief Classe responsável pela lógica de combate, turnos e cálculo de atributos.
 * A classe gerencia a interação entre Player e Inimigo, aplicando variabilidade
 * baseada em sorte e modificadores de classe/nível.
 */
class Batalha {
private:
    Personagem* _player;           ///< Ponteiro para o personagem do jogador.
    Personagem* _inimigo;          ///< Ponteiro para o oponente (NPC ou Boss).
    int _turnoAtual;               ///< Indicador de turno atual da batalha.
    std::vector<AcaoBatalha> _acoesDisponiveis; ///< Lista de ações (Ataque, Defesa, Esquiva).
    float _fatorDificuldade;       ///< Indicador de dificuldade da batalha.
    int _progressoBatalha;         ///< Indicador de progresso da batalha.

    /**
     * @brief Calcula a variabilidade de uma ação baseada em sorte.
     * @details A fórmula base é $$Atributo \times [0.8, 1.2]$$.
     * @param valorBase O valor do atributo original.
     * @return O valor modificado pela sorte.
     */
    float calcularVariabilidade(int valorBase);

public:
    /**
     * @brief Construtor da batalha.
     * @param player Ponteiro para o herói.
     * @param inimigo Ponteiro para o inimigo (boss ou NPC).
     */
    Batalha(Personagem* player, Personagem* inimigo);

    /**
     * @brief Configura o cenário de combate e inicializa os turnos.
     * @note Chamado quando a Cena identifica um encontro.
     */
    void iniciarBatalha();


     /**
     * @brief Executa a lógica de uma ação específica.
     * @param acao Valor do enum AcaoBatalha selecionado.
     * @details Em se tratando de ataques:
     * - **Simples**: Apenas pontos de ataque.
     * - **Rápido**: Ataque + Agilidade + consumo de Mana (Reduz agilidade inimiga).
     * - **Forte**: Ataque + Alto consumo de Mana (Reduz defesa e esquiva inimiga).
     * @throw std::invalid_argument Se uma ação inválida for processada.
     */
    void realizarAcao(AcaoBatalha acao);   

    /**
     * @brief Lógica de defesa baseada na proporção $\frac{Defesa}{Ataque}$.
     * @details 
     * - Se $\frac{Defesa}{Ataque} < 0.8 \rightarrow 100\%$ de dano.
     * - Se $0.8 \le \frac{Defesa}{Ataque} < 1.0 \rightarrow 75\%$ de dano.
     * - Se $Ataque < Defesa \rightarrow 0\%$ de dano.
     */
    void processarDefesa();

    /**
     * @brief Lógica de esquiva baseada em agilidade.
     * @details 
     * - $Agilidade > Ataque \rightarrow 0\%$ de dano.
     * - $Agilidade < Ataque \rightarrow 100\%$ de dano.
     * - $Agilidade = Ataque \rightarrow 50\%$ de dano.
     */
    void processarEsquiva();

    /**
     * @brief Define e entrega os itens/experiência após a vitória.
     * @param cenaAtual Referência para atualizar o estado do mapa.
     */
    void definirRecompensa(Cena& cenaAtual);

    /**
     * @brief Finaliza o combate, limpa buffers e retorna ao estado de exploração.
     */
    void finalizarBatalha();

    // Getter de turno
    int getTurno() const { return _turnoAtual; }
};

#endif