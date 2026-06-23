/**
 * @file Demo.hpp
 * @brief Declaração da função responsável por executar a demo de validação do jogo.
 */

#ifndef DEMO_HPP
#define DEMO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"

/**
 * @brief Executa a demonstração de validação do jogo.
 *
 * Inicializa um personagem pré-configurado, carrega uma cena de teste
 * e permite ao usuário interagir com trechos, NPCs, itens e batalhas
 * simuladas até o encerramento da demo.
 *
 * @param view Interface responsável pela exibição de mensagens.
 * @param ctrl Interface responsável pela leitura das entradas do usuário.
 */
void executarDemo(IView& view, IController& ctrl);

#endif