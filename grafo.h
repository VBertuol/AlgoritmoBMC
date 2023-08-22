#ifndef GRAFO
#define GRAFO

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define TAM 10000

//define a estrutura da lista ligada (um inteiro com a posicao do mapa e um ponteiro para o proximo nodo)//
typedef struct Nodo{
    int pos;
    struct Nodo *prox;
}nodo;

//define a estrutura do grafo (lista de adjacencia)//
typedef struct Grafo{
    nodo *lista[TAM];
}grafo;

grafo *cria_grafo();

nodo *insere_lista(nodo *lista, int y);

grafo *push_grafo(grafo *mapa, int x, int y);

#endif