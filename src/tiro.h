#ifndef TIRO_H
#define TIRO_H
#define VELOCIDADE_TIRO 10

#include "raylib.h"

typedef struct Tiro {
    Vector2 posicao;
    struct Tiro* next;
} Tiro;

Tiro *adicionarTiro(Tiro *lista, Vector2 posicao);
void desenharTiros(Tiro *lista);
void atualizarTiros(Tiro *lista);
void liberarTiros(Tiro *lista);

#endif