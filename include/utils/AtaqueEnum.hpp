/**
 * @file AtaqueEnum.hpp
 * @brief Enum usado para identificar um ataque com id fixo.
 *
 * Ataques definidos em regras.md seção 2.
 * Utilizado em classes variadas para evitar comparações por string.
 */

#ifndef ATAQUE_ENUM_HPP
#define ATAQUE_ENUM_HPP

/**
 * @enum IdAtaque
 * @brief Identifica um ataque por um id.
 */
enum class IdAtaque {
    // Arqueiro
    Flecha,             //< Ataque Simples
    TiroRapido,         //< Ataque Rapido
    FlechaExplosiva,    //< Ataque Forte 1
    TiroCerteiro,       //< Ataque Forte 2
    Saraivada,          //< Ataque Forte 3
    TiroFinal,          //< Ataque Forte 4

    // Guerreiro
    Espada,             //< Ataque Simples
    GolpeRelampago,     //< Ataque Rapido
    FuriaBerserker,     //< Ataque Forte 1
    GolpeDevastador,    //< Ataque Forte 2
    Perfuracao,         //< Ataque Forte 3
    GolpeDoAbismo,      //< Ataque Forte 4

    // Mago
    Truque,             //< Ataque Simples
    ProjetilArcano,     //< Ataque Rapido
    BolaDeFogo,         //< Ataque Forte 1
    Raio,               //< Ataque Forte 2
    DrenoDaMagia,       //< Ataque Forte 3
    VorticeArcano,      //< Ataque Forte 4

    // Tanque
    Escudo,             //< Ataque Simples
    Investida,          //< Ataque Rapido
    PancadaDeEscudo,    //< Ataque Forte 1
    Terremoto,          //< Ataque Forte 2
    BarreiraDeEspinhos, //< Ataque Forte 3
    Martirio            //< Ataque Forte 4
};

#endif
