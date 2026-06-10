#include "database/BancoTrechoMapa.hpp"
#include <stdexcept>

InfoTrechoMapa BancoTrechoMapa::obterTrechoMapa(int id) {
    switch (id) {

    // Cena 1: trechos 101–103
    case 101:
        return { 101, "", 1, {1, 2}, 2, 102, -1, 1 };
    case 102:
        return { 102, "", 2, {3, 1}, 2, 103, 101, 1 };
    case 103:
        return { 103, "", 3, {4, 2}, 2, -1, 102, 1 };

    // Cena 2: trechos 201–203
    case 201:
        return { 201, "", -1, {10, 11}, 2, 202, -1, 2 };
    case 202:
        return { 202, "", -1, {12, 10}, 2, 203, 201, 2 };
    case 203:
        return { 203, "", -1, {13, 11}, 2, -1, 202, 2 };

    // Cena 3: trechos 301–303
    case 301:
        return { 301, "", -1, {20, 21}, 2, 302, -1, 3 };
    case 302:
        return { 302, "", -1, {22, 20}, 2, 303, 301, 3 };
    case 303:
        return { 303, "", -1, {23, 21}, 2, -1, 302, 3 };

    // Cena 4: trechos 401–403
    case 401:
        return { 401, "", -1, {30, 31}, 2, 402, -1, 4 };
    case 402:
        return { 402, "", -1, {32, 30}, 2, 403, 401, 4 };
    case 403:
        return { 403, "", -1, {33, 31}, 2, -1, 402, 4 };

    // Cena 5: trechos 501–503
    case 501:
        return { 501, "", -1, {40, 41}, 2, 502, -1, 5 };
    case 502:
        return { 502, "", -1, {42, 40}, 2, 503, 501, 5 };
    case 503:
        return { 503, "", -1, {43, 41}, 2, -1, 502, 5 };

    // Cena 6: trechos 601–603
    case 601:
        return { 601, "", -1, {50, 51}, 2, 602, -1, 6 };
    case 602:
        return { 602, "", -1, {52, 50}, 2, 603, 601, 6 };
    case 603:
        return { 603, "", -1, {53, 51}, 2, -1, 602, 6 };

    // Cena 7: trechos 701–703
    case 701:
        return { 701, "", -1, {60, 61}, 3, 702, -1, 7 };
    case 702:
        return { 702, "", -1, {62, 60}, 3, 703, 701, 7 };
    case 703:
        return { 703, "", -1, {63, 61}, 3, -1, 702, 7 };

    default:
        throw std::invalid_argument("TrechoMapa com id desconhecido: " + std::to_string(id));
    }
}
