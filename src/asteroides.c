#include "asteroides.h"
#include <raymath.h>

Asteroide criarAsteroide(AsteroideTipo tipo, Vector2 posicao, Vector2 velocidade)
{
    Asteroide asteroide = {
        .ativo = true,
        .posicao = posicao,
        .tipo = tipo,
        .rotacao = GetRandomValue(0, 360),
        .velocidaderotacao = GetRandomValue(ASTEROIDE_ROTACAO_VELOCIDADE_MIN, ASTEROIDE_ROTACAO_VELOCIDADE_MAX),
        .velocidade = velocidade
    };
    return asteroide;
};

void AsteroidAtualizar(Asteroide *asteroide, float FrameTime, float velocidadeExtra)
{
    if(!asteroide->ativo) return;

    Vector2 velocidadeReal = asteroide->velocidade;
    velocidadeReal.y += velocidadeExtra;

    asteroide->posicao = Vector2Add(asteroide->posicao,
        Vector2Scale(velocidadeReal, FrameTime));
    asteroide->rotacao += asteroide->velocidaderotacao * FrameTime;
}

void iniciarAsteroides(Asteroide asteroides[], int qtd, float velocidadeExtra) {
    for (int i = 0; i < qtd; i++) {
        if (!asteroides[i].ativo) {
            AsteroideTipo tipo = GetRandomValue(1, 3);
            
            Vector2 pos = { (float)GetRandomValue(0, GetScreenWidth()), -50.0f };

            Vector2 vel = { 0.0f, (float)GetRandomValue(20, 50)};
            
            asteroides[i] = criarAsteroide(tipo, pos, vel);
            break;
        }
    }
}

void desenharAsteroide(Asteroide asteroides[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (asteroides[i].ativo) {
            float raio = 20.0f;
            
            if (asteroides[i].tipo == ASTEROIDE_PEQUENO) raio = 15.0f;
            else if (asteroides[i].tipo == ASTEROIDE_MEDIO) raio = 30.0f;
            else if (asteroides[i].tipo == ASTEROIDE_GRANDE) raio = 50.0f;

            DrawPoly(asteroides[i].posicao, 7, raio, asteroides[i].rotacao, DARKGRAY);
            DrawPolyLines(asteroides[i].posicao, 7, raio, asteroides[i].rotacao, LIGHTGRAY);
        }
    }
}