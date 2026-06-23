# The Dark Age - The Arcanum Quest

**Grupo 5** - RPG Turn-Based Game  
**Disciplina:** Programação e Desenvolvimento de Software II - UFMG  
**Semestre:** 2026/1 | **Turma:** TF

---

## Sumário

1. [Integrantes](#integrantes-do-grupo)
2. [Descrição do Projeto](#descrição-do-projeto)
3. [Motivação](#motivação)
4. [Objetivos e Funcionalidades](#objetivos)
5. [Visão Geral do Jogo](#visão-geral-do-jogo)
6. [Como Compilar e Testar](#como-compilar-e-testar)
7. [Estrutura de Diretórios](#estrutura-de-diretórios)

---

## Integrantes do Grupo

| Nome | Matrícula |
|------|-----------|
| Henrique Viana Lima de Oliveira | 2023066543 |
| Mariana Ferreira de Castro | 2025019658 |
| Laura Silveira Brandão Pinto | 2025075060 |
| Matheus Mariano Euzébio | 2025102628 |

---

## Descrição do Projeto

*The Dark Age - The Arcanum Quest* é um jogo de RPG baseado em turnos ambientado em um universo original inspirado em uma campanha real de Dungeons & Dragons, mestrada pelo aluno Henrique Viana e jogada/ vivenciada pelos alunos Matheus, Mariana e Laura. Como na campanha original jogador assume o controle de um herói e deve escolher dentre as seguintes classes: Guerreiro, Mago, Arqueiro ou Tank, e sobre as ordens de Ruffen, deve percorrer seis regiões distintas do mundo, cada uma dominada por um poderoso boss aliado ao antagonista Sonath. O objetivo narrativo principal é reunir os Arcanos para enfrentar o boss final, Sonath, avançando por cenas e desafios que alteram o ritmo e a estratégia do jogador.

## Motivação

A motivação para o desenvolvimento deste jogo nasce da experiência vivida pelos integrantes do grupo em sessões reais de RPG de mesa: os personagens, a lore e os eventos do jogo têm origem em uma campanha autêntica, o que torna o projeto tanto um exercício técnico quanto uma forma criativa de preservar e expandir uma história coletiva. Do ponto de vista técnico, o projeto foi pensado para aplicar conceitos de Programação Orientada a Objetos, modularização e separação entre lógica de jogo e interface, permitindo evolução tanto para execução em terminal quanto para interface gráfica. A estrutura inicial do repositório já prevê diretórios específicos para contratos, implementação, testes, documentação e dados.

---

## Objetivos

Desenvolver um motor de RPG em turnos que represente personagens, classes, batalhas, inventário, itens, cenas e progressão de nível de forma organizada e extensível.

Funcionalidades implementadas:

- Escolha de classe no início do jogo (Guerreiro, Mago, Arqueiro, Tank)
- Exploração: andar por trechos, vasculhar itens, interagir com NPCs
- Inventário com 8 slots e uso de itens em batalha
- Batalha em turnos: ataque simples, rápido e forte, defesa, esquiva, fuga
- Condições: Berserk, Envenenado, Paralisado, Atordoado, ModAtributo, CemPorcentoAcerto
- Arcanos: seis poderes divinos com efeitos passivos em combate e progressão
- XP, subida de nível e banco de inimigos por fase
- Hierarquia de Regras (RegrasAtaque, RegrasBatalha, RegrasProgresso, RegrasClassePersonagem, RegrasItem)
- Padrão MVC com interfaces IView e IController; implementação via TerminalView e InputController
- Injeção de dependência de Dados (RNG) para testes determinísticos
- Testes com doctest e relatório de cobertura via gcovr

---

## Visão Geral do Jogo

### Classes de Personagem

| Classe | Arma | Característica |
|--------|------|----------------|
| Guerreiro | Espada | Alta resistência física |
| Mago | Magia | Uso ampliado de habilidades mágicas |
| Arqueiro | Arco | Alta agilidade e ataques à distância |
| Tank | Escudo | Bloqueio e redução de dano |

### Atributos
Cada personagem possui: **vida**, **PP/mana**, **ataque**, **defesa**, **agilidade**, **XP** e **nível**.

### Itens (Inventário — máx. 8 slots)
- **Comidas** — alteram pontos de vida (ex.: Lichia aumenta, Pera reduz)
- **Poções** — aumentam atributos temporariamente (duram 1 a 4 turnos)
- **Cristais** — efeitos únicos; removidos ao mudar de cena

### Arcanos (Poderes dos Deuses)

| Arcano | Deus | Efeito |
|--------|------|--------|
| Poder do Caos | Asmodeus | Parte do dano causado vira vida |
| Poder da Alma | Talos | +50% XP ganho e imunidade a Paralisado |
| Poder da Natureza | Eldath | Maior chance de encontrar itens raros |
| Poder da Vida | Lathander | Regeneração de HP passiva por turno |
| Poder dos Elementos | Glaron (Bahamut e Tiamat) | +20% de dano em ataques |
| Poder da Mente | Azuth | -25% no custo de mana das habilidades |

### Sistema de Batalha

Batalhas são por turnos - age primeiro quem tem maior **agilidade**. Em cada turno o jogador pode: **atacar** (simples, rápido ou forte), **defender**, **esquivar**, **usar item** ou **fugir**. Condições aplicadas durante a batalha afetam as ações disponíveis no turno seguinte.

### Inimigos

| Fase | Região | Boss | Nível |
|------|--------|------|-------|
| I | Magisk | Device | 1-2 |
| II | Mantuu | Vaelthor | 3-4 |
| III | Xantares | Malphas | 5-6 |
| IV | Kenyrock | N'baki D'Itris | 7-8 |
| V | Skyprout | Livies | 9-10 |
| VI | Retorno Magisk | Nyriel | 9-10 |
| Final | - | Sonath | 10 |

---

## Como Compilar e Testar

```bash
# Compilar o projeto
make

# Executar todos os testes
make test

# Gerar relatório de cobertura (requer gcovr)
make test_coverage

# Limpar artefatos de build
make clean
```

---

## Estrutura de Diretórios

```
PDS2-2026-PF-grupo5/
├── include/                    # Cabeçalhos (.hpp)
│   ├── controllers/
│   ├── core/
│   │   └── rules/
│   ├── database/
│   ├── demo/
│   ├── entities/
│   │   ├── battle/
│   │   ├── character/
│   │   ├── items/
│   │   └── map/
│   ├── utils/
│   └── views/
├── src/                        # Implementações (.cpp)
│   ├── controllers/
│   ├── core/
│   │   └── rules/
│   ├── database/
│   ├── demo/
│   ├── entities/
│   │   ├── battle/
│   │   ├── character/
│   │   ├── items/
│   │   └── map/
│   ├── views/
│   └── main.cpp
├── tests/                      # Testes unitários (doctest)
│   ├── controllers/
│   ├── core/
│   ├── database/
│   ├── entities/
│   │   ├── battle/
│   │   ├── character/
│   │   ├── items/
│   │   └── map/
│   └── views/
├── design/                     # Documentação de design
├── data/                       # Dados do jogo
├── docs/                       # Documentação gerada (Doxygen, cobertura)
├── Makefile
├── Doxyfile
└── README.md
```

---

## Licença

Projeto acadêmico - UFMG, DCC. Todos os direitos reservados aos autores.
