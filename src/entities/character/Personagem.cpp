/**
 * @file Personagem.cpp
 * @brief Implementação da classe Personagem.
 *
 * Programação defensiva: todos os parâmetros inválidos lançam exceções
 * (std::invalid_argument ou std::out_of_range) em vez de usar assert,
 * garantindo detecção de erros mesmo em builds de release.
 */

#include <stdexcept>
#include "entities/character/Personagem.hpp"
#include "core/rules/RegrasProgresso.hpp"

Personagem::Personagem(
    std::string nome,
    std::string descricao,
    std::string fala,
    double ataque,
    double defesa,
    double vidaTotal,
    double ppTotal,
    double agilidade,
    TipoClasse tipoClasse,
    TipoPersonagem tipo,
    int nivel)
    : _nome(nome),
      _descricao(descricao),
      _fala(fala),
      _ataque(ataque),
      _defesa(defesa),
      _vidaAtual(vidaTotal),
      _vidaTotal(vidaTotal),
      _ppAtual(ppTotal),
      _ppTotal(ppTotal),
      _agilidade(agilidade),
      _nivel(nivel),
      _xp(0),
      _tipo(tipo),
      _classe(tipoClasse)
{
    if (vidaTotal <= 0)
        throw std::invalid_argument("Vida total deve ser positiva.");
    if (ppTotal < 0)
        throw std::invalid_argument("PP total nao pode ser negativo.");
    if (ataque < 0)
        throw std::invalid_argument("Ataque nao pode ser negativo.");
    if (defesa < 0)
        throw std::invalid_argument("Defesa nao pode ser negativa.");
    if (agilidade < 0)
        throw std::invalid_argument("Agilidade nao pode ser negativa.");
    if (nivel <= 0)
        throw std::invalid_argument("Nivel deve ser positivo.");
    
    if(_tipo == TipoPersonagem::Jogador) {
        _vidaTotal += 80;
        _vidaAtual = _vidaTotal;
        _ppTotal += 40;
        _ppAtual = _ppTotal;
    }
}

void Personagem::receberDano(double dano) {
    if (dano < 0)
        throw std::invalid_argument("Dano nao pode ser negativo.");
    _vidaAtual -= dano;
    if (_vidaAtual < 0)
        _vidaAtual = 0;
}

void Personagem::recuperarVida(double cura) {
    if (cura < 0)
        throw std::invalid_argument("Cura nao pode ser negativa.");
    _vidaAtual += cura;
    if (_vidaAtual > _vidaTotal)
        _vidaAtual = _vidaTotal;
}

void Personagem::recuperarMana(double quantidadeMana) {
    if (quantidadeMana < 0)
        throw std::invalid_argument("Quantidade de mana nao pode ser negativa.");
    _ppAtual += quantidadeMana;
    if (_ppAtual > _ppTotal)
        _ppAtual = _ppTotal;
}

void Personagem::gastarMana(double custoMana) {
    if (custoMana < 0)
        throw std::invalid_argument("Custo de mana nao pode ser negativo.");
    _ppAtual -= custoMana;
    if (_ppAtual < 0)
        _ppAtual = 0;
}

void Personagem::ganharXp(double quantidadeXp) {
    if (quantidadeXp < 0)
        throw std::invalid_argument("XP nao pode ser negativo.");
    _xp += quantidadeXp;
    while (_nivel < 10 && _xp >= RegrasProgresso::getXPParaProximoNivel(_nivel)) {
        subirNivel();
    }
}

void Personagem::subirNivel() {
    _nivel++;
    //if(_nivel == 3 || _nivel == 5 || _nivel == 7)
    //    _classe.alteraAtaqueForte(_nivel);
}

bool Personagem::estaVivo() const {
    return _vidaAtual > 0;
}

std::string Personagem::getNome() const { return _nome; }
std::string Personagem::getDescricao() const { return _descricao; }
std::string Personagem::getFala() const { return _fala; }
double Personagem::getVidaAtual() const { return _vidaAtual; }
double Personagem::getVidaTotal() const { return _vidaTotal; }
double Personagem::getAtaque() const { return _ataque; }
double Personagem::getDefesa() const { return _defesa; }
double Personagem::getAgilidade() const { return _agilidade; }
double Personagem::getManaAtual() const { return _ppAtual; }
double Personagem::getManaTotal() const { return _ppTotal; }
int Personagem::getNivel() const { return _nivel; }
double Personagem::getXp() const { return _xp; }
TipoPersonagem Personagem::getTipo() const { return _tipo; }
const ClassePersonagem& Personagem::getClasse() const { return _classe; }

void Personagem::aplicarCondicao(const Condicao& condicao) {
    if (condicao.tipo == TipoCondicao::ModAtributo) {
        switch (condicao.atributoAlvo) {
            case Atributo::Ataque:    _ataque    -= condicao.valorParametro; break;
            case Atributo::Defesa:    _defesa    -= condicao.valorParametro; break;
            case Atributo::Agilidade: _agilidade -= condicao.valorParametro; break;
            case Atributo::Poder:     _ppAtual   -= condicao.valorParametro; break;
            default: break;
        }
    }
    _condicoesAtivas.push_back(condicao);
}

void Personagem::removerCondicao(int posicao) {
    if (posicao < 0 || posicao >= (int)_condicoesAtivas.size())
        throw std::out_of_range("Posicao de condicao invalida.");

    const Condicao& c = _condicoesAtivas[posicao];
    if (c.tipo == TipoCondicao::ModAtributo) {
        switch (c.atributoAlvo) {
            case Atributo::Ataque:    _ataque    += c.valorParametro; break;
            case Atributo::Defesa:    _defesa    += c.valorParametro; break;
            case Atributo::Agilidade: _agilidade += c.valorParametro; break;
            case Atributo::Poder:     _ppAtual   += c.valorParametro; break;
            default: break;
        }
    }
    _condicoesAtivas.erase(_condicoesAtivas.begin() + posicao);
}

const std::vector<Condicao>& Personagem::getCondicoesAtivas() const {
    return _condicoesAtivas;
}

void Personagem::alteraAtaqueForte() {
    _classe.alteraAtaqueForte(_nivel);
}

// ── Arcanos ──────────────────────────────────────────────────────────────────

void Personagem::adicionarArcano(TipoArcano arcano) {
    if (arcano == TipoArcano::Nenhum)
        throw std::invalid_argument("TipoArcano::Nenhum nao pode ser adicionado.");
    // Evita duplicatas
    for (const auto& a : _arcanosAtivos) {
        if (a == arcano) return;
    }
    _arcanosAtivos.push_back(arcano);
}

bool Personagem::temArcano(TipoArcano arcano) const {
    for (const auto& a : _arcanosAtivos) {
        if (a == arcano) return true;
    }
    return false;
}

const std::vector<TipoArcano>& Personagem::getArcanos() const {
    return _arcanosAtivos;
}