#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

#include <string>

class IController {
public:
    virtual ~IController() = default;
    virtual std::string lerTexto() = 0;
    virtual int lerInteiro() = 0;
};

#endif
