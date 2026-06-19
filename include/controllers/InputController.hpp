#ifndef INPUTCONTROLLER_HPP
#define INPUTCONTROLLER_HPP

#include "utils/IController.hpp"

class InputController : public IController {
public:
    std::string lerTexto() override;
    int lerInteiro() override;
};

#endif
