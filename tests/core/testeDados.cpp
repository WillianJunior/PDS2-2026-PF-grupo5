#include "../doctest.h"

#include "core/Dados.hpp"
#include <stdexcept>
#include <vector>

// ── Dados individuais ─────────────────────────────────────────────────────────

TEST_CASE("d4 retorna valor entre 1 e 4") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d4();
        CHECK(v >= 1);
        CHECK(v <= 4);
    }
}

TEST_CASE("d6 retorna valor entre 1 e 6") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d6();
        CHECK(v >= 1);
        CHECK(v <= 6);
    }
}

TEST_CASE("d8 retorna valor entre 1 e 8") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d8();
        CHECK(v >= 1);
        CHECK(v <= 8);
    }
}

TEST_CASE("d10 retorna valor entre 1 e 10") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d10();
        CHECK(v >= 1);
        CHECK(v <= 10);
    }
}

TEST_CASE("d12 retorna valor entre 1 e 12") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d12();
        CHECK(v >= 1);
        CHECK(v <= 12);
    }
}

TEST_CASE("d20 retorna valor entre 1 e 20") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d20();
        CHECK(v >= 1);
        CHECK(v <= 20);
    }
}

// ── rolar(N, X) ──────────────────────────────────────────────────────────────

TEST_CASE("rolar NdX retorna soma dentro do intervalo esperado") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int r3d6 = d.rolar(3, 6);
        CHECK(r3d6 >= 3);
        CHECK(r3d6 <= 18);

        int r2d8 = d.rolar(2, 8);
        CHECK(r2d8 >= 2);
        CHECK(r2d8 <= 16);

        int r1d20 = d.rolar(1, 20);
        CHECK(r1d20 >= 1);
        CHECK(r1d20 <= 20);
    }
}

TEST_CASE("rolar lanca excecao para quantidade menor que 1") {
    Dados d(42);
    CHECK_THROWS_AS(d.rolar(0, 6),  std::invalid_argument);
    CHECK_THROWS_AS(d.rolar(-1, 6), std::invalid_argument);
}

TEST_CASE("rolar lanca excecao para lados menor que 2") {
    Dados d(42);
    CHECK_THROWS_AS(d.rolar(1, 1), std::invalid_argument);
    CHECK_THROWS_AS(d.rolar(1, 0), std::invalid_argument);
}

// ── Reprodutibilidade ─────────────────────────────────────────────────────────

TEST_CASE("semente fixa produz sequencia identica em duas instancias") {
    Dados d1(42), d2(42);
    for (int i = 0; i < 20; i++)
        CHECK(d1.d20() == d2.d20());
}

TEST_CASE("sementes diferentes produzem sequencias distintas") {
    Dados d1(1), d2(999);
    bool algumDiferente = false;
    for (int i = 0; i < 20; i++)
        if (d1.d6() != d2.d6()) { algumDiferente = true; break; }
    CHECK(algumDiferente);
}

// ── Rolagens compostas ────────────────────────────────────────────────────────

TEST_CASE("rolar4d6 retorna valor entre 3 e 18") {
    Dados d(42);
    for (int i = 0; i < 50; i++) {
        int v = d.rolar4d6();
        CHECK(v >= 3);
        CHECK(v <= 18);
    }
}

TEST_CASE("gerarAtributos retorna 4 valores em ordem decrescente dentro de [3, 18]") {
    Dados d(42);
    std::vector<int> atributos = d.gerarAtributos();

    CHECK(atributos.size() == 4);
    for (int v : atributos) {
        CHECK(v >= 3);
        CHECK(v <= 18);
    }
    for (int i = 0; i < 3; i++)
        CHECK(atributos[i] >= atributos[i + 1]);
}

TEST_CASE("d20Vantagem retorna valor entre 1 e 20") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d20Vantagem();
        CHECK(v >= 1);
        CHECK(v <= 20);
    }
}

TEST_CASE("d20Desvantagem retorna valor entre 1 e 20") {
    Dados d(42);
    for (int i = 0; i < 30; i++) {
        int v = d.d20Desvantagem();
        CHECK(v >= 1);
        CHECK(v <= 20);
    }
}

TEST_CASE("d20Vantagem tende a ser maior ou igual a d20Desvantagem em media") {
    Dados dV(42), dD(42);
    double somaVant = 0, somaDesv = 0;
    const int N = 1000;
    for (int i = 0; i < N; i++) {
        somaVant += dV.d20Vantagem();
        somaDesv += dD.d20Desvantagem();
    }
    CHECK(somaVant / N > somaDesv / N);
}
