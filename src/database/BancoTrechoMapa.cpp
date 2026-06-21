/**
 * @file BancoTrechoMapa.cpp
 * @brief Repositorio estatico de trechos de mapa (21 trechos - 7 cenas x 3 trechos).
 *
 * Padrao de ID: cenaId x 100 + indice (ex: cena 1 -> 101, 102, 103).
 *   Trecho X01 - Exploracao: NPC de dialogo + itens. Sem inimigo.
 *   Trecho X02 - Combate comum: inimigo regular da fase.
 *   Trecho X03 - Boss / Arauto: inimigo final da fase.
 *
 * IDs de inimigos (BancoInimigo):
 *   Fase I   -> 1   (Orc Saqueador),    101 (Device - Arauto de Talos)
 *   Fase II  -> 12  (Elfo Arqueiro),    102 (Vaelthor - Arauto de Glaron)
 *   Fase III -> 22  (Tiefling Ladrao),  103 (Malphas - Arauto de Asmodeus)
 *   Fase IV  -> 32  (Conjurador),       104 (N'baki D'Itris - Arauto de Azuth)
 *   Fase V   -> 42  (Anao Berserker),   105 (Livies - Arauto de Lathander)
 *   Fase VI  -> 52  (Cavaleiro Morte),  106 (Nyriel - Arauto de Eldath)
 *   Cena 7   -> 53  (Zumbi Colossal),   999 (Sonath - Boss Final)
 */

#include "database/BancoTrechoMapa.hpp"
#include <stdexcept>

InfoTrechoMapa BancoTrechoMapa::obterTrechoMapa(int id) {

    if(id <= 0)
        throw std::invalid_argument("ID de trecho invalido");

    switch (id) {

    // Cena 1: Magisk - Floresta Geada (LV 1-2)
    case 101: {
        std::vector<int> itens = {1};
        return InfoTrechoMapa{ 101,
            "Uma clareira iluminada pelos raios do sol. Ruinas de uma aldeia orc cercam o local.",
            1, itens, false, -1, 102, -1, 1 };
    }
    case 102: {
        std::vector<int> itens = {2};
        return InfoTrechoMapa{ 102,
            "Uma passagem sombria coberta de nevoa. Sons de galhos quebrando vem das sombras.",
            2, itens, true, 1, 103, 101, 1 };
    }
    case 103: {
        std::vector<int> itens = {4, 2};
        return InfoTrechoMapa{ 103,
            "O centro da Floresta Geada. Uma tempestade imovavel persiste aqui ha decadas. Device aguarda.",
            3, itens, true, 101, -1, 102, 1 };
    }

    // Cena 2: Mantuu - Territorios Militares (LV 3-4)
    case 201: {
        std::vector<int> itens = {10, 11};
        return InfoTrechoMapa{ 201,
            "Um campo de batalha abandonado de Mantuu. Estandartes rasgados tremulam no vento.",
            4, itens, false, -1, 202, -1, 2 };
    }
    case 202: {
        std::vector<int> itens = {12, 10};
        return InfoTrechoMapa{ 202,
            "Uma fortaleza parcialmente destruida. Soldados de Mantuu patrulham os escombros.",
            5, itens, true, 12, 203, 201, 2 };
    }
    case 203: {
        std::vector<int> itens = {13, 11};
        return InfoTrechoMapa{ 203,
            "O salao do trono de Mantuu. Vaelthor, Arauto de Glaron, emerge das sombras draconicas.",
            6, itens, true, 102, -1, 202, 2 };
    }

    // Cena 3: Xantares - Portos e Becos (LV 5-6)
    case 301: {
        std::vector<int> itens = {20, 21};
        return InfoTrechoMapa{ 301,
            "Um porto movimentado de Xantares. Navios piratas ancoram sob estandartes negros.",
            7, itens, false, -1, 302, -1, 3 };
    }
    case 302: {
        std::vector<int> itens = {22, 20};
        return InfoTrechoMapa{ 302,
            "Um beco sombrio do submundo de Xantares. Tieflings observam de cima dos telhados.",
            8, itens, true, 22, 303, 301, 3 };
    }
    case 303: {
        std::vector<int> itens = {23, 21};
        return InfoTrechoMapa{ 303,
            "Um templo antigo dedicado a Asmodeus, profanado e recosturado como o proprio Malphas.",
            9, itens, true, 103, -1, 302, 3 };
    }

    // Cena 4: Kenyrock - Academias de Magia (LV 7-8)
    case 401: {
        std::vector<int> itens = {30, 31};
        return InfoTrechoMapa{ 401,
            "Uma academia de magia de Kenyrock, agora tomada por ilusoes e armadilhas arcanas.",
            10, itens, false, -1, 402, -1, 4 };
    }
    case 402: {
        std::vector<int> itens = {32, 30};
        return InfoTrechoMapa{ 402,
            "A biblioteca proibida de Kenyrock. Conjuradores elficos guardam os tomos mais perigosos.",
            11, itens, true, 32, 403, 401, 4 };
    }
    case 403: {
        std::vector<int> itens = {33, 31};
        return InfoTrechoMapa{ 403,
            "O observatorio arcano de Kenyrock. N'baki D'Itris, Arauto de Azuth, calibra seu Artifice.",
            12, itens, true, 104, -1, 402, 4 };
    }

    // Cena 5: Skyprout - Guildas e Minas (LV 9-10)
    case 501: {
        std::vector<int> itens = {40, 41};
        return InfoTrechoMapa{ 501,
            "A entrada de uma mina profunda de Skyprout, tomada por uma guilda corrompida.",
            13, itens, false, -1, 502, -1, 5 };
    }
    case 502: {
        std::vector<int> itens = {42, 40};
        return InfoTrechoMapa{ 502,
            "Os andares intermediarios da mina. Anoes berserk guardam os cristais mais valiosos.",
            14, itens, true, 42, 503, 501, 5 };
    }
    case 503: {
        std::vector<int> itens = {43, 41};
        return InfoTrechoMapa{ 503,
            "O nucleo da mina. Livies, Arauto de Lathander, medita entre as pedras que pulsam com vida.",
            15, itens, true, 105, -1, 502, 5 };
    }

    // Cena 6: Retorno a Magisk - Servos de Sonath
    case 601: {
        std::vector<int> itens = {50, 51};
        return InfoTrechoMapa{ 601,
            "A Floresta Geada, mais densa e sombria do que antes. A legiao de Sonath a transformou.",
            16, itens, false, -1, 602, -1, 6 };
    }
    case 602: {
        std::vector<int> itens = {52, 50};
        return InfoTrechoMapa{ 602,
            "As ruinas do centro mercantil original de Cadian. Cavaleiros da morte patrulham os escombros.",
            17, itens, true, 52, 603, 601, 6 };
    }
    case 603: {
        std::vector<int> itens = {53, 51};
        return InfoTrechoMapa{ 603,
            "O templo onde Lilith se sacrificou. Nyriel, Arauto de Eldath, guarda o local em luto silencioso.",
            18, itens, true, 106, -1, 602, 6 };
    }

    // Cena 7: Confronto Final - Santuario de Sonath
    case 701: {
        std::vector<int> itens = {60, 61};
        return InfoTrechoMapa{ 701,
            "A entrada do santuario de Sonath. Amoras silvestres crescem entre as pedras.",
            19, itens, false, -1, 702, -1, 7 };
    }
    case 702: {
        std::vector<int> itens = {62, 60};
        return InfoTrechoMapa{ 702,
            "O corredor do santuario. Zumbis colossais guardam a camara final.",
            20, itens, true, 53, 703, 701, 7 };
    }
    case 703: {
        std::vector<int> itens = {63, 61};
        return InfoTrechoMapa{ 703,
            "A camara do trono de Sonath. Um golias de quase 3 metros, um braco corroido, olhos que carregam 500 anos de odio e proposito.",
            -1, itens, true, 999, -1, 702, 7 };
    }

    default:
        throw std::invalid_argument("TrechoMapa com id desconhecido: "
            + std::to_string(id));
    }
}
