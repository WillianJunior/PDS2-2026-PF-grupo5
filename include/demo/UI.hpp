#ifndef DEMO_UI_HPP
#define DEMO_UI_HPP

#include <string>
#include "utils/IView.hpp"

void exibirCentrado(IView& view, const std::string& texto);
void exibirAsciiArtArquivo(IView& view, const std::string& caminho);

#endif
