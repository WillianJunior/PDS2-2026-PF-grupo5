#include <iostream>
#include <limits>
#include "controllers/InputController.hpp"

std::string InputController::lerTexto() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int InputController::lerInteiro() {
    int valor;

    while (true) {
        std::cin >> valor;

        if (!std::cin.fail()) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return valor;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout << "Entrada invalida. Digite um numero: ";
    }
}