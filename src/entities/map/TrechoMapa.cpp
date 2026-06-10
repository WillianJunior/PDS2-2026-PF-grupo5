/**
 * @file TrechoMapa.cpp
 * @brief Implementação da classe TrechoMapa
 */

#include "entities/map/TrechoMapa.hpp"
#include <stdexcept>

/**
 * @brief Construtor da classe TrechoMapa.
 * Inicializa os atributos básicos do trecho
 */
TrechoMapa::TrechoMapa(const InfoTrechoMapa& dados):_dados(dados), _aberto(false),_itensEncontrados(0),_inimigosDerrotados(0){

}
/**
 * @brief Marca o trecho como aberto.
 */
void TrechoMapa::abrirTrecho(){
    _aberto = true;
}

bool TrechoMapa::estaAberto() const{
    return _aberto;
}

bool TrechoMapa::possuiItensRestantes() const{
    return _itensEncontrados < (int)_dados.idsItens.size();
}

Item TrechoMapa::gerarItem() {
    if (!possuiItensRestantes())
        throw std::runtime_error("Nao ha itens restantes no trecho");
    int itemId = sortearItem();
    Item item = Item::gerarItem(_dados.cenaId, itemId);
    registrarItemEncontrado();
    return item;
}

int TrechoMapa::sortearItem() const {
    if (!possuiItensRestantes()) return -1;
    return _dados.idsItens[_itensEncontrados];
}

void TrechoMapa::registrarItemEncontrado()
{
    if(possuiItensRestantes())
        _itensEncontrados++;
}

bool TrechoMapa::possuiInimigosRestantes() const{
    return _inimigosDerrotados < _dados.quantidadeInimigos;
}

void TrechoMapa::registrarInimigoDerrotado(){
    if(possuiInimigosRestantes())
        _inimigosDerrotados++;
}


int TrechoMapa::pegarItensRestantes() const{
    return (int)_dados.idsItens.size() - _itensEncontrados;
}

int TrechoMapa::pegarInimigosRestantes() const
{
    return _dados.quantidadeInimigos - _inimigosDerrotados;
}

int TrechoMapa::pegarId() const
{
    return _dados.id;
}

std::string TrechoMapa::pegarDescricao() const
{
    return _dados.descricao;
}

int TrechoMapa::pegarTrechoAnterior() const
{
    return _dados.trechoAnterior;
}

int TrechoMapa::pegarProximoTrecho() const
{
    return _dados.proximoTrecho;
}

int TrechoMapa::pegarNPCInteracao() const
{
    return _dados.npcInteracao;
}


