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
      _turnoAtual(0),
      _fatorDificuldade(1.0),
      _progressoBatalha(0),
      _dados(dados),
      _view(view),
      _controller(controller),
      _regras(regras)
{}

Batalha::~Batalha() {}

// ─────────────────────────────────────────────────────────────────────────────
// Log narrativo
// ─────────────────────────────────────────────────────────────────────────────

void Batalha::_registrar(const std::string& msg) { _log.push_back(msg); }
const std::vector<std::string>& Batalha::getLog() const { return _log; }
void Batalha::limparLog() { _log.clear(); }

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
bool Batalha::verificarAcerto(Personagem* alvo, double coefAtaque, int nivel,
                               bool gastaPP, bool vantagem, double cdAlvo) {
    for (const auto& c : alvo->getCondicoesAtivas()) {
        if (c.tipo == TipoCondicao::CemPorcentoAcerto)
            return true;
    }

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
    double ndCalculado = _inimigo->getNivel() / 2.0;
    _fatorDificuldade = RegrasBatalha::ajustarNDValido(ndCalculado);
    
    // Garante que o ND não seja menor que 0.125 (mínimo da tabela)
    if (_fatorDificuldade < 0.125)
        _fatorDificuldade = 0.125;

    atualizarAcoesDisponiveis();
}

// ─────────────────────────────────────────────────────────────────────────────
// Helper de log para ataques do player (método privado inline)
// ─────────────────────────────────────────────────────────────────────────────

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

    // ── Ataque Simples | Ataque Rapido | Ataque Forte  ─────────────────────────────────
    case AcaoBatalha::AtaqueSimples:
    case AcaoBatalha::AtaqueRapido:
    case AcaoBatalha::AtaqueForte:
    {
        Ataque ataque = _player->getClasse().getAtaque(TipoAtaque::Simples);

        if(acao == AcaoBatalha::AtaqueForte)
            ataque = _player->getClasse().getAtaque(TipoAtaque::Forte);
        else if(acao == AcaoBatalha::AtaqueRapido) {
            ataque = _player->getClasse().getAtaque(TipoAtaque::Rapido);
        }

        const DadosAtaque& dadosAtaque = BancoDadosAtaque::getDadosAtaque(ataque.id);
        int numeroDeHits = 0;
        double custoPP   = ataque.custoPP;
        _player->gastarMana(custoPP);
        
        for (int i = 0; i < dadosAtaque.numeroDeExecucoes; i++) {
        double coef = Regras::calcularCoeficiente(_player->getAtaque());
            if(ataque.tipo == TipoAtaque::Rapido)
                 coef = Regras::calcularCoeficiente(_player->getAgilidade());

            double cdAlvo = Regras::calcularCD(_inimigo->getAgilidade());
            double dano   = 0;

            if (ataque.efeito.timing == TimingEfeito::AntesDoAcerto
                    && ataque.efeito.hit <= numeroDeHits) {
                if (_dados.rolar(1, 100) <= ataque.efeito.chance) {
                    if (ataque.efeito.afetaProprio)
                        aplicarCondicao(ataque.efeito.condicao, true);
                    else
                        aplicarCondicao(ataque.efeito.condicao, false);
                }
            }

            bool acertou = verificarAcerto(_inimigo, coef, _player->getNivel(),
                                           /*gastaPP=*/false, vantagem, cdAlvo);
            bool comElementos = false;
            double curaChao   = 0.0;

            if (acertou) {
                dano = RegrasAtaque::calcularDano(*_player, ataque);
                numeroDeHits++;
                if (_player->temArcano(TipoArcano::Elementos)) {
                    dano *= 1.20;
                    comElementos = true;
                }
                dano = calcularVariabilidade(dano);
                if (dano < 0) dano = 0;

                _inimigo->receberDano(dano);

                if (_player->temArcano(TipoArcano::Caos)) {
                    curaChao = dano * 0.25;
                    _player->recuperarVida(curaChao);
                }
            }

            if (!acertou) {
                _registrar("Golpe " + std::to_string(i + 1) +
                           ": você errou o ataque contra " + _inimigo->getNome() + ".");
            } else {
                std::string _msg = "Golpe " + std::to_string(i + 1) +
                                   ": você acertou " + _inimigo->getNome() +
                                   " causando " + std::to_string(static_cast<int>(dano)) + " de dano!";
                if (comElementos) _msg += " (Elementos: +20%)";
                _registrar(_msg);
                if (curaChao > 0)
                    _registrar("  Arcano do Caos: você recuperou " +
                               std::to_string(static_cast<int>(curaChao)) + " PV.");
            }

            if (ataque.efeito.timing == TimingEfeito::DepoisDoAcerto
                    && ataque.efeito.hit <= numeroDeHits) {
                if (_dados.rolar(1, 100) <= ataque.efeito.chance) {
                    if (ataque.efeito.afetaProprio)
                        aplicarCondicao(ataque.efeito.condicao, true);
                    else
                        aplicarCondicao(ataque.efeito.condicao, false);
                }
            }
        }
        processarCondicoesAtivas();
        if (_inimigo->estaVivo())
            processarAtaqueInimigo();
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
    case AcaoBatalha::UsarItem: {
        Condicao atordoado = {TipoCondicao::Atordoado, "Atordoado", 2};
        aplicarCondicao(atordoado, true);
        processarCondicoesAtivas();
        break;
    }

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
    double danoRecebido  = ataqueInimigo * fator;
    double ganhoPP = 0;
    if (danoRecebido > 0) {
        _player->receberDano(danoRecebido);
        ganhoPP = danoRecebido - _dados.rolar(2,6);
    }
    else {
        ganhoPP = ataqueInimigo;
    }

    if(ganhoPP < 0) ganhoPP = 0;     
    
    _player->recuperarMana(ganhoPP);


    for (const auto& c : _inimigo->getCondicoesAtivas()) {
        if (c.tipo == TipoCondicao::Paralisado) {
            _registrar(_inimigo->getNome() + " está paralisado e não pode reagir! Você recupera "
                + std::to_string(static_cast<int>(ganhoPP)) + " de PP.");
            processarCondicoesAtivas();
            return;
        }
    }
    
    const std::string& nome = _inimigo->getNome();
    if (fator == 0.0) {
        _registrar(nome + " atacou — bloqueio total! Nenhum dano recebido. Você recupera "
                   + std::to_string(static_cast<int>(ganhoPP)) + " de PP.");
    } else if (fator <= 0.75) {
        _registrar(nome + " atacou! Defesa reduziu o dano para "
                   + std::to_string(static_cast<int>(danoRecebido)) + ". Você recupera "
                    + std::to_string(static_cast<int>(ganhoPP)) + " de PP.");
    } else {
        _registrar(nome + " atacou com força total! Você recebeu "
                   + std::to_string(static_cast<int>(danoRecebido)) + " de dano. Você recupera " 
                    + std::to_string(static_cast<int>(ganhoPP)) + " de PP.");
    }

    processarCondicoesAtivas();
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
    int    bonus         = Regras::bonusProficiencia(_player->getNivel());
    double agiComBonus   = _player->getAgilidade() + static_cast<double>(bonus);
    double fator         = RegrasBatalha::ProcessarEsquiva(agiComBonus, ataqueInimigo);
    double danoRecebido  = ataqueInimigo * fator;
    Condicao paralisado = {TipoCondicao::Paralisado, "Paralisado", 3};

    if (danoRecebido > 0)
        _player->receberDano(danoRecebido);

    for (const auto& c : _inimigo->getCondicoesAtivas()) {
        if (c.tipo == TipoCondicao::Paralisado) {
            _registrar(_inimigo->getNome() + " está paralisado e não pode reagir!");
            processarCondicoesAtivas();
            return;
        }
    }

    const std::string& nome = _inimigo->getNome();
    if (fator == 0.0) {
        _registrar(nome + " atacou! Esquiva perfeita! Nenhum dano recebido.");
        aplicarCondicao(paralisado, false);
    } else if (fator <= 0.5) {
        _registrar(nome + " atacou! Esquiva parcial — você recebeu "
                   + std::to_string(static_cast<int>(danoRecebido)) + " de dano.");
        _inimigo->aplicarCondicao(paralisado);
    } else {
        _registrar(nome + " atacou! Esquiva falhou — você recebeu "
                   + std::to_string(static_cast<int>(danoRecebido)) + " de dano.");
    }

    processarCondicoesAtivas();
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
        && condicao.tipo == TipoCondicao::Paralisado) {
        _registrar("Arcano da Alma: imunidade a Paralisado ativada!");
        return;
    }

    alvo->aplicarCondicao(condicao);
    vetor.push_back(condicao);

    std::string nomeCondicao = condicao.nomeCustom.empty()
        ? [&]() -> std::string {
            switch (condicao.tipo) {
                case TipoCondicao::Berserk:           return "Berserk";
                case TipoCondicao::ModAtributo:       return "Modifica Atributo";
                case TipoCondicao::CemPorcentoAcerto: return "100% Acerto";
                case TipoCondicao::Paralisado:        return "Paralisado";
                case TipoCondicao::Atordoado:         return "Atordoado";
                case TipoCondicao::Envenenado:        return "Envenenado";
                default:                              return "Condição";
            }
        }()
        : condicao.nomeCustom;

    _registrar(alvo->getNome() + " sofreu: " + nomeCondicao + "!");
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
        _registrar("Arcano da Vida: você regenerou "
                   + std::to_string(static_cast<int>(regen)) + " PV.");
    }

    // ── Helper: processa um vetor de condições de um combatente ──────────
    auto processar = [&](std::vector<Condicao>& vetor, Personagem* pers) {
        for (int i = static_cast<int>(vetor.size()) - 1; i >= 0; --i) {
            Condicao& c = vetor[i];

            // Efeito por turno
            switch (c.tipo) {
                case TipoCondicao::Berserk: {
                    double dano = static_cast<double>(_dados.rolar(1, 4));
                    pers->receberDano(dano);
                    _registrar("Fúria Berserk: " + pers->getNome() + " sofreu "
                               + std::to_string(static_cast<int>(dano)) + " de dano!");
                    break;
                }
                case TipoCondicao::Envenenado: {
                    double dano = static_cast<double>(_dados.rolar(2, 6));
                    pers->receberDano(dano);
                    std::string nomeEfeito = c.nomeCustom.empty() ? "veneno" : c.nomeCustom;
                    _registrar(pers->getNome() + " sofreu "
                               + std::to_string(static_cast<int>(dano))
                               + " de dano por " + nomeEfeito + "!");
                    break;
                }
                default: break;
            }

            c.duracaoTurnos--;

            if (c.duracaoTurnos <= 0) {
                // Reverte ModAtributo em Personagem
                const auto& conds = pers->getCondicoesAtivas();
                for (int j = 0; j < static_cast<int>(conds.size()); ++j) {
                    if (conds[j].tipo == c.tipo &&
                        conds[j].atributoAlvo == c.atributoAlvo) {
                        pers->removerCondicao(j);
                        break;
                    }
                }

                std::string nomeCondicao = c.nomeCustom.empty()
                    ? [&]() -> std::string {
                        switch (c.tipo) {
                            case TipoCondicao::Berserk:           return "Berserk";
                            case TipoCondicao::ModAtributo:       return "Modifica Atributo";
                            case TipoCondicao::CemPorcentoAcerto: return "100% Acerto";
                            case TipoCondicao::Paralisado:        return "Paralisado";
                            case TipoCondicao::Atordoado:         return "Atordoado";
                            case TipoCondicao::Envenenado:        return "Envenenado";
                            default:                              return "Condição";
                        }
                    }()
                    : c.nomeCustom;

                _registrar("A condição " + nomeCondicao + " expirou em " + pers->getNome() + ".");
                vetor.erase(vetor.begin() + i);
            }
        }
    };

    processar(_condicoesPlayer,  _player);
    processar(_condicoesInimigo, _inimigo);

    atualizarAcoesDisponiveis();
}

/**
 * Verifica se a fuga esta disponivel para o player.
 *
 * Delega a RegrasBatalha::FugirDisponivel usando _fatorDificuldade como ND.
 * Fuga bloqueada em Boss e Impossivel (Regras.md 2.9, 4.6).
 */
bool Batalha::verificarFuga() {
    return RegrasBatalha::FugirDisponivel(_player->getNivel(), _fatorDificuldade);
}

/**
 * Aplica o ataque do inimigo ao player sem nenhuma redução defensiva.
 * Usado pela camada demo após ações ofensivas (o inimigo sempre contra-ataca).
 */
void Batalha::processarAtaqueInimigo() {
    for (const auto& c : _inimigo->getCondicoesAtivas()) {
        if (c.tipo == TipoCondicao::Paralisado) {
            _registrar(_inimigo->getNome() + " está paralisado e não pode reagir!");
            processarCondicoesAtivas();
            return;
        }
    }

    double dano = calcularVariabilidade(_inimigo->getAtaque());
    if (dano > 0)
        _player->receberDano(dano);

    _registrar(_inimigo->getNome() + " atacou e causou "
               + std::to_string(static_cast<int>(dano)) + " de dano em você!");
}

/**
 * Avança o turno quando o player está Paralisado (nenhuma ação disponível).
 * O inimigo ataca normalmente, condições são processadas e o turno avança.
 */
void Batalha::pularTurno() {
    processarAtaqueInimigo();
    processarCondicoesAtivas();
    _turnoAtual++;
    atualizarAcoesDisponiveis();
}

bool Batalha::temManaSuficiente(TipoAtaque tipo) {
    return _player->getManaAtual() >= _player->getClasse().getAtaque(tipo).custoPP ;
}