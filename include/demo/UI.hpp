/**
 * @file DemoUI.hpp
 * @brief Funções auxiliares para exibição de elementos visuais da demo.
 */

#ifndef DEMO_UI_HPP
#define DEMO_UI_HPP

#include <string>
#include "utils/IView.hpp"


/**
 * @brief Exibe um texto centralizado na interface de visualização.
 *
 * Calcula o espaçamento necessário para posicionar o texto de forma
 * centralizada em relação à largura definida pela implementação.
 *
 * @param view Interface responsável pela exibição das mensagens.
 * @param texto Texto a ser exibido.
 */
void exibirCentrado(IView& view, const std::string& texto);

/**
 * @brief Exibe uma arte ASCII armazenada em um arquivo.
 *
 * Lê o conteúdo do arquivo informado e o exibe linha por linha
 * utilizando a interface de visualização.
 *
 * @param view Interface responsável pela exibição das mensagens.
 * @param caminho Caminho para o arquivo contendo a arte ASCII.
 */
void exibirAsciiArtArquivo(IView& view, const std::string& caminho);

#endif