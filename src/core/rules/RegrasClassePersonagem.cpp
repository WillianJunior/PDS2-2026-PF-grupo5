#include <stdexcept>
#include "core/rules/RegrasClassePersonagem.hpp"

int RegrasClassePersonagem::getDadoVida(TipoClasse classe)
{
    switch (classe)
    {
    case TipoClasse::Guerreiro: return 10;
    case TipoClasse::Arqueiro:  return 8;
    case TipoClasse::Mago:      return 6;
    case TipoClasse::Tanque:    return 12;
    }
    throw std::invalid_argument("TipoClasse desconhecido em getDadoVida.");
}

// Retorna {ataque, defesa, poder, agilidade} segundo a tabela de prioridades.
// valoresRolados deve estar em ordem decrescente (índice 0 = maior = 1º).
std::array<double, 4> RegrasClassePersonagem::distribuirAtributos(
    TipoClasse classe,
    const std::vector<int>& valoresRolados)
{
    if (valoresRolados.size() < 4)
        throw std::invalid_argument("distribuirAtributos requer ao menos 4 valores.");

    const double v1 = valoresRolados[0]; // 1º (maior)
    const double v2 = valoresRolados[1];
    const double v3 = valoresRolados[2];
    const double v4 = valoresRolados[3]; // 4º (menor)

    // Ordem de retorno: {ataque, defesa, poder, agilidade}
    // Tabela §1.3 de docs/projeto/regras.md
    switch (classe)
    {
    case TipoClasse::Guerreiro: return { v1, v2, v4, v3 }; // ATQ=1º DEF=2º POD=4º AGI=3º
    case TipoClasse::Arqueiro:  return { v2, v4, v3, v1 }; // ATQ=2º DEF=4º POD=3º AGI=1º
    case TipoClasse::Tanque:    return { v2, v1, v3, v4 }; // ATQ=2º DEF=1º POD=3º AGI=4º
    case TipoClasse::Mago:      return { v3, v4, v1, v2 }; // ATQ=3º DEF=4º POD=1º AGI=2º
    }
    throw std::invalid_argument("TipoClasse desconhecido em distribuirAtributos.");
}

double RegrasClassePersonagem::calcularVidaInicial(TipoClasse classe, double valorDefesa)
{
    return getDadoVida(classe) + calcularCoeficiente(valorDefesa);
}

double RegrasClassePersonagem::calcularVidaNovoNivel(
    TipoClasse classe,
    double valorDefesa,
    Dados& dados)
{
    int lados = getDadoVida(classe);
    return dados.rolar(1, lados) + calcularCoeficiente(valorDefesa);
}
