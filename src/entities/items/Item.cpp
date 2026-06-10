#include "entities/items/Item.hpp"
#include "database/BancoItem.hpp"

// Construtor
Item::Item(std::string nome, std::string descricao, TipoItem tipo,
           std::string efeito, int valor, int duracao, int cenaId)
    : _nome(nome), _descricao(descricao), _tipo(tipo),
      _efeito(efeito), _valor(valor), _duracao(duracao), _cenaId(cenaId) {}

// Getters
std::string Item::pegarNome() const { return _nome; }
std::string Item::pegarDescricao() const { return _descricao; }
TipoItem Item::pegarTipo() const { return _tipo; }
std::string Item::pegarEfeito() const { return _efeito; }
int Item::pegarValor() const { return _valor; }
int Item::pegarDuracao() const { return _duracao; }
int Item::getCenaId() const { return _cenaId; }

Item Item::gerarItem(int cenaId, int itemId) {
    return BancoItem::obterItem(cenaId, itemId);
}
