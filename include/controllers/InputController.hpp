/**
 * @file InputController.hpp
 * @brief Declaração da classe InputController.
 */

#ifndef INPUTCONTROLLER_HPP
#define INPUTCONTROLLER_HPP

#include "utils/IController.hpp"

/**
 * @class InputController
 * @brief Implementação concreta da interface IController para entrada de dados via terminal.
 *
 * Responsável por capturar informações digitadas pelo usuário,
 * permitindo a leitura de textos e números inteiros.
 */

class InputController : public IController {
public:
     /**
     * @brief Lê uma linha de texto digitada pelo usuário.
     * @return Texto informado pelo usuário.
     */
    std::string lerTexto() override;

    /**
     * @brief Lê um número inteiro digitado pelo usuário.
     * @return Valor inteiro informado pelo usuário.
     */
    int lerInteiro() override;
};

#endif
