/**
 * @file Criacao.hpp
 * @brief Declarações relacionadas à criação/carregamento de personagens.
 */

#ifndef DEMO_CRIACAO_HPP
#define DEMO_CRIACAO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "entities/character/Jogador.hpp"
#include "demo/ConfigExploracao.hpp"

/**
 * @brief Exibe intro, sistema de saves e cria ou carrega um personagem.
 *
 * @param view        Interface de exibição.
 * @param ctrl        Interface de input.
 * @param cenaInicial [out] ID da cena em que o jogador deve começar (1 se novo).
 * @return Jogador pronto para uso.
 */
Jogador criarPersonagem(IView& view, IController& ctrl, int& cenaInicial);

/**
 * @brief Versão com flags de configuração.
 * cfg.skipEnter=true -> pula cutscene, título, diálogos de animação e
 * leituras diretas de stdin (útil para testes)
 */
Jogador criarPersonagem(IView& view, IController& ctrl, int& cenaInicial,
                        const ConfigExploracao& cfg);

#endif
