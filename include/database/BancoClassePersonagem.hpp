/**
 * @file BancoClassePersonagem.hpp
 * @brief Fábrica estática de definições de classe e ataques por TipoClasse.
 */

#ifndef BANCOCLASSEPERSONAGEM_HPP
#define BANCOCLASSEPERSONAGEM_HPP

#include "entities/character/ClassePersonagem.hpp"

/**
 * @class BancoClassePersonagem
 * @brief Fornece dados de configuração de classe a partir do tipo selecionado.
 *
 * Atua como um banco de dados estático para definir os atributos
 * e ataques iniciais de cada classe jogável.
 */
class BancoClassePersonagem {
public:
    /**
     * @brief Configura os dados básicos da classe no objeto fornecido.
     * @param tipo Tipo de classe do personagem.
     * @param classePersonagem Referência ao objeto ClassePersonagem que será preenchido.
     */
    static void defineClasse(TipoClasse tipo, ClassePersonagem& classePersonagem);

    /**
     * @brief Retorna o conjunto inicial de três ataques da classe.
     * @param tipo Tipo de classe do personagem.
     * @return Array de três ataques definidos para o tipo de classe.
     */
    static std::array<Ataque, 3> defineAtaques(TipoClasse tipo);

    /**
     * @brief Retorna os ataques fortes possíveis para a classe.
     * @param tipo Tipo de classe do personagem.
     * @return Array de quatro ataques fortes possíveis para a classe.
     */
    static std::array<Ataque, 4> getAtaquesFortesPossiveis(TipoClasse tipo);
};

#endif