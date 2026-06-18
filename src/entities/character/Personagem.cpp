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
      _vidaTotal(vidaTotal),
      _vidaAtual(vidaTotal),
      _ppTotal(ppTotal),
      _ppAtual(ppTotal),
      _agilidade(agilidade),
      _xp(0),
      _classe(tipoClasse),
      _tipo(tipo),
      _nivel(nivel)
{
    assert(vidaTotal > 0 && "Vida total deve ser positiva");
    assert(ppTotal >= 0 && "Mana total nao pode ser negativa");
    assert(ataque >= 0 && "Ataque nao pode ser negativo");
    assert(defesa >= 0 && "Defesa nao pode ser negativa");
    assert(agilidade >= 0 && "Agilidade nao pode ser negativa");
    assert(nivel > 0 && "Nivel deve ser positivo");
}

void Personagem::receberDano(double dano) {
    assert(dano >= 0 && "Dano nao pode ser negativo");
    _vidaAtual -= dano;
    if(_vidaAtual < 0)
        _vidaAtual = 0;
}

void Personagem::recuperarVida(double cura) {
    assert(cura >= 0 && "Cura nao pode ser negativa");
    _vidaAtual += cura;
    if(_vidaAtual > _vidaTotal)
        _vidaAtual = _vidaTotal;
}

void Personagem::recuperarMana(double quantidadeMana) {
    assert(quantidadeMana >= 0 && "Mana nao pode ser negativa");
    _ppAtual += quantidadeMana;
    if(_ppAtual > _ppTotal)
        _ppAtual = _ppTotal;
}

void Personagem::gastarMana(double custoMana) {
    assert(custoMana >= 0 && "Mana nao pode ser negativa");
    _ppAtual -= custoMana;
    if(_ppAtual < 0)
        _ppAtual = 0;
}

void Personagem::ganharXp(double quantidadeXp) {
    assert(quantidadeXp >= 0 && "Xp nao pode ser negativo");
    _xp += quantidadeXp;
    while (_nivel < 10 && _xp >= RegrasProgresso::getXPParaProximoNivel(_nivel)) {
        subirNivel();
    }
}

void Personagem::subirNivel() {
    _nivel++;
    //if(_nivel == 3 && _nivel == 5 && _nivel == 7)
    //    _classe.alteraAtaqueForte(_nivel);
}

bool Personagem::estaVivo() const {
    return _vidaAtual > 0;
}

std::string Personagem::getNome() const {
    return _nome;
}

std::string Personagem::getDescricao() const {
    return _descricao;
}

std::string Personagem::getFala() const {
    return _fala;
}

double Personagem::getVidaAtual() const {
    return _vidaAtual;
}

double Personagem::getAtaque() const {
    return _ataque;
}

double Personagem::getDefesa() const {
    return _defesa;
}

double Personagem::getAgilidade() const {
    return _agilidade;
}

double Personagem::getManaAtual() const {
    return _ppAtual;
}

int Personagem::getNivel() const {
    return _nivel;
}

double Personagem::getXp() const {
    return _xp;
}

TipoPersonagem Personagem::getTipo() const {
    return _tipo;
}

const ClassePersonagem& Personagem::getClasse() const {
    return _classe;
}

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