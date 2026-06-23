#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "core/rules/RegrasClassePersonagem.hpp"
#include "utils/TipoArcanoEnum.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// Sistema de saves
// ─────────────────────────────────────────────────────────────────────────────

static const std::string DIR_SAVES = "data/saves/";
static const int NUM_SLOTS = 3;

struct SaveData {
    bool   existe    = false;
    std::string playerName;
    std::string charName;
    int    classeId  = 1;
    double atk = 0, def = 0, poder = 0, agi = 0;
    double xp  = 0;
    int    cenaId    = 1;
    std::vector<int> arcanos;
};

static std::string caminhoSlot(int slot)
{
    return DIR_SAVES + "slot" + std::to_string(slot) + ".sav";
}

static SaveData lerSave(int slot)
{
    SaveData s;
    std::ifstream f(caminhoSlot(slot));
    if (!f.is_open()) return s;
    std::string linha;
    if (!std::getline(f, linha) || linha != "DARK_AGE_SAVE") return s;
    s.existe = true;
    while (std::getline(f, linha)) {
        auto pos = linha.find('=');
        if (pos == std::string::npos) continue;
        std::string chave = linha.substr(0, pos);
        std::string valor = linha.substr(pos + 1);
        if      (chave == "playerName") s.playerName = valor;
        else if (chave == "charName")   s.charName   = valor;
        else if (chave == "classeId")   s.classeId   = std::stoi(valor);
        else if (chave == "atk")        s.atk        = std::stod(valor);
        else if (chave == "def")        s.def        = std::stod(valor);
        else if (chave == "poder")      s.poder      = std::stod(valor);
        else if (chave == "agi")        s.agi        = std::stod(valor);
        else if (chave == "xp")         s.xp         = std::stod(valor);
        else if (chave == "cenaId")     s.cenaId     = std::stoi(valor);
        else if (chave == "arcanos" && !valor.empty()) {
            std::istringstream ss(valor);
            std::string token;
            while (std::getline(ss, token, ','))
                if (!token.empty()) s.arcanos.push_back(std::stoi(token));
        }
    }
    return s;
}

static void gravarSave(int slot, const SaveData& s)
{
    std::filesystem::create_directories(DIR_SAVES);
    std::ofstream f(caminhoSlot(slot));
    f << "DARK_AGE_SAVE\n";
    f << "playerName=" << s.playerName << "\n";
    f << "charName="   << s.charName   << "\n";
    f << "classeId="   << s.classeId   << "\n";
    f << "atk="        << s.atk        << "\n";
    f << "def="        << s.def        << "\n";
    f << "poder="      << s.poder      << "\n";
    f << "agi="        << s.agi        << "\n";
    f << "xp="         << s.xp         << "\n";
    f << "cenaId="     << s.cenaId     << "\n";
    f << "arcanos=";
    for (size_t i = 0; i < s.arcanos.size(); i++) {
        if (i) f << ",";
        f << s.arcanos[i];
    }
    f << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers de nome
// ─────────────────────────────────────────────────────────────────────────────

static const TipoClasse classesPorId[] = {
    TipoClasse::Guerreiro, TipoClasse::Mago,
    TipoClasse::Arqueiro,  TipoClasse::Tanque
};
static const char* nomesClasses[] = { "Guerreiro", "Mago", "Arqueiro", "Tanque" };

static std::string nomeClasse(int id)
{
    if (id >= 1 && id <= 4) return nomesClasses[id-1];
    return "???";
}

static std::string nomeCena(int id)
{
    switch (id) {
        case 1: return "Magisk - Floresta Geada";
        case 2: return "Mantuu - Territorios Militares";
        case 3: return "Xantares - Portos e Becos";
        case 4: return "Kenyrock - Academias de Magia";
        case 5: return "Skyprout - Guildas e Minas";
        case 6: return "Retorno a Magisk";
        case 7: return "Santuario de Sonath";
        default: return "Fase " + std::to_string(id);
    }
}

static std::string nomeArcano(int id)
{
    switch (id) {
        case 1: return "Alma";
        case 2: return "Elementos";
        case 3: return "Caos";
        case 4: return "Mente";
        case 5: return "Vida";
        case 6: return "Natureza";
        default: return "???";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Cutscene (Capitulo 1)
// ─────────────────────────────────────────────────────────────────────────────

static void mostrarCutscene()
{
    limparTela();
    std::ifstream f("data/descricoes/capitulo1.txt");
    if (!f.is_open()) {
        digitarAnimado("\n  Antes do tempo, havia apenas o vazio...\n\n", 24);
        pressioneQualquerTecla();
        return;
    }
    std::string linha;
    while (std::getline(f, linha)) {
        if (!linha.empty() && linha.back() == '\r') linha.pop_back();
        bool isSep = (linha.find("==") != std::string::npos ||
                      linha.find("Capitulo") != std::string::npos);
        digitarAnimado(linha + "\n", isSep ? 7 : 16);
        if (linha.empty())
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    pressioneQualquerTecla();
}

// ─────────────────────────────────────────────────────────────────────────────
// Tela de titulo com reveal do cranio
// ─────────────────────────────────────────────────────────────────────────────

static void mostrarTitulo(IView& view)
{
    limparTela();
    revelarAsciiHorario("data/arcanos/7.txt", 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    exibirAsciiArtArquivo(view, "data/titulo.txt");
    pressioneQualquerTecla();
}

// ─────────────────────────────────────────────────────────────────────────────
// Menu de saves
// ─────────────────────────────────────────────────────────────────────────────

static void imprimirLinhaSave(int slot, const SaveData& s)
{
    std::string label = "  [" + std::to_string(slot) + "] ";
    if (!s.existe) {
        std::cout << label << "--- vazio ---\n";
    } else {
        std::cout << label
                  << s.playerName << " / " << s.charName
                  << "  (" << nomeClasse(s.classeId) << ")"
                  << "  |  " << nomeCena(s.cenaId);
        if (!s.arcanos.empty()) {
            std::cout << "  |  Arcanos:";
            for (int a : s.arcanos) std::cout << " " << nomeArcano(a);
        }
        std::cout << "\n";
    }
}

// Retorna 1-3 = slot carregado, 0 = novo jogo
static int menuSaves(IView&)
{
    limparTela();
    std::cout << "\n";
    std::cout << "  +================================================+\n";
    std::cout << "  |           CARREGAR JORNADA                     |\n";
    std::cout << "  +================================================+\n\n";
    std::array<SaveData, 3> saves;
    for (int i = 0; i < NUM_SLOTS; i++)
        saves[i] = lerSave(i + 1);
    for (int i = 0; i < NUM_SLOTS; i++)
        imprimirLinhaSave(i + 1, saves[i]);
    std::cout << "\n  [N] Nova jornada\n\n  Escolha: " << std::flush;
    std::string entrada;
    std::getline(std::cin, entrada);
    if (entrada == "N" || entrada == "n") return 0;
    try {
        int slot = std::stoi(entrada);
        if (slot >= 1 && slot <= NUM_SLOTS && saves[slot-1].existe)
            return slot;
    } catch (...) {}
    return 0;
}

// ─────────────────────────────────────────────────────────────────────────────
// Construtor de Jogador
// ─────────────────────────────────────────────────────────────────────────────

static Jogador construirJogador(const std::string& charName,
                                 TipoClasse classe,
                                 const std::array<double,4>& attr)
{
    double vida = RegrasClassePersonagem::calcularVidaInicial(classe, attr[1]);
    return Jogador(charName, "", "", attr[0], attr[1], vida, attr[2], attr[3],
                   classe, TipoPersonagem::Jogador);
}

// ─────────────────────────────────────────────────────────────────────────────
// Criacao de novo personagem
// ─────────────────────────────────────────────────────────────────────────────

static Jogador criarNovoPersonagem(IView& view, IController& ctrl,
                                    int& cenaInicial, int& slotEscolhido)
{
    (void)view;
    limparTela();

    std::cout << "\n  Como voce se chama, aventureiro?\n  > " << std::flush;
    std::string playerName = ctrl.lerTexto();
    if (playerName.empty()) playerName = "Aventureiro";

    std::cout << "\n  E qual e o nome do seu personagem?\n  > " << std::flush;
    std::string charName = ctrl.lerTexto();
    if (charName.empty()) charName = playerName;

    limparTela();
    std::cout << "\n  Bem-vindo, " << playerName << ".\n";
    std::vector<int> rolados = animarGeracaoAtributos();

    // Tabela de distribuicao
    std::cout << "  Como os atributos ficam por classe:\n\n";
    std::cout << "  +-----------+--------+--------+-----------+-------+\n";
    std::cout << "  | Classe    | Ataque | Defesa | Agilidade | Poder |\n";
    std::cout << "  +-----------+--------+--------+-----------+-------+\n";
    for (int i = 0; i < 4; i++) {
        auto a = RegrasClassePersonagem::distribuirAtributos(classesPorId[i], rolados);
        std::cout << "  | " << nomesClasses[i];
        for (int p = (int)std::string(nomesClasses[i]).size(); p < 9; p++) std::cout << ' ';
        auto col = [](int v, int w) {
            std::string s = std::to_string(v);
            return s + std::string(w - (int)s.size(), ' ');
        };
        std::cout << " | " << col((int)a[0], 6)
                  << " | " << col((int)a[1], 6)
                  << " | " << col((int)a[3], 9)
                  << " | " << col((int)a[2], 5) << " |\n";
    }
    std::cout << "  +-----------+--------+--------+-----------+-------+\n\n";

    int opcao = 0;
    while (true) {
        std::cout << "  Escolha sua classe:\n";
        std::cout << "  [1] Guerreiro  [2] Mago  [3] Arqueiro  [4] Tanque\n  > " << std::flush;
        opcao = ctrl.lerInteiro();
        if (opcao >= 1 && opcao <= 4) break;
        std::cout << "  Opcao invalida.\n";
    }

    TipoClasse classe = classesPorId[opcao - 1];
    auto attr = RegrasClassePersonagem::distribuirAtributos(classe, rolados);

    std::cout << "\n  Atributos de " << nomesClasses[opcao-1] << ":\n";
    std::cout << "  Ataque: " << (int)attr[0]
              << "  Defesa: " << (int)attr[1]
              << "  Agilidade: " << (int)attr[3]
              << "  Poder: " << (int)attr[2] << "\n\n";

    std::cout << "  Confirmar? [s/n] " << std::flush;
    std::string resp = ctrl.lerTexto();
    if (!resp.empty() && (resp[0] == 'n' || resp[0] == 'N'))
        return criarNovoPersonagem(view, ctrl, cenaInicial, slotEscolhido);

    std::cout << "\n  Em qual slot deseja salvar? [1/2/3]\n  > " << std::flush;
    int slot = ctrl.lerInteiro();
    if (slot < 1 || slot > NUM_SLOTS) slot = 1;
    slotEscolhido = slot;

    SaveData s;
    s.existe = true; s.playerName = playerName; s.charName = charName;
    s.classeId = opcao; s.atk = attr[0]; s.def = attr[1];
    s.poder = attr[2]; s.agi = attr[3]; s.xp = 0; s.cenaId = 1;
    gravarSave(slot, s);

    cenaInicial = 1;
    return construirJogador(charName, classe, attr);
}

// ─────────────────────────────────────────────────────────────────────────────
// Dialogo de abertura — Ruffen em Magisk
// ─────────────────────────────────────────────────────────────────────────────

static void dialogoAberturaRuffen(const std::string& charName)
{
    limparTela();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto fala = [](const std::string& texto, int delay = 18) {
        digitarAnimado(texto + "\n", delay * 4 / 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
    };

    digitarAnimado("\n  [ Magisk -- Floresta Geada ]\n\n", 16);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    fala("  Um homem de cabelos grisalhos e olhos cansados se aproxima.");
    fala("  Ele veste o brasao de Magisk, mas carrega algo mais pesado.");
    std::cout << "\n";
    fala("  RUFFEN: \"Bem-vindo a Magisk, " + charName + ".");
    fala("          Gostaria de te receber mais calorosamente,");
    fala("          mas isso nao sera possivel.\"");
    std::cout << "\n";
    fala("  RUFFEN: \"Sonath -- o Titan Eterno.");
    fala("          Um goliath de quase tres metros, olhos que carregam");
    fala("          quinhentos anos de odio. Ele caiu uma vez.");
    fala("          Mas algo o trouxe de volta.\"");
    std::cout << "\n";
    fala("  RUFFEN: \"Ele e sua Legiao estao em busca dos Arcanos.");
    fala("          Va ate a Floresta Geada e impeca o primeiro deles!\"\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    digitarAnimado("\n  [ Floresta Geada -- as margens de Magisk ]\n\n", 16);
    fala("  Device, Arauto de Talos, aguarda em algum lugar la dentro.\n");

    pressioneQualquerTecla();
}

// ─────────────────────────────────────────────────────────────────────────────
// Ponto de entrada publico
// ─────────────────────────────────────────────────────────────────────────────

Jogador criarPersonagem(IView& view, IController& ctrl, int& cenaInicial)
{
    mostrarCutscene();
    mostrarTitulo(view);
    limparTela();

    int slotEscolhido = 0;
    int slotCarregado = menuSaves(view);

    if (slotCarregado > 0) {
        // Carrega save
        SaveData s = lerSave(slotCarregado);
        TipoClasse classe = classesPorId[s.classeId - 1];
        std::array<double,4> attr = {s.atk, s.def, s.poder, s.agi};
        cenaInicial = s.cenaId;

        Jogador j = construirJogador(s.charName, classe, attr);
        if (s.xp > 0) j.ganharXp(s.xp);
        for (int a : s.arcanos)
            j.adicionarArcano(static_cast<TipoArcano>(a));
        return j;
    }

    // Novo personagem
    Jogador j = criarNovoPersonagem(view, ctrl, cenaInicial, slotEscolhido);
    if (cenaInicial == 1)
        dialogoAberturaRuffen(j.getNome());
    return j;
}
