#ifndef FILAESTATICA
#define FILAESTATICA

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//arquivo reutilizado do Trabalho 1, apenas com as funcoes necessarias para o grafo//

//estrutura da fila estatica (um vetor e variaveis que apontam o inicio e o final da fila no vetor)//
typedef struct {
    int v[MAX];
    int inicio, fim;
}Fila;

Fila *cria_Fila();

int vazia_Fila(Fila *f);

void push_Fila(Fila *f, int x);

int pop_Fila(Fila *f);

#endif