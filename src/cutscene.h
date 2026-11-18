#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "raylib.h"
#include <stdbool.h>

#define NUM_CENAS            4
#define TEMPO_AUTO_CENA      20.0f   // segundos até passar sozinho
#define DELAY_FIM_SLIDESHOW  1.5f    // pausa depois da última cena
#define TEMPO_FADE_CENA      0.4f    // fade-in de cada cena

typedef struct {
    Texture2D cenas[NUM_CENAS];
    int cenaAtual;
    float tempoCena;
    float tempoFim;
    bool emDelayFinal;
} Cutscene;

void carregarCutscene(Cutscene *c);              // carrega as texturas (chamar 1 vez)
void iniciarCutscene(Cutscene *c);               // reseta para a cena 1
bool atualizarCutscene(Cutscene *c, float dt);   // retorna true quando acabou (já com o delay)
bool cutsceneMostrandoImagem(const Cutscene *c); // false durante o delay final
void desenharCutscene(const Cutscene *c);
void liberarCutscene(Cutscene *c);

#endif