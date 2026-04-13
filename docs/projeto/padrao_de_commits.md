# Padronização de Commits

**Objetivo**: propor um padrão para a escrita de mensagens de commits neste projeto. Busca facilitar a colaboração e a organização do histórico do projeto para todos os membros do grupo.

**Formato da mensagem**:
Cada commit deve seguir este padrão:

`tipo: descrição curta em português`

## Tipos de Commit

| Tipo | Quando usar? |
| :--- | :--- |
| **feat** | Adição de uma nova funcionalidade (ex: lógica de combate, novos itens). |
| **fix** | Correção de erros ou bugs identificados. |
| **docs** | Alterações em arquivos de documentação (README, manuais, comentários). |
| **refactor** | Melhorias no código que não alteram o comportamento (limpeza, renomeação). |
| **chore** | Configurações de projeto ou tarefas repetitivas (ex: ajustar o `.gitignore`). |
| **test** | Criação ou ajuste de testes. |

## Exemplos de Uso

* `feat: implementa sistema de pontos de experiência`
* `fix: corrige bug que impedia o uso de poções de cura`
* `docs: atualiza a seção de requisitos do sistema no README`
* `refactor: simplifica a estrutura das classes de inimigos`
* `chore: organiza a estrutura de pastas do projeto`


## Algumas dicas

1. **Ser objetivo na descrição principal:** A primeira linha do commit deve ser curta e direta, resumindo a mudança de forma clara. Se quiser adicionar detalhes, utilize o corpo do commit. 
2. **Usar Verbos no Presente:** Opte por "adiciona", "remove", "corrige" em vez de "adicionei" ou "corrigido".
3. **Agrupar mudanças:** Commitem pequenas partes lógicas para facilitar o entendimento das mudanças e evitar conflitos. Se um commit contiver mudanças em 10 arquivos diferentes com 10 propósitos diferentes, pode ser complexo para compreender o que foi feito.
4. **Quebre mudanças grandes em commits menores:** Se uma funcionalidade nova envolve várias etapas, considere dividir o trabalho em commits menores e mais específicos. Por exemplo, primeiro crie a estrutura de classes, depois implemente a lógica, e por fim adicione os testes.