/**
 * @file UI.hpp
 * @brief Funções auxiliares para exibição e animações de terminal da demo.
 */

#ifndef DEMO_UI_HPP
#define DEMO_UI_HPP

#include <string>
#include <vector>
#include "utils/IView.hpp"
#include "utils/IController.hpp"
#include "demo/ConfigExploracao.hpp"

// Forward declarations para evitar includes pesados no header
class Cena;
class Jogador;

// ─────────────────────────────────────────────────────────────────────────────
// Exibição básica (via IView)
// ─────────────────────────────────────────────────────────────────────────────

/** Exibe texto centralizado na largura do terminal. */
void exibirCentrado(IView& view, const std::string& texto);

/** Exibe arte ASCII de um arquivo, centralizada. */
void exibirAsciiArtArquivo(IView& view, const std::string& caminho);

// ─────────────────────────────────────────────────────────────────────────────
// Helpers de exploração
// ─────────────────────────────────────────────────────────────────────────────

/** Aguarda Enter (pula silenciosamente se cfg.skipEnter == true). */
void aguardarEnter(IView& view, IController& ctrl,
                   const std::string& msg,
                   const ConfigExploracao& cfg = {});

/** Exibe cabeçalho de cena: arte ASCII, título e descrição. */
void exibirHeaderCena(IView& view, const Cena& cena);

/** Exibe relatório final de atributos e inventário do jogador via IView. */
void exibirRelatorio(IView& view, Jogador& jogador);

/** Carrega e exibe um arquivo de diálogo linha a linha via IView.
 *  Retorna silenciosamente se o arquivo não puder ser aberto. */
void exibirDialogo(IView& view, const std::string& caminho);

// ─────────────────────────────────────────────────────────────────────────────
// Animações (escrevem diretamente em stdout para controle preciso)
// ─────────────────────────────────────────────────────────────────────────────

/** Efeito máquina de escrever: imprime texto caractere a caractere. */
void digitarAnimado(const std::string& texto, int delayMs = 20);

/**
 * Revela arte ASCII de um arquivo em espiral no sentido horário,
 * substituindo caracteres progressivamente (técnica de loading bar 2-D).
 */
void revelarAsciiHorario(const std::string& caminho, int delayMs = 10);

/** Aguarda qualquer tecla sem exigir Enter (modo raw). */
void pressioneQualquerTecla(const std::string& msg = "\n  [ Pressione qualquer tecla para continuar... ]\n");

/** Limpa o terminal via ANSI. */
void limparTela();

/**
 * Gera 4 atributos via 4d6kh3, exibindo animação de rolagem.
 * @return Vetor com os 4 valores finais, em ordem decrescente.
 */
std::vector<int> animarGeracaoAtributos();

#endif
