# Comandos do Makefile

| Comando | Descrição |
|---|---|
| `make` ou `make all` | Compila os arquivos fonte em `src/` e gera o executável em `bin/` |
| `make run` | Compila o projeto (se necessário) e executa o programa |
| `make compile_tests` | Compila os arquivos de teste em `tests/` junto com os fontes (exceto `main.cpp`), com instrumentação de cobertura (gcovr) (`--coverage`) |
| `make test` | Executa `compile_tests` e roda os testes; falhas nos testes não interrompem o processo |
| `make coverage` | Executa os testes e gera relatório de cobertura no terminal via `gcovr` (independente se testes passam ou falham); também gera relatório HTML detalhado em `docs/coverage/index.html` |
| `make test_coverage` | Executa `make test` e `make coverage` em sequência, exibindo a porcentagem de testes passados e gerando o relatório HTML de cobertura |
| `make clean` | Remove os diretórios `build/` e `bin/`, o binário `exec_tests` e os arquivos de cobertura (`.gcda`, `.gcno`, `docs/coverage/`) |
