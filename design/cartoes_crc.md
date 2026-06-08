# Cartões CRC
*Dark Age - The Arcanum Quest*  
**Grupo 5**: RPG Turn-Based Game  
**Disciplina:** Programação e Desenvolvimento de Software II - UFMG  
**Semestre:** 2026/1  
**Turma:**  TF

>---
>## Controle de Revisões 
>| Rev. | Descrição | Elab. | Data |
>|:----:|:---------|:-----:|:---:|
>| 0 | Emissão Inicial | MME | 27/04/26 |
>| 1 | Adiciona Inventário e Cena | LSBP | 28/04/26 |
>| 2 | Adiciona TrechoMapa e Batalha e alteralção na formatação | MFC | 28/04/26 |
>| 3 | Atualização em Batalha | MFC | 07/05/26 |
>| 4 | Hierarquia de classes regras, Classe utilitária Dados,Padrão MVC e Redistribuição de responsabilidade | HVLO | 07/06/26 |
>| | | | |

## Entidades do Jogo

### Classe Personagem

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Nome | - |
| | Ataque | Item (modifica o atributo) |
| | Defesa | Item (modifica o atributo) |
| | Vida Atual | Item (modifica o atributo) |
| | Vida Total | - |
| | PP Atual (Mana) | Item (modifica o atributo) |
| | PP Total (Mana) | - |
| | Agilidade | Item (modifica o atributo) |
| | Nível | - |
| | XP | - |
| | TipoPersonagem (NPC, Boss, Inimigo, Jogador) | - |
| | ClassePersonagem | ClassePersonagem |
| | Condições ativas (lista de condições em vigor) | - |
| **Realização** | receberDano() | - |
| | atualizarVida() | RegrasPersonagem |
| | atualizarMana() | - |
| | ganharExperiencia() | RegrasProgresso |
| | subirNivel() | RegrasProgresso, RegrasPersonagem |
| | aplicarCondicao() | - |
| | removerCondicao() | - |
| | obterInformacoes() | - |
| | estaVivo() | - |

**Nota:** A classe deve criar e manter a identidade de cada indivíduo de uma cena. O cálculo de PV por nível, coeficientes e progressão é delegado às classes de Regras correspondentes.

---

### Classe ClassePersonagem

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | NomeDeClasse | - |
| | DescriçãoDeClasse | - |
| | TipoDeArma | - |
| | DadoDeVida (d6, d8, d10 ou d12) | - |
| | PP Total (Mana) | - |
| | Lista de Ataques: Nome | - |
| | Lista de Ataques: Descrição | - |
| | Lista de Ataques: CustoPP | - |
| | Lista de Ataques: Condição aplicada | - |
| | AtaqueForteAtivo (qual o forte escolhido) | - |
| **Realização** | definirAtaquesDisponiveis() | RegrasClassePersonagem |
| | calcularDano() | RegrasAtaque, Dados |
| | trocarAtaqueForte() | RegrasAtaque |
| | fornecerDadosAtaque() | Personagem, Batalha |

---

### Classe Item

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | nome | - |
| | descricao | - |
| | categoria (pocao, alimento, cristal) | Inventario |
| | efeito (aumentar ataque, recuperar vida, etc.) | Personagem |
| **Realização** | aplicarEfeito() | Personagem, Batalha |

---

### Classe Inventário

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Itens e suas características | Item, Personagem, Batalha, Cena |
| | Capacidade máxima do inventário | - |
| | Quantidade atual de itens armazenados | Item, Batalha |
| **Realização** | salvarItem() | Item |
| | utilizarItem() | Item |
| | excluirItem() | - |
| | listarItens() | - |
| | verificarEspacos() | - |
| | fecharInventario() | - |

---

### Classe Cena

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Nível da cena | - |
| | Personagens (Player e NPCs) | Personagem, ClassePersonagem |
| | Itens e Inventário | Item, Inventario |
| | Trechos de mapa (quais e quantos existem) | TrechoMapa |
| | Recompensa entregue (flag) | - |
| **Realização** | inicializarCena() | - |
| | finalizarCena() | - |
| | verificarContinuidade() | - |
| | andar() | TrechoMapa |
| | vasculhar() | Item, Inventario |
| | interagirComNPC() | Personagem, ClassePersonagem |
| | abrirInventario() | Inventario |
| | iniciarBatalha() | Batalha |

---

### Classe TrechoMapa

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Id | - |
| | Cena (a qual cena o trecho pertence) | Cena |
| | Descricao (características do trecho, flavor) | - |
| | Itens (lista de itens presentes) | Item |
| | NPC (lista de NPCs presentes) | Personagem, ClassePersonagem |
| | ND do trecho (Nível de Desafio dos inimigos) | RegrasBatalha |
| | Coordenadas (localização do trecho) | - |
| **Realização** | abrirTrecho() | Cena, Item, Personagem, ClassePersonagem |
| | classificarDificuldade() | RegrasBatalha |

**Notas:**
- O atributo `coordenadas` só faz sentido caso seja implementada interface gráfica.
- O ND do trecho é fixo por cenário e independe do nível do jogador.
- `classificarDificuldade()` delega para `RegrasBatalha` usando o ND do trecho e o nível do jogador.

---

### Classe Batalha

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Player | Personagem |
| | Inimigo | Personagem |
| | Turno (em qual turno a batalha está) | - |
| | Acoes disponíveis por turno | - |
| | FatorDificuldade (classificação do confronto) | RegrasBatalha |
| | ProgressoBatalha | - |
| **Realização** | iniciarBatalha() | Cena, Personagem, ClassePersonagem, RegrasBatalha |
| | realizarAcao() | Personagem, ClassePersonagem, RegrasAtaque, Dados |
| | processarEsquiva() | Personagem, RegrasBatalha |
| | processarDefesa() | Personagem, RegrasBatalha |
| | aplicarCondicao() | Personagem |
| | processarCondicoesAtivas() | Personagem, Dados |
| | finalizarBatalha() | Cena, Personagem, RegrasProgresso |
| | definirRecompensa() | Cena, Personagem, RegrasBatalha, RegrasProgresso |
| | verificarFuga() | RegrasBatalha |

**Notas:**
- Toda lógica de limiares de dificuldade, XP ganho e bloqueio de fuga é delegada a `RegrasBatalha`.
- Toda lógica de cálculo de dano e acerto é delegada a `RegrasAtaque` e `ClassePersonagem`.
- `Dados` é injetado via construtor para permitir testes determinísticos.

---

## Utilitários

---

### Classe Dados

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Semente do gerador (RNG interno) | - |
| **Realização** | d4() | - |
| | d6() | - |
| | d8() | - |
| | d10() | - |
| | d12() | - |
| | d20() | - |
| | rolar(quantidade, lados) | - |
| | rolar4d6() — descarta o menor | - |
| | gerarAtributos() — 4× rolar4d6, ordem decrescente | - |
| | d20Vantagem() — 2d20, retorna o maior | - |
| | d20Desvantagem() — 2d20, retorna o menor | - |

**Nota:** Classe utilitária pura, sem dependências externas. Aceita semente fixa no construtor para testes TDD determinísticos. Deve ser injetada por quem precisar de aleatoriedade, `Batalha`, `ClassePersonagem`, criação de personagem.

---

## Hierarquia de Regras

> Classes de Regras são separadas por tema,
> com uma classe pai `Regras` que centraliza os métodos compartilhados por todas as filhas.
> Quando houver duplicação entre filhas, o método sobe para a pai.

---

### Classe Regras *(pai abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | - | - |
| **Realização** | calcularCoeficiente(valorAtributo) → y = 0,5x − 5 | - |
| | bonusProficiencia(nivel) → lookup tabela | - |
| | xpParaProximoNivel(nivel) → lookup tabela | - |

**Nota:** Disponibiliza como `static protected` os três métodos que todas as filhas utilizam: fórmula de coeficiente, bônus de proficiência e XP por nível. Nenhuma filha reimplementa esses cálculos.

---

### Classe RegrasAtaque *(filha de Regras)*

> Responsável por: Matheus

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Definições dos ataques simples por classe (dado, escala por nível) | - |
| | Definições dos ataques rápidos por classe (custo PP, efeito) | - |
| | Definições dos ataques fortes por classe (custo PP, dado, nível de desbloqueio, condição) | - |
| **Realização** | calcularDanoSimples(classe, nivel, dados) | Dados |
| | calcularDanoRapido(classe, dados) | Dados |
| | calcularDanoForte(nomeAtaque, nivel, dados) | Dados |
| | calcularRolagemAcerto(coefAtaque, nivel, gastaPP, vantagem) | Dados, Regras |
| | obterCondicaoAtaque(nomeAtaque) | - |
| | getAtaquesFortesDisponiveis(classe, nivel) | - |

---

### Classe RegrasClassePersonagem *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Dados de cada classe (dado de vida, prioridade de atributos, PP base) | - |
| | Tabela de distribuição de atributos por classe (1º→ATQ, etc.) | - |
| **Realização** | distribuirAtributos(classe, valoresRolados) → mapa atributo:valor | - |
| | calcularPPTotal(valorPoder) | - |
| | calcularVidaInicial(classe, coefDefesa) | - |
| | calcularVidaNovoNivel(classe, coefDefesa, dados) | Dados |
| | getDadoVida(classe) | - |

---

### Classe RegrasBatalha *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Tabela de limiares de dificuldade por nível (Fácil/Médio/Difícil/Boss) | - |
| | Tabela de XP por ND de inimigo | - |
| **Realização** | classificarConfronto(lvJogador, ndInimigo) → Trivial/Fácil/.../Boss | - |
| | calcularXPGanho(ndInimigo, lvJogador) | Regras |
| | fugirDisponivel(lvJogador, ndInimigo) | - |
| | calcularCD(coefAgilidade) → 10 + coef | - |
| | processarDefesa(coefDefesa, ataqueInimigo) → dano resultante | - |
| | processarEsquiva(coefAgilidade, ataqueInimigo) → dano resultante | - |

---

### Classe RegrasProgresso *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Tabela de XP necessário por nível (LV 1–10) | - |
| | Tabela de bônus de proficiência por nível | - |
| **Realização** | verificarUpNivel(xpAtual, nivelAtual) → bool | Regras |
| | getBonusProficiencia(nivel) | Regras |
| | getXPParaProximoNivel(nivel) | Regras |

---

### Classe RegrasPersonagem *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | - | - |
| **Realização** | calcularCoeficiente(valorAtributo) → y = 0,5x − 5 | Regras |
| | calcularCD(valorAgilidade) → 10 + coef | - |
| | calcularPPTotal(valorPoder) → valor × 5 | - |
| | calcularVidaInicial(classe, valorDefesa) | RegrasClassePersonagem |
| | calcularVidaNovoNivel(classe, valorDefesa, dados) | RegrasClassePersonagem, Dados |

---

## Padrão MVC — View e Controller

---

### Interface IView *(abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | exibirRolagem(atributos) | - |
| | exibirEscolhaClasse() | - |
| | confirmarPersonagem(personagem) | Personagem |
| | exibirEstadoBatalha(player, inimigo, turno) | Personagem |
| | exibirAcoesDisponiveis(acoes) | - |
| | exibirResultadoAcao(descricao) | - |
| | exibirCondicao(condicao, alvo) | - |
| | exibirFimBatalha(vitoria, xpGanho) | - |
| | exibirCena(cena) | Cena |
| | exibirMensagem(msg) | - |
| | exibirMenu(titulo, opcoes) | - |

**Nota:** Interface pura (todos os métodos virtuais puros). Implementações concretas:
- `TerminalView` — renderiza no `stdout`
- `GraphicsView` — renderiza via biblioteca gráfica (ex: SFML)

Trocar a implementação = trocar **uma linha** no `main.cpp`. Nenhuma outra classe precisa ser alterada.

---

### Interface IController *(abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | capturarEscolha(min, max) → int | - |
| | capturarTexto() → string | - |
| | aguardarConfirmacao() | - |

**Nota:** Interface pura. Implementação concreta: `InputController` (lê do `cin` no terminal; captura eventos de teclado/clique na versão gráfica).

---

## Alterações Necessárias nas Classes Já Existentes

> Esta seção descreve o que precisa ser modificado em cada classe que já foi (ou está sendo) implementada para se alinhar com a nova arquitetura: classes de Regras, classe Dados e padrão MVC.
> Nada aqui quebra o que já foi feito, são adições e delegações.

---

### Batalha

**Arquivo:** `include/entities/battle/Batalha.hpp` + `src/entities/battle/Batalha.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Construtor não recebe `Dados` | Adicionar `Dados& dados` (ou `Dados* dados`) como parâmetro do construtor |
| Construtor não recebe `IView` / `IController` | Adicionar `IView* view` e `IController* controller` como parâmetros |
| Lógica de `processarDefesa()` inline | Delegar o cálculo para `RegrasBatalha::processarDefesa()` |
| Lógica de `processarEsquiva()` inline | Delegar o cálculo para `RegrasBatalha::processarEsquiva()` |
| `realizarAcao()` calcula dano internamente | Delegar para `ClassePersonagem::calcularDano()` → `RegrasAtaque` |
| `definirRecompensa()` calcula XP internamente | Delegar para `RegrasBatalha::calcularXPGanho()` e `RegrasProgresso` |
| Não existe verificação de fuga | Adicionar `verificarFuga()` chamando `RegrasBatalha::fugirDisponivel()` |
| Não existe lógica de condições | Adicionar `aplicarCondicao()` e `processarCondicoesAtivas()` que iteram sobre condições ativas do personagem |
| Rolagens de dado feitas com `rand()` ou inline | Substituir por chamadas a `_dados.d20()`, `_dados.rolar()`, etc. |
| Não exibe nada para o jogador | Adicionar chamadas a `_view->exibirEstadoBatalha()`, `_view->exibirResultadoAcao()`, etc. nos pontos corretos |

---

### Personagem

**Arquivo:** `include/entities/Personagem.hpp` + `src/entities/Personagem.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Não possui lista de condições ativas | Adicionar atributo `std::vector<Condicao> _condicoesAtivas` |
| Não possui `aplicarCondicao()` | Adicionar método que insere uma condição na lista e aplica o efeito imediato no atributo |
| Não possui `removerCondicao()` | Adicionar método que reverte o efeito e remove da lista |
| `subirNivel()` calcula PV inline | Delegar para `RegrasPersonagem::calcularVidaNovoNivel()` |
| `ganharExperiencia()` verifica up de nível inline | Delegar para `RegrasProgresso::verificarUpNivel()` |
| Construtor define PV inicial inline | Delegar para `RegrasPersonagem::calcularVidaInicial()` |

---

### ClassePersonagem

**Arquivo:** `include/entities/ClassePersonagem.hpp` + `src/entities/ClassePersonagem.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Não possui `_ataqueFortAtivo` | Adicionar atributo que guarda qual ataque forte está equipado atualmente |
| Não possui `trocarAtaqueForte()` | Adicionar método que valida se o nível permite a troca e atualiza `_ataqueFortAtivo` |
| Não possui `_dadoDeVida` | Adicionar atributo do tipo `int` com o número de lados do dado de vida da classe |
| `calcularDano()` faz os cálculos internamente | Refatorar para chamar `RegrasAtaque::calcularDano*()` passando `Dados&` |
| Não guarda condição associada ao ataque | Adicionar campo de condição em cada entrada da lista de ataques |
| `RegrasAtaque` não recebe `Dados` | Garantir que `Dados&` é passado por quem chama `calcularDano()` (ex: `Batalha`) |

---

### Cena

**Arquivo:** `include/entities/Cena.hpp` + `src/entities/Cena.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Não possui `IView*` / `IController*` | Adicionar como atributos e receber via construtor |
| Exibição feita com `cout` direto | Substituir por chamadas a `_view->exibirCena()`, `_view->exibirMensagem()` |
| Input feito com `cin` direto | Substituir por chamadas a `_controller->capturarEscolha()` |
| `iniciarBatalha()` instancia `Batalha` sem `Dados` nem `IView` | Passar `_dados`, `_view` e `_controller` para o construtor de `Batalha` |

---

### TrechoMapa

**Arquivo:** `include/entities/TrechoMapa.hpp` + `src/entities/TrechoMapa.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Não possui atributo de ND | Adicionar `float _nd` (Nível de Desafio do inimigo do trecho) |
| Não possui `classificarDificuldade()` | Adicionar método que chama `RegrasBatalha::classificarConfronto(lvJogador, _nd)` |
| ND não é definido na construção | Receber `nd` como parâmetro do construtor |

---

### Item

**Arquivo:** `include/entities/Item.hpp` + `src/entities/Item.cpp`

| O que alterar | Como alterar |
| --- | --- |
| Sem alterações estruturais necessárias | A classe Item não depende de Regras, Dados, View ou Controller |
| Efeitos como condições não estão mapeados | Verificar se `aplicarEfeito()` consegue aplicar condições em `Personagem` via `aplicarCondicao()` |