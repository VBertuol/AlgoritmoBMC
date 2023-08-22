#include "grafo.h"

//funcao que cria um grafo//
grafo *cria_grafo() {
    int i;
    grafo *novo = (grafo *)malloc(sizeof(grafo));
    for(i=0;i<TAM;i++)
        novo->lista[i] = NULL;
    return novo;
}

//funcao que insere um elemento no final da lista//
nodo *insere_lista(nodo *lista, int y) {
    if (lista == NULL) {
        nodo *novo = (nodo *)malloc(sizeof(nodo));
        novo->pos = y;
        novo->prox = NULL;
        return novo;
    }
    lista->prox = insere_lista(lista->prox, y);
    return lista;
}

//funcao que insere um elemento no grafo (uma posicao do mapa e seus vizinhos)//
grafo *push_grafo(grafo *mapa, int x, int y) {
    mapa->lista[x] = insere_lista(mapa->lista[x], y);
    return mapa;
}