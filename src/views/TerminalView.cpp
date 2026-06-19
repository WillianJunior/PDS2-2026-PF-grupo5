#include <iostream>
#include <string>
#include "views/TerminalView.hpp"

void TerminalView::exibir(const std::string& msg) const {
    std::cout << msg << '\n';
}

void TerminalView::exibirLinha() const {
    std::cout << std::string(55, '-') << '\n';
}
