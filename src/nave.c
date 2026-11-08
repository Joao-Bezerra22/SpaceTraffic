#include "nave.h"
#define NAVE_LINHAS 8
#define NAVE_COLUNAS 8

int desenhoNave[NAVE_LINHAS][NAVE_COLUNAS] = {
    {0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,0,1,1,0,1,1},
    {1,0,0,0,0,0,0,1},
};

void iniciarNave(Nave *nave) {
    nave->largura = 40;
    nave->altura = 40;
    nave->posicao.x = (GetScreenWidth() - nave->largura) / 2;
    nave->posicao.y = GetScreenHeight() - 120.0f;
    nave->velocidade = 5;
    nave->vidas = 3;
}

void desenharNave(Nave nave) {
   int tamanho = nave.largura / NAVE_COLUNAS;

    for (int linha = 0; linha < NAVE_LINHAS; linha++) {
        for (int coluna = 0; coluna < NAVE_COLUNAS; coluna++) {
            if (desenhoNave[linha][coluna] == 1) {
                DrawRectangle(
                    nave.posicao.x + coluna * tamanho,
                    nave.posicao.y + linha * tamanho,
                    tamanho, tamanho, WHITE);
            }
        }
    }
}

void atualizarNave(Nave *nave) {
    if (IsKeyDown(KEY_LEFT)) {
        nave->posicao.x -= nave->velocidade;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        nave->posicao.x += nave->velocidade;
    }

    if(IsKeyDown(KEY_UP)) {
        nave->posicao.y -= nave->velocidade;
    }

    if(IsKeyDown(KEY_DOWN)) {
        nave->posicao.y += nave->velocidade;
    }

    float limiteX = GetScreenWidth() - nave->largura;
    float limiteY = GetScreenHeight() - nave->altura;

    if (nave->posicao.x < 0)        nave->posicao.x = 0;
    if (nave->posicao.x > limiteX)  nave->posicao.x = limiteX;
    if (nave->posicao.y < 0)        nave->posicao.y = 0;
    if (nave->posicao.y > limiteY)  nave->posicao.y = limiteY;
}