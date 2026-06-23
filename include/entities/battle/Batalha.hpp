/**
 * @file Batalha.hpp
 * @brief Gerenciador do motor de combate por turnos do RPG.
 *
 * A classe Batalha é responsável pelo fluxo completo de um encontro:
 * iniciativa, turnos, execução de ações, aplicação de condições,
 * cálculo de recompensas e finalização. Toda a lógica de *regras*
 * (fórmulas, tabelas, limiares) é delegada às classes de Regras
 * correspondentes — Batalha apenas orquestra o fluxo.
 *
 * @see Regras.md — Seção 2 (Sistema de Combate) e Seção 4 (Dificuldade de Encontros)
 */

#ifndef BATALHA_HPP
#define BATALHA_HPP

#include <vector>
#include <string>

#include "../character/Personagem.hpp"
#include "../items/Item.hpp"
#include "Condicao.hpp"
#include "core/Dados.hpp"

// Evita a dependência circular com Cena (Forward Declaration).
class Cena;
class RegrasBatalha;
class IView;
class IController;

/**
 * @enum AcaoBatalha
 * @brief Define as ações possíveis que o jogador ou NPC podem tomar.
 */
enum class AcaoBatalha {
    AtaqueSimples, ///< Dado de dano + coef. ATQ. Sem custo de PP. Escala em quantidade por nível.
    AtaqueRapido,  ///< Age antes do inimigo. Usa coef. AGI. Consome PP. Efeito por classe.
    AtaqueForte,   ///< Alta potência. Consome PP. Escolhido/trocado nos LVs 3, 5 e 7.
    Defesa,        ///< Reduz dano recebido pelo coef. de DEF. Sem custo.
    Esquiva,       ///< Soma Bônus de Proficiência à CD neste turno. Sem custo.
    UsarItem,      ///< Utiliza um item do inventário.
    Fugir          ///< Abandona o combate. Bloqueado em confrontos Boss/Impossível.
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
    double _fatorDificuldade;       ///< Indicador de dificuldade da batalha.
    int _progressoBatalha;         ///< Indicador de progresso da batalha.
    Dados& _dados;                           // ← novo: injetado via construtor
    IView* _view;                            // ← novo: interface de exibição
    IController* _controller;               // ← novo: interface de input
    RegrasBatalha* _regras;                  // ← novo: regras de combate
    std::vector<Condicao> _condicoesPlayer;  // ← novo: condições ativas no player
    std::vector<Condicao> _condicoesInimigo; // ← novo: condições ativas no inimigo
    
    /**
     * @brief Calcula a variabilidade de uma ação baseada em sorte.
     * @details A fórmula base é $$Atributo \times [0.8, 1.2]$$.
     * @param valorBase O valor do atributo original.
     * @return O valor modificado pela sorte.
     */
    double calcularVariabilidade(double valorBase);
    
    /**
     * @brief Verifica se uma rolagem de acerto supera a CD do alvo.
     * @param coefAtaque Coeficiente de ATQ (ou AGI para AtaqueRapido).
     * @param nivel      Nível do atacante (para Bônus de Proficiência).
     * @param gastaPP    Se true, soma Bônus de Proficiência à rolagem.
     * @param vantagem   Se true, rola 2d20 e usa o maior.
     * @param cdAlvo     CD do alvo a ser superada.
     * @return true se a rolagem superar (não apenas igualar) a CD.
     */
    bool verificarAcerto(Personagem* alvo, double coefAtaque, int nivel,
                        bool gastaPP, bool vantagem, double cdAlvo);

    /**
     * @brief Atualiza _acoesDisponiveis com base nas condições ativas do player.
     * @example Atordoado remove AtaqueRapido e AtaqueForte; Paralisado remove tudo.
     */
    void atualizarAcoesDisponiveis();  

public:
    /**
     * @brief Construtor completo com todas as dependências.
     * @param player     Ponteiro para o herói.
     * @param inimigo    Ponteiro para o inimigo.
     * @param dados      Referência ao gerador de dados (use semente fixa em testes).
     * @param view       Ponteiro para a interface de exibição (opcional por enquanto).
     * @param controller Ponteiro para a interface de input (opcional por enquanto).
     * @param regras     Ponteiro para as regras de combate (opcional por enquanto).
     */
    Batalha(Personagem* player, Personagem* inimigo,
            Dados& dados,
            IView* view = nullptr,
            IController* controller = nullptr,
            RegrasBatalha* regras = nullptr);

    /**
     * @brief Destrutor da classe Batalha.
     */
    ~Batalha();

    /**
     * @brief Configura o encontro: calcula _fatorDificuldade, define iniciativa
     *        e avança o turno para 1.
     * @note A iniciativa é definida pela Agilidade — maior age primeiro.
     *       Em empate, o player age primeiro.
     * @see Regras.md — Seção 2.1
     */
    void iniciarBatalha();

    /**
     * @brief Executa a ação escolhida pelo jogador no turno atual.
     * @param acao Ação selecionada (do enum AcaoBatalha).
     * @throw std::invalid_argument Se a ação não estiver em _acoesDisponiveis.
     * Delega dano para ClassePersonagem::calcularDano() via RegrasAtaque.
     * @see Regras.md — Seção 2.2, 2.3, 2.4
     */
    void realizarAcao(AcaoBatalha acao);   

    /**
     * @brief Processa a ação de Defesa: reduz dano pelo coef. DEF.
     * Delega o cálculo a RegrasBatalha::processarDefesa().
     * @see Regras.md — Seção 2.6
     */
    void processarDefesa();

    /**
     * @brief Processa a ação de Esquiva: soma Bônus de Proficiência à CD.
     * Delega o cálculo a RegrasBatalha::processarEsquiva().
     * @see Regras.md — Seção 2.7
     */
    void processarEsquiva();

    /**
     * @brief Define e entrega recompensas após vitória (XP e itens).
     * @param cenaAtual Referência para atualizar o estado da Cena.
     * XP calculado por RegrasBatalha::calcularXPGanho() (com redução para Trivial).
     * @see Regras.md — Seção 4.5 e 4.6
     */
    void definirRecompensa(Cena& cenaAtual);

    /**
     * @brief Finaliza o combate, limpa buffers e retorna ao estado de exploração.
     */
    void finalizarBatalha();

    /**
     * @brief Aplica uma condição a um dos combatentes.
     * @param condicao  Struct com tipo, duração e parâmetros da condição.
     * @param noPlayer  true → aplica ao player; false → aplica ao inimigo.
     * @see Regras.md — Seção 2.5 (Condições de Combate)
     */
    void aplicarCondicao(const Condicao& condicao, bool noPlayer);

    /**
     * @brief Processa todas as condições ativas no início de cada turno.
     * Aplica efeito de turno, decrementa duração e remove condições expiradas.
     */
    void processarCondicoesAtivas();

    /**
     * @brief Verifica se a fuga está disponível (delega a RegrasBatalha).
     * @return true se o jogador pode fugir.
     * @see Regras.md — Seção 4.6
     */
    bool verificarFuga();

    /**
     * @brief Aplica o ataque do inimigo ao player sem redução defensiva.
     * Chamado pelo loop de batalha da camada demo após ações ofensivas do player
     * (AtaqueSimples, AtaqueRapido, AtaqueForte, UsarItem).
     * Para Defesa e Esquiva, o contra-ataque já está embutido em realizarAcao().
     */
    void processarAtaqueInimigo();

    /**
     * @brief Avança o turno quando o player está Paralisado (sem ações disponíveis).
     * Aplica ataque integral do inimigo, processa condições e incrementa o turno.
     * @see Regras.md — Seção 2.5 (Paralisado)
     */
    void pularTurno();

    // Getters
    int getTurno() const { return _turnoAtual; }
    double getFatorDificuldade() const { return _fatorDificuldade; }
    const std::vector<AcaoBatalha>& getAcoesDisponiveis() const { return _acoesDisponiveis; }
};

#endif