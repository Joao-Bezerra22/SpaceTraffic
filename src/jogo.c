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

    jogo->velocidadeKMH = VELOCIDADE_INICIAL_KMH;
    jogo->velocidadeExtraAsteroides = 0.0f;

    jogo->lapAtual = 1;
    jogo->tempoParaLap = TEMPO_ENTRE_LAPS;
    jogo->linhaLapAtiva = false;
    jogo->posicaoLinhaLapY = -10.0f;

    jogo->spawnRateAtual = 0.8f;
    jogo->limiteMinimoAtual = SPAWN_MINIMO_LAP1;

    jogo->pontuacao = 0.0f;
}