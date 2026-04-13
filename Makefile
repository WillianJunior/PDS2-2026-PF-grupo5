# Compilador e flags
CXX      := g++
CXX_FLAGS := -std=c++11 -Wall -Iinclude

# Diretórios do projeto
SRC     := src
INCLUDE := include
BUILD   := build
BIN     := bin

# Nome do executável
TARGET  := $(BIN)/jogo_rpg # TODO: alterar quando já tivermos um nome definido para o jogo.

# Listagem de arquivos fonte e objetos
SOURCES := $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/**/*.cpp)
OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)

# Comando padrão para compilar o projeto 
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) $^ -o $@

# Compilação dos objetos
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# Comando para executar o programa 
run: all
	@./$(TARGET)

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all run clean