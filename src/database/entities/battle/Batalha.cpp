/**
 * @file Batalha.cpp
 * @brief Implementação do motor de combate por turnos.
 *
 * Orquestra o fluxo completo de um encontro: iniciativa, execução de ações,
 * aplicação e processamento de condições, recompensas e finalização.
 * Toda a lógica de fórmulas é delegada a RegrasBatalha e RegrasAtaque —
 * Batalha apenas orquestra.
 *
 * @see Batalha.hpp, Regras.md — Seção 2 e Seção 4
 * @see TipoArcanoEnum.hpp — efeitos passivos de Arcanos em combate
 */

#include "entities/battle/Batalha.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/items/Item.hpp"
#include "entities/map/Cena.hpp"
#include "core/rules/RegrasBatalha.hpp"
#include "core/rules/RegrasAtaque.hpp"
#include "core/rules/Regras.hpp"
#include "utils/TipoArcanoEnum.hpp"

#include <algorithm>
#include <stdexcept>

// ─────────────────────────────────────────────────────────────────────────────
// Construtor / Destrutor
// ─────────────────────────────────────────────────────────────────────────────

Batalha::Batalha(
    Personagem *player,
    Personagem *inimigo,
    Dados &dados,
    IView *view,
    IController *controller,
    RegrasBatalha *regras)
    : _player(player),
      _inimigo(inimigo),
      _dados(dados),
      _view(view),
      _controller(controller),
      _regras(regras),
      _turnoAtual(0),
      _fatorDificuldade(1.0),
      _progressoBatalha(0)
{}

Batalha::~Batalha() {}

// ─────────────────────────────────────────────────────────────────────────────
// Privados — cálculos auxiliares
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Aplica variabilidade de ±20 % ao valorBase.
 * Mapeia 1d5 → {0.8, 0.9, 1.0, 1.1, 1.2}.
 */
double Batalha::calcularVariabilidade(double valorBase) {
    int roll = _dados.rolar(1, 5);           // 1..5
    double fator = 0.8 + (roll - 1) * 0.1;  // 0.8 → 1.2
    return valorBase * fator;
}

/**
 * Verifica se a rolagem de acerto supera a CD do alvo.
 *
 * Regras.md §1.5: empate (rolagem == CD) NÃO acerta.
 * Se vantagem = true, rola 2d20 e usa o maior (Regras.md §2.5 — Berserk).
 * Se gastaPP = true, soma Bônus de Proficiência (Regras.md §3.2).
 */
bool Batalha::verificarAcerto(double coefAtaque, int nivel,
                               bool gastaPP, bool vantagem, double cdAlvo) {
    int r1 = _dados.rolar(1, 20);
    int r2 = vantagem ? _dados.rolar(1, 20) : r1;
    int rolagem = std::max(r1, r2);

    double total = static_cast<double>(rolagem) + coefAtaque;
    if (gastaPP)
        total += Regras::bonusProficiencia(nivel);

    return total > cdAlvo;
}

/**
 * Reconstrói _acoesDisponiveis com base nas condições ativas do player.
 *
 * - Paralisado  → sem nenhuma ação.
 * - Atordoado   → sem AtaqueRapido nem AtaqueForte.
 * - Boss/Impossível → sem Fugir.
 */
void Batalha::atualizarAcoesDisponiveis() {
    _acoesDisponiveis = {
        AcaoBatalha::AtaqueSimples,
        AcaoBatalha::AtaqueRapido,
        AcaoBatalha::AtaqueForte,
        AcaoBatalha::Defesa,
        AcaoBatalha::Esquiva,
        AcaoBatalha::UsarItem,
        AcaoBatalha::Fugir
    };

    const auto& conds = _player->getCondicoesAtivas();
    for (const auto& c : conds) {
        if (c.tipo == TipoCondicao::Paralisado) {
            _acoesDisponiveis.clear();
            return;
        }
        if (c.tipo == TipoCondicao::Atordoado) {
            auto remover = [&](AcaoBatalha a) {
                _acoesDisponiveis.erase(
                    std::remove(_acoesDisponiveis.begin(), _acoesDisponiveis.end(), a),
                    _acoesDisponiveis.end());
            };
            remover(AcaoBatalha::AtaqueRapido);
            remover(AcaoBatalha::AtaqueForte);
        }
    }

    // Bloqueia Fugir em Boss / Impossível
    if (!verificarFuga()) {
        _acoesDisponiveis.erase(
            std::remove(_acoesDisponiveis.begin(), _acoesDisponiveis.end(), AcaoBatalha::Fugir),
            _acoesDisponiveis.end());
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Mecânica principal
// ─────────────────────────────────────────────────────────────────────────────

/**
 * Configura o encontro.
 *
 * _fatorDificuldade é usado como ND do inimigo nas tabelas de XP.
 * Na ausência de um campo ND em Personagem, estima-se pelo nível do inimigo
 * (ND ≈ nivel / 2). O chamador pode sobrescrever _fatorDificuldade se
 * souber o ND exato.
 */
void Batalha::iniciarBatalha() {
    _turnoAtual       = 1;
    _progressoBatalha = 0;
    _fatorDificuldade = _inimigo->getNivel() * 0.5;

    // Garante que o ND não seja menor que 0.125 (mínimo da tabela)
    if (_fatorDificuldade < 0.125)
        _fatorDificuldade = 0.125;

    atualizarAcoesDisponiveis();
}

/**
 * Executa a ação escolhida pelo player neste turno.
 *
 * Para ataques: verifica acerto contra a CD do inimigo, calcula dano via
 * RegrasAtaque::calcularDano e aplica modificadores de Arcano antes de
 * chamar _inimigo->receberDano().
 *
 * Efeitos de Arcano aplicados aqui:
 *  - Elementos  → ×1,20 no dano saído do player.
 *  - Caos       → 25 % do dano como cura para o player.
 *  - Mente      → −25 % no custo de PP de AtaqueRapido / AtaqueForte.
 */
void Batalha::realizarAcao(AcaoBatalha acao) {
    if (std::find(_acoesDisponiveis.begin(), _acoesDisponiveis.end(), acao)
            == _acoesDisponiveis.end())
        throw std::invalid_argument("Acao nao disponivel neste turno.");

    // Verifica vantagem (Berserk do player)
    bool vantagem = false;
    for (const auto& c : _player->getCondicoesAtivas()) {
        if (c.tipo == TipoCondicao::Berserk) {
            vantagem = true;
            break;
        }
    }

    switch (acao) {

    // ── Ataque Simples ────────────────────────────────────────────────────
    case AcaoBatalha::AtaqueSimples: {
        const Ataque& ataque = _player->getClasse().getAtaque(TipoAtaque::Simples);
        double coef  = Regras::calcularCoeficiente(_player->getAtaque());
        double cdAlvo = Regras::calcularCD(_inimigo->getAgilidade());

        if (verificarAcerto(coef, _player->getNivel(), /*gastaPP=*/false, vantagem, cdAlvo)) {
            double dano = RegrasAtaque::calcularDano(*_player, ataque);

            if (_player->temArcano(TipoArcano::Elementos))
                dano *= 1.20;

            dano = calcularVariabilidade(dano);
            if (dano < 0) dano = 0;

            _inimigo->receberDano(dano);

            if (_player->temArcano(TipoArcano::Caos))
                _player->recuperarVida(dano * 0.25);
        }
        break;
    }

    // ── Ataque Rápido ─────────────────────────────────────────────────────
    case AcaoBatalha::AtaqueRapido: {
        const Ataque& ataque = _player->getClasse().getAtaque(TipoAtaque::Rapido);
        double custoPP = ataque.custoPP;

        if (_player->temArcano(TipoArcano::Mente))
            custoPP *= 0.75;

        _player->gastarMana(custoPP);

        // Rápido usa Agilidade no acerto (Regras.md §2.3)
        double coef   = Regras::calcularCoeficiente(_player->getAgilidade());
        double cdAlvo = Regras::calcularCD(_inimigo->getAgilidade());

        if (verificarAcerto(coef, _player->getNivel(), /*gastaPP=*/true, vantagem, cdAlvo)) {
            double dano = RegrasAtaque::calcularDano(*_player, ataque);

            if (_player->temArcano(TipoArcano::Elementos))
                dano *= 1.20;

            dano = calcularVariabilidade(dano);
            if (dano < 0) dano = 0;

            _inimigo->receberDano(dano);

            if (_player->temArcano(TipoArcano::Caos))
                _player->recuperarVida(dano * 0.25);
        }
        break;
    }

    // ── Ataque Forte ──────────────────────────────────────────────────────
    case AcaoBatalha::AtaqueForte: {
        const Ataque& ataque = _player->getClasse().getAtaque(TipoAtaque::Forte);
        double custoPP = ataque.custoPP;

        if (_player->temArcano(TipoArcano::Mente))
            custoPP *= 0.75;

        _player->gastarMana(custoPP);

        double coef   = Regras::calcularCoeficiente(_player->getAtaque());
        double cdAlvo = Regras::calcularCD(_inimigo->getAgilidade());

        if (verificarAcerto(coef, _player->getNivel(), /*gastaPP=*/true, vantagem, cdAlvo)) {
            double dano = RegrasAtaque::calcularDano(*_player, ataque);

            if (_player->temArcano(TipoArcano::Elementos))
                dano *= 1.20;

            dano = calcularVariabilidade(dano);
            if (dano < 0) dano = 0;

            _inimigo->receberDano(dano);

            if (_player->temArcano(TipoArcano::Caos))
                _player->recuperarVida(dano * 0.25);
        }
        break;
    }

    // ── Defender ──────────────────────────────────────────────────────────
    case AcaoBatalha::Defesa:
        processarDefesa();
        break;

    // ── Esquivar ──────────────────────────────────────────────────────────
    case AcaoBatalha::Esquiva:
        processarEsquiva();
        break;

    // ── Usar Item ─────────────────────────────────────────────────────────
    case AcaoBatalha::UsarItem:
        // Delegado ao Controller/View — Batalha apenas libera a ação.
        break;

    // ── Fugir ─────────────────────────────────────────────────────────────
    case AcaoBatalha::Fugir:
        // O retorno é interpretado pelo chamador; nenhuma ação adicional aqui.
        verificarFuga();
        break;
    }

    _turnoAtual++;
    atualizarAcoesDisponiveis();
}

/**
 * Processa a defesa do player contra o ataque do inimigo.
 *
 * Usa RegrasBatalha::ProcessarDefesa para determinar o fator de dano
 * recebido (0 = bloqueio total, 0.75 ou 1.0). O "ataque do inimigo"
 * é representado pelo atributo bruto de Ataque do inimigo.
 *
 * @see Regras.md §2.6
 */
void Batalha::processarDefesa() {
    double ataqueInimigo = calcularVariabilidade(_inimigo->getAtaque());
    double fator = RegrasBatalha::ProcessarDefesa(_player->getDefesa(), ataqueInimigo);
    double danoRecebido = ataqueInimigo * fator;

    if (danoRecebido > 0)
        _player->receberDano(danoRecebido);
}

/**
 * Processa a esquiva do player contra o ataque do inimigo.
 *
 * A CD efetiva do player recebe o Bônus de Proficiência neste turno
 * (Regras.md §2.7). Usa RegrasBatalha::ProcessarEsquiva com a Agilidade
 * aumentada pelo bônus.
 */
void Batalha::processarEsquiva() {
    double ataqueInimigo = calcularVariabilidade(_inimigo->getAtaque());
    int bonus = Regras::bonusProficiencia(_player->getNivel());
    double agiComBonus = _player->getAgilidade() + static_cast<double>(bonus);
    double fator = RegrasBatalha::ProcessarEsquiva(agiComBonus, ataqueInimigo);
    double danoRecebido = ataqueInimigo * fator;

    if (danoRecebido > 0)
        _player->receberDano(danoRecebido);
}

/**
 * Concede XP ao player após vitória e aplica modificadores de Arcano.
 *
 * Arcano da Alma: +50 % no XP ganho (Regras.md §6.2).
 * A cena não precisa ser modificada diretamente aqui — o chamador a
 * atualiza conforme necessário.
 *
 * @see Regras.md §4.5, §4.6, §6.2
 */
void Batalha::definirRecompensa(Cena& cenaAtual) {
    (void)cenaAtual; // reservado para atualização de estado da cena pelo chamador

    double xp = RegrasBatalha::CalcularXPGanho(_fatorDificuldade, _player->getNivel());

    if (_player->temArcano(TipoArcano::Alma))
        xp *= 1.50;

    _player->ganharXp(xp);
}

/**
 * Encerra o combate: limpa as condições temporárias de Batalha e
 * reseta contadores internos.
 */
void Batalha::finalizarBatalha() {
    _condicoesPlayer.clear();
    _condicoesInimigo.clear();
    _turnoAtual       = 0;
    _progressoBatalha = 0;
}

/**
 * Aplica uma condição a um combatente.
 *
 * A condição é armazenada em DOIS lugares:
 *  1. No vetor de Batalha (_condicoesPlayer / _condicoesInimigo) para o
 *     processamento por turno com decremento de duração.
 *  2. Em Personagem::aplicarCondicao(), que trata o efeito imediato de
 *     ModAtributo e guarda para revertê-lo ao expirar.
 *
 * Efeito de Arcano:
 *  - Alma → bloqueia TipoCondicao::Paralisado no player.
 *
 * @see Regras.md §2.5, §6.2
 */
void Batalha::aplicarCondicao(const Condicao& condicao, bool noPlayer) {
    Personagem* alvo  = noPlayer ? _player : _inimigo;
    auto& vetor       = noPlayer ? _condicoesPlayer : _condicoesInimigo;

    // Arcano da Alma: imunidade a Paralisado
    if (noPlayer
        && _player->temArcano(TipoArcano::Alma)
        && condicao.tipo == TipoCondicao::Paralisado)
        return;

    alvo->aplicarCondicao(condicao);
    vetor.push_back(condicao);
}

/**
 * Processa todas as condições ativas no início de cada turno.
 *
 * Fluxo por condição:
 *  1. Aplica efeito de turno (Berserk: −1d4 PV; Envenenado: −2d6 PV).
 *  2. Decrementa duracaoTurnos (se > 0).
 *  3. Se expirou (duracaoTurnos == 0): remove da lista de Batalha e
 *     reverte o atributo em Personagem (para ModAtributo).
 *
 * Condições com duracaoTurnos ≤ 0 são permanentes na cena e não expiram.
 *
 * Arcano da Vida: regenera +1d4 PV no início do turno do player;
 * a cura é amplificada ×1,5 conforme o efeito do arcano.
 *
 * @see Regras.md §2.5, §6.2
 */
void Batalha::processarCondicoesAtivas() {

    // ── Arcano da Vida: regen passiva ─────────────────────────────────────
    if (_player->temArcano(TipoArcano::Vida)) {
        double regen = static_cast<double>(_dados.rolar(1, 4)) * 1.5;
        _player->recuperarVida(regen);
    }

    // ── Helper: processa um vetor de condições de um combatente ──────────
    auto processar = [&](std::vector<Condicao>& vetor, Personagem* pers) {
        for (int i = static_cast<int>(vetor.size()) - 1; i >= 0; --i) {
            Condicao& c = vetor[i];

            // Efeito por turno
            switch (c.tipo) {
                case TipoCondicao::Berserk:
                    pers->receberDano(static_cast<double>(_dados.rolar(1, 4)));
                    break;
                case TipoCondicao::Envenenado:
                    pers->receberDano(static_cast<double>(_dados.rolar(2, 6)));
                    break;
                default: break;
            }

            // Sem duração limitada → permanente nesta cena
            if (c.duracaoTurnos <= 0) continue;

            c.duracaoTurnos--;

            if (c.duracaoTurnos == 0) {
                // Reverte ModAtributo em Personagem
                const auto& conds = pers->getCondicoesAtivas();
                for (int j = 0; j < static_cast<int>(conds.size()); ++j) {
                    if (conds[j].tipo == c.tipo &&
                        conds[j].atributoAlvo == c.atributoAlvo) {
                        pers->removerCondicao(j);
                        break;
                    }
                }
                vetor.erase(vetor.begin() + i);
            }
        }
    };

    processar(_condicoesPlayer,  _player);
    processar(_condicoesInimigo, _inimigo);

    atualizarAcoesDisponiveis();
}

/**
 * Verifica se a fuga está disponível para o player.
 *
 * Delega a RegrasBatalha::FugirDisponivel usando _fatorDificuldade como ND.
 * Fuga bloqueada em Boss e Impossível (Regras.md §2.9, §4.6).
 */
bool Batalha::verificarFuga() {
    return RegrasBatalha::FugirDisponivel(_player->getNivel(), _fatorDificuldade);
}
