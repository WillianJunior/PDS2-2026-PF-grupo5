## Estrutura base do projeto

**Objetivo**: documentar a estrutura de diretórios proposta para o projeto, explicando a função de cada pasta e arquivo.

``` Markdown
├── bin/                # Executáveis gerados após a compilação (executável final).
├── build/              # Arquivos objeto (.o) e temporários do compilador.
├── data/               # Arquivos de texto (.txt) para persistência de dados e mapas.
├── docs/               # Documentação gerada pelo Doxygen, diagramas CRC e user stories.
├── include/            # Arquivos de cabeçalho (.hpp) -> Definição dos contratos.
│   ├── core/           # Lógica do jogo.
│   ├── entities/       # Classes de personagens e inimigos.
│   └── items/          # Gestão de inventário e equipamentos.
├── src/                # Arquivos de implementação (.cpp).
│   ├── core/
│   ├── entities/
│   └── main.cpp        # Ponto de entrada do programa.
├── tests/              # Testes unitários (TDD).
├── Makefile            # Automação de compilação.
└── README.md           # Documentação geral e guia de uso.
```
