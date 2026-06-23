/**
 * @file DemoCriacao.hpp
 * @brief Declarações relacionadas à criação de personagens para a demo.
 */

#ifndef DEMO_CRIACAO_HPP
#define DEMO_CRIACAO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "entities/character/Jogador.hpp"


/**
 * @brief Cria um personagem a partir das informações fornecidas pelo usuário.
 *
 * Conduz o processo de criação do personagem, coletando os dados
 * necessários e retornando uma instância de jogador configurada.
 *
 * @param view Interface responsável pela exibição das mensagens.
 * @param ctrl Interface responsável pela leitura das entradas do usuário.
 *
 * @return Jogador criado e configurado.
 */
Jogador criarPersonagem(IView& view, IController& ctrl);

#endif