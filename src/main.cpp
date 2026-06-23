#include <iostream>
#include <exception>

#include "views/TerminalView.hpp"
#include "controllers/InputController.hpp"
#include "demo/Exploracao.hpp"

int main()
{
    try
    {
        TerminalView view;
        InputController ctrl;
        executarExploracao(view, ctrl);
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