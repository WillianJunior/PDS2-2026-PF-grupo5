/**
 * @file CondutorBatalha.hpp
 */
#ifndef DEMO_CONDUTOR_BATALHA_HPP
#define DEMO_CONDUTOR_BATALHA_HPP

#include <string>
#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "demo/ConfigExploracao.hpp"
#include "entities/battle/Batalha.hpp"

class Jogador;
class Personagem;
class Dados;
class Cena;

enum class ResultadoBatalha { Vitoria, Derrota, Fuga };

class CondutorBatalha {
public:
    CondutorBatalha(IView& view, IController& ctrl,
                    Jogador& jogador, Personagem& inimigo,
                    Dados& dados, Cena& cena,
                    const ConfigExploracao& cfg = {});

    ResultadoBatalha executar();

private:
    IView&           _view;
    IController&     _ctrl;
    Jogador&         _jogador;
    Personagem&      _inimigo;
    Dados&           _dados;
    Cena&            _cena;
    ConfigExploracao _cfg;

    static std::string _labelAcao(AcaoBatalha acao, Jogador& jogador);

    void _exibirHUD(Batalha& batalha, int turno) const;
    void _exibirDescricaoAtaques() const;
    void _animarAtaquePlayer(Batalha& batalha);
    void _animarAtaqueInimigo(Batalha& batalha);
};

#endif
