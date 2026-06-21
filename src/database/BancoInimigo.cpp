/**
 * @file BancoInimigo.cpp
 * @brief Repositório estático de todos os inimigos e bosses do jogo.
 *
 * Cada Personagem é construído com atributos balanceados para o nível
 * esperado do jogador na fase correspondente.
 *
 * Construtor: Personagem(nome, descricao, fala,
 *                        ataque, defesa, vidaTotal, ppTotal, agilidade,
 *                        TipoClasse, TipoPersonagem, nivel)
 *
 * Balanceamento de atributos por ND:
 *   CD inimigo = 5 + 0.5 * agilidade
 *   Dano base  = dados_classe + (0.5 * ataque - 5)
 *   HP cresce  ~30 PV por nível de dificuldade, PP proporcional ao papel.
 *
 * @see Regras.md §4.7, §6.2 | BancoInimigo.hpp | BancoTrechoMapa.cpp
 */

#include "database/BancoInimigo.hpp"
#include <stdexcept>
#include <string>

Personagem BancoInimigo::obterInimigo(int id)
{
    if (id <= 0)
        throw std::invalid_argument("ID de inimigo invalido: deve ser maior que zero.");

    switch (id)
    {
    // ════════════════════════════════════════════════════════════════════════
    // FASE I — Magisk  (LV 1–2)
    // ════════════════════════════════════════════════════════════════════════

    case 1: // Orc Saqueador — ND 1/2
        return Personagem(
            "Orc Saqueador",
            "Um orc encurvado coberto de peles rasgadas. Sobrevivente da expulsao de Cadian.",
            "GRRAAH! Isso e meu!",
            10.0,  // ataque
            8.0,   // defesa
            30.0,  // vidaTotal
            10.0,  // ppTotal
            8.0,   // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            1);

    case 2: // Orc Berserker — ND 1
        return Personagem(
            "Orc Berserker",
            "Um orc enorme de olhos vermelhos. Entra em furia ao menor estimulo.",
            "Eu NAO sinto dor!",
            13.0,  // ataque
            6.0,   // defesa
            45.0,  // vidaTotal
            15.0,  // ppTotal
            7.0,   // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            1);

    case 3: // Orc Xamã — ND 1
        return Personagem(
            "Orc Xama",
            "Um orc idoso com ossos e ervas pendurados no pescoco. Lanca maldicos antigas.",
            "Os espiritos da Floresta Geada te consumirao!",
            9.0,   // ataque
            9.0,   // defesa
            28.0,  // vidaTotal
            45.0,  // ppTotal (mago)
            10.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::Inimigo,
            1);

    case 101: // Device — Arauto de Talos  |  BOSS Fase I  |  ND 3
        return Personagem(
            "Device",
            "Arauto de Talos. Um principe aasimar de pele palida e cabelos loiros quase brancos, coberto por uma armadura imponente. Seu sangue celestial foi corrompido pela furia de Talos — mas a beleza glacial ainda permanece, fria como o olho da tempestade.",
            "A tempestade nao tem misericordia. E eu tampouco.",
            15.0,  // ataque
            12.0,  // defesa
            80.0,  // vidaTotal
            55.0,  // ppTotal
            11.0,  // agilidade
            TipoClasse::Tanque,
            TipoPersonagem::BOSS,
            2);

    // ════════════════════════════════════════════════════════════════════════
    // FASE II — Mantuu  (LV 3–4)
    // ════════════════════════════════════════════════════════════════════════

    case 11: // Guerreiro Humano — ND 1
        return Personagem(
            "Guerreiro de Mantuu",
            "Soldado humano da frota naval de Mantuu. Treinado desde a infancia para o combate.",
            "Pela gloria de Mantuu!",
            14.0,  // ataque
            12.0,  // defesa
            55.0,  // vidaTotal
            20.0,  // ppTotal
            10.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            3);

    case 12: // Elfo Arqueiro — ND 2
        return Personagem(
            "Elfo Arqueiro",
            "Um alto elfo de expressao fria. Seus disparos sao calculados com precisao cirurgica.",
            "Voce nao e rapido o suficiente para mim.",
            13.0,  // ataque
            10.0,  // defesa
            50.0,  // vidaTotal
            30.0,  // ppTotal
            19.0,  // agilidade — alto
            TipoClasse::Arqueiro,
            TipoPersonagem::Inimigo,
            3);

    case 13: // Dragonato de Elite — ND 3
        return Personagem(
            "Dragonato de Elite",
            "Um dragonato com armadura draconica. Serve como guarda-costas dos nobres de Mantuu.",
            "Voce deveria ter recuado quando teve a chance.",
            16.0,  // ataque
            17.0,  // defesa
            75.0,  // vidaTotal
            30.0,  // ppTotal
            10.0,  // agilidade
            TipoClasse::Tanque,
            TipoPersonagem::Inimigo,
            4);

    case 102: // Vaelthor — Arauto de Glaron  |  BOSS Fase II  |  ND 5
        return Personagem(
            "Vaelthor",
            "Arauto de Glaron. Um dragonborn ancestral cujas escamas brilham como obsidiana e platina — eco da divisao entre Bahamut e Tiamat. Cada ataque carrega o peso dos elementos.",
            "Glaron dividiu-se para criar o equilibrio. Eu sou o que restou quando a ordem e o caos se encontraram.",
            19.0,  // ataque
            15.0,  // defesa
            130.0, // vidaTotal
            65.0,  // ppTotal
            12.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::BOSS,
            4);

    // ════════════════════════════════════════════════════════════════════════
    // FASE III — Xantares  (LV 5–6)
    // ════════════════════════════════════════════════════════════════════════

    case 21: // Pirata Humano — ND 2
        return Personagem(
            "Pirata de Xantares",
            "Um humano de cicatrizes no rosto e faca envenenada na cinta. Conhece cada beco dos portos de Xantares.",
            "Seus bolsos ou sua vida. Na verdade... os dois.",
            15.0,  // ataque
            10.0,  // defesa
            65.0,  // vidaTotal
            25.0,  // ppTotal
            14.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            5);

    case 22: // Tiefling Ladrão — ND 3
        return Personagem(
            "Tiefling Ladrao",
            "Um tiefling esguio que se move como sombra. Suas laminas sao mais rapidas do que os olhos conseguem acompanhar.",
            "Nao e pessoal. E negocio.",
            15.0,  // ataque
            9.0,   // defesa
            60.0,  // vidaTotal
            35.0,  // ppTotal
            21.0,  // agilidade — muito alto
            TipoClasse::Arqueiro,
            TipoPersonagem::Inimigo,
            5);

    case 23: // Tiefling Mercenário — ND 4
        return Personagem(
            "Tiefling Mercenario",
            "Um tiefling corpulento com olhos de brasa. Vendeu sua alma por ouro ha muito tempo.",
            "Paguei caro por essas garras. Voce vai pagar mais caro ainda.",
            19.0,  // ataque
            13.0,  // defesa
            85.0,  // vidaTotal
            40.0,  // ppTotal
            12.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            6);

    case 103: // Malphas — Arauto de Asmodeus  |  BOSS Fase III  |  ND 6
        return Personagem(
            "Malphas",
            "Arauto de Asmodeus. Um tiefling costurado de multiplos corpos — partes de criaturas e humanoides fundidas pelo caos do Senhor das Trevas. Cada costura pulsa com energia infernal.",
            "O caos nao e desordem. E liberdade. E voce vai entender isso enquanto se despedaca.",
            21.0,  // ataque
            15.0,  // defesa
            175.0, // vidaTotal
            85.0,  // ppTotal
            14.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::BOSS,
            6);

    // ════════════════════════════════════════════════════════════════════════
    // FASE IV — Kenyrock  (LV 7–8)
    // ════════════════════════════════════════════════════════════════════════

    case 31: // Mago da Ilusão — ND 3
        return Personagem(
            "Mago da Ilusao",
            "Um alto elfo de vestes cambiantes. Manipula percepcao e realidade com a mesma facilidade.",
            "O que voce ve? Apenas o que eu quero que veja.",
            15.0,  // ataque
            9.0,   // defesa
            60.0,  // vidaTotal
            90.0,  // ppTotal
            15.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::Inimigo,
            7);

    case 32: // Conjurador Élfico — ND 4
        return Personagem(
            "Conjurador Elfico",
            "Um elfo de Kenyrock especializado em aprisionamento arcano. Seus feiticos paralisam antes que o inimigo perceba.",
            "A magia de Azuth e ordem absoluta. Fique quieto.",
            17.0,  // ataque
            11.0,  // defesa
            72.0,  // vidaTotal
            100.0, // ppTotal
            13.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::Inimigo,
            7);

    case 33: // Arquimago de Kenyrock — ND 5
        return Personagem(
            "Arquimago de Kenyrock",
            "Um humano anciao com olhos que brilham em azul arcano. Membro do Conselho Arcano de Kenyrock.",
            "Ousadia nao substitui conhecimento. E voce nao tem nenhum dos dois.",
            20.0,  // ataque
            12.0,  // defesa
            85.0,  // vidaTotal
            115.0, // ppTotal
            14.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::Inimigo,
            8);

    case 104: // N'baki D'Itris — Arauto de Azuth  |  BOSS Fase IV  |  ND 7
        return Personagem(
            "N'baki D'Itris",
            "Arauto de Azuth. Originario de Zenabu, combina Artifice avancado com magia arcana de nivel divino. Sua mente processa batalha como calculo — nenhum movimento e desperdicado.",
            "Zenabu sobreviveu as Guerras Arcanas porque compreendemos algo que o norte jamais compreendeu: conhecimento e arma. E eu tenho muito mais que voce.",
            21.0,  // ataque
            13.0,  // defesa
            215.0, // vidaTotal
            130.0, // ppTotal
            17.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::BOSS,
            8);

    // ════════════════════════════════════════════════════════════════════════
    // FASE V — Skyprout  (LV 9–10)
    // ════════════════════════════════════════════════════════════════════════

    case 41: // Guerreiro Drow — ND 4
        return Personagem(
            "Guerreiro Drow",
            "Um drow das profundezas de Skyprout. Acostumado a lutar nas minas escuras onde a luz nao chega.",
            "A escuridao e meu lar. E sera seu tumulo.",
            19.0,  // ataque
            15.0,  // defesa
            95.0,  // vidaTotal
            40.0,  // ppTotal
            19.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            9);

    case 42: // Anão Berserker — ND 5
        return Personagem(
            "Anao Berserker",
            "Um anao das guildas corrompidas de Skyprout. Sua raiva e proporcional ao seu tamanho — que e gigante para um anao.",
            "GUILDA DO MARTELO NAO RECUA!",
            22.0,  // ataque
            17.0,  // defesa
            130.0, // vidaTotal
            30.0,  // ppTotal
            8.0,   // agilidade — lento
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            9);

    case 43: // Necromante Humano — ND 6
        return Personagem(
            "Necromante de Skyprout",
            "Um humano palido cujas maos nunca param de gesticular feiticos. Serve uma das guildas corrompidas de Skyprout.",
            "A morte nao e o fim. E apenas o inicio do meu exercito.",
            15.0,  // ataque
            11.0,  // defesa
            75.0,  // vidaTotal
            110.0, // ppTotal
            13.0,  // agilidade
            TipoClasse::Mago,
            TipoPersonagem::Inimigo,
            9);

    case 105: // Livies — Arauto de Lathander  |  BOSS Fase V  |  ND 8
        return Personagem(
            "Livies",
            "Arauto de Lathander. Um ser de presenca serena e olhar que parece enxergar alem do corpo fisico. Nao combate com forca bruta — cada golpe e preciso e inevitavel como o nascer do sol.",
            "A vida e o dom mais precioso e o mais desperdicado. Venho lembrando isso ha seculos.",
            19.0,  // ataque
            15.0,  // defesa
            270.0, // vidaTotal — muito alta (arcano da Vida)
            110.0, // ppTotal
            19.0,  // agilidade
            TipoClasse::Arqueiro,
            TipoPersonagem::BOSS,
            10);

    // ════════════════════════════════════════════════════════════════════════
    // FASE VI — Retorno a Magisk
    // ════════════════════════════════════════════════════════════════════════

    case 51: // Orc Veterano — ND 5
        return Personagem(
            "Orc Veterano",
            "Um orc sobrevivente da Floresta Geada, enrijecido por decadas de batalha sob as ordens de Sonath.",
            "Desta vez, nos nao fugimos.",
            19.0,  // ataque
            17.0,  // defesa
            105.0, // vidaTotal
            30.0,  // ppTotal
            12.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::Inimigo,
            8);

    case 52: // Cavaleiro da Morte — ND 6
        return Personagem(
            "Cavaleiro da Morte",
            "Uma figura encoberta por armadura negra. Nao se sabe se ainda ha algo vivo dentro daquela armadura.",
            "...",
            21.0,  // ataque
            19.0,  // defesa
            125.0, // vidaTotal
            55.0,  // ppTotal
            10.0,  // agilidade
            TipoClasse::Tanque,
            TipoPersonagem::Inimigo,
            9);

    case 53: // Zumbi Colossal — ND 7
        return Personagem(
            "Zumbi Colossal",
            "Uma criatura imensa reanimada por Sonath a partir de varios corpos. Lenta, mas capaz de destruir muros com um unico golpe.",
            "URRHHH...",
            24.0,  // ataque
            15.0,  // defesa
            160.0, // vidaTotal
            10.0,  // ppTotal
            6.0,   // agilidade — muito lento
            TipoClasse::Tanque,
            TipoPersonagem::Inimigo,
            9);

    case 106: // Nyriel — Arauto de Eldath  |  BOSS Fase VI  |  ND 8
        return Personagem(
            "Nyriel",
            "Arauto de Eldath. Uma elfa cujos cabelos parecem feitos de galhos e cujos olhos refletem florestas que ja nao existem mais. Carrega o luto de cada arvore que Sonath destruiu.",
            "Eldath e a paz que antecede e sucede toda tempestade. Voce passou pela tempestade. Agora enfrente a paz — que pode ser mais implacavel.",
            19.0,  // ataque
            17.0,  // defesa
            245.0, // vidaTotal
            125.0, // ppTotal
            21.0,  // agilidade — alta
            TipoClasse::Mago,
            TipoPersonagem::BOSS,
            10);

    // ════════════════════════════════════════════════════════════════════════
    // BOSS FINAL — Sonath
    // ND 9–10  |  Golias corrompido, braço destruído pelo ácido
    // Motivação: reunir todos os Arcanos para ser o deus de um novo mundo
    // ════════════════════════════════════════════════════════════════════════

    case 999: // Sonath — Boss Final
        return Personagem(
            "Sonath",
            "O Senhor da Legiao. Um golias de quase 3 metros com um braco inteiro corroido pelo acido do ritual traido por Ruffen. Passou 500 anos reunindo poder para provar que o equilibrio de Ao nao pode existir sem o caos que ele representa.",
            "Ruffen me traiu. Os deuses me abandonaram. Mas Ao... Ao me deu uma missao. E eu a cumprirei com ou sem voce no caminho.",
            26.0,  // ataque
            19.0,  // defesa
            380.0, // vidaTotal — boss final
            150.0, // ppTotal
            15.0,  // agilidade
            TipoClasse::Guerreiro,
            TipoPersonagem::BOSS,
            10);

    default:
        throw std::invalid_argument(
            "Inimigo nao encontrado: id " + std::to_string(id));
    }
}
