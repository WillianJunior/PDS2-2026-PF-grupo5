Parte 1 - Configurações e Início do Jogo

Início 
Descrição:
Como jogador, eu quero escolher uma classe no início do jogo para definir meu estilo de combate.

Critérios de aceitação:
- Apresentar as habilidades embutidas de cada classe com uma descrição de sua função;
- Apresentar a forma de ataque de cada classe com seu item definido;
- Mostrar vantagens e desvantagens de cada classe baseado em seus atributos iniciais.

Vasculhar
Descrição:
Como jogador, eu quero vasculhar o ambiente para encontrar itens e inimigos.

Critérios de aceitação:
- O jogador pode executar a ação de vasculhar durante seu turno fora de batalha;
- Ao vasculhar, o sistema deve informar se existem itens ou inimigos no ambiente;
- Caso um item seja encontrado, o jogador pode decidir pegar o item ou não;
- Caso um inimigo seja encontrado, o jogador pode decidir engajar em uma batalha ou não.

Inventário
Descrição:
Como jogador, eu quero ter acesso ao meu inventário para usar e administrar meus itens.

Critérios de aceitação:
- O jogador pode acessar o inventário a qualquer momento do seu turno fora de batalha, ou em seu turno de ataque em batalha para uso de itens;
- O inventário vai exibir os itens obtidos pelo jogador;
- Quando um item é usado, ele some do inventário;
- O inventário tem espaços limitados, permitindo ao jogador também excluir itens para pegar outros.


Parte 2 - Batalha

Ataque
Descrição:
Como jogador, eu quero atacar o inimigo para derrotá-lo.

Critérios de aceitação:
- A função “ataque” ficará disponível no turno do jogador durante uma batalha;
- A força do ataque do jogador será definido pela sua pontuação em ataque e pelo uso da mana;
- Existem 3 tipos de ataque: ataque simples (depende apenas dos pontos de ataque), ataque rápido (depende dos pontos de ataque, dos de agilidade e consome mana; reduz a agilidade do oponente) e ataque forte (depende dos pontos de ataque e consome mana; reduz consideravelmente a defesa do oponente, reduz a esquiva do oponente);
- O ataque causará dano.

Defesa
Descrição:
Como jogador, eu quero me defender em turno para diminuir o dano em meu personagem.

Critérios de aceitação:
- A função “defesa” ficará disponível após o ataque de um oponente, no turno do oponente, durante uma batalha;
- A função “defesa” anula ou reduz o dano desferido pelo oponente;
- Para que o dano seja anulado, os pontos de defesa do personagem deverão ser maiores que os pontos de ataque do oponente;
- Para que o dano seja reduzido a defesa dos jogador deverá corresponder ao nível e à classe de seu personagem.

Esquiva
Descrição:
Como jogador, eu quero tentar esquivar em um turno para não tomar dano.

Critérios de aceitação:
- A função “esquiva” ficará disponível após o ataque de um oponente, no turno do oponente, durante uma batalha;
- A função “esquiva” se bem-sucedida, anula o dano desferido pelo oponente;
- Para que o dano seja anulado, os pontos de agilidade do personagem deverão ser maiores que os pontos de ataque do oponente;
- A agilidade do jogador deve corresponder ao nível e à classe de seu personagem.


Parte 3 - Itens 

Comidas
Descrição:
Como jogador, eu quero usar um item de vida (comida) para recuperar minha vida.

Critérios de aceitação:
- Durante o seu turno, o jogador poderá alterar seus pontos de vida usando uma comida;
- A alteração de vida não pode ultrapassar os limites de valores definidos;
- O jogador precisa ter a comida correspondente no inventário, e após o uso, ela é retirada do inventário;
- Se em batalha o uso da comida é considerado a ação do turno.

Poções
Descrição:
Como jogador, eu quero usar uma poção para melhorar minhas habilidades.

Critérios de aceitação:
- Durante o seu turno, o jogador poderá aumentar seus pontos de habilidade (ataque, defesa, esquiva e mana) usando uma poção;
- O jogador precisa ter a poção correspondente no inventário, e após o uso, ela é retirada do inventário;
- A poção pode durar de 1 a 4 turnos de batalha, dependendo de seu valor definido na inicialização do item;
- Se em batalha o uso da poção é considerado a ação do turno.

Cristais
Descrição:
Como jogador, eu quero usar um cristal para ganhar vantagens.

Critérios de aceitação:
- Durante o seu turno fora de batalha, o jogador poderá equipar cristais momentaneamente para ter vantagens no jogo;
- O jogador precisa ter o cristal correspondente no inventário, que pode ser equipado para ter efeito ativado;
- Os cristais são apagados do inventário quando a cena muda.


Parte 4 - Progressão da história

Subir de nível
Descrição:
Como jogador, eu quero subir de nível após alcançar determinado valor de xp para aumentar meus atributos.

Critérios de aceitação:
- Uma quantidade de xp é coletada com base na dificuldade do inimigo derrotado (fácil, médio, difícil e boss) que pode ser aumentado ou diminuído baseado na sorte;
- Após uma quantidade de xp é coletada, definida pelo próximo nível multiplicado por um valor fixo, o personagem sobe de nível;
- Após subir de nível, o personagem tem seus atributos aumentados por um valor.