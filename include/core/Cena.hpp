#ifndef CENA_HPP
#define CENA_HPP

#include "TrechoMapa.hpp"
#include "Batalha.hpp"

class Cena{
private:
    int _nivel;
    TrechoMapa* _trechoAtual;

public:
    Cena(int nivel);

    void iniciarCena();
    void finalizarCena();

    bool verificarContinuidade() const;

    void andar();
    void vasculhar();
    void interagirNPCs();
    void abrirInventario();
    void iniciarBatalha();

};


#endif