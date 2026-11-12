#ifndef ASTEROIDES_H
#define ASTEROIDES_H
#include <stdlib.h>
#include "raylib.h"

typedef enum AsteroideTipo {
    ASTEROIDE_PEQUENO = 1,
    ASTEROIDE_MEDIO = 2,
    ASTEROIDE_GRANDE = 3
} AsteroideTipo;

#define ASTEROIDE_ROTACAO_VELOCIDADE_MIN 5
#define ASTEROIDE_ROTACAO_VELOCIDADE_MAX 240
#define MAX_ASTEROIDES 50
typedef struct asteroide {
    bool ativo;
    Vector2 posicao;
    AsteroideTipo tipo;
    float rotacao;
    float velocidaderotacao;
    Vector2 velocidade;
} Asteroide;

Asteroide criarAsteroide(AsteroideTipo tipo, Vector2 posicao, Vector2 velocidade);
void AsteroidAtualizar(Asteroide *asteroide, float FrameTime, float velocidadeExtra);
void desenharAsteroide(Asteroide asteroide[], int quantidade);
void iniciarAsteroides(Asteroide asteroides[], int quantidade, float velocidadeExtra);
#endif