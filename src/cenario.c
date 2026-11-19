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

void iniciarMarte(Marte *marte) {
    marte->raio = GetScreenWidth() * 1.15f;
    marte->posicao.x = GetScreenWidth() / 2.0f;
    
    marte->posicao.y = GetScreenHeight() + marte->raio - 95.0f;
    marte->ativo = true;
}

void atualizarMarte(Marte *marte, float dt, float velocidadeExtra) {
    if (!marte->ativo) return;

    float velocidadeDecolagem = 180.0f + (velocidadeExtra * 0.5f);
    marte->posicao.y += velocidadeDecolagem * dt;

    if (marte->posicao.y - marte->raio > GetScreenHeight()) {
        marte->ativo = false;
    }
}

void desenharMarte(Marte marte) {
    if (!marte.ativo) return;

    int x = (int)marte.posicao.x;
    int y = (int)marte.posicao.y;
    float r = marte.raio;

    DrawCircle(x, y, r + 18.0f, (Color){ 210, 80, 40, 20 });
    DrawCircle(x, y, r + 8.0f,  (Color){ 225, 95, 50, 45 });

    DrawCircle(x, y, r, (Color){ 204, 82, 46, 255 });

    DrawCircle(x, y + 18, r - 6.0f,  (Color){ 186, 68, 36, 255 });
    DrawCircle(x, y + 42, r - 14.0f, (Color){ 165, 55, 28, 255 });

    int topo = y - (int)r;

    DrawEllipse(x - 210, topo + 55, 55, 12, (Color){ 145, 45, 22, 180 });
    DrawEllipse(x + 180, topo + 48, 65, 14, (Color){ 145, 45, 22, 180 });
    DrawEllipse(x - 40,  topo + 78, 80, 16, (Color){ 140, 42, 20, 190 });
    DrawEllipse(x + 320, topo + 85, 50, 11, (Color){ 145, 45, 22, 170 });
    DrawEllipse(x - 340, topo + 90, 45, 10, (Color){ 145, 45, 22, 170 });

    DrawEllipse(x - 110, topo + 42, 18, 6, (Color){ 222, 102, 62, 200 });
    DrawEllipse(x - 110, topo + 43, 14, 4, (Color){ 125, 36, 18, 230 });

    DrawEllipse(x + 95,  topo + 62, 24, 8, (Color){ 222, 102, 62, 200 });
    DrawEllipse(x + 95,  topo + 63, 19, 6, (Color){ 125, 36, 18, 230 });

    DrawEllipse(x - 260, topo + 75, 16, 5, (Color){ 222, 102, 62, 180 });
    DrawEllipse(x - 260, topo + 76, 12, 3, (Color){ 125, 36, 18, 220 });

    DrawEllipse(x + 240, topo + 72, 20, 6, (Color){ 222, 102, 62, 180 });
    DrawEllipse(x + 240, topo + 73, 15, 4, (Color){ 125, 36, 18, 220 });
}