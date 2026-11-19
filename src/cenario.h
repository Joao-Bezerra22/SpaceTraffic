#ifndef CENARIO_H
#define CENARIO_H

#define NUM_ESTRELAS 100
#define MAX_PLANETAS 4

typedef struct {
    float x;
    float y;
} Estrela;

typedef enum {
    planeta_venus,
    planeta_terra,
    planeta_marte,
    planeta_jupiter
} TipoPlaneta;

typedef struct {
    Vector2 posicao;
    float raio;
    TipoPlaneta tipo;
    float velocidadeBase;
    int lapPertencente;
} Planeta;

void iniciarEstrelas(Estrela estrelas[]);
void atualizarEstrelas(Estrela estrelas[], float velocidadeExtra);
void desenharEstrelas(Estrela estrelas[]);

void iniciarPlanetas(Planeta planetas[]);
void atualizarPlanetas(Planeta planetas[], float dt, float velocidadeExtra, int lapAtual);
void desenharPlanetas(Planeta planetas[], int lapAtual);

#endif