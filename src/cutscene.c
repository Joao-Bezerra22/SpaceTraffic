#include "cutscene.h"
#include <raymath.h>
#include <math.h>

static const char *arquivosCenas[NUM_CENAS] = {
    "assets/cena_1_16x9.png",      // cena 1: casa em Marte
    "assets/cena_2_16x9.png",   // cena 2: alien acordando
    "assets/cena_3_16x9.png",   // cena 3: celular
    "assets/Cena_4_16x9.png"    // cena 4: nave no espaço
};

void carregarCutscene(Cutscene *c) {
    for (int i = 0; i < NUM_CENAS; i++) {
        c->cenas[i] = LoadTexture(arquivosCenas[i]);
        SetTextureFilter(c->cenas[i], TEXTURE_FILTER_POINT); // pixel art nítido
    }
    iniciarCutscene(c);
}

void iniciarCutscene(Cutscene *c) {
    c->cenaAtual = 0;
    c->tempoCena = 0.0f;
    c->tempoFim = 0.0f;
    c->emDelayFinal = false;
}

bool atualizarCutscene(Cutscene *c, float dt) {
    if (c->emDelayFinal) {
        c->tempoFim += dt;
        return c->tempoFim >= DELAY_FIM_SLIDESHOW;
    }

    c->tempoCena += dt;

    if (IsKeyPressed(KEY_SPACE) || c->tempoCena >= TEMPO_AUTO_CENA) {
        c->cenaAtual++;
        c->tempoCena = 0.0f;

        if (c->cenaAtual >= NUM_CENAS) {
            c->emDelayFinal = true;
            c->tempoFim = 0.0f;
        }
    }
    return false;
}

bool cutsceneMostrandoImagem(const Cutscene *c) {
    return !c->emDelayFinal;
}

void desenharCutscene(const Cutscene *c) {
    if (c->emDelayFinal) return;   // delay: só fundo preto com estrelas

    Texture2D t = c->cenas[c->cenaAtual];
    float escala = fminf((float)GetScreenWidth() / t.width, (float)GetScreenHeight() / t.height);
    float w = t.width * escala;
    float h = t.height * escala;

    Rectangle origem  = { 0, 0, (float)t.width, (float)t.height };
    Rectangle destino = { (GetScreenWidth() - w) / 2.0f, (GetScreenHeight() - h) / 2.0f, w, h };
    float alpha = Clamp(c->tempoCena / TEMPO_FADE_CENA, 0.0f, 1.0f);

    DrawTexturePro(t, origem, destino, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));

    const char *dica = TextFormat("%d/%d  -  ESPACO para continuar", c->cenaAtual + 1, NUM_CENAS);
    int larguraDica = MeasureText(dica, 20);
    int xDica = (GetScreenWidth() - larguraDica) / 2;
    int yDica = GetScreenHeight() - 35;
    DrawText(dica, xDica + 2, yDica + 2, 20, BLACK);   // sombra
    DrawText(dica, xDica, yDica, 20, WHITE);
}

void liberarCutscene(Cutscene *c) {
    for (int i = 0; i < NUM_CENAS; i++) UnloadTexture(c->cenas[i]);
}