#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include <poll.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "demo/UI.hpp"
#include "entities/map/Cena.hpp"
#include "entities/character/Jogador.hpp"
#include "entities/items/Inventario.hpp"

// ── Skip mode global ──────────────────────────────────────────────────────────
bool g_skipMode = false;
void resetarModoSkip() { g_skipMode = false; }

// ── Helpers internos ──────────────────────────────────────────────────────────
static int larguraTerminal()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
        return ws.ws_col;
    return 80;
}

static void setRaw(struct termios& oldt)
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

static void restoreTerminal(const struct termios& oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

// ── Exibição básica ───────────────────────────────────────────────────────────
void exibirCentrado(IView& view, const std::string& texto)
{
    int pad = std::max(0, (larguraTerminal() - (int)texto.size()) / 2);
    view.exibir(std::string(pad, ' ') + texto);
}

void exibirAsciiArtArquivo(IView& view, const std::string& caminho)
{
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) return;
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        linhas.push_back(linha);
    }
    size_t maxLarg = 0;
    for (const auto& l : linhas) maxLarg = std::max(maxLarg, l.size());
    int pad = std::max(0, (larguraTerminal() - (int)maxLarg) / 2);
    std::string prefixo(pad, ' ');
    for (const auto& l : linhas) view.exibir(prefixo + l);
}

void limparTela()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

// ── digitarAnimado com spacebar skip ─────────────────────────────────────────
void digitarAnimado(const std::string& texto, int delayMs)
{
    if (g_skipMode) {
        std::cout << texto << std::flush;
        return;
    }

    struct termios oldt;
    setRaw(oldt);

    for (char c : texto) {
        std::cout << c << std::flush;
        if (g_skipMode) continue;

        struct pollfd pfd{STDIN_FILENO, POLLIN, 0};
        if (poll(&pfd, 1, delayMs) > 0 && (pfd.revents & POLLIN)) {
            int ch = getchar();
            if (ch == ' ') {
                g_skipMode = true;
            }
        }
    }

    restoreTerminal(oldt);
}

// ── pressioneQualquerTecla (reseta skip) ─────────────────────────────────────
void pressioneQualquerTecla(const std::string& msg)
{
    g_skipMode = false;
    std::cout << msg << std::flush;
    struct termios oldt;
    setRaw(oldt);
    getchar();
    restoreTerminal(oldt);
    std::cout << '\n';
}

// ── revelarAsciiHorario ───────────────────────────────────────────────────────
void revelarAsciiHorario(const std::string& caminho, int delayMs)
{
    std::ifstream f(caminho);
    if (!f.is_open()) return;
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(f, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        linhas.push_back(linha);
    }
    if (linhas.empty()) return;
    int rows = (int)linhas.size();
    int cols = 0;
    for (const auto& l : linhas) cols = std::max(cols, (int)l.size());
    for (auto& l : linhas) l.resize(cols, ' ');
    int termW = larguraTerminal();
    int pad   = std::max(0, (termW - cols) / 2);
    std::string prefixo(pad, ' ');
    std::vector<std::string> grid(rows, std::string(cols, ' '));
    for (int r = 0; r < rows; r++) std::cout << prefixo << grid[r] << '\n';
    std::cout << std::flush;
    auto reprint = [&]() {
        std::cout << "\033[" << rows << "A\r";
        for (int r = 0; r < rows; r++) std::cout << prefixo << grid[r] << '\n';
        std::cout << std::flush;
    };
    std::vector<std::pair<int,int>> ordem;
    {
        int top = 0, bot = rows-1, left = 0, right = cols-1;
        while (top <= bot && left <= right) {
            for (int c = left; c <= right; c++) ordem.push_back({top, c});
            top++;
            for (int r = top; r <= bot; r++) ordem.push_back({r, right});
            right--;
            if (top <= bot) {
                for (int c = right; c >= left; c--) ordem.push_back({bot, c});
                bot--;
            }
            if (left <= right) {
                for (int r = bot; r >= top; r--) ordem.push_back({r, left});
                left++;
            }
        }
    }
    std::vector<std::pair<int,int>> pos;
    for (auto [r, c] : ordem)
        if (linhas[r][c] != ' ') pos.push_back({r, c});
    if (pos.empty()) { reprint(); return; }
    int batchSize = std::max(1, (int)pos.size() / 60);
    for (size_t i = 0; i < pos.size(); i++) {
        auto [r, c] = pos[i];
        grid[r][c] = linhas[r][c];
        bool ultimo = (i == pos.size() - 1);
        if ((int)i % batchSize == batchSize - 1 || ultimo) {
            reprint();
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
}

// ── Helpers de exploração ─────────────────────────────────────────────────────
void aguardarEnter(IView& view, IController& ctrl,
                   const std::string& msg,
                   const ConfigExploracao& cfg)
{
    if (cfg.skipEnter) return;
    view.exibir(msg);
    ctrl.lerTexto();
}

void exibirHeaderCena(IView& view, const Cena& cena)
{
    exibirAsciiArtArquivo(view,
        "data/arcanos/" + std::to_string(cena.pegarId()) + ".txt");

    std::string titulo =
        "  Cena " + std::to_string(cena.pegarId()) +
        "  ~*~  " + cena.pegarArcano() + "  ";
    std::string borda = "+" + std::string(titulo.size(), '=') + "+";

    exibirCentrado(view, borda);
    exibirCentrado(view, "|" + titulo + "|");
    exibirCentrado(view, borda);
    view.exibir("");
    exibirCentrado(view, cena.pegarDescricao());
    view.exibir("");
}

void exibirRelatorio(IView& view, Jogador& jogador)
{
    view.exibirLinha();
    view.exibir("=== Relatório de Validação ===");
    view.exibir("Personagem  : " + jogador.getNome() +
                " (" + jogador.getClasse().getNome() + ")");
    view.exibir("Nível       : " + std::to_string(jogador.getNivel()) +
                " | XP: " + std::to_string(static_cast<int>(jogador.getXp())));
    view.exibir("HP          : " + std::to_string(static_cast<int>(jogador.getVidaAtual())) +
                " / " + std::to_string(static_cast<int>(jogador.getVidaTotal())));

    view.exibir("\n--- Inventário final ---");
    int qtd = jogador.getInventario().quantidadeItens();
    if (qtd == 0)
        view.exibir("Inventário vazio.");
    else
        jogador.getInventario().listarItens(view);

    view.exibirLinha();
    view.exibir("Fim da demo c:");
    view.exibirLinha();
}

void exibirDialogo(IView& view, const std::string& caminho)
{
    std::ifstream f(caminho);
    if (!f.is_open()) return;
    std::string linha;
    while (std::getline(f, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        view.exibir("  " + linha);
    }
}

// ── animarGeracaoAtributos ────────────────────────────────────────────────────
std::vector<int> animarGeracaoAtributos()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> d6(1, 6);
    std::uniform_int_distribution<int> spinDist(3, 18);
    std::cout << "\n  Gerando atributos...\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::vector<int> resultado;
    for (int i = 0; i < 4; i++) {
        std::array<int,4> dados4;
        for (int& d : dados4) d = d6(rng);
        int minIdx = 0;
        for (int j = 1; j < 4; j++)
            if (dados4[j] < dados4[minIdx]) minIdx = j;
        int total = 0;
        for (int j = 0; j < 4; j++)
            if (j != minIdx) total += dados4[j];
        for (int s = 0; s < 10; s++) {
            int fake = spinDist(rng);
            std::cout << "\r  4d6kh3 (...) = " << fake << "   " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(55));
        }
        std::cout << "\r  4d6kh3 (";
        for (int j = 0; j < 4; j++) {
            if (j > 0) std::cout << ", ";
            if (j == minIdx)
                std::cout << "\033[9m" << dados4[j] << "\033[29m";
            else
                std::cout << dados4[j];
        }
        std::cout << ") = \033[1m" << total << "\033[0m\n" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        resultado.push_back(total);
    }
    std::sort(resultado.begin(), resultado.end(), std::greater<int>());
    int soma = 0;
    for (int v : resultado) soma += v;
    std::cout << "\n  Total = \033[1m" << soma << "\033[0m\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    return resultado;
}

// ── animarDadoComResultado ────────────────────────────────────────────────────
void animarDadoComResultado(const std::string& label, int faces,
                             int resultado, int spinCount, int modifier)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, faces);
    std::string modStr = (modifier > 0) ? "+" + std::to_string(modifier)
                       : (modifier < 0) ? std::to_string(modifier)
                       : "";
    std::string dadoStr = "d" + std::to_string(faces) + modStr;
    for (int s = 0; s < spinCount; s++) {
        int fake = dist(rng);
        std::cout << "\r  " << label << " [" << dadoStr << "]: "
                  << fake + modifier << "   " << std::flush;
        int ms = 30 + s * 8;
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    int total = resultado + modifier;
    std::string cor = (resultado == faces)  ? "\033[1;33m" :  // max = amarelo
                      (resultado <= 1)      ? "\033[1;31m" :  // 1 = vermelho
                                              "\033[1m";
    std::cout << "\r  " << label << " [" << dadoStr << "]: "
              << cor << total << "\033[0m   \n" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}
