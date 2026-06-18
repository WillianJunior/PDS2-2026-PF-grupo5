/**
 * @file Cena.cpp
 * @brief Implementação da classe Cena
 */
#include "entities/map/Cena.hpp"
#include "database/BancoTrechoMapa.hpp"
#include <memory>
#include <stdexcept>

/**
 * @brief Construtor da classe Cena.
 */
Cena::Cena(const InfoCena& dados, Jogador& jogador)
    :_dadosCena(dados),
    _jogador(jogador),
    _inventarioAberto(false),
    _emBatalha(false),
    _explorando(false){

    if(dados.id <= 0){
    throw std::invalid_argument("ID da cena invalido");
    }

}

/**
 * @brief Inicializa a cena
 */
void Cena::iniciarCena(){
    mudarTrecho(_dadosCena.trechoInicial);
    _explorando = true;

}

/**
 * @brief Finaliza a cena.
 */
void Cena::finalizarCena(){
    _explorando = false;
    _emBatalha = false;
    _inventarioAberto = false;

    _trechoAtual.reset();
}

/**
 * @brief Gerencia a movimentação no mapa.
 */
void Cena::andar(){
    if(!_trechoAtual){ throw std::runtime_error(
        "Trecho atual nao carregado"
    );}

    int proximoTrecho = _trechoAtual->pegarProximoTrecho();
   
    if(proximoTrecho == -1){return;}

    mudarTrecho(proximoTrecho);

}

/**
 * @brief Permite vasculhar o trecho atual do mapa.
 */
void Cena::vasculhar(){
    if(!_trechoAtual)
    {
        throw std::runtime_error(
            "Trecho atual nao carregado"
        );
    }

    if (!_trechoAtual->possuiItensRestantes()) return;
    if (_jogador.getInventario().estaCheio()) return;

    Item item = _trechoAtual->gerarItem();
    _jogador.adicionarItem(new Item(item));
}

/**
 * @brief Realiza as interações com os NPCs de diálogo
 */
void Cena::interagirNPCs(){
    if(!_trechoAtual){
    throw std::runtime_error(
        "Trecho atual nao carregado"
    );
    }

    auto npc = _trechoAtual->pegarNPCInteracao();
    if(npc == -1){return;} //caso não tenha NPC
   
   
    //parte do viewer de interação

}

/**
 * @brief Abre o inventário do jogador
 */
void Cena::abrirInventario(){
    _inventarioAberto = true;
    _jogador.getInventario().listarItens();
}

/**
 * @brief Inicializa uma batalha
 */
void Cena::iniciarBatalha(){
    _explorando = false;
    _emBatalha = true;
}

void Cena::mudarTrecho(int idTrecho){
    if(idTrecho <= 0){
    throw std::invalid_argument("ID de trecho invalido");
    }

    InfoTrechoMapa dados = BancoTrechoMapa::obterTrechoMapa(idTrecho);

    _trechoAtual = std::make_unique<TrechoMapa>(dados);

    _trechoAtual->abrirTrecho();
}

int Cena::pegarId() const{
    return _dadosCena.id;
}

std::string Cena::pegarArcano() const{
    return _dadosCena.arcano;
}

const TrechoMapa& Cena::pegarTrechoAtual() const{
    if(!_trechoAtual){
        throw std::runtime_error(
            "Trecho atual da cena ainda não foi carregado"
        );
    }

    return *_trechoAtual;
}

bool Cena::inventarioAberto() const{
    return _inventarioAberto;
}

bool Cena::emBatalha() const{
    return _emBatalha;
}

bool Cena::explorando() const{
    return _explorando;
}

