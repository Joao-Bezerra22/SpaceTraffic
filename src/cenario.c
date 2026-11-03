#include "raylib.h"
#include "cenario.h"

void iniciarEstrelas(Estrela estrelas[]) {
   for(int i = 0; i<NUM_ESTRELAS; i++){
        estrelas[i].x = GetRandomValue(0, GetScreenWidth());
        estrelas[i].y = GetRandomValue(0, GetScreenHeight());
    }
}

void atualizarEstrelas(Estrela estrelas[], float velocidadeExtra) {
    for(int i = 0; i<NUM_ESTRELAS; i++){
        estrelas[i].y = estrelas[i].y + 1.0f + (velocidadeExtra/ 50.0f);
        if(estrelas[i].y > GetScreenHeight() || estrelas[i].x > GetScreenWidth()){
                estrelas[i].y = 0.0f;
                estrelas[i].x = (float)GetRandomValue(0, GetScreenWidth());
        }
    }
}

void desenharEstrelas(Estrela estrelas[]) {
    for(int i = 0; i<NUM_ESTRELAS; i++){
        DrawCircle((int)estrelas[i].x,(int)estrelas[i].y, 1, WHITE);
    }
}