#include "entities/items/Item.hpp"

// Construtor
Item::Item(std::string nome, std::string descricao, TipoItem tipo,
           std::string efeito, int valor, int duracao)
    : _nome(nome), _descricao(descricao), _tipo(tipo),
      _efeito(efeito), _valor(valor), _duracao(duracao) {}

// Getters
std::string Item::pegarNome() const { return _nome; }
std::string Item::pegarDescricao() const { return _descricao; }
TipoItem Item::pegarTipo() const { return _tipo; }
std::string Item::pegarEfeito() const { return _efeito; }
int Item::pegarValor() const { return _valor; }
int Item::pegarDuracao() const { return _duracao; }
