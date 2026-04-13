# Projeto Final 2026/1 - Grupo 5
> UFMG - Programação e Desenvolvimento de Software 2 - Turma PF 
(PDS2-2026-PF-grupo5)

## Estrutura base do projeto
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