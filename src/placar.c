#include <stdio.h>
#include "raylib.h"
#include "placar.h"

void carregarPlacar(Placar *placar) {
    placar->quantidade = 0;

    FILE *arquivo = fopen(ARQUIVO_TOPSCORES, "r");
    if (arquivo == NULL) {
        return;
    }

    while (placar->quantidade < MAX_TOPSCORES &&
           fscanf(arquivo, "%d", &placar->pontos[placar->quantidade]) == 1) {
        placar->quantidade++;
    }

    fclose(arquivo);
}

void salvarPlacar(Placar placar) {
    FILE *arquivo = fopen(ARQUIVO_TOPSCORES, "w");
    if (arquivo == NULL) {
        return;
    }

    for (int i = 0; i < placar.quantidade; i++) {
        fprintf(arquivo, "%d\n", placar.pontos[i]);
    }

    fclose(arquivo);
}

int registrarPontuacao(Placar *placar, int pontos) {
    if (pontos <= 0) {
        return -1;
    }

    int posicao = placar->quantidade;
    for (int i = 0; i < placar->quantidade; i++) {
        if (placar->pontos[i] < pontos) {
            posicao = i;
            break;
        }
    }

    if (posicao >= MAX_TOPSCORES) {
        return -1;
    }

    
    int ultimo = placar->quantidade;
    if (ultimo >= MAX_TOPSCORES) {
        ultimo = MAX_TOPSCORES - 1;  
    }
    for (int i = ultimo; i > posicao; i--) {
        placar->pontos[i] = placar->pontos[i - 1];
    }

    placar->pontos[posicao] = pontos;
    if (placar->quantidade < MAX_TOPSCORES) {
        placar->quantidade++;
    }

    return posicao;
}

void desenharTopScores(Placar placar) {
    int larguraTitulo = MeasureText("TOP SCORES", 50);
    DrawText("TOP SCORES", (GetScreenWidth() - larguraTitulo) / 2, 50, 50, YELLOW);

    if (placar.quantidade == 0) {
        const char *vazio = "Nenhuma pontuacao ainda";
        int larguraVazio = MeasureText(vazio, 25);
        DrawText(vazio, (GetScreenWidth() - larguraVazio) / 2, 180, 25, LIGHTGRAY);
        return;
    }

    for (int i = 0; i < placar.quantidade; i++) {
        const char *linha = TextFormat("%d.  %d", i + 1, placar.pontos[i]);
        int larguraLinha = MeasureText(linha, 30);
        Color cor = (i == 0) ? GOLD : WHITE;
        DrawText(linha, (GetScreenWidth() - larguraLinha) / 2, 130 + i * 40, 30, cor);
    }
}
