# Cartões CRC
*Dark Age: The Arcanum Quest*  
**Grupo 5** — RPG Turn-Based Game  
**Disciplina:** Programação e Desenvolvimento de Software II — UFMG  
**Semestre:** 2026/1 | **Turma:** TF

> ## Controle de Revisões
> | Rev. | Descrição | Elab. | Data |
> |:----:|:---------|:-----:|:---:|
> | 0 | Emissão Inicial | MME | 27/04/26 |
> | 1 | Adiciona Inventário e Cena | LSBP | 28/04/26 |
> | 2 | Adiciona TrechoMapa e Batalha | MFC | 28/04/26 |
> | 3 | Atualização em Batalha | MFC | 07/05/26 |
> | 4 | Hierarquia Regras, Dados, MVC | HVLO | 07/06/26 |
> | 5 | Sistema de Arcanos, BancoInimigo completo, testes Batalha | HVLO | 22/06/26 |

---

## Entidades do Jogo

### Classe Personagem

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Nome, Descrição, Fala | — |
| | Ataque, Defesa, Agilidade | Item (modifica atributo) |
| | Vida Atual / Total | Item (modifica atributo) |
| | PP Atual / Total (Mana) | Item (modifica atributo) |
| | Nível, XP | — |
| | TipoPersonagem (NPC, Boss, Inimigo, Jogador) | — |
| | ClassePersonagem | ClassePersonagem |
| | Condições ativas (lista) | Condicao |
| | Arcanos ativos (lista) | TipoArcanoEnum |
| **Realização** | receberDano() | — |
| | recuperarVida() | — |
| | gastarMana() / recuperarMana() | — |
| | ganharXp() | RegrasProgresso |
| | subirNivel() | RegrasProgresso |
| | aplicarCondicao() | Condicao |
| | removerCondicao() | — |
| | getCondicoesAtivas() | — |
| | adicionarArcano() | TipoArcanoEnum |
| | temArcano() | — |
| | getArcanos() | — |
| | estaVivo() | — |

**Nota:** A classe mantém a identidade de cada personagem. Cálculos de progressão são delegados a RegrasProgresso. O sistema de Arcanos é aditivo e sem duplicatas — `TipoArcano::Nenhum` é rejeitado.

---

### Classe Jogador *(herda de Personagem)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Inventário | Inventario |
| **Realização** | getInventario() | Inventario |
| | usarItem() | Item, Personagem |

---

### Classe ClassePersonagem

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Nome e Descrição da classe | — |
| | TipoDeArma, DadoDeVida | — |
| | PP Total (Mana) | — |
| | Lista de ataques (Nome, Descrição, CustoPP, Condição) | — |
| | AtaqueForte ativo | — |
| **Realização** | definirAtaquesDisponiveis() | RegrasClassePersonagem |
| | calcularDano() | RegrasAtaque, Dados |
| | alteraAtaqueForte() | RegrasAtaque |
| | fornecerDadosAtaque() | Personagem, Batalha |

---

### Classe Item

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Nome, Descrição | — |
| | Categoria (pocao, alimento, cristal) | Inventario |
| | Efeito (aumentar ataque, recuperar vida, etc.) | Personagem |
| **Realização** | aplicarEfeito() | Personagem, Batalha |

---

### Classe Inventário

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Itens armazenados | Item |
| | Capacidade máxima (8 slots) | — |
| | Quantidade atual | — |
| **Realização** | salvarItem() | Item |
| | utilizarItem() | Item |
| | excluirItem() | — |
| | listarItens() | — |
| | verificarEspacos() | — |
| | quantidadeItens() | — |

---

### Classe Cena

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | ID e nível da cena | — |
| | Jogador | Jogador |
| | Trechos de mapa | TrechoMapa |
| | Recompensa entregue (flag) | — |
| **Realização** | iniciarCena() / finalizarCena() | — |
| | andar() | TrechoMapa |
| | vasculhar() / descartarItem() | Item, Inventario |
| | pegarTrechoAtual() | TrechoMapa |
| | pegarId() / pegarDescricao() | — |

---

### Classe TrechoMapa

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | ID, ID da cena | — |
| | Descrição (flavor text) | — |
| | Lista de itens disponíveis | Item |
| | ID do NPC de interação | — |
| | ID do próximo trecho | — |
| | Flag de presença de inimigo | — |
| | ND (Nível de Desafio) | RegrasBatalha |
| **Realização** | possuiItensRestantes() | — |
| | sortearItem() / descartarItem() | — |
| | possuiInimigo() | — |
| | pegarProximoTrecho() / pegarNPCInteracao() | — |

---

### Classe Batalha

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Player, Inimigo | Personagem |
| | Turno atual | — |
| | Ações disponíveis por turno | AcaoBatalha |
| | FatorDificuldade | RegrasBatalha |
| | ProgressoBatalha | — |
| | Condições ativas do player e do inimigo | Condicao |
| **Realização** | iniciarBatalha() | Personagem, RegrasBatalha |
| | realizarAcao() | Personagem, RegrasAtaque, Dados |
| | atualizarAcoesDisponiveis() | — |
| | aplicarCondicao() | Personagem |
| | processarCondicoesAtivas() | Personagem, Dados |
| | processarDefesa() | RegrasBatalha |
| | processarEsquiva() | RegrasBatalha |
| | finalizarBatalha() | — |
| | definirRecompensa() | Cena, RegrasBatalha, RegrasProgresso |
| | verificarFuga() | RegrasBatalha |
| | getTurno() / getFatorDificuldade() | — |
| | getAcoesDisponiveis() | — |

**Nota:** `aplicarCondicao()` respeita o Arcano Alma (bloqueia Paralisado). `processarCondicoesAtivas()` aplica efeitos de turno (Berserk, Envenenado, Vida) e chama `atualizarAcoesDisponiveis()` ao final. `Dados` é injetado via construtor para testes determinísticos.

---

## Utilitários

---

### Classe Dados

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Semente do gerador (RNG interno) | — |
| **Realização** | d4(), d6(), d8(), d10(), d12(), d20() | — |
| | rolar(quantidade, lados) | — |
| | rolar4d6() — descarta o menor | — |
| | gerarAtributos() — 4× rolar4d6, ordem decrescente | — |
| | d20Vantagem() / d20Desvantagem() | — |

**Nota:** Classe utilitária pura. Aceita semente fixa no construtor para TDD determinístico. Injetada via construtor em Batalha e ClassePersonagem.

---

## Hierarquia de Regras

> `Regras` é a classe pai abstrata. As filhas especializam por domínio e herdam os métodos compartilhados (`calcularCoeficiente`, `bonusProficiencia`, `xpParaProximoNivel`). Quando houver duplicação entre filhas, o método sobe para a pai.

---

### Classe Regras *(pai abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | calcularCoeficiente(valorAtributo) → y = 0,5x − 5 | — |
| | bonusProficiencia(nivel) → lookup tabela | — |
| | xpParaProximoNivel(nivel) → lookup tabela | — |

**Nota:** Disponibiliza como `static protected` os três métodos que todas as filhas utilizam. Nenhuma filha reimplementa esses cálculos.

---

### Classe RegrasAtaque *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Definições dos ataques por classe (dado, escala por nível, custo PP, condição) | — |
| **Realização** | calcularDanoSimples(classe, nivel, dados) | Dados |
| | calcularDanoRapido(classe, dados) | Dados |
| | calcularDanoForte(nomeAtaque, nivel, dados) | Dados |
| | calcularRolagemAcerto(coefAtaque, nivel, gastaPP, vantagem) | Dados, Regras |
| | obterCondicaoAtaque(nomeAtaque) | — |
| | getAtaquesFortesDisponiveis(classe, nivel) | — |

---

### Classe RegrasClassePersonagem *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Dados de cada classe (dado de vida, PP base, prioridade de atributos) | — |
| **Realização** | distribuirAtributos(classe, valoresRolados) | — |
| | calcularPPTotal(valorPoder) | — |
| | calcularVidaInicial(classe, coefDefesa) | — |
| | calcularVidaNovoNivel(classe, coefDefesa, dados) | Dados |
| | getDadoVida(classe) | — |

---

### Classe RegrasBatalha *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Tabela de limiares de dificuldade por nível | — |
| | Tabela de XP por ND de inimigo | — |
| **Realização** | classificarConfronto(lvJogador, ndInimigo) | — |
| | calcularXPGanho(ndInimigo, lvJogador) | Regras |
| | fugirDisponivel(lvJogador, ndInimigo) | — |
| | calcularCD(coefAgilidade) | — |
| | processarDefesa(coefDefesa, ataqueInimigo) | — |
| | processarEsquiva(coefAgilidade, ataqueInimigo) | — |

---

### Classe RegrasProgresso *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Conhecimento** | Tabela de XP necessário por nível (LV 1–10) | — |
| | Tabela de bônus de proficiência por nível | — |
| **Realização** | verificarUpNivel(xpAtual, nivelAtual) | Regras |
| | getBonusProficiencia(nivel) | Regras |
| | getXPParaProximoNivel(nivel) | Regras |

---

### Classe RegrasItem *(filha de Regras)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | calcularEfeitoItem(item, personagem) | Item, Personagem |

---

## Padrão MVC — View e Controller

---

### Interface IView *(abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | exibir(msg) / exibirLinha() | — |
| | exibirEstadoBatalha(player, inimigo, turno) | Personagem |
| | exibirAcoesDisponiveis(acoes) | — |
| | exibirResultadoAcao(descricao) | — |
| | exibirCondicao(condicao, alvo) | — |
| | exibirFimBatalha(vitoria, xpGanho) | — |
| | exibirCena(cena) | Cena |
| | exibirMenu(titulo, opcoes) | — |

**Nota:** Interface pura (todos os métodos virtuais puros). Implementações concretas: `TerminalView` (stdout). Trocar a implementação = trocar uma linha no `main.cpp`.

---

### Interface IController *(abstrata)*

| Tipo | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Realização** | lerInteiro() → int | — |
| | lerTexto() → string | — |
| | aguardarConfirmacao() | — |

**Nota:** Implementação concreta: `InputController` (lê do `cin` no terminal).

---

## Bancos de Dados Estáticos

Classes utilitárias com métodos estáticos que centralizam todos os dados do jogo. Lançam `std::invalid_argument` para IDs inválidos.

| Banco | Responsabilidade |
|-------|-----------------|
| BancoCena | Retorna InfoCena por ID (1–7) |
| BancoInimigo | Retorna Personagem inimigo por ID (1–999) |
| BancoItem | Retorna Item por ID de cena e ID de item |
| BancoClassePersonagem | Retorna ClassePersonagem por TipoClasse |
| BancoDadosAtaque | Retorna DadosAtaque por classe e tipo de ataque |
| BancoNpcInteracao | Retorna InfoNPCInteracao por ID |
| BancoTrechoMapa | Retorna InfoTrechoMapa por ID de cena |
