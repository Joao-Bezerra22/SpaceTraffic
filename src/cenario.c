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
    int topo = y - (int)marte.raio;

     // O centro fica fora da tela: só a "calota" de cima do planeta aparece
    DrawCircle(x, y, marte.raio + 18.0f, (Color){ 210, 80, 40, 20 });
    DrawCircle(x, y, marte.raio + 8.0f,  (Color){ 225, 95, 50, 45 });
    DrawCircle(x, y, marte.raio, (Color){ 204, 82, 46, 255 });
    DrawCircle(x, y + 20, marte.raio - 8.0f, (Color){ 180, 64, 34, 255 });

    // Crateras: { deslocamento em x, distância do topo, largura }
    static const int crateras[][3] = {
        { -340, 90, 45 }, { -260, 75, 16 }, { -210, 55, 55 }, { -110, 42, 18 }, { -40, 78, 80 },
        {   95, 62, 24 }, {  180, 48, 65 }, {  240, 72, 20 }, {  320, 85, 50 },
    };
    for (int i = 0; i < (int)(sizeof(crateras) / sizeof(crateras[0])); i++) {
        int cx = x + crateras[i][0];
        int cy = topo + crateras[i][1];
        float w = (float)crateras[i][2];
        DrawEllipse(cx, cy,     w,        w / 3.0f, (Color){ 222, 102, 62, 200 });
        DrawEllipse(cx, cy + 1, w * 0.8f, w / 4.0f, (Color){ 135,  40, 20, 220 });
    }
}

void desenharJupiter(float baseY) {
    float r = GetScreenWidth() * 0.55f;
    int cx = GetScreenWidth() / 2;
    float cy = baseY - r;   // baseY = ponto mais baixo do planeta (onde ficava a linha)

    DrawCircle(cx, (int)cy, r + 10.0f, (Color){ 225, 195, 155, 45 });   // brilho

    // Faixas: cada linha horizontal tem a largura do círculo naquela altura e um brilho que oscila
    for (int y = (int)(cy - r); y < (int)baseY; y += 2) {
        float dy = y - cy;
        float meia = sqrtf(fmaxf(0.0f, r * r - dy * dy));
        float k = 0.85f + 0.15f * sinf(dy * 0.07f) + 0.08f * sinf(dy * 0.19f);
        Color cor = { (unsigned char)(210 * k), (unsigned char)(170 * k), (unsigned char)(125 * k), 255 };
        DrawRectangle((int)(cx - meia), y, (int)(2.0f * meia), 2, cor);
    }

    // Grande Mancha Vermelha
    DrawEllipse(cx + (int)(r * 0.35f), (int)(cy + r * 0.45f), r * 0.14f, r * 0.06f, (Color){ 195, 70, 45, 255 });
}