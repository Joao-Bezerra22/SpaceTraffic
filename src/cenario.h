#ifndef CENARIO_H
#define CENARIO_H

#include "raylib.h"
#include "raymath.h"
#include <math.h>

#define NUM_ESTRELAS 100

typedef struct {
    float x;
    float y;
} Estrela;

typedef struct {
    Vector2 posicao;
    float raio;
    bool ativo;
} Marte;

void iniciarEstrelas(Estrela estrelas[]);
void atualizarEstrelas(Estrela estrelas[], float velocidadeExtra);
void desenharEstrelas(Estrela estrelas[]);

void iniciarMarte(Marte *marte);
void atualizarMarte(Marte *marte, float dt, float velocidadeExtra);
void desenharMarte(Marte marte);

void desenharJupiter(float baseY);

#endif