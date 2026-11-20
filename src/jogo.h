#ifndef JOGO_H
#define JOGO_H

#include "raylib.h"
#include "nave.h"
#include "tiro.h"
#include "asteroides.h"

#define VELOCIDADE_MAX_KMH   445.0f
#define TAXA_ACELERACAO      15.0f
#define LAP_MAX              3
#define SPAWN_MINIMO_LAP1    0.23f
#define SPAWN_MINIMO_LAP2    0.28f
#define SPAWN_MINIMO_LAP3    0.12f
#define PONTOS_POR_ASTEROIDE 50

#define VELOCIDADE_INICIAL_KMH     100.0f
#define PERDA_VELOCIDADE_BATIDA    150.0f
#define TEMPO_ENTRE_LAPS           42.0f
#define REDUCAO_SPAWN_POR_SEGUNDO  0.25f
#define DIVISOR_PONTOS_VELOCIDADE  10.0f

#define COOLDOWN_TIRO 0.4f

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

    float pontuacao;

    float cooldownTiro;
} Jogo;


void reiniciarJogo(Jogo *jogo);
#endif
