#include "database/BancoTrechoMapa.hpp"
#include <stdexcept>

InfoTrechoMapa BancoTrechoMapa::obterTrechoMapa(int id) {

    if(id <= 0)
    {
        throw std::invalid_argument(
            "ID de trecho invalido"
        );
    }

    switch (id) {

    // Cena 1: trechos 101–103
    case 101:
        return { 101, "", 1, {1, 2}, false, -1, 102, -1, 1 };
    case 102:
        return { 102, "", 2, {3, 1}, false, -1, 103, 101, 1 };
    case 103:
        return { 103, "", 3, {4, 2}, false, -1, -1, 102, 1 };

    // Cena 2: trechos 201–203
    case 201:
        return { 201, "", -1, {10, 11}, false, -1, 202, -1, 2 };
    case 202:
        return { 202, "", -1, {12, 10}, false, -1, 203, 201, 2 };
    case 203:
        return { 203, "", -1, {13, 11}, false, -1, -1, 202, 2 };

    // Cena 3: trechos 301–303
    case 301:
        return { 301, "", -1, {20, 21}, false, -1, 302, -1, 3 };
    case 302:
        return { 302, "", -1, {22, 20}, false, -1, 303, 301, 3 };
    case 303:
        return { 303, "", -1, {23, 21}, false, -1, -1, 302, 3 };

    // Cena 4: trechos 401–403
    case 401:
        return { 401, "", -1, {30, 31}, false, -1, 402, -1, 4 };
    case 402:
        return { 402, "", -1, {32, 30}, false, -1, 403, 401, 4 };
    case 403:
        return { 403, "", -1, {33, 31}, false, -1, -1, 402, 4 };

    // Cena 5: trechos 501–503
    case 501:
        return { 501, "", -1, {40, 41}, false, -1, 502, -1, 5 };
    case 502:
        return { 502, "", -1, {42, 40}, false, -1, 503, 501, 5 };
    case 503:
        return { 503, "", -1, {43, 41}, false, -1, -1, 502, 5 };

    // Cena 6: trechos 601–603
    case 601:
        return { 601, "", -1, {50, 51}, false, -1, 602, -1, 6 };
    case 602:
        return { 602, "", -1, {52, 50}, false, -1, 603, 601, 6 };
    case 603:
        return { 603, "", -1, {53, 51}, false, -1, -1, 602, 6 };

    // Cena 7: trechos 701–703
    case 701:
        return { 701, "", -1, {60, 61}, false, -1, 702, -1, 7 };
    case 702:
        return { 702, "", -1, {62, 60}, false, -1, 703, 701, 7 };
    case 703:
        return { 703, "", -1, {63, 61}, false, -1, -1, 702, 7 };

    default:
        throw std::invalid_argument("TrechoMapa com id desconhecido: "
        + std::to_string(id));
    }
}
