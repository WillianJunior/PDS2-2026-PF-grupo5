# Compilador e flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Diretórios do projeto
SRC     := src
INCLUDE := include
BUILD   := build
BIN     := bin

# Nome do executável
TARGET  := $(BIN)/The_Dark_Age_-_The_Arcanum_Quest

# Arquivos fonte e objetos (busca recursiva real via find)
SOURCES      := $(shell find $(SRC) -name '*.cpp')
OBJECTS      := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCES))

# Para testes: fontes sem main.cpp + arquivos de teste
SRCS_NO_MAIN := $(filter-out $(SRC)/main.cpp, $(SOURCES))
TEST_SRCS    := $(shell find tests/ -name '*.cpp')

# Comando padrão para compilar o projeto
all: $(TARGET)

INCLUDE_DIRS := $(shell find include -type d)
ALL_INCLUDES := $(addprefix -I,$(INCLUDE_DIRS))

# Linkagem do executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilação dos objetos
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(ALL_INCLUDES) -c $< -o $@

# Comando para executar o programa
run: all
	@./$(TARGET)

# Compilação dos testes com flags de cobertura
compile_tests:
	rm -f *.gcda *.gcno
	$(CXX) $(CXXFLAGS) $(ALL_INCLUDES) -Itests --coverage $(SRCS_NO_MAIN) $(TEST_SRCS) -o exec_tests

# Execução dos testes
test: compile_tests
	@echo "=== Executando testes ==="
	@./exec_tests 2>&1 | tee exec_tests.log || true
	@summary_line=$$(grep 'test cases:' exec_tests.log | tail -n1); \
	total=$$(printf '%s' "$$summary_line" | sed -E 's/.*test cases: *([0-9]+).*/\1/'); \
	passed=$$(printf '%s' "$$summary_line" | sed -E 's/.*\| *([0-9]+) passed.*/\1/'); \
	if [ -n "$$total" ] && [ "$$total" -ne 0 ]; then \
		percent=$$(awk "BEGIN {printf \"%.2f\", ($$passed/$$total)*100}"); \
		echo "Testes passando: $$percent%"; \
	else \
		echo "Não foi possível calcular a porcentagem de testes passados."; \
	fi

# Relatório de cobertura de testes
coverage: test
	@echo "=== Cobertura de Testes ==="
	gcovr -r . --filter src/
	@mkdir -p docs/coverage
	gcovr -r . --filter src/ --html-details -o docs/coverage/index.html
	@echo "Relatório HTML gerado em docs/coverage/index.html"

# Combina testes e cobertura em um único comando
test_coverage: coverage
	@echo "Teste e cobertura concluídos. Relatório em docs/coverage/index.html"

# Limpeza dos executáveis e arquivos de mapeamento (.gcda, .gcno)
clean:
	rm -rf $(BUILD) $(BIN) exec_tests *.gcda *.gcno docs/coverage

.PHONY: all run compile_tests test coverage test_coverage clean
