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

# Linkagem do executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilação dos objetos
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Comando para executar o programa
run: all
	@./$(TARGET)

# Compilação dos testes com flags de cobertura
compile_tests:
	$(CXX) $(CXXFLAGS) -Itests --coverage $(SRCS_NO_MAIN) $(TEST_SRCS) -o exec_tests

# Execução dos testes
test: compile_tests
	-./exec_tests

# Relatório de cobertura de testes
coverage: test
	@echo "=== Cobertura de Testes ==="
	gcovr -r . --filter src/
	@mkdir -p docs/coverage
	gcovr -r . --filter src/ --html-details -o docs/coverage/index.html
	@echo "Relatório HTML gerado em docs/coverage/index.html"

# Limpeza dos executáveis e arquivos de mapeamento (.gcda, .gcno)
clean:
	rm -rf $(BUILD) $(BIN) exec_tests *.gcda *.gcno docs/coverage

.PHONY: all run compile_tests test coverage clean
