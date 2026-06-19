#include <iostream>
#include <limits>
#include "controllers/InputController.hpp"

std::string InputController::lerTexto() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int InputController::lerInteiro() {
    int n = 0;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return n;
}
