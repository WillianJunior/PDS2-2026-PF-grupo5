# Regras
*Dark Age - The Arcanum Quest*  
**Grupo 5**: RPG Turn-Based Game  
**Disciplina:** Programação e Desenvolvimento de Software II - UFMG  
**Semestre:** 2026/1  
**Turma:**  TF

---
## Controle de Revisões 

>| Rev. | Descrição | Elab. | Data |
>|:----:|:---------|:-----:|:---:|
>| 0 | Emissão Inicial | HVLO | 03/06/26 |
>| 1 | Adiciona trecho 2.5 Condições | HVLO | 03/06/26 |
>| 2 | Adiciona Controle de Revisões | HVLO | 07/06/26 |
>| 3 | Adiciona Seção 5 — Itens e Inventário | MFC | 09/06/26 |

## Sobre
> Este documento descreve todas as regras, mecânicas e sistemas do jogo.
> Serve como referência central para o grupo de desenvolvimento e como
> base para a implementação da classe `Regras`.
>
> *Inspirado no sistema D&D 5e, adaptado para combate solo e progressão até LV 10.*

---

## Índice

- [Regras](#regras)
  - [Controle de Revisões](#controle-de-revisões)
  - [Sobre](#sobre)
  - [Índice](#índice)
  - [1. Personagem](#1-personagem)
    - [1.1 Classes](#11-classes)
    - [1.2 Geração de Atributos](#12-geração-de-atributos)
    - [1.3 Distribuição por Classe](#13-distribuição-por-classe)
    - [1.4 Coeficientes](#14-coeficientes)
    - [1.5 O que cada Atributo faz](#15-o-que-cada-atributo-faz)
      - [Ataque](#ataque)
      - [Defesa](#defesa)
      - [Poder — PP (Pontos de Poder)](#poder--pp-pontos-de-poder)
      - [Agilidade](#agilidade)
  - [2. Sistema de Combate](#2-sistema-de-combate)
    - [2.1 Estrutura do Turno](#21-estrutura-do-turno)
    - [2.2 Ataque Simples](#22-ataque-simples)
    - [2.3 Ataque Rápido](#23-ataque-rápido)
    - [2.4 Ataque Forte](#24-ataque-forte)
      - [Guerreiro — Ataques Fortes](#guerreiro--ataques-fortes)
      - [Mago — Ataques Fortes](#mago--ataques-fortes)
      - [Arqueiro — Ataques Fortes](#arqueiro--ataques-fortes)
      - [Tank — Ataques Fortes](#tank--ataques-fortes)
    - [2.5 Condições](#25-condições)
      - [Descrição das Condições](#descrição-das-condições)
      - [Tabela Resumo](#tabela-resumo)
    - [2.6 Defender](#26-defender)
    - [2.7 Esquivar](#27-esquivar)
    - [2.8 Usar Item](#28-usar-item)
    - [2.9 Fugir](#29-fugir)
  - [3. Progressão](#3-progressão)
    - [3.1 Níveis e XP](#31-níveis-e-xp)
    - [3.2 Bônus de Proficiência](#32-bônus-de-proficiência)
  - [4. Dificuldade de Encontros](#4-dificuldade-de-encontros)
    - [4.1 Origem do Balanceamento](#41-origem-do-balanceamento)
    - [4.2 Limiares por Nível do Jogador](#42-limiares-por-nível-do-jogador)
    - [4.3 Tabela de ND e XP dos Inimigos](#43-tabela-de-nd-e-xp-dos-inimigos)
    - [4.4 Classificação do Confronto](#44-classificação-do-confronto)
    - [4.5 Casos Extremos](#45-casos-extremos)
      - [Trivial — Jogador muito acima do inimigo](#trivial--jogador-muito-acima-do-inimigo)
      - [Boss — Inimigo muito acima do jogador](#boss--inimigo-muito-acima-do-jogador)
      - [Impossível — Inimigo extremamente acima do jogador](#impossível--inimigo-extremamente-acima-do-jogador)
    - [4.6 Efeitos Mecânicos da Classificação](#46-efeitos-mecânicos-da-classificação)
    - [4.7 Referência de ND por Inimigo](#47-referência-de-nd-por-inimigo)
  - [5. Itens e Inventário](#5-itens-e-inventário)
    - [5.1 Inventário](#51-inventário)
    - [5.2 Comidas](#52-comidas)
      - [Frutas](#frutas)
      - [Carnes](#carnes)
      - [Cogumelos e ervas](#cogumelos-e-ervas)
    - [5.3 Poções](#53-poções)
      - [Predefinições de Poção](#predefinições-de-poção)
    - [5.4 Cristais](#54-cristais)
      - [Cristal de Agressão](#cristal-de-agressão)
      - [Cristal de Proteção](#cristal-de-proteção)
      - [Cristal de Veneno](#cristal-de-veneno)
      - [Cristal de Velocidade](#cristal-de-velocidade)
      - [Cristal de Drenagem](#cristal-de-drenagem)

---

## 1. Personagem

### 1.1 Classes

Todo jogador escolhe uma das quatro classes disponíveis. A classe define a
distribuição de atributos, o dado de vida, o estilo de combate e as opções de
Ataque Forte disponíveis ao longo da progressão.

| Classe | Dado de Vida | Perfil |
|---|---|---|
| **Guerreiro** | 1d10 | Alto dano, resistente, combate direto |
| **Mago** | 1d6 | Dano mágico elevado, baixa defesa, controle de PP |
| **Arqueiro** | 1d8 | Velocidade e precisão, ataques múltiplos |
| **Tank** | 1d12 | Máxima resistência, dano baseado em Defesa |

---

### 1.2 Geração de Atributos

Os atributos são gerados **antes da escolha de classe**, pelo método **4d6 — Descarte do Menor**, inspirado no D&D 5e.

**Como funciona:**
- Rolam-se **4 dados de 6 lados (4d6)**.
- O **menor valor é descartado**.
- Os 3 dados restantes são somados.
- Esse processo se repete **4 vezes**, gerando 4 valores.

**Exemplo:**

| Rolagem | Soma | Descartado | Resultado |
|---|---|---|---|
| 3, 2, 5, 3 | 13 | 2 | **11** |
| 4, 5, 6, 6 | 21 | 4 | **17** |
| 4, 6, 2, 2 | 14 | 2 | **12** |
| 6, 1, 6, 3 | 16 | 1 | **15** |

Os 4 valores são então **ordenados de forma decrescente** — no exemplo acima: `[17, 15, 12, 11]` — e exibidos ao jogador antes da escolha de classe.

---

### 1.3 Distribuição por Classe

Após a geração, os valores são distribuídos entre os atributos conforme a prioridade de cada classe. O 1º valor (maior) vai para o atributo de maior prioridade, e assim por diante.

| Classe | Ataque | Defesa | Agilidade | Poder |
|---|---|---|---|---|
| Guerreiro | **1º** | 2º | 3º | 4º |
| Arqueiro | 2º | 4º | **1º** | 3º |
| Tank | 2º | **1º** | 4º | 3º |
| Mago | 3º | 4º | 2º | **1º** |

**Exemplo prático com `[17, 15, 12, 11]`:**

| Classe | Ataque | Defesa | Agilidade | Poder |
|---|---|---|---|---|
| Guerreiro | 17 (1º) | 15 (2º) | 12 (3º) | 11 (4º) |
| Arqueiro | 15 (2º) | 11 (4º) | 17 (1º) | 12 (3º) |
| Tank | 15 (2º) | 17 (1º) | 11 (4º) | 12 (3º) |
| Mago | 12 (3º) | 11 (4º) | 15 (2º) | 17 (1º) |

> **Visibilidade ao jogador:** Na tela de criação, o jogador vê os valores gerados, os coeficientes resultantes e para qual atributo cada valor iria em cada classe — antes de confirmar a escolha.

---

### 1.4 Coeficientes

Cada valor de atributo gera um **coeficiente** usado nas mecânicas de combate e progressão.

$$y = 0{,}5x - 5$$

onde **x** é o valor do atributo e **y** é o coeficiente.

**Exemplo com o Mago `[17, 15, 12, 11]`:**

| Atributo | Valor | Cálculo | Coeficiente |
|---|---|---|---|
| Poder | 17 | 0,5 × 17 − 5 | **+3,5** |
| Agilidade | 15 | 0,5 × 15 − 5 | **+2,5** |
| Ataque | 12 | 0,5 × 12 − 5 | **+1,0** |
| Defesa | 11 | 0,5 × 11 − 5 | **+0,5** |

---

### 1.5 O que cada Atributo faz

####  Ataque

O coeficiente de Ataque é somado a toda **rolagem de acerto e dano**.

- **Acerto:** `1d20 + Coef. ATQ` (+ Bônus de Proficiência em ataques que consomem PP)
- Se o resultado for **maior** que a CD do inimigo → ataque acerta
- Se for **igual** à CD → **não** acerta
- Se acertar → rola o dado de dano conforme o tipo de ataque

> **Exemplo — Mago (Coef. ATQ = +1):**
> Rolagem de acerto: `1d20 + 1` → precisa superar a CD do inimigo.

---

####  Defesa

O coeficiente de Defesa determina o total de **Pontos de Vida (PV)**.

- **LV 1:** começa com o valor **máximo** do dado de vida + coef. Defesa
- **Novo nível:** soma `rolagem do dado de vida + coef. Defesa` ao PV total

| Classe | Dado de Vida |
|---|---|
| Tank | 1d12 |
| Guerreiro | 1d10 |
| Arqueiro | 1d8 |
| Mago | 1d6 |

> **Exemplo — Mago (Coef. DEF = +0,5):**
>
> | Nível | Cálculo | PV Acumulado |
> |---|---|---|
> | 1 | 6 (máx. 1d6) + 0,5 | **6,5** |
> | 2 | 6,5 + 1d6 (ex: 3) + 0,5 | **10,0** |
> | 3 | 10,0 + 1d6 (ex: 4) + 0,5 | **14,5** |

---

####  Poder — PP (Pontos de Poder)

O Poder define o total de **Pontos de Poder (PP)**, recurso gasto em habilidades e ataques especiais.

- **PP Total = Valor do atributo Poder × 5**
- Ataques que consomem PP somam o **Bônus de Proficiência** na rolagem de acerto
- Custos de PP são sempre **múltiplos de 5**

> **Exemplo — Mago (Poder = 17):** PP Total = 17 × 5 = **85 PP**

---

####  Agilidade

A Agilidade define **quem age primeiro** no turno e a **dificuldade de ser acertado**.

**Classe de Dificuldade (CD):**

$$CD = 10 + Coef.\,Agilidade$$

- O inimigo precisa **superar** (não apenas igualar) a CD para acertar
- Em empate de Agilidade na iniciativa → **o jogador age primeiro**

> **Exemplo — Mago (Coef. AGI = +2,5):** CD = 10 + 2,5 = **12,5**
> O inimigo precisa rolar **acima de 12,5** para acertar.

---

## 2. Sistema de Combate

### 2.1 Estrutura do Turno

O combate é **por turnos**. A ordem é definida pela Agilidade — age primeiro quem tiver o maior valor. Em caso de empate, o jogador age primeiro.

Em cada turno, o jogador escolhe **uma** das seguintes ações:

| Ação | Custo de PP | Descrição resumida |
|---|---|---|
| Ataque Simples | Nenhum | Ataque básico da classe, escala em quantidade por nível |
| Ataque Rápido | 10–15 PP | Age sempre antes do inimigo no turno; efeito secundário por classe |
| Ataque Forte | 20–50 PP | Alta potência; escolhido e trocado conforme progressão de nível |
| Defender | Nenhum | Reduz o dano recebido pelo coeficiente de Defesa |
| Esquivar | Nenhum | Soma o Bônus de Proficiência à própria CD neste turno |
| Usar Item | Nenhum | Utiliza um item do inventário |
| Fugir | Nenhum | Tenta abandonar o combate (bloqueado em confrontos Boss) |

---

### 2.2 Ataque Simples

Ataque básico da classe, sem custo de PP. O dado de dano e a quantidade de ataques por turno escalem com o nível.

> **Rolagem:** `dado(s) de dano + Coef. ATQ`
> **Acerto:** `1d20 + Coef. ATQ` vs CD do inimigo

**Resumo por classe:**

| Classe | Dado de Dano | LV 1–2 | LV 3–4 | LV 5–6 | LV 7–10 |
|---|---|---|---|---|---|
| Guerreiro | 1d8 | 1 ataque | 2 ataques | 2 ataques | 3 ataques |
| Arqueiro | 1d8 | 1 ataque | 1 ataque | 2 ataques | 3 ataques |
| Tank | 1d6 | 1 ataque | 1 ataque | 2 ataques | 3 ataques |
| Mago | — | 1d10 | 2d10 | 3d10 | 4d10 |

> O Mago não ganha ataques extras, mas o número de dados de dano cresce a cada faixa de nível. Feitiço é raro e poderoso — não um spam.

---

### 2.3 Ataque Rápido

Ataque veloz que **sempre age antes do inimigo no turno**, independentemente da ordem de iniciativa. Se o inimigo também usar um Ataque Rápido no mesmo turno, o jogador age primeiro.

> **Rolagem de acerto:** `1d20 + Coef. AGI + Bônus de Proficiência`
> (usa Agilidade, não Ataque — é um golpe baseado em velocidade)

**Resumo por classe:**

| Classe | Nome | Custo | Dado de Dano | Efeito |
|---|---|---|---|---|
| Guerreiro | Golpe Relâmpago | 15 PP | 2× (1d4 + Coef. ATQ) | 2º ataque reduz AGI do inimigo em 1 até o próximo turno |
| Mago | Projétil Arcano | 15 PP | 1d6 + Coef. ATQ | Não requer rolagem de acerto — sempre acerta |
| Arqueiro | Tiro Rápido | 10 PP | 2× (1d4 + Coef. ATQ) | Se ambos acertarem, o 2º causa dano dobrado |
| Tank | Investida | 15 PP | 1d6 + Coef. DEF | 50% de chance de fazer o inimigo perder o próximo turno de ataque |

> **Detalhe do Mago:** o Projétil Arcano ignora completamente a CD do inimigo — ideal para inimigos com defesa alta, mas o dano é propositalmente baixo para compensar.

---

### 2.4 Ataque Forte

Ataque de alta potência com custo em PP e um efeito especial único. Cada classe começa com uma opção no LV 1 e desbloqueia novas alternativas nos níveis 3, 5 e 7.

**Regras de troca:**
- Nos LVs 3, 5 e 7, ao ganhar o nível, o jogo pergunta: *"Deseja trocar seu Ataque Forte?"*
- O jogador vê os dois ataques em comparação (atual vs novo) e decide
- Não há obrigação de trocar — o jogador pode manter o mesmo para sempre

> O último ataque forte, desbloqueado no **LV 7**, é propositalmente mais poderoso e mais caro. Ele representa o pico de domínio da classe.

---

####  Guerreiro — Ataques Fortes

**Resumo:**

| Nome | Custo | Dado | LV | Efeito |
|---|---|---|---|---|
| Fúria Berserker | 30 PP | 3d6 + Coef. ATQ | 1 | Vantagem no acerto (2d20, maior); sofre 1d4 de dano |
| Golpe Devastador | 25 PP | 2d10 + Coef. ATQ | 3 | −2 Defesa do inimigo por 2 turnos |
| Perfuração | 25 PP | 2d8 + Coef. ATQ | 5 | Ignora o coef. Defesa do inimigo no dano |
| Golpe do Abismo | 45 PP | LV × d10 + Coef. ATQ | 7 | CD do jogador −3 por 1 turno; recupera 15 PP se matar |

**Detalhes:**

- **Fúria Berserker** — O guerreiro entra em estado de fúria total. Rola dois d20 de acerto e usa o maior (vantagem), mas se expõe completamente — sofre 1d4 de dano independentemente de acertar ou errar.

- **Golpe Devastador** — Um impacto pesado que compromete a armadura do inimigo, reduzindo seu coeficiente de Defesa em 2 por 2 turnos. Ótimo contra inimigos muito blindados.

- **Perfuração** — Um golpe preciso que atravessa toda armadura. O coeficiente de Defesa do inimigo é completamente ignorado no cálculo de dano — como se ele não tivesse proteção alguma.

- **Golpe do Abismo** — O guerreiro abandona qualquer postura defensiva e desfere tudo de uma vez. No LV 10: até 10d10 de dano potencial. Como custo, sua CD cai em 3 até o próximo turno. Se o ataque derrotar o inimigo, o guerreiro recupera 15 PP — recompensa por terminar a luta com estilo.

---

####  Mago — Ataques Fortes

**Resumo:**

| Nome | Custo | Dado | LV | Efeito |
|---|---|---|---|---|
| Bola de Fogo | 40 PP | 4d6 + Coef. ATQ | 1 | Dano em área — atinge todos os inimigos presentes |
| Raio | 35 PP | 2d10 + Coef. ATQ | 3 | 50% de chance de paralisar o inimigo por 1 turno |
| Dreno de Magia | 20 PP | 1d8 + Coef. ATQ | 5 | Rouba PP do inimigo e adiciona ao próprio PP |
| Vórtice Arcano | 50 PP | LV × d6 + Coef. ATQ | 7 | Ignora completamente o coef. Defesa do inimigo |

**Detalhes:**

- **Bola de Fogo** — Uma explosão mágica que afeta toda a área. Se houver múltiplos inimigos no encontro, todos recebem o dano completo. Contra um único alvo, funciona como dano normal.

- **Raio** — Um raio elétrico concentrado. Se acertar, há 50% de chance de o inimigo ser paralisado e perder completamente o próximo turno de ataque.

- **Dreno de Magia** — O feitiço mais econômico do Mago. O dano é baixo, mas o Mago drena PP do inimigo (se ele tiver) e adiciona ao próprio total. Contra inimigos sem PP, comporta-se como ataque simples.

- **Vórtice Arcano** — O Mago abre um colapso de energia mágica diretamente no inimigo, contornando qualquer barreira física. O coeficiente de Defesa do inimigo é completamente ignorado no dano. No LV 10: até 10d6, todos penetrando defesa. O custo de 50 PP é o maior do jogo para refletir isso.

---

####  Arqueiro — Ataques Fortes

**Resumo:**

| Nome | Custo | Dado | LV | Efeito |
|---|---|---|---|---|
| Flecha Explosiva | 30 PP | 2d8 + Coef. ATQ | 1 | −2 AGI do inimigo por 2 turnos |
| Tiro Certeiro | 35 PP | 2d10 + Coef. ATQ | 3 | Auto-acerto — ignora CD do inimigo |
| Saraivada | 40 PP | 5d4 + Coef. ATQ | 5 | Cada dado rola acerto individualmente |
| Tiro Final | 40 PP | LV × d6 + Coef. AGI | 7 | Auto-acerto — usa Coef. AGI no lugar de ATQ |

**Detalhes:**

- **Flecha Explosiva** — A flecha detona ao impactar, espalhando fogo nos pés do inimigo. Sua AGI é reduzida em 2 por 2 turnos, tornando-o mais lento e mais fácil de acertar.

- **Tiro Certeiro** — Um disparo calculado que não pode errar. Sem rolagem de acerto — a flecha ignora completamente a CD do inimigo. Ideal contra alvos com defesa ou esquiva muito alta.

- **Saraivada** — Uma chuva de flechas de alta variância. São 5 dados de dano, mas cada um requer uma rolagem de acerto separada. Pode ser devastador ou decepcionante — o risco faz parte da mecânica.

- **Tiro Final** — Uma única flecha disparada com precisão absoluta. Sem rolagem de acerto. Usa o coeficiente de **Agilidade** em vez de Ataque, pois é puro controle e timing, não força bruta. No LV 10: 10d6 garantidos.

---

####  Tank — Ataques Fortes

**Resumo:**

| Nome | Custo | Dado | LV | Efeito |
|---|---|---|---|---|
| Pancada de Escudo | 25 PP | 1d10 + Coef. DEF | 1 | Atordoa o inimigo — sem Ataque Rápido/Forte no próximo turno |
| Terremoto | 30 PP | 2d6 + Coef. DEF | 3 | −3 Defesa do inimigo por 3 turnos |
| Barreira de Espinhos | 30 PP | 1d8 + Coef. DEF | 5 | +3 CD até o próximo turno; inimigo devolve 1d6 se atacar |
| Martírio | 35 PP | LV × d8 + Coef. DEF | 7 | Sofre LV × 2 de dano antes de atacar |

**Detalhes:**

- **Pancada de Escudo** — O escudo é usado como arma de impacto. O dano usa o coeficiente de Defesa (não Ataque). Se acertar, o inimigo fica atordoado e não pode usar Ataque Rápido ou Ataque Forte no próximo turno.

- **Terremoto** — Um golpe pesado no chão que desequilibra o inimigo e fractura sua armadura. A Defesa do inimigo é reduzida em 3 por 3 turnos — o maior debuff de Defesa do jogo.

- **Barreira de Espinhos** — O Tank assume postura totalmente reativa. Ganha +3 na CD (fica quase intocável) e, se o inimigo atacar nesse turno, devolve automaticamente 1d6 de dano independentemente do resultado do ataque. Troca ofensiva por sobrevivência e punição.

- **Martírio** — O Tank abaixa o escudo e absorve o próximo impacto intencionalmente, usando a força do golpe para se impulsionar. Antes de atacar, sofre `LV × 2` de dano fixo em si mesmo (no LV 10: 20 de dano). Em compensação, no LV 10: até 10d8 usando Defesa como base — e o Tank tem o maior pool de PV do jogo para bancar esse trade.

---

### 2.5 Condições

Condições são efeitos aplicados a um personagem durante o combate — pelo jogador,
por um inimigo, ou como efeito colateral de um ataque. Toda condição altera ao menos
um dos campos mecânicos do personagem afetado e possui uma **duração em turnos**
definida por quem a aplicou.

Algumas condições são **genéricas**, ou seja, possuem um parâmetro de nome livre.
Mecanicamente são idênticas, mas podem aparecer na lore com nomes diferentes —
*Amaldiçoado*, *Corroído*, *Enfraquecido* são todos a mesma condição "Reduz Atributo"
com nomes distintos.

---

#### Descrição das Condições

**Berserk**
O personagem afetado entra em fúria descontrolada. A cada turno, sofre `1d4` de dano
fixo, independentemente de qualquer ação. Em compensação, todas as suas rolagens de
acerto passam a ter **vantagem** — rola 2d20 e usa o maior. Representa perda de
controle: bate melhor, mas se consome no processo.

---

**Modifica Atributo** *(condição genérica — nome personalizável)*
Um atributo específico do personagem afetado é modificado em X pontos pelo período da
condição, ou seja, o valor pode ser positivo (reduz o atributo) ou negativo (aumenta/boost).
Como todos os coeficientes derivam diretamente dos atributos, modificar um atributo
afeta em cascata tudo que depende dele: reduzir AGI baixa a CD, aumentar ATQ eleva o
dano, e assim por diante. Qual atributo e quanto modifica são definidos pela fonte que
aplicou a condição (ataque inimigo, poção, cristal, etc.).

> *Exemplos de redução com nome personalizado: "Amaldiçoado" (reduz ATQ), "Corroído"
> (reduz DEF), "Lentidão" (reduz AGI).*
> *Exemplos de boost: Poção de Força (+ATQ), Cristal de Proteção (+DEF).*

---

**100% de Acerto** *(condição genérica — nome personalizável)*
O atributo de AGI do personagem afetado é forçado a −10, tornando sua CD efetivamente
`10 + (0,5 × (−10) − 5) = 0`. O próximo ataque recebido conecta automaticamente — não
há como esquivar ou defender contra o acerto. O dano ainda é rolado normalmente.

> *Exemplos de uso com nome personalizado: "Vulnerável", "Exposto", "Marcado".*

---

**Paralisado**
O personagem afetado perde completamente a capacidade de agir. Durante X turnos,
nenhuma ação está disponível — sem ataque, defesa, esquiva, item ou fuga. O turno
simplesmente passa.

---

**Atordoado**
O personagem afetado tem sua capacidade de reação comprometida. No turno seguinte,
não pode usar **Ataque Rápido** nem **Ataque Forte**. Ações básicas — Ataque Simples,
Defender, Esquivar e Usar Item — continuam disponíveis.

---

**Envenenado** *(condição genérica — nome personalizável)*
O personagem afetado sofre `2d6` de dano no início de cada turno enquanto a condição
durar. Diferente de Berserk, não altera rolagens nem ações — apenas corrói
gradualmente. Pode ser usado para representar veneno, fogo, sangramento ou qualquer
efeito de dano contínuo.

> *Exemplos de uso com nome personalizado: "Sangrando", "Em Chamas", "Amaldiçoado".*

---

**Sem Condição**
O ataque não aplica nenhum efeito adicional além do dano. Nenhum campo do personagem
é alterado.

---

#### Tabela Resumo

| Condição | PV atual | PP atual | ATQ | DEF | AGI | Poder | Rolagem de acerto | Ações disponíveis |
|---|---|---|---|---|---|---|---|---|
| Berserk | −1d4/turno | — | — | — | — | — | Vantagem (2d20, melhor) | Todas |
| Modifica Atributo* | — | — | ±X ou — | ±X ou — | ±X ou — | ±X ou — | — | Todas |
| 100% de Acerto* | — | — | — | — | Força AGI = −10 | — | — | Todas |
| Paralisado | — | — | — | — | — | — | — | Nenhuma |
| Atordoado | — | — | — | — | — | — | — | Sem Atq. Rápido/Forte |
| Envenenado* | −2d6/turno | — | — | — | — | — | — | Todas |
| Sem Condição | — | — | — | — | — | — | — | Todas |

*\* Condição genérica com nome personalizável.*

---

### 2.6 Defender

O jogador opta por se proteger em vez de atacar. O dano recebido neste turno é **reduzido pelo coeficiente de Defesa**.

- `Dano recebido = Dano do inimigo − Coef. DEF`
- O dano mínimo é 0 (não gera cura)

---

### 2.7 Esquivar

O jogador tenta desviar do ataque inimigo. Neste turno, o **Bônus de Proficiência é somado à sua CD**.

- `CD temporária = CD normal + Bônus de Proficiência`
- O efeito dura apenas o turno em que a ação foi escolhida

---

### 2.8 Usar Item

O jogador gasta sua **ação do turno** para utilizar um item do inventário.
O efeito e as restrições dependem do tipo:

- **Comida** — efeito imediato em PV (positivo ou negativo). Pode ser usada a qualquer momento em batalha.
- **Poção** — bônus temporário a um atributo; a contagem de turnos começa imediatamente no turno do uso.
- **Cristal** — *não pode ser utilizado durante o combate.* Deve ser equipado fora de batalha.

Ver [Seção 5](#5-itens-e-inventário) para as regras completas de cada tipo.

---

### 2.9 Fugir

O jogador tenta abandonar o combate.

- Disponível em confrontos **Trivial**, **Fácil**, **Médio** e **Difícil**
- **Bloqueada** em confrontos classificados como **Boss** ou **Impossível**

---

## 3. Progressão

### 3.1 Níveis e XP

Todo personagem começa no **LV 1** e evolui até o **LV 10** acumulando XP ao vencer combates.

| Nível Atual | XP para avançar |
|---|---|
| 1° | 300 |
| 2° | 900 |
| 3° | 2.700 |
| 4° | 6.500 |
| 5° | 14.000 |
| 6° | 23.000 |
| 7° | 34.000 |
| 8° | 48.000 |
| 9° | 64.000 |
| 10° | — *(nível máximo)* |

---

### 3.2 Bônus de Proficiência

Valor somado a rolagens de acerto e dano em ataques que consomem PP. Habilidades de classe podem ter regras próprias de aplicação.

| Níveis | Bônus |
|---|---|
| 1° – 3° | +2 |
| 4° – 6° | +3 |
| 7° – 9° | +4 |
| 10° | +5 |

---

## 4. Dificuldade de Encontros

### 4.1 Origem do Balanceamento

O sistema é baseado nas tabelas do **Dungeon Master's Guide (D&D 5e)**, que define a dificuldade de um encontro pelo **Nível de Desafio (ND)** do inimigo — chamado de *Challenge Rating (CR)* no original.

No D&D original, as tabelas são calibradas para uma *party* de 4 jogadores. Neste jogo, o sistema foi **adaptado para combate solo**, com limiares proporcionalmente menores.

A diferença central da nossa adaptação: o ND dos inimigos é definido pelo **cenário**, não pelo nível do jogador. Um goblin continua sendo um goblin LV 10 adentro — o que muda é como o sistema classifica esse confronto para o jogador.

> *Fonte: D&D 5e Dungeon Master's Guide, Cap. 3 — "Creating Adventures", tabela "Encounter Difficulty"; e SRD 5.1, tabela "Experience Points by Challenge Rating".*

---

### 4.2 Limiares por Nível do Jogador

Para cada nível, existem quatro limiares de XP. O XP do inimigo (determinado pelo ND) é comparado a esses limiares para classificar o confronto.

| Nível | Fácil | Médio | Difícil | Boss |
|---|---|---|---|---|
| 1° | 25 | 50 | 75 | 100 |
| 2° | 50 | 100 | 150 | 200 |
| 3° | 75 | 150 | 225 | 400 |
| 4° | 125 | 250 | 375 | 500 |
| 5° | 250 | 500 | 750 | 1.100 |
| 6° | 300 | 600 | 900 | 1.400 |
| 7° | 350 | 750 | 1.100 | 1.700 |
| 8° | 450 | 900 | 1.400 | 2.100 |
| 9° | 550 | 1.100 | 1.600 | 2.400 |
| 10° | 600 | 1.200 | 1.900 | 2.800 |

---

### 4.3 Tabela de ND e XP dos Inimigos

| ND | XP | | ND | XP |
|---|---|---|---|---|
| 1/8 | 25 | | 11 | 7.200 |
| 1/4 | 50 | | 12 | 8.400 |
| 1/2 | 100 | | 13 | 10.000 |
| 1 | 200 | | 14 | 11.500 |
| 2 | 450 | | 15 | 13.000 |
| 3 | 700 | | 16 | 15.000 |
| 4 | 1.100 | | 17 | 18.000 |
| 5 | 1.800 | | 18 | 20.000 |
| 6 | 2.300 | | 19 | 22.000 |
| 7 | 2.900 | | 20 | 25.000 |
| 8 | 3.900 | | | |
| 9 | 5.000 | | | |
| 10 | 5.900 | | | |

> NDs acima de 10 constam como referência. O ND máximo prático para este jogo (LV 1–10, solo) é em torno de ND 9–10, reservado ao boss final.

---

### 4.4 Classificação do Confronto

**Fluxo:**
```
ND do inimigo → XP do inimigo → compara com limiares do LV do jogador → classificação
```

| Condição | Classificação |
|---|---|
| XP < limiar Fácil | **Trivial** |
| limiar Fácil ≤ XP < limiar Médio | **Fácil** |
| limiar Médio ≤ XP < limiar Difícil | **Médio** |
| limiar Difícil ≤ XP < limiar Boss | **Difícil** |
| XP ≥ limiar Boss | **Boss** |

**Exemplo — inimigo ND 2 (450 XP), três perspectivas:**

| Jogador | Limiares | Resultado |
|---|---|---|
| LV 3 | Fácil=75 / Boss=400 | 450 ≥ 400 → **Boss** |
| LV 5 | Fácil=250 / Médio=500 | 250 ≤ 450 < 500 → **Médio** |
| LV 8 | Fácil=450 / Médio=900 | 450 = 450 → **Fácil** |

*O inimigo não muda. O que muda é a perspectiva do jogador.*

---

### 4.5 Casos Extremos

#### Trivial — Jogador muito acima do inimigo

O combate ocorre normalmente, mas o XP ganho é **reduzido proporcionalmente** para desestimular o farming de inimigos fracos.

$$XP\,ganho = XP_{base} \times \frac{XP_{base}}{Limiar\,Fácil\,do\,jogador}$$

> **Exemplo:** Jogador LV 6 (limiar Fácil = 300) vs ND 1/8 (25 XP):
> `25 × (25 / 300) ≈ 2 XP`

Mensagem exibida ao jogador: *"Este inimigo é muito fraco. Você ganhará pouquíssimo XP."*

---

#### Boss — Inimigo muito acima do jogador

A opção **Fugir fica bloqueada** — o inimigo não deixa escapar.

Mensagem exibida ao iniciar o combate: *"Um inimigo poderoso barra o seu caminho! A fuga não é possível."*

---

#### Impossível — Inimigo extremamente acima do jogador

Caso especial de Boss: XP do inimigo é o **dobro ou mais** do limiar Boss.

> **Exemplo:** LV 1 (limiar Boss = 100) vs ND 4 (1.100 XP) → Impossível

O jogador recebe um **aviso antes do combate iniciar**, com a opção de recuar. É a única janela de fuga disponível.

Mensagem: *"Este inimigo está muito além das suas capacidades. Deseja continuar mesmo assim?"*

---

### 4.6 Efeitos Mecânicos da Classificação

| Classificação | XP ganho | Fugir | Mensagem ao jogador |
|---|---|---|---|
| Trivial | Reduzido (proporcional) | Sempre disponível | *"Inimigo muito fraco — pouco XP"* |
| Fácil | 100% do XP base | Sempre disponível | — |
| Médio | 100% do XP base | Sempre disponível | — |
| Difícil | 100% do XP base | Disponível | *"Confronto difícil — cuidado"* |
| Boss | 100% do XP base | **Bloqueada** | *"Um inimigo poderoso barra seu caminho!"* |
| Impossível | 100% do XP base | Apenas antes de iniciar | *"Está além das suas capacidades"* |

---

### 4.7 Referência de ND por Inimigo

Sugestão de ND para os inimigos do jogo, compatíveis com o sistema LV 1–10 solo:

| ND | XP | Exemplos |
|---|---|---|
| 1/8 | 25 | Goblin, Rato Gigante, Esqueleto básico |
| 1/4 | 50 | Kobold, Zumbi, Lobo |
| 1/2 | 100 | Orc, Hobgoblin, Gnoll |
| 1 | 200 | Bugbear, Gnoll Líder, Lobisomem |
| 2 | 450 | Ogro, Sacerdote das Sombras |
| 3 | 700 | Vampiro servo, Cavaleiro Negro |
| 4 | 1.100 | Múmia, Medusa, Arcanista das Trevas |
| 5 | 1.800 | Troll, Demônio menor |
| 6 | 2.300 | Gigante das Colinas, Senhor das Sombras |
| 7 | 2.900 | Mini-boss de dungeon |
| 8 | 3.900 | Boss intermediário |
| 9–10 | 5.000–5.900 | Boss final / Sonath |

---

## 5. Itens e Inventário

Durante o jogo, o player terá à sua disposição um inventário limitado para armazenar itens encontrados nas cenas. As regras de uso e armazenamento desses itens, bem como suas categorias e efeitos, serão detalhados a seguir.

---

### 5.1 Inventário

O inventário representa um espaço onde o jogador pode armazenar consigo determinada quantidade de itens. Ele possui **8 slots de armazenamento** e **1 ou 2 slots de equipamento**, reservados exclusivamente para Cristais (seção 5.4).

**Slots de armazenamento**: Compreendem os itens ainda não utilizados, incluindo cristais ainda não eqiupados. Qualquer item pode ser **descartado manualmente** a qualquer momento fora de batalha. Cada item ocupa exatamente 1 slot no inventário, ou seja, itens iguais não são empilháveis. Ao usar um item, ele é automaticamente removido do inventário.

**Slots de equipamento**: Esses slots permitem equipar determinado número de cristais. Até o nível 5, o jogador poderá equipar apenas 1 cristal por vez. A partir do nível 6, poderá equipar até 2 cristais simultaneamente. 

Os cristais equipados saem do armazenamento e ocupam um slot de equipamento dedicado,
ficando ativos a partir do próximo combate. Um cristal desequipado é automaticamente transferido de volta para o armazenamento, liberando o slot de equipamento. Se não houver slot de armazenamento disponível, o cristal desequipado é descartado.

O personagem só pode **equipar ou desequipar um cristal fora de batalha**.
Ao fim de cada cena, todos os cristais (equipados ou não) são automaticamente removidos do slot de equipamento, independentemente de terem sido usados.

Em resumo: 

| Nível | Slots de armazenamento | Slots de equipamento (Cristal) |
|---|---|---|
| LV 1 – LV 5 | 8 | 1 |
| LV 6 – LV 10 | 8 | 2 |


> **Exemplo:** Um personagem LV 3 encontra dois cristais durante a exploração. 
> Ambos ocupam slots normais. Ele equipa um deles — o cristal sai do armazenamento e vai
> para o slot dedicado, liberando um slot normal. O segundo cristal permanece na
> bolsa. Ao fim da cena, o Cristal equipado é removido automaticamente; o Cristal na bolsa permanece até ser usado, equipado ou descartado.

---

### 5.2 Comidas

Comidas têm **efeito imediato sobre os PV** do personagem:
- Positivo (cura), ou
- Negativo (dano). 

Podem ser usadas em batalha, consumindo a ação do turno, ou fora dela, sem custo de ação.

A cura nunca ultrapassa o limite máximo de PV do personagem. O dano de uma comida
negativa, entretanto, é aplicado integralmente e pode levar o personagem a 0 PV. O resultado final do uso de uma comida é calculado pela fórmula:

$$PV\,resultante = clamp(PV\,atual + efeito,\;0,\;PV\,máximo)$$

As comidas, no geral, seguem a mesma estrutura, mas são **temáticas de cada cena**. É possível diferenciar uma comida boa de uma ruim a partir de sua descrição. As predefinições abaixo descrevem as categorias existentes:

---

#### Frutas
Alimento abundante nas cenas. Frutas benignas oferecem uma **cura leve**, enquanto frutas deterioradas ou venenosas causam dano equivalente. São o tipo de comida mais comum nas cenas iniciais.

| Variação | Efeito base |
|---|---|
| Fruta fresca | +1d6 PV |
| Fruta podre / venenosa | −1d6 PV |


#### Carnes
Alimento substancial de alto valor nutritivo. Carnes bem preparadas oferecem **cura elevada**, enquanto carnes cruas ou estragadas causam mal-estar severo. São menos comuns e aparecem sobretudo em cenas de combate mais avançadas.

| Variação | Efeito base |
|---|---|
| Carne preparada | +2d6 PV |
| Carne crua / estragada | −2d6 PV |


#### Cogumelos e ervas
Categoria de maior diversidade. Cogumelos e ervas medicinais oferecem **cura alta e confiável**, mas seus equivalentes tóxicos são os alimentos mais perigosos do jogo, causando danos substanciais ao jogador.Identificar a diferença faz parte da progressão temática de certas cenas.

| Variação | Efeito base |
|---|---|
| Cogumelo medicinal | +2d8 PV |
| Cogumelo tóxico | −2d8 PV |


---

### 5.3 Poções

Poções concedem um **bônus temporário a um único atributo** durante um número fixo
de turnos de batalha. Podem ser usadas a qualquer momento, isto é, em batalha,consumindo a ação do turno, ou fora dela,sem custo de ação. Caso uma poção seja usada fora de batalha, o bônus entra em vigor no próximo combate, e a duração começa a contar a partir do primeiro turno desse combate.

Ao expirar, o atributo retorna ao valor original, sem nenhuma penalidade adicional.

**Regra de reaplicação:** usar a mesma poção enquanto o efeito ainda estiver ativo
**não acumula o bônus**, apenas **reinicia a contagem** de turnos para a duração
normal. Não é possível empilhar duas instâncias do mesmo bônus.

---

#### Predefinições de Poção

Há exatamente uma poção por atributo. Cada poção define um bônus fixo e uma duração
fixa, sem variações por nível.

| Poção | Atributo | Bônus | Duração |
|---|---|---|---|
| Poção de Força | Ataque | +4 | 3 turnos |
| Poção de Resistência | Defesa | +4 | 4 turnos |
| Poção de Velocidade | Agilidade | +4 | 3 turnos |
| Poção de Mana | Poder | +4 | 4 turnos |

**Efeito derivado do bônus de atributo:**
Como os coeficientes derivam diretamente dos atributos (Coef. = 0,5 × atributo − 5),
um bônus de +4 no atributo representa um ganho de **+2 no coeficiente** durante a
duração da poção. Isso afeta em cascata tudo que depende daquele atributo:

- **Força** → +2 em todas as rolagens de acerto e dano do personagem
- **Resistência** → +2 no cálculo de PV ganho por nível *(sem efeito retroativo
  no PV atual; apenas nos ganhos futuros durante o combate onde o nível é atingido, se aplicável)*
- **Velocidade** → +2 na CD do personagem, tornando-o mais difícil de acertar, e
  +2 na iniciativa
- **Mana** → +2 PP por ponto de Poder (equivalente a +20 PP) durante os turnos
  ativos; os PP são revertidos ao expirar a poção

> **Exemplo — Poção de Velocidade (Coef. AGI = +2,5):**
> Com a poção ativa: Coef. AGI temporário = +4,5 → CD temporária = 10 + 4,5 = **14,5**
> O inimigo precisa superar 14,5 para acertar, em vez dos 12,5 normais.

---

### 5.4 Cristais

Cristais são itens de equipamento que ativam efeitos especiais de combate, muitas
vezes ligados à lore de cada cena. Ao contrário de comidas e poções, **não são
consumidos ao usar** — permanecem equipados durante toda a cena e são removidos
automaticamente ao fim dela. Os cristais são itens raros, podendo ser encontrados nas cenas ou recebidos como recompensa ao vencer uma batalha. 

**Regras de uso:**
- Cristais só podem ser **equipados ou desequipados fora de batalha**
- O efeito entra em vigor **a partir do próximo combate** após o equipamento
- Ao fim de cada cena, todos os Cristais equipados são removidos automaticamente
  (ver 5.1)
- Cristais não equipados permanecem no inventário normalmente

**Limite de cristais equipados:**

| Nível | Cristais simultâneos |
|---|---|
| LV 1 – LV 5 | 1 |
| LV 6 – LV 10 | 2 |

A partir do LV 6, o personagem pode equipar **dois Cristais simultaneamente**. Se os efeitos dos dois Cristais afetarem os mesmos atributos ou condições, ambos se aplicam normalmente, exceto nos casos em que a regra de reaplicação de condição impeça duplicação (ver Seção 5.3 e Seção 2.5).

---

Assim como as comidas, os cristais seguem predefinições gerais e são **temáticos por cena**. As definições abaixo definem as categorias canônicas de efeito. Cada cena pode instanciar variações com nomes e flavour próprios, desde que o efeito mecânico pertença a uma dessas categorias.


#### Cristal de Agressão
Ao iniciar a batalha, o portador entra no estado **Berserk** por 3 turnos — rolagens de acerto com vantagem (2d20, melhor), ao custo de 1d4 de dano sofrido por turno. Ideal para personagens com alto Ataque que priorizam encerrar combates rapidamente. Evoca poderes destrutivos e caóticos.


#### Cristal de Proteção
Enquanto equipado, o personagem ganha **+5 na Classe de Dificuldade** durante todos os combates da cena. Nenhuma rolagem adicional é necessária — o bônus é permanente enquanto o Cristal estiver ativo. Favorece Tanks e personagens com Defesa priorizada. Evoca poderes de resistência e vida.


#### Cristal de Veneno
O primeiro ataque bem-sucedido do portador em cada combate aplica a condição
**Envenenado** no alvo por 3 turnos (−2d6 por turno, no início do turno do inimigo). O efeito se reinicia a cada novo combate da cena. Evoca poderes da natureza e decadência.

---

#### Cristal de Velocidade
Ao iniciar cada combate da cena, o portador recebe **+3 na iniciativa** e **+2 na CD** durante os 2 primeiros turnos. Representa um surto de agilidade sobrenatural na abertura do confronto. Evoca poderes do vento e do tempo.

---

#### Cristal de Drenagem
Ao fim de cada turno em que o portador acertar pelo menos um ataque, ele recupera
**1d4 PV**. A cura não ultrapassa o limite máximo de PV. Evoca poderes obscuros de
absorção vital — frequente em cenas ligadas à morte e ao submundo.

---

*Documento desenvolvido para o projeto PDS II — Grupo 5*
*Referências: D&D 5e Dungeon Master's Guide (DMG) + System Reference Document (SRD) 5.1*
