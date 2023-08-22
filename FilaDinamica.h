#ifndef FILADINAMICA
#define FILADINAMICA

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//arquivo reutilizado do Trabalho 1, apenas com as funcoes necessarias para o grafo//

//estrutura da lista ligada da fila (variavel que recebe a informacao e ponteiro para o proximo nodo)//
typedef struct Nodo_Fila{
    int info;
    struct Nodo_Fila *prox;
}nodo_Fila;

//estrutura da fila dinamica (um nodo que eh o inicio (a cabeca) da lista e outro que eh o fim (ultimo nodo))//
typedef struct {
    nodo_Fila *inicio;
    nodo_Fila *fim;
}Fila;

Fila *cria_Fila();

int vazia_Fila(Fila *f);

void push_Fila(Fila *f, int x);

int pop_Fila(Fila *f);

#endif