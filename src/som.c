#include "som.h"

void carregarSom(Som *som) {
    InitAudioDevice();

    som->proximoTiro = 0;
    som->proximaExplosao = 0;
    som->proximoDano = 0;
    som->trilhaAtual = TRILHA_NENHUMA;

    Wave waveTiro = LoadWave(ARQ_SOM_TIRO);
    Wave waveExplosao = LoadWave(ARQ_SOM_EXPLOSAO);
    Wave waveDano = LoadWave(ARQ_SOM_DANO);

    for (int i = 0; i < POOL_TIRO; i++) {
        som->tiros[i] = LoadSoundFromWave(waveTiro);
        SetSoundVolume(som->tiros[i], 0.6f);
    }
    for (int i = 0; i < POOL_EXPLOSAO; i++) {
        som->explosoes[i] = LoadSoundFromWave(waveExplosao);
        SetSoundVolume(som->explosoes[i], 0.7f);
    }
    for (int i = 0; i < POOL_DANO; i++) {
        som->danos[i] = LoadSoundFromWave(waveDano);
        SetSoundVolume(som->danos[i], 0.8f);
    }

    UnloadWave(waveTiro);
    UnloadWave(waveExplosao);
    UnloadWave(waveDano);
    som->trilhas[TRILHA_MENU]     = LoadMusicStream(ARQ_TRILHA_MENU);
    som->trilhas[TRILHA_CUTSCENE] = LoadMusicStream(ARQ_TRILHA_CUTSCENE);
    som->trilhas[TRILHA_JOGO]     = LoadMusicStream(ARQ_TRILHA_JOGO);

    for (int i = 0; i < NUM_TRILHAS; i++) {
         if (som->trilhas[i].frameCount == 0) {
            TraceLog(LOG_WARNING, "SOM: trilha %d NAO carregou (confira nome/pasta do arquivo)", i);
        }
        som->trilhas[i].looping = true;
        SetMusicVolume(som->trilhas[i], 0.5f);
    }
}

void tocarSomTiro(Som *som) {
    PlaySound(som->tiros[som->proximoTiro]);
    som->proximoTiro = (som->proximoTiro + 1) % POOL_TIRO;
}

void tocarSomExplosao(Som *som) {
    PlaySound(som->explosoes[som->proximaExplosao]);
    som->proximaExplosao = (som->proximaExplosao + 1) % POOL_EXPLOSAO;
}

void tocarSomDano(Som *som) {
    PlaySound(som->danos[som->proximoDano]);
    som->proximoDano = (som->proximoDano + 1) % POOL_DANO;
}

void tocarTrilha(Som *som, Trilha trilha) {
    if (trilha == som->trilhaAtual) return;

    if (som->trilhaAtual != TRILHA_NENHUMA) {
        StopMusicStream(som->trilhas[som->trilhaAtual]);
    }

    som->trilhaAtual = trilha;

    if (trilha != TRILHA_NENHUMA) {
        PlayMusicStream(som->trilhas[trilha]);
    }
}

void atualizarSom(Som *som) {
    if (som->trilhaAtual != TRILHA_NENHUMA) {
        UpdateMusicStream(som->trilhas[som->trilhaAtual]);
    }
}

void liberarSom(Som *som) {
    for (int i = 0; i < POOL_TIRO; i++) UnloadSound(som->tiros[i]);
    for (int i = 0; i < POOL_EXPLOSAO; i++) UnloadSound(som->explosoes[i]);
    for (int i = 0; i < POOL_DANO; i++) UnloadSound(som->danos[i]);
    for (int i = 0; i < NUM_TRILHAS; i++) UnloadMusicStream(som->trilhas[i]);
    CloseAudioDevice();
}