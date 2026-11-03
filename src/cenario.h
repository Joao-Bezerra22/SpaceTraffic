#ifndef CENARIO_H
#define CENARIO_H

#define NUM_ESTRELAS 100

typedef struct {
    float x;
    float y;
} Estrela;

void iniciarEstrelas(Estrela estrelas[]);
void atualizarEstrelas(Estrela estrelas[], float velocidadeExtra);
void desenharEstrelas(Estrela estrelas[]);

#endif