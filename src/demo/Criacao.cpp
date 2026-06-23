#include <string>
#include <vector>

#include "demo/Criacao.hpp"
#include "demo/UI.hpp"
#include "core/rules/RegrasClassePersonagem.hpp"
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

    static const TipoClasse opcaoParaClasse[] = {
        TipoClasse::Guerreiro,
        TipoClasse::Mago,
        TipoClasse::Arqueiro,
        TipoClasse::Tanque
    };

    TipoClasse classe = opcaoParaClasse[opcaoClasse - 1];
    auto attr = RegrasClassePersonagem::distribuirAtributos(classe, atributos);

    return Jogador(
        nome, "", "",
        attr[0],
        attr[1],
        RegrasClassePersonagem::calcularVidaInicial(classe, attr[1]),
        attr[2],
        attr[3],
        classe,
        TipoPersonagem::Jogador
    );
}
