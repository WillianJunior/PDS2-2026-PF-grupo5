#ifndef IVIEW_HPP
#define IVIEW_HPP

#include <string>

class IView {
public:
    virtual ~IView() = default;
    virtual void exibir(const std::string& msg) const = 0;
    virtual void exibirLinha() const = 0;
};

#endif
