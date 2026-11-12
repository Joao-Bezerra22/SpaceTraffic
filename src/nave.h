#ifndef NAVE_H
#define NAVE_H
#define DISTANCIA_DO_CHAO 120.0f

#include "raylib.h"

typedef struct {
    Vector2 posicao;     
    float largura;       
    float altura;
    float velocidade;  
    int vidas; 
} Nave;

void iniciarNave(Nave *nave);
void atualizarNave(Nave *nave);
void desenharNave(Nave nave);
void posicionarNaveNoInicio(Nave *nave);

#endif