/**
 * @file BancoInimigo.hpp
 * @brief Repositorio estatico de inimigos e bosses do jogo.
 *
 * Convencao de IDs:
 *   1 -  99  : Inimigos comuns (por fase)
 *   101- 106 : Arautos (bosses de fase)
 *   999      : Sonath (boss final)
 *
 * Fases:
 *   Fase I   Magisk     (LV 1-2)   IDs  1-3,  Arauto 101 (Device)
 *   Fase II  Mantuu     (LV 3-4)   IDs 11-13, Arauto 102 (Vaelthor)
 *   Fase III Xantares   (LV 5-6)   IDs 21-23, Arauto 103 (Malphas)
 *   Fase IV  Kenyrock   (LV 7-8)   IDs 31-33, Arauto 104 (N'baki D'Itris)
 *   Fase V   Skyprout   (LV 9-10)  IDs 41-43, Arauto 105 (Livies)
 *   Fase VI  Ret.Magisk            IDs 51-53, Arauto 106 (Nyriel)
 *   Boss Final                     ID  999       (Sonath)
 */

#ifndef BANCO_INIMIGO_HPP
#define BANCO_INIMIGO_HPP

#include "entities/character/Personagem.hpp"

/**
 * @class BancoInimigo
 * @brief Fabrica estatica de Personagens inimigos.
 */
class BancoInimigo {
public:
    /**
     * @brief Retorna um Personagem inimigo pelo seu ID.
     * @param id ID do inimigo.
     * @return Personagem configurado para combate.
     * @throw std::invalid_argument Se o ID nao existir.
     */
    static Personagem obterInimigo(int id);
};

#endif
