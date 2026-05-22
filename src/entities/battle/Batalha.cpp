#include "entities/battle/Batalha.hpp"
#include "entities/character/Personagem.hpp"
#include "entities/items/Item.hpp"
#include "entities/map/Cena.hpp"

// Construtor
Batalha::Batalha(Personagem *player, Personagem *inimigo) {}

// Mecânica de batalha
float Batalha::calcularVariabilidade(int valorBase) { return 0.0f; }
void Batalha::iniciarBatalha() {}
void Batalha::realizarAcao(AcaoBatalha acao) {}
void Batalha::processarDefesa() {}
void Batalha::processarEsquiva() {}
void Batalha::definirRecompensa(Cena &cenaAtual) {}
void Batalha::finalizarBatalha() {}
