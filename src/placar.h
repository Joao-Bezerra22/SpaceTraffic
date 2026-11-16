#ifndef PLACAR_H
#define PLACAR_H

#define MAX_TOPSCORES 5
#define ARQUIVO_TOPSCORES "topscores.txt"

typedef struct {
    int pontos[MAX_TOPSCORES];   
    int quantidade;              
} Placar;

void carregarPlacar(Placar *placar);
void salvarPlacar(Placar placar);
int registrarPontuacao(Placar *placar, int pontos);
void desenharTopScores(Placar placar);

#endif
