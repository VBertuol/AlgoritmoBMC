#include "FilaEstatica.h"

//arquivo reutilizado do Trabalho 1, apenas com as funcoes necessarias para o grafo//

//funcao que cria a fila estatica, armazenando um espaco de fila (struct)//
Fila *cria_Fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = f->fim = 0;
    return f;
}

//funcao que verifica se a fila esta vazia//
int vazia_Fila(Fila *f) {
    if(f->inicio == f->fim)
        return 1;
    return 0;
}

//funcao que insere o numero de um programa na fila (no fim dela)//
void push_Fila(Fila *f, int x) {
    f->v[f->fim] = x;
    f->fim = (f->fim + 1) % MAX;
}

//funcao que remove o numero de um programa da fila e o retorna (do inicio dela)//
int pop_Fila(Fila *f) {
    int x = f->v[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    return x;
}