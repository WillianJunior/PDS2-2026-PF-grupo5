#include "core/rules/RegrasBatalha.hpp"
#include <array>
#include <map>
#include <string>
#include <stdexcept>

// Definição das tabelas estáticas

/**
 * Chaves fracionárias:
 *   0.125 = ND 1/8  |  0.25 = ND 1/4  |  0.5 = ND 1/2
 * Todos os valores são representáveis exatamente em double (potências de 2),
 * portanto a comparação de chave no std::map é segura.
 */
const std::map<double, double> RegrasBatalha::TABELA_XP_ND = {
    {0.125,  25.0},   // ND 1/8
    {0.25,   50.0},   // ND 1/4
    {0.5,   100.0},   // ND 1/2
    {1.0,   200.0},
    {2.0,   450.0},
    {3.0,   700.0},
    {4.0,  1100.0},
    {5.0,  1800.0},
    {6.0,  2300.0},
    {7.0,  2900.0},
    {8.0,  3900.0},
    {9.0,  5000.0},
    {10.0, 5900.0}
};

/**
 * LIMIARES[nivel - 1] = { Fácil, Médio, Difícil, Boss }
 * Fonte: D&D 5e DMG Cap.3 adaptado para combate solo (1 jogador).
 */
const std::array<std::array<double, 4>, 10> RegrasBatalha::LIMIARES = {{
    {  25.0,   50.0,    75.0,   100.0},  // LV  1
    {  50.0,  100.0,   150.0,   200.0},  // LV  2
    {  75.0,  150.0,   225.0,   400.0},  // LV  3
    { 125.0,  250.0,   375.0,   500.0},  // LV  4
    { 250.0,  500.0,   750.0,  1100.0},  // LV  5
    { 300.0,  600.0,   900.0,  1400.0},  // LV  6
    { 350.0,  750.0,  1100.0,  1700.0},  // LV  7
    { 450.0,  900.0,  1400.0,  2100.0},  // LV  8
    { 550.0, 1100.0,  1600.0,  2400.0},  // LV  9
    { 600.0, 1200.0,  1900.0,  2800.0}   // LV 10
}};

//  Consultas às tabelas 

double RegrasBatalha::getXPporND(double ndInimigo) {
    auto it = TABELA_XP_ND.find(ndInimigo);
    if (it == TABELA_XP_ND.end())
        throw std::invalid_argument(
            "ND invalido: " + std::to_string(ndInimigo) +
            ". Use 0.125, 0.25, 0.5 ou inteiros de 1 a 20.");

    return it->second;
}

double RegrasBatalha::getLimiar(int nivel, int indiceDificuldade) {
    if (nivel < 1 || nivel > NIVEL_MAXIMO)
        throw std::out_of_range("Nivel deve estar entre 1 e 10.");
    if (indiceDificuldade < 0 || indiceDificuldade > 3)
        throw std::out_of_range("Indice de dificuldade deve ser 0 (Facil), 1 (Medio), 2 (Dificil) ou 3 (Boss).");

    return LIMIARES[nivel - 1][indiceDificuldade];
}

//  Classificação de encontro 

RegrasBatalha::Dificuldade RegrasBatalha::ClassificarConfronto(int lvJogador, double ndInimigo) {
    double xpInimigo = getXPporND(ndInimigo);

    double limFacil   = getLimiar(lvJogador, 0);
    double limMedio   = getLimiar(lvJogador, 1);
    double limDificil = getLimiar(lvJogador, 2);
    double limBoss    = getLimiar(lvJogador, 3);

    // Impossível: XP do inimigo é o dobro ou mais do limiar Boss
    if (xpInimigo >= limBoss * 2.0)
        return Dificuldade::Impossivel;

    if (xpInimigo >= limBoss)
        return Dificuldade::Boss;

    if (xpInimigo >= limDificil)
        return Dificuldade::Dificil;

    if (xpInimigo >= limMedio)
        return Dificuldade::Medio;

    if (xpInimigo >= limFacil)
        return Dificuldade::Facil;

    return Dificuldade::Trivial;
}

std::string RegrasBatalha::DificuldadeParaString(Dificuldade d) {
    switch (d) {
        case Dificuldade::Trivial:    return "Trivial";
        case Dificuldade::Facil:      return "Fácil";
        case Dificuldade::Medio:      return "Médio";
        case Dificuldade::Dificil:    return "Difícil";
        case Dificuldade::Boss:       return "Boss";
        case Dificuldade::Impossivel: return "Impossível";
        default:                      return "Desconhecida";
    }
}

//  XP e fuga 

double RegrasBatalha::CalcularXPGanho(double ndInimigo, int lvJogador) {
    double xpBase   = getXPporND(ndInimigo);
    double limFacil = getLimiar(lvJogador, 0);

    // Confronto Trivial: aplica redução proporcional para desestimular farming
    if (xpBase < limFacil) {
        double xpReduzido = xpBase * (xpBase / limFacil);
        return xpReduzido;
    }

    return xpBase;
}

bool RegrasBatalha::FugirDisponivel(int lvJogador, double ndInimigo) {
    Dificuldade d = ClassificarConfronto(lvJogador, ndInimigo);

    // Fuga bloqueada em Boss e Impossível
    return d != Dificuldade::Boss && d != Dificuldade::Impossivel;
}

//  Cálculos de combate defensivo 

double RegrasBatalha::ProcessarDefesa(double defPlayer, double ataqueInimigo) {
    // Inimigo sem ataque: jogador não toma dano
    if (ataqueInimigo <= 0.0)
        return 0.0;

    // DEF do player supera o ATQ do inimigo → bloqueio total
    if (defPlayer > ataqueInimigo)
        return 0.0;

    double ratio = defPlayer / ataqueInimigo;

    if (ratio >= 0.8)
        return 0.75; // 75% do dano

    return 1.0;      // 100% do dano
}

double RegrasBatalha::ProcessarEsquiva(double agiPlayer, double ataqueInimigo) {
    if (agiPlayer > ataqueInimigo)
        return 0.0;  // Esquiva total

    if (agiPlayer < ataqueInimigo)
        return 1.0;  // Sem esquiva — dano total

    return 0.5;      // Empate → 50% do dano
}