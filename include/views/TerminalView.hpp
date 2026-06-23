/**
 * @file TerminalView.hpp
 * @brief Declaração da classe TerminalView.
 */

#ifndef TERMINALVIEW_HPP
#define TERMINALVIEW_HPP

#include "utils/IView.hpp"

/**
 * @class TerminalView
 * @brief Implementação concreta da interface IView para saída de dados no terminal.
 *
 * Responsável por exibir mensagens e elementos visuais
 * da interface textual do jogo através do console.
 */
class TerminalView : public IView {
public:

    /**
     * @brief Exibe uma mensagem no terminal.
     * @param msg Texto a ser exibido.
     */
    void exibir(const std::string& msg) const override;

    /**
     * @brief Exibe uma linha separadora no terminal.
     */
    void exibirLinha() const override;
};

#endif