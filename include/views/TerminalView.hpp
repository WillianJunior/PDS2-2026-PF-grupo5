#ifndef TERMINALVIEW_HPP
#define TERMINALVIEW_HPP

#include "utils/IView.hpp"

class TerminalView : public IView {
public:
    void exibir(const std::string& msg) const override;
    void exibirLinha() const override;
};

#endif
