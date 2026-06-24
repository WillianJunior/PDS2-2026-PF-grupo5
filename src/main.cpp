#include <iostream>
#include <exception>
#include <string>

#include "views/TerminalView.hpp"
#include "controllers/InputController.hpp"
#include "demo/Exploracao.hpp"
#include "demo/ConfigExploracao.hpp"

int main(int argc, char* argv[])
{
    ConfigExploracao cfg;
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--skip-lore")  cfg.skipLore  = true;
        if (arg == "--skip-enter") cfg.skipEnter = true;
    }

    try
    {
        TerminalView view;
        InputController ctrl;
        executarExploracao(view, ctrl, cfg);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro fatal: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Erro fatal desconhecido.\n";
        return 1;
    }
    return 0;
}
