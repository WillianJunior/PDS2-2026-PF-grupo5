/**
 * @file AtaqueEnum.hpp
 * @brief Enum usado para identificar um ataque com id fixo.
 */

#ifndef ATAQUE_ENUM_HPP
#define ATAQUE_ENUM_HPP

enum class IdAtaque {
    // Arqueiro
    Flecha, TiroRapido, FlechaExplosiva, TiroCerteiro, Saraivada, TiroFinal,
    // Guerreiro
    Espada, GolpeRelampago, FuriaBerserker, GolpeDevastador, Perfuracao, GolpeDoAbismo,
    // Mago
    Truque, ProjetilArcano, BolaDeFogo, Raio, DrenoDaMagia, VorticeArcano,
    // Tanque
    Escudo, Investida, PancadaDeEscudo, Terremoto, BarreiraDeEspinhos, Martirio
};

#endif // ATAQUE_ENUM_HPP
