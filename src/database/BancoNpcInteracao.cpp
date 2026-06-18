#include "database/BancoNpcInteracao.hpp"

#include <stdexcept>

InfoNPCInteracao BancoNPCInteracao::obterNPC(int id)
{
    switch(id)
    {
        case 1:
            return {
                1,
                 "Nome",
                "Descricao do npc",
                "Fala"
            };

        case 2:
            return {
                2,
                "Nome",
                "Descricao do npc",
                "Fala"
            };

        case 3:
            return {
                3,
                "Nome",
                "Descricao do npc",
                "Fala"
            };

        default:
            throw std::runtime_error(
                "NPC de interacao nao encontrado."
            );
    }
}