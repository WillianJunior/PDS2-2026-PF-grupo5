/**
 * @file AtaqueEnum.hpp
 * @brief Enum tipado para os atributos do personagem.
 *
 * Ataques definidos em regras.md seção 2.
 * Utilizado em classes variadas para evitar comparações por string.
 */

#ifndef ATAQUE_ENUM_HPP
#define ATAQUE_ENUM_HPP

/**
 * @enum IdAtaque
 * @brief Identifica um ataque, 
 */
enum class IdAtaque {
    // Arqueiro
    Flecha,
    TiroRapido,
    FlechaExplosiva,
    TiroCerteiro,
    Saraivada,
    TiroFinal,

    // Guerreiro
    Espada,
    GolpeRelampago,
    FuriaBerserker,
    GolpeDevastador,
    Perfuracao,
    GolpeDoAbismo,

    // Mago
    Truque,
    ProjetilArcano,
    BolaDeFogo,
    Raio,
    DrenoDaMagia,
    VorticeArcano,

    // Tanque
    Escudo,
    Investida,
    PancadaDeEscudo,
    Terremoto,
    BarreiraDeEspinhos,
    Martirio
};

#endif
