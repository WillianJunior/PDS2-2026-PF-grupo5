**Classe Personagem**

Responsabilidades:

Conhecimentos(Atributos):
- Nome
- Ataque
- Defesa
- Vida Atual
- Vida Total
- PP Atual (Mana)
- PP Total (Mana)
- Agilidade
- Nível
- XP
- Tipo de Personagem (NPC, Boss, Inimigo, Jogador)
- **ClassePersonagem**

Realizações:
- Criar e manter a identidade de cada individuo de uma cena.
- Atualizar seus próprios atributos baseado em chamadas de outras classes:
    - Receber dano
    - Recuperar vida
    - Consumir mana
    - Ganhar experiência
    - Subir nível
- Fornecer informações do Personagem para outras classes.
- Gerenciar se está vivo ou morto.

Colaborações:
- ClassePersonagem


**Classe ClassePersonagem**

Responsabilidades:

Conhecimentos:
- NomeDeClasse
- DescriçãoDeClasse
- TipoDeArma
- PP Total (Mana)
- Lista de Ataques:
    - Nome
    - Descrição
    - Dano
    - CustoPP

Realizações:
- Definir ataques disponíveis para a classe.
- Fornecer dados dos ataques para outras classes.


**Classe Invantário**

Responsabilidades:

Conhecimentos:
- Itens e suas características
- Capacidade maxima do inventário
- Quantidade atual de itens armazenados

Realizações:
- Interagir com os itens:
    - Salvar itens no inventário
    - Utilizar um item
    - Excluir um item do inventário
- Listar os itens no inventário
- Verificar espaços (slots) disponíveis/usados
- Fechar inventário

Colaborações:
- Itens
- Personagem
- ClassePersonagem
- Batalha
- Cena


**Classe Cena**

Responsabilidades:

Conhecimentos:
- Nível da cena
- Carcterísticas dos personagens (Player e NPCs) que fazem parte da cena
- Itens e Inventário

Realizações:
- Inicializar cena (inicia os NPCs, os itens, configura o nível de dificuldade) e finalizar cena
- Verificar continuidade (fazer com que o player progrida no jogo, barrando ações quando se tornam repetitivas na cena)
- Ações:
    - Andar: engatilha ações aleatórias (conversar com NPC, batalhar com NPC, descobrir cenário)
    - Vasculhar para encontrar itens
    - Interagir com NPCs
    - Abrir inventário
    - Iniciar batalha

Colaborações:
- Itens
- Personagem
- ClassePersonagem
- Batalha
- Inventário