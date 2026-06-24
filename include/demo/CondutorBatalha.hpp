/**
 * @file CondutorBatalha.hpp
 * @brief Orquestrador do loop de batalha para a camada demo.
 *
 * Encapsula a lógica de apresentação de um combate completo entre jogador e oponente
 */

#ifndef DEMO_CONDUTOR_BATALHA_HPP
#define DEMO_CONDUTOR_BATALHA_HPP

#include <string>

#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "demo/ConfigExploracao.hpp"
#include "entities/battle/Batalha.hpp" // define AcaoBatalha

// Forward declarations
class Jogador;
class Personagem;
class Dados;
class Cena;

/**
 * @enum ResultadoBatalha
 * @brief Resultado possível de um confronto conduzido por CondutorBatalha.
 */
enum class ResultadoBatalha { Vitoria, Derrota, Fuga };

/**
 * @class CondutorBatalha
 * @brief Conduz um combate completo entre jogador e inimigo via IView/IController.
 *
 */
class CondutorBatalha {
public:
    /**
     * @param view    Interface de exibição
     * @param ctrl    Interface de entrada de inputs do jogador
     * @param jogador Player
     * @param inimigo Oponente (inimigo comum ou boss)
     * @param dados   Gerador de dados (injetado para testabilidade)
     * @param cena    Cena atual (usada em definirRecompensa ao vencer)
     * @param cfg     Flags de comportamento da demo
     */
    CondutorBatalha(IView& view, IController& ctrl,
                    Jogador& jogador, Personagem& inimigo,
                    Dados& dados, Cena& cena,
                    const ConfigExploracao& cfg = {});

    /**
     * @brief Executa o loop de batalha até vitória, derrota ou fuga.
     * @return Resultado do combate.
     */
    ResultadoBatalha executar();

private:
    IView&           _view;
    IController&     _ctrl;
    Jogador&         _jogador;
    Personagem&      _inimigo;
    Dados&           _dados;
    Cena&            _cena;
    ConfigExploracao _cfg;

    static std::string _labelAcao(AcaoBatalha acao);
};

#endif
