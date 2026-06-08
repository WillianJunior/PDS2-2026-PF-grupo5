#ifndef STRUCT_CENA_HPP
#define STRUCT_CENA_HPP

#include <string>
#include <vector>

struct InfoCena {

    int id;

    std::string arcano;

    std::string descricao;

    int trechoInicial;

    std::vector<int> trechos;
};



#endif