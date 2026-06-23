# Arquitetura — The Dark Age: The Arcanum Quest

## Tecnologias e Ferramentas

| Camada | Tecnologia |
|--------|-----------|
| Linguagem | C++17 |
| Compilador | g++ (flags: `-std=c++17 -Wall -Wextra`) |
| Build | GNU Make (Makefile com busca recursiva via `find`) |
| Testes | [doctest](https://github.com/doctest/doctest) (header-only, `tests/doctest.h`) |
| Cobertura | gcovr + `--coverage` do g++ → HTML em `docs/coverage/` |
| Documentação | Doxygen (`Doxyfile`) |
| RNG | `std::mt19937` encapsulado em `Dados` (injetável via semente para testes) |

---

## Fluxo de Execução (Game Loop)

```mermaid
flowchart TD
    A([main.cpp]) --> B[Jogador escolhe classe\nWarrior / Mage / Archer / Tank]
    B --> C[BancoCena::obterCena\ncarrega InfoCena por ID]
    C --> D[Cena\norquestra exploração]
    D --> E{Evento}
    E -->|encontro| F[Batalha\ncombate por turnos]
    E -->|item encontrado| G[Inventario\nadiciona Item]
    E -->|NPC| H[BancoNpcInteracao\ndiálogo / recompensa]
    F -->|vitória| I[definirRecompensa\nXP + item]
    I --> J{Subiu de nível?}
    J -->|sim| K[Personagem::subirNivel\nRegrasProgresso]
    J -->|não| D
    K --> D
    D -->|cena concluída| L{Última cena?}
    L -->|não| C
    L -->|sim — Sonath derrotado| M([FIM — Arcanos])
```

---

## Organização de Camadas e Classes

```mermaid
flowchart TD
    subgraph ENTRY["Ponto de Entrada"]
        MAIN["main.cpp"]
    end

    subgraph MVC["Padrão MVC"]
        direction TB
        IV["«interface»\nIView\nexibir / exibirLinha"]
        IC["«interface»\nIController\n(entrada do usuário)"]
        TV["TerminalView\nimplementa IView\n(stdout)"]
        CTRL["InputController\nimplementa IController\n(stdin / teclado)"]
        IV --> TV
        IC --> CTRL
    end

    subgraph ENTITIES["Entidades — src/entities/"]
        direction TB

        subgraph CHAR["character/"]
            CP["ClassePersonagem\narchetipo + fórmulas de dano\n_ataqueForteAtivo, _dadoDeVida"]
            PERS["Personagem\nHP, XP, nível, atributos\n_condicoesAtivas"]
            JOG["Jogador\nextende Personagem\n(herói do player)"]
            CP --> PERS
            PERS --> JOG
        end

        subgraph BATTLE["battle/"]
            BAT["Batalha\norquestra turnos\niniciar / realizarAcao\ndefinirRecompensa"]
            COND["Condicao «struct»\ntipo, duração, parâmetros"]
            BAT --> COND
        end

        subgraph ITEMS["items/"]
            ITEM["Item\nPoção / Comida / Cristal"]
            INV["Inventario\n8 slots\nadicionar / usar / remover"]
            INV --> ITEM
        end

        subgraph MAP["map/"]
            CENA["Cena\ncontrolador de capítulo\nandar / vasculhar / interagirNPCs"]
            TRECHO["TrechoMapa\nsegmento dentro da cena\n_nd / classificarDificuldade"]
            CENA --> TRECHO
        end
    end

    subgraph CORE["Núcleo — src/core/"]
        DADOS["Dados\nRNG: std::mt19937\nrolar(n) injetável em testes"]

        subgraph RULES["rules/"]
            REG["«abstrata»\nRegras\ncalcularCoeficiente\nbonusProficiencia\nxpParaProximoNivel"]
            RB["RegrasBatalha\ndificuldade / XP / defesa\nprocessarDefesa / Esquiva / calcularXP"]
            RA["RegrasAtaque\nfórmulas de dano por classe"]
            RI["RegrasItem\neficácia de Poção / Comida"]
            RP["RegrasProgresso\nthresholds de XP / level-up"]
            REG --> RB
            REG --> RA
            REG --> RI
            REG --> RP
        end
    end

    subgraph DB["Banco de Dados estático — src/database/"]
        BC["BancoCena\nobterCena(id) → InfoCena"]
        BT["BancoTrechoMapa\nobterTrechoMapa(id)"]
        BI["BancoInimigo\nobterInimigo(id) → Personagem"]
        BK["BancoItem\nobterItem(id) → Item"]
        BCA["BancoClassePersonagem\nobterClasse(id)"]
        BDA["BancoDadosAtaque\nobterDados(id)"]
        BN["BancoNpcInteracao\nobterNpc(id)"]
    end

    subgraph UTILS["Utilitários — include/utils/"]
        AE["AtaqueEnum\nSimples / Rapido / Forte"]
        AT["AtributoEnum\nATQ / DEF / AGI / MAG..."]
        TE["TipoCondicaoEnum\nAtordoado / Paralisado..."]
        TAR["TipoArcanoEnum\n(artefatos de cada região)"]
    end

    subgraph TESTS["Testes — tests/"]
        DT["doctest.h\nheader-only framework"]
        TCORE["core/\ntesteDados, testeRegras\ntesteRegrasAtaque..."]
        TENT["entities/\ntesteBatalha, testePersonagem\ntesteInventario, testeCena..."]
        TDB["database/\ntesteBancoCena\ntesteBancoInimigo..."]
    end

    %% Dependências principais
    MAIN --> MVC
    MAIN --> ENTITIES
    MAIN --> DB

    BAT --> DADOS
    BAT --> IV
    BAT --> IC
    BAT --> RB
    BAT --> PERS

    CENA --> BAT
    CENA --> IV
    CENA --> IC
    CENA --> BC
    CENA --> BT
    CENA --> BI
    CENA --> BN
    CENA --> INV

    TRECHO --> RB

    PERS --> RP
    CP --> RA
    ITEM --> RI

    BC --> UTILS
    BI --> CP
    BK --> ITEM
    BDA --> AE
```

---

## Injeção de Dependência em Batalha

```mermaid
flowchart LR
    subgraph Construtor["Batalha(player, inimigo, dados, view, controller, regras)"]
        P["Personagem* player"]
        I["Personagem* inimigo"]
        D["Dados& dados\n(semente fixa em testes)"]
        V["IView* view\n(nullptr em prod hoje)"]
        C["IController* controller"]
        R["RegrasBatalha* regras"]
    end
    Construtor --> BAT2["Batalha\norquestra turnos"]
```

---

## Hierarquia de Regras

```mermaid
classDiagram
    class Regras {
        <<abstract>>
        #calcularCoeficiente(valor) float
        #bonusProficiencia(nivel) int
        #xpParaProximoNivel(nivel) int
    }
    class RegrasBatalha {
        +classificarConfronto() string
        +calcularXPGanho() int
        +processarDefesa() double
        +processarEsquiva() double
    }
    class RegrasAtaque {
        +calcularDano(classe, tipo) double
    }
    class RegrasItem {
        +calcularEficacia(item) double
    }
    class RegrasProgresso {
        +xpParaSubir(nivel) int
        +bonusProficiencia(nivel) int
    }

    Regras <|-- RegrasBatalha
    Regras <|-- RegrasAtaque
    Regras <|-- RegrasItem
    Regras <|-- RegrasProgresso
```

---

## Estrutura de Diretórios

```
PDS2-2026-PF-grupo5/
├── include/                   # Contratos (.hpp)
│   ├── controllers/           # InputController.hpp
│   ├── core/
│   │   ├── Dados.hpp
│   │   └── rules/             # Regras*.hpp
│   ├── database/              # Banco*.hpp + Struct*.hpp
│   ├── demo/                  # Demo.hpp, Exploracao.hpp
│   ├── entities/
│   │   ├── battle/            # Batalha.hpp, Condicao.hpp
│   │   ├── character/         # ClassePersonagem.hpp, Personagem.hpp, Jogador.hpp
│   │   ├── items/             # Item.hpp, Inventario.hpp
│   │   └── map/               # Cena.hpp, TrechoMapa.hpp
│   ├── utils/                 # Enums + IView.hpp + IController.hpp
│   └── views/                 # TerminalView.hpp
├── src/                       # Implementações (.cpp) — espelha include/
├── tests/                     # Testes doctest — espelha src/
│   ├── doctest.h
│   ├── main.cpp               # DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
│   ├── core/
│   ├── database/
│   ├── entities/
│   ├── controllers/
│   └── views/
├── design/                    # Cartões CRC + User Stories
├── docs/                      # Doxygen + regras.md + cobertura HTML
├── Makefile
└── Doxyfile
```
