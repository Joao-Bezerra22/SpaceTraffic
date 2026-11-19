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

void iniciarPlanetas(Planeta planetas[]) {
    planetas[0].posicao = (Vector2){ GetScreenWidth() * 0.25f, -220.0f };
    planetas[0].raio = 11.5f;
    planetas[0].tipo = planeta_venus;
    planetas[0].velocidadeBase = 32.0f;
    planetas[0].lapPertencente = 1;

    planetas[1].posicao = (Vector2){ GetScreenWidth() * 0.75f, -580.0f };
    planetas[1].raio = 12.5f;
    planetas[1].tipo = planeta_terra;
    planetas[1].velocidadeBase = 35.0f;
    planetas[1].lapPertencente = 1;

    planetas[2].posicao = (Vector2){ GetScreenWidth() * 0.30f, -270.0f };
    planetas[2].raio = 10.5f;
    planetas[2].tipo = planeta_marte;
    planetas[2].velocidadeBase = 33.0f;
    planetas[2].lapPertencente = 2;

    planetas[3].posicao = (Vector2){ GetScreenWidth() * 0.70f, -425.0f };
    planetas[3].raio = 17.5f;
    planetas[3].tipo = planeta_jupiter;
    planetas[3].velocidadeBase = 38.0f;
    planetas[3].lapPertencente = 2;
}

void atualizarPlanetas(Planeta planetas[], float dt, float velocidadeExtra, int lapAtual) {
    for (int i = 0; i < MAX_PLANETAS; i++) {
        if (planetas[i].lapPertencente != lapAtual) continue;

        float velocidadeReal = planetas[i].velocidadeBase + (velocidadeExtra * 0.15f);
        planetas[i].posicao.y += velocidadeReal * dt;

        if (planetas[i].posicao.y - planetas[i].raio > GetScreenHeight() + 50.0f) {
            planetas[i].posicao.y = -700.0f;
            planetas[i].posicao.x = (float)GetRandomValue(60, GetScreenWidth() - 60);
        }
    }
}

void desenharPlanetas(Planeta planetas[], int lapAtual) {
    for (int i = 0; i < MAX_PLANETAS; i++) {
        if (planetas[i].lapPertencente != lapAtual) continue;

        int x = (int)planetas[i].posicao.x;
        int y = (int)planetas[i].posicao.y;
        float r = planetas[i].raio;

        if (planetas[i].tipo == planeta_venus) {
            DrawCircle(x, y, r, (Color){ 215, 155, 65, 255 });
            DrawEllipse(x, y - (int)(r * 0.35f), r * 0.78f, r * 0.16f, (Color){ 238, 195, 110, 255 });
            DrawEllipse(x + (int)(r * 0.1f), y + (int)(r * 0.15f), r * 0.85f, r * 0.18f, (Color){ 185, 120, 45, 255 });
            DrawEllipse(x - (int)(r * 0.1f), y + (int)(r * 0.52f), r * 0.62f, r * 0.14f, (Color){ 235, 185, 95, 255 });
        }
        else if (planetas[i].tipo == planeta_terra) {
            DrawCircle(x, y, r, (Color){ 35, 105, 210, 255 });

            DrawCircle(x - (int)(r * 0.32f), y - (int)(r * 0.15f), r * 0.38f, (Color){ 55, 165, 75, 255 });
            DrawCircle(x - (int)(r * 0.18f), y + (int)(r * 0.25f), r * 0.28f, (Color){ 55, 165, 75, 255 });
            DrawCircle(x + (int)(r * 0.35f), y + (int)(r * 0.10f), r * 0.34f, (Color){ 55, 165, 75, 255 });

            DrawEllipse(x, y - (int)(r * 0.78f), r * 0.48f, r * 0.16f, RAYWHITE);
            DrawEllipse(x, y + (int)(r * 0.78f), r * 0.45f, r * 0.15f, RAYWHITE);
        }
        else if (planetas[i].tipo == planeta_marte) {
            DrawCircle(x, y, r, (Color){ 195, 75, 45, 255 });
            DrawCircle(x - (int)(r * 0.25f), y + (int)(r * 0.10f), r * 0.32f, (Color){ 145, 48, 28, 255 });
            DrawCircle(x + (int)(r * 0.28f), y - (int)(r * 0.15f), r * 0.22f, (Color){ 145, 48, 28, 255 });
            DrawEllipse(x, y - (int)(r * 0.78f), r * 0.42f, r * 0.14f, RAYWHITE);
        }
        else if (planetas[i].tipo == planeta_jupiter) {
            DrawCircle(x, y, r, (Color){ 210, 180, 140, 255 });
            DrawEllipse(x, y - (int)(r * 0.42f), r * 0.85f, r * 0.14f, (Color){ 165, 110, 70, 255 });
            DrawEllipse(x, y + (int)(r * 0.05f), r * 0.94f, r * 0.16f, (Color){ 180, 120, 75, 255 });
            DrawEllipse(x, y + (int)(r * 0.48f), r * 0.80f, r * 0.13f, (Color){ 155, 100, 65, 255 });
            DrawEllipse(x + (int)(r * 0.25f), y + (int)(r * 0.24f), r * 0.26f, r * 0.15f, (Color){ 195, 70, 45, 255 });
        }
    }
}