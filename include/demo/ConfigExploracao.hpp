/**
 * @file ConfigExploracao.hpp
 * @brief Flags de configuração para a demo de exploração.
 */

#ifndef DEMO_CONFIG_EXPLORACAO_HPP
#define DEMO_CONFIG_EXPLORACAO_HPP

/**
 * Controla comportamentos opcionais da exploração.
 * Defaults false = comportamento de produção completo.
 * Útil como test seam e para o modo --skip-lore da demo
 */
struct ConfigExploracao {
    bool skipLore  = false; // pula diálogos pós-boss e confronto de Ruffen
    bool skipEnter = false; // aguardarEnter() retorna sem esperar input
};

#endif
