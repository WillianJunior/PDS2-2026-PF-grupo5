/**
 * @file UI.hpp
 */
#ifndef DEMO_UI_HPP
#define DEMO_UI_HPP

#include <string>
#include <vector>
#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "demo/ConfigExploracao.hpp"

class Cena;
class Jogador;

// ── Flag global de skip (espaço durante digitarAnimado acelera o texto) ───────
extern bool g_skipMode;
void resetarModoSkip();

// ── Exibição básica ───────────────────────────────────────────────────────────
void exibirCentrado(IView& view, const std::string& texto);
void exibirAsciiArtArquivo(IView& view, const std::string& caminho);

// ── Helpers de exploração ─────────────────────────────────────────────────────
void aguardarEnter(IView& view, IController& ctrl,
                   const std::string& msg,
                   const ConfigExploracao& cfg = {});
void exibirHeaderCena(IView& view, const Cena& cena);
void exibirRelatorio(IView& view, Jogador& jogador);
void exibirDialogo(IView& view, const std::string& caminho);

// ── Animações ─────────────────────────────────────────────────────────────────
/** Typewriter: pressionar ESPAÇO acelera para o fim imediato. */
void digitarAnimado(const std::string& texto, int delayMs = 20);
void revelarAsciiHorario(const std::string& caminho, int delayMs = 10);
void pressioneQualquerTecla(const std::string& msg = "\n  [ Pressione qualquer tecla para continuar... ]\n");
void limparTela();
std::vector<int> animarGeracaoAtributos();

/**
 * Anima um dado girando e para no valor 'resultado'.
 * @param label    Prefixo exibido (ex: "Iniciativa inimigo")
 * @param faces    Número de faces do dado
 * @param resultado Valor final real a exibir
 * @param spinCount Quantos frames de spin antes de parar (default 10)
 */
/**
 * @param modifier  Modificador somado ao resultado final (mostra d20+mod).
 *                  Passe 0 para não exibir modificador.
 */
void animarDadoComResultado(const std::string& label, int faces,
                             int resultado, int spinCount = 10, int modifier = 0);

#endif
