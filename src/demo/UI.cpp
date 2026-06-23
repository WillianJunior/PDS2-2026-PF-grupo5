#include <algorithm>
#include <fstream>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>

#include "demo/UI.hpp"

static int larguraTerminal()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
        return ws.ws_col;
    return 80;
}

void exibirCentrado(IView& view, const std::string& texto)
{
    int pad = std::max(0, (larguraTerminal() - (int)texto.size()) / 2);
    view.exibir(std::string(pad, ' ') + texto);
}

void exibirAsciiArtArquivo(IView& view, const std::string& caminho)
{
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) return;

    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(arquivo, linha))
        linhas.push_back(linha);

    size_t maxLarg = 0;
    for (const auto& l : linhas)
        maxLarg = std::max(maxLarg, l.size());

    int pad = std::max(0, (larguraTerminal() - (int)maxLarg) / 2);
    std::string prefixo(pad, ' ');

    for (const auto& l : linhas)
        view.exibir(prefixo + l);
}
