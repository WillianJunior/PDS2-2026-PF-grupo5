/**
 * @file Exploracao.hpp
 * @brief Declaração da funcionalidade de exploração do jogo.
 */

#ifndef EXPLORACAO_HPP
#define EXPLORACAO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "demo/ConfigExploracao.hpp"

/** Executa a demo completa com comportamento de produção (lore + pauses). */
void executarExploracao(IView& view, IController& ctrl);

/** Executa a demo com flags de configuração explícitas (útil para testes). */
void executarExploracao(IView& view, IController& ctrl, const ConfigExploracao& cfg);

#endif
