#include <string>
#include <vector>

#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "Dados.hpp"

Jogador criarPersonagem(IView& view, IController& ctrl)
{
    exibirAsciiArtArquivo(view, "data/arcanos/geral.txt");
    exibirAsciiArtArquivo(view, "data/titulo.txt");

    view.exibir("Digite o nome do personagem:");
    std::string nome = ctrl.lerTexto();

    view.exibir("+----+-----------+--------------+------------------+--------------------------------------------------+");
    view.exibir("| ID | Classe    | Dado de Vida | Arma             | Perfil                                           |");
    view.exibir("+----+-----------+--------------+------------------+--------------------------------------------------+");
    view.exibir("| 1  | Guerreiro | 1d10         | Espada           | Alto dano, resistente, combate direto            |");
    view.exibir("| 2  | Mago      | 1d6          | Magia            | Dano mágico elevado, baixa defesa, controle PP   |");
    view.exibir("| 3  | Arqueiro  | 1d8          | Arco             | Velocidade e precisão, ataques múltiplos         |");
    view.exibir("| 4  | Tank      | 1d12         | Escudo           | Máxima resistência, dano baseado em Defesa       |");
    view.exibir("+----+-----------+--------------+------------------+--------------------------------------------------+");

    Dados dados;
    std::vector<int> atributos = dados.gerarAtributos();

    view.exibir("Atributos rolados: ");
    for (int atributo : atributos)
        view.exibir(std::to_string(atributo));

    view.exibir("+-----------+-----------+-----------+-----------+-----------+");
    view.exibir("| Classe    | Ataque    | Defesa    | Agilidade | Poder     |");
    view.exibir("+-----------+-----------+-----------+-----------+----------+");
    view.exibir("| Guerreiro | "+std::to_string(atributos[0])+"        | "+std::to_string(atributos[1])+"        | "+std::to_string(atributos[2])+"        | "+std::to_string(atributos[3])+"        |");
    view.exibir("| Mago      | "+std::to_string(atributos[2])+"        | "+std::to_string(atributos[3])+"        | "+std::to_string(atributos[1])+"        | "+std::to_string(atributos[0])+"        |");
    view.exibir("| Arqueiro  | "+std::to_string(atributos[1])+"        | "+std::to_string(atributos[3])+"        | "+std::to_string(atributos[0])+"        | "+std::to_string(atributos[2])+"        |");
    view.exibir("| Tank      | "+std::to_string(atributos[1])+"        | "+std::to_string(atributos[0])+"        | "+std::to_string(atributos[3])+"        | "+std::to_string(atributos[2])+"        |");
    view.exibir("+-----------+----------+-----------+------------+-----------+");

    int opcaoClasse;
    while (true)
    {
        view.exibirLinha();
        view.exibir("Escolha sua classe:");
        view.exibir("[1] Guerreiro");
        view.exibir("[2] Mago");
        view.exibir("[3] Arqueiro");
        view.exibir("[4] Tank");

        opcaoClasse = ctrl.lerInteiro();

        if (opcaoClasse >= 1 && opcaoClasse <= 4)
        {
            view.exibir("Opção escolhida: " + std::to_string(opcaoClasse) + "\n");
            break;
        }

        view.exibir("Opcao invalida.");
    }

    switch (opcaoClasse)
    {
    case 1:
        return Jogador(nome, "", "",
            atributos[0], atributos[1],
            10.0 + (0.5 * atributos[1]) - 5,
            atributos[3], atributos[2],
            TipoClasse::Guerreiro, TipoPersonagem::Jogador);

    case 2:
        return Jogador(nome, "", "",
            atributos[2], atributos[3],
            6.0 + (0.5 * atributos[3]) - 5,
            atributos[0], atributos[1],
            TipoClasse::Mago, TipoPersonagem::Jogador);

    case 3:
        return Jogador(nome, "", "",
            atributos[1], atributos[3],
            8.0 + (0.5 * atributos[3]) - 5,
            atributos[2], atributos[0],
            TipoClasse::Arqueiro, TipoPersonagem::Jogador);

    default:
        return Jogador(nome, "", "",
            atributos[1], atributos[0],
            12.0 + (0.5 * atributos[0]) - 5,
            atributos[2], atributos[3],
            TipoClasse::Tanque, TipoPersonagem::Jogador);
    }
}
