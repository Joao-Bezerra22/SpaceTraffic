#include "jogo.h"

void reiniciarJogo(Jogo *jogo) {
    iniciarNave(&jogo->nave);

    liberarTiros(jogo->listaTiros);
    jogo->listaTiros = NULL;

    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        jogo->asteroides[i].ativo = false;
    }

    jogo->tempoContagem = 3.0f;
    jogo->tempoUltimoSpawn = 0.0f;
    jogo->tempoJogo = 0.0f;

    jogo->velocidadeKMH = 100.0f;
    jogo->velocidadeExtraAsteroides = 0.0f;

    jogo->lapAtual = 1;
    jogo->tempoParaLap = 20.0f;
    jogo->linhaLapAtiva = false;
    jogo->posicaoLinhaLapY = -10.0f;

    jogo->spawnRateAtual = 0.8f;
    jogo->limiteMinimoAtual = SPAWN_MINIMO_LAP1;
}