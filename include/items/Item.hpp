#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

enum TipoItem{
    Pocao, Comida, Cristal 
};

class Item{
private: 
    std::string _nome;
    std::string _descricao;
    TipoItem _tipo;

    std::string _efeito;
    int _valor;
    int _duracao;

public:
    Item(std::string nome, std::string descricao, TipoItem tipo, std::string efeito, int valor, int duracao);

    std::string pegarNome() const;
    std::string pegarDescricao() const;
    TipoItem pegarTipo() const;

    std::string pegarEfeito() const;
    int pegarValor() const;
    int pegarDuracao() const;
};

#endif