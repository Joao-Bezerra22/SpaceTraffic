#ifndef TIRO_H
#define TIRO_H

#include "raylib.h"

typedef struct Tiro {
    Vector2 posicao;
    struct Tiro* next;
} Tiro;

Tiro *adicionarTiro(Tiro *lista, Vector2 posicao);
void desenharTiros(Tiro *lista);

#endif