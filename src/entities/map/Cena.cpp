/**
 * @file Cena.cpp
 * @brief Implementação da classe Cena
 */
#include "entities/map/Cena.hpp"
#include "database/BancoTrechoMapa.hpp"
#include <memory>

/**
 * @brief Construtor da classe Cena.
 */
Cena::Cena(const InfoCena& dados)
    :_dadosCena(dados), 
    _inventarioAberto(false),
    _emBatalha(false),
    _explorando(false){
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
 * @brief Verifica a continuidade da cena
 */
bool Cena::verificarContinuidade() const{
    //para ser definido
}

/**
 * @brief Gerencia a movimentação no mapa.
 */
void Cena::andar(){
    if(!_trechoAtual){return;}

    int proximoTrecho = _trechoAtual->pegarProximoTrecho();
   
    if(proximoTrecho == -1){return;}

    mudarTrecho(proximoTrecho);

}

/**
 * @brief Permite vasculhar o trecho atual do mapa.
 */
void Cena::vasculhar(){
    if(_trechoAtual->possuiItensRestantes()){
        _trechoAtual->registrarItemEncontrado();

        //fazer o rand para o itens encontrado


    }
}

/**
 * @brief Realiza as interações com os NPCs de diálogo
 */
void Cena::interagirNPCs(){
    auto npc = _trechoAtual->pegarNPCInteracao();
    if(npc == -1){return;} //se não tiver npc
   
   
    //fazer um banco de npc com as falas

}

/**
 * @brief Abre o inventário do jogador
 */
void Cena::abrirInventario(){
    _inventarioAberto = true;
}

/**
 * @brief Inicializa uma batalha
 */
void Cena::iniciarBatalha(){
    _explorando = false;
    _emBatalha = true;
}

void Cena::mudarTrecho(int idTrecho){
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

