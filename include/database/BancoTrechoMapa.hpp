#ifndef INFO_TRECHO_MAPA_HPP
#define INFO_TRECHO_MAPA_HPP

#include "database/StructTrechoMapa.hpp"

class BancoTrechoMapa{
public:

    static InfoTrechoMapa obterTrechoMapa(int id);
};

#endif