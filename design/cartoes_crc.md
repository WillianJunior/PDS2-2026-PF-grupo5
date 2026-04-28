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