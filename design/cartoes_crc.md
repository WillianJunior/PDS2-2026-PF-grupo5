# Cartões CRC

### Classe Personagem

| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | Nome                                           | -                                                       |
|                  | Ataque                                         | Item (modifica o atributo)                              |
|                  | Defesa                                         | Item (modifica o atributo)                              |
|                  | Vida Atual                                     | Item (modifica o atributo)                              |
|                  | Vida Total                                     | -                                                       |
|                  | PP Atual (Mana)                                | Item (modifica o atributo)                              |
|                  | PP Total (Mana)                                | -                                                       |
|                  | Agilidade                                      | Item (modifica o atributo)                              |
|                  | Nível                                          | -                                                       |
|                  | XP                                             | -                                                       |
|                  | TipoPersonagem (NPC, Boss, Inimigo, Jogador)   | -                                                       |
|                  | ClassePersonagem                               | ClassePersonagem                                        |
| **Realização**   | receberDano()                                  | -                                                       |
|                  | atualizarVida()                                | -                                                       |
|                  | atualizarMana()                                | -                                                       |
|                  | ganharExperiencia()                            | -                                                       |
|                  | subirNivel()                                   | -                                                       |
|                  | obterInformacoes()                             | -                                                       |
|                  | estaVivo()                                     | -                                                       |

**Nota**: A classe deve criar e manter a identidade de cada indivíduo de uma cena

---

### Classe ClassePersonagem

| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | NomeDeClasse                                   | -                                                       |
|                  | DescriçãoDeClasse                              | -                                                       |
|                  | TipoDeArma                                     | -                                                       |
|                  | PP Total (Mana)                                | -                                                       |
|                  | Lista de Ataques: Nome                         | -                                                       |
|                  | Lista de Ataques: Descrição                    | -                                                       |
|                  | Lista de Ataques: Dano                         | -                                                       |
|                  | Lista de Ataques: CustoPP                      | -                                                       |
| **Realização**   | Definir ataques disponíveis para a classe      | Personagem                                              |
|                  | Fornecer dados dos ataques                     | Personagem, Batalha                                     |

---

### Classe Item

| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | nome                                           | -                                                       |
|                  | descricao                                      | -                                                       |
|                  | categoria (pocao, alimento, cristal)           | Inventario (armazena e organiza os itens)               |
|                  | efeito (aumentar ataque, recuperar vida, etc.) | Personagem (recebe o efeito)                            |
| **Realização**   | aplicarEfeito()                                | Personagem, Batalha (momento em que o item é utilizado) |

---

### Classe Inventário

| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | Itens e suas características                   | Itens, Personagem, Batalha, Cena                        |
|                  | Capacidade máxima do inventário                | -                                                       |
|                  | Quantidade atual de itens armazenados          | Itens, Batalha                                          |
| **Realização**   | Salvar itens no inventário                     | Item                                                    |
|                  | Utilizar um item                               | Item                                                    |
|                  | Excluir um item do inventário                  | -                                                       |
|                  | Listar os itens no inventário                  | -                                                       |
|                  | Verificar espaços (slots) disponíveis/usados   | -                                                       |
|                  | Fechar inventário                              | -                                                       |

---

### Classe Cena

| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | Nível da cena                                  | -                                                       |
|                  | Personagens - Características  (Player e NPCs) | Personagem, ClassePersonagem                            |
|                  | Itens e Inventário                             | Itens, Inventario                                       |
|                  | Trechos de mapa (quais e quantos existem)      | TrechoMapa                                              |
| **Realização**   | Inicializar cena                               | -                                                       |
|                  | Finalizar cena                                 | -                                                       |
|                  | Verificar continuidade                         | -                                                       |
|                  | Ações: Andar                                   | -                                                       |
|                  | Ações: Vasculhar para encontrar itens          | Item, Inventario                                        |
|                  | Ações: Interagir com NPCs                      | Personagem, ClassePersonagem                            |
|                  | Ações: Abrir inventário                        | Inventario                                              |
|                  | Ações: Iniciar batalha                         | Batalha                                                 |

---

### Classe TrechoMapa
| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | Id                                             | -                                                       |
|                  | Cena (a qual cena o trecho pertence)           | Cena                                                    |
|                  | Descricao (caracteristicas do trecho, flavor)  | -                                                       |
|                  | Itens (lista de itens presentes)               | Item                                                    |
|                  | NPC (lista de NPC presentes)                   | Personagem, ClassePersonagem                            |
|                  | Coordenadas (localização do trecho)            | -                                                       |
| **Realização**   | abrirTrecho()                                  | Cena, Item, Personagem, ClassePersonagem                |

**Notas**: 
- Essa classe é responsável por definir o que cada trecho de mapa possui, incluindo itens e personagens (NPC)
- O atributo `coordenadas` talvez só faça sentido caso criemos uma interface gráfica para o jogo
- O método `abrirTrecho()` é responsável por revelar o conteúdo do trecho para o jogador, permitindo que ele interaja com os itens e NPCs presentes.

---

### Classe Batalha
| Tipo             | Responsabilidades                              | Colaboradores                                           |
| :--------------- | :--------------------------------------------- | :------------------------------------------------------ |
| **Conhecimento** | Player                                         | Personagem                                              |
|                  | Inimigo                                        | Personagem                                              |
|                  | Turno (em qual turno a batalha está)           | -                                                       |
|                  | Acoes (lista de ações disponíveis por turno)   | -                                                       |
| **Realização**   | iniciarBatalha()                               | Cena, Item, Personagem, ClassePersonagem                |
|                  | realizarAcao()                                 | Personagem                                              |
|                  | processarEsquiva()                             | Personagem                                              |
|                  | processarDefesa()                              | Personagem                                              |
|                  | finalizarBatalha()                             | Cena, Personagem                                        |
|                  | definirRecompensa()                            | Cena, Personagem                                        |

**Notas**:
- A classe Batalha é responsável por gerenciar o combate entre o player e um inimigo, controlando os turnos e as ações disponíveis.
- O método `iniciarBatalha()` é chamado quando o player encontra um inimigo, configurando os personagens e as ações disponíveis.
- O método `realizarAcao()` é chamado durante o turno do player, permitindo que ele escolha uma ação (ataque, usar item, etc.) e aplicando os efeitos dessa ação.
- O método `finalizarBatalha()` é chamado quando um dos personagens é derrotado ou quando o player decide fugir da batalha. Nesse momento, as consequências da batalha são aplicadas (recompensas e punições)