/**
 * @file Inventario.hpp
 * @brief Definição da classe Inventario para gestão de itens dos personagens.
 */

#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <memory>
#include <stdexcept>

#include "Item.hpp"
#include "../character/Personagem.hpp"

class IView; // forward declaration — evita include pesado no header

/**
 * @class InventarioCheioException
 * @brief Lançada quando uma tentativa de adição de um item excede a capacidade máxima do inventário.
 */
class InventarioCheioException : public std::overflow_error {
public:
    InventarioCheioException() : std::overflow_error("Inventario cheio") {}
};

/**
 * @class Inventario
 * @brief Classe responsável pelo armazenamento e gerenciamento de itens.
 * Possui uma capacidade limitada e permite que o personagem armazene, use ou remova itens coletados durante o jogo.
 * Toda a gestão de memória é feita via RAII (std::unique_ptr), sem new/delete manual.
 */
class Inventario {
private:
    struct No {
        std::unique_ptr<Item> _item;      ///< Dono do item armazenado neste nó.
        std::unique_ptr<No>   _proximo;   ///< Dono do próximo nó da lista.
    };

    std::unique_ptr<No> _inicio;
    int _quantidade;    ///< Contador de itens atualmente armazenados.
    static const int _capacidadeMax = 8; ///< Capacidade máxima do inventário.

public:
    Inventario();
    ~Inventario();

    /** @brief Move constructor (necessário porque há destrutor declarado). */
    Inventario(Inventario&& other) noexcept;

    void adicionarItem(std::unique_ptr<Item> item);
    void usarItem(int posicao, Personagem& personagem);
    void removerItem(int posicao);
    bool estaCheio() const;
    int quantidadeItens() const;
    void listarItens() const;
    void listarItens(IView& view) const; // roteia exibição pelo IView (testável)
    void fecharInventario();
};

#endif
