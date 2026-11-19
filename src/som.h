#ifndef SOM_H
#define SOM_H

#include "raylib.h"

#define ARQ_SOM_TIRO      "sons/414886__lilmati__retro-laser-shot-02.wav"
#define ARQ_SOM_EXPLOSAO  "sons/506326__thevoicesgames__retro-explosion-1.wav"
#define ARQ_SOM_DANO "sons/330629__stormwaveaudio__sci-fi-force-field-impact-15.wav"


#define POOL_TIRO      6
#define POOL_EXPLOSAO  6
#define POOL_DANO 6

#define ARQ_TRILHA_MENU      "sons/TELA_INICIAL.wav"
#define ARQ_TRILHA_CUTSCENE  "sons/CUTSCENE.wav"
#define ARQ_TRILHA_JOGO      "sons/JOGANDO.wav.wav"

typedef enum {
    TRILHA_NENHUMA = -1,
    TRILHA_MENU = 0,
    TRILHA_CUTSCENE,
    TRILHA_JOGO,
    NUM_TRILHAS
} Trilha;

typedef struct {
    Sound tiros[POOL_TIRO];
    Sound explosoes[POOL_EXPLOSAO];
    Sound danos[POOL_DANO];
    int proximoTiro;
    int proximaExplosao;
    int proximoDano;

    Music trilhas[NUM_TRILHAS];
    Trilha trilhaAtual;

} Som;


void carregarSom(Som *som);

void tocarSomTiro(Som *som);
void tocarSomExplosao(Som *som);
void tocarSomDano(Som *som);

void tocarTrilha(Som *som, Trilha trilha);
void atualizarSom(Som *som);

void liberarSom(Som *som);

#endif