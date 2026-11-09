#include "stdlib.h"
#include "tiro.h"

Tiro *adicionarTiro(Tiro *lista, Vector2 posicao){
    Tiro *novoTiro = malloc(sizeof(Tiro));

    if(novoTiro == NULL) return lista;

    novoTiro->posicao = posicao;
    novoTiro->next = lista;

    return novoTiro;
}

void desenharTiros(Tiro *lista) {
    Tiro *atual = lista;

    while (atual != NULL) {
        DrawRectangle(atual->posicao.x, atual->posicao.y, 4, 12, YELLOW);
        atual = atual->next;
    }
}