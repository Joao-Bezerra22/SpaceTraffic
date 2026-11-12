#ifndef JOGO_H
#define JOGO_H

#include "raylib.h"
#include "nave.h"
#include "tiro.h"
#include "asteroides.h"

#define VELOCIDADE_MAX_KMH   350.0f
#define TAXA_ACELERACAO      15.0f
#define LAP_MAX              3
#define SPAWN_MINIMO_LAP1    0.4f
#define SPAWN_MINIMO_LAP2    0.25f
#define SPAWN_MINIMO_LAP3    0.1f

typedef struct {
    Nave nave;
    Tiro *listaTiros;
    Asteroide asteroides[MAX_ASTEROIDES];

    float tempoContagem;
    float tempoUltimoSpawn;
    float tempoJogo;

    float velocidadeKMH;
    float velocidadeExtraAsteroides;

    int lapAtual;
    float tempoParaLap;
    bool linhaLapAtiva;
    float posicaoLinhaLapY;

    float spawnRateAtual;
    float limiteMinimoAtual;
} Jogo;


void reiniciarJogo(Jogo *jogo);
#endif