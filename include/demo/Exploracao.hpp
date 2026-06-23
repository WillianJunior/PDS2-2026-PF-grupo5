/**
* @file Exploracao.hpp
* @brief Declaração da funcionalidade de exploração do jogo.
*/

#ifndef EXPLORACAO_HPP
#define EXPLORACAO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"


/**
 * @brief Executa o modo de exploração.
 *
 * Inicia e controla o fluxo de exploração do jogo, permitindo ao
 * jogador percorrer cenários, interagir com elementos do ambiente
 * e avançar pela narrativa.
 *
 * @param view Interface responsável pela exibição das mensagens.
 * @param ctrl Interface responsável pela leitura das entradas do usuário.
 */
void executarExploracao(IView& view, IController& ctrl);

#endif