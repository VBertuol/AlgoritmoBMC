#include "FilaDinamica.h"

//arquivo reutilizado do Trabalho 1, apenas com as funcoes necessarias para o grafo//

//funcao que cria a fila dinamica, armazenando um espaco de fila (struct)//
Fila *cria_Fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

//funcao que verifica se a fila esta vazia//
int vazia_Fila(Fila *f) {
    if(f->inicio == NULL)
        return 1;
    return 0;
}

//funcao que insere o numero de um programa na fila (no fim dela)//
void push_Fila(Fila *f, int x) {
    nodo_Fila *novo = (nodo_Fila *)malloc(sizeof(nodo_Fila));
    novo->info = x;
    novo->prox = NULL;
    if(f->fim != NULL)
        f->fim->prox = novo;
    f->fim = novo;
    if(f->inicio == NULL)
        f->inicio = novo;
}

//funcao que remove o numero de um programa da fila e o retorna (do inicio dela)//
int pop_Fila(Fila *f) {
    int x = f->inicio->info;
    nodo_Fila *aux = f->inicio->prox;
    if(f->fim == f->inicio)
        f->fim = NULL;
    free(f->inicio);
    f->inicio = aux;
    return x;
}