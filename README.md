## Gupo 5: RPG Turn-Based Game
## The Dark Age — The Dark Age - The Arcanum Quest

**Disciplina:** Programação e Desenvolvimento de Software II — UFMG  
**Semestre:** 2026/1 
**Turma:**  TF
---
##Integrantes do Grupo

| Nome | Matrícula |
|------|-----------|
| Matheus [Sobrenome] | 2023066543 |
| Mariana Ferreira de Castro | 2025019658 |
| Laura Silveira | 2025075060 |
| Henrique Viana | 2025102628 |

## Descrição do Projeto

*The Dark Age - The Arcanum Quest* é um jogo de RPG baseado em turnos ambientado em um universo original inspirado em uma campanha real de Dungeons & Dragons, mestrada pelo aluno Henrique Viana e jogada/ vivenciada pelos alunos Matheus, Mariana e Laura. Como na campanha original jogador assume o controle de um herói e deve escolher dentre as seguintes classes: Guerreiro, Mago, Arqueiro ou Tank, e sobre as ordens de Ruffen, deve percorrer seis regiões distintas do mundo, cada uma dominada por um poderoso boss aliado ao antagonista Sonath. O objetivo narrativo principal é reunir os Arcanos para enfrentar o boss final, Sonath, avançando por cenas e desafios que alteram o ritmo e a estratégia do jogador.

## Motivação

A motivação para o desenvolvimento deste jogo nasce da experiência vivida pelos integrantes do grupo em sessões reais de RPG de mesa: os personagens, a lore e os eventos do jogo têm origem em uma campanha autêntica, o que torna o projeto tanto um exercício técnico quanto uma forma criativa de preservar e expandir uma história coletiva. Do ponto de vista técnico, o projeto foi pensado para aplicar conceitos de Programação Orientada a Objetos, modularização e separação entre lógica de jogo e interface, permitindo evolução tanto para execução em terminal quanto para interface gráfica. A estrutura inicial do repositório já prevê diretórios específicos para contratos, implementação, testes, documentação e dados.

---

## Objetivos
Desenvolver um motor de RPG em turnos capaz de representar personagens, classes, batalhas, inventário, itens, cenas e progressão de nível de forma organizada e extensível. O sistema deve permitir que o jogador explore o mapa, vasculhe ambientes, interaja com NPCs, participe de batalhas e utilize itens para alterar atributos e influenciar o resultado das lutas.

 - Funcionalidades previstas
 - Escolha de classe no início do jogo.
 - Sistema de exploração com ações como andar e vasculhar.
 - Inventário com capacidade limitada.
 - Batalha em turnos com ações ofensivas e defensivas.
 - Uso de comidas, poções e cristais.
 - Sistema de experiência e subida de nível.
 - Estrutura preparada para cenas, trechos de mapa e bosses.

 ---

## Visão Geral do Jogo

### Classes de Personagem
| Classe | Arma | Característica |
|--------|------|----------------|
| Guerreiro | Espada | Alta resistência física |
| Mago | Magia | Uso ampliado de habilidades mágicas |
| Arqueiro | Arco | Alta agilidade e ataques à distância |
| Escudeiro | Escudo | Bloqueio e redução de dano |

### Atributos
Cada personagem possui: **vida**, **PP/mana**, **ataque**, **defesa**, **agilidade**, **XP** e **nível**.

### Itens (Inventário — máx. 8 slots)
- **Comidas** — alteram pontos de vida (ex.: Lichia aumenta, Pera reduz)
- **Poções** — aumentam atributos temporariamente (duram 1 a 4 turnos)
- **Cristais** — efeitos únicos; removidos ao mudar de cena

### Arcanos (Poderes dos Deuses)
| Arcano | Deus | Efeito |
|--------|--------|--------|
| Poder do Caos | Asmodeus | Parte do dano causado é convertido em vida |
| Poder da Alma | Talos | Amplifica a energia espiritual do portador, aumentando ganho de XP e resistência contra efeitos mentais |
| Poder da Natureza | Eldath | Aumenta a chance de encontrar recursos raros, itens naturais e criaturas amistosas |
| Poder da Vida | Lathander | Cura recebida e regeneração natural são significativamente aumentadas |
| Poder dos Elementos | Glaron (Bahamut e Tiamat) | Fortalece ataques físicos e elementais, aumentando dano e resistência elemental |
| Poder da Mente | Azuth | Expande o uso de habilidades mágicas, reduzindo custo de mana e aumentando controle arcano |


### Sistema de Batalha
Batalhas são por turnos — age primeiro quem tem maior **agilidade**. Em cada turno o jogador pode: **atacar** (simples, rápido ou forte), **defender**, **esquivar**, **usar item** ou **fugir** (quando disponível).

---

##  Licença

Projeto acadêmico — UFMG, DCC. Todos os direitos reservados aos autores.

