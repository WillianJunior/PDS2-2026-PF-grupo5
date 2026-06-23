#ifndef DEMO_CRIACAO_HPP
#define DEMO_CRIACAO_HPP

#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "entities/character/Jogador.hpp"

Jogador criarPersonagem(IView& view, IController& ctrl);

#endif
