#include "minheap.h"
#include "graph.h"
#include "list.h"
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int vertice_idx;
    double distancia;
}HeapNode;


struct MinHeap_s{
    int tamanho_atual;
    int capacidade;
    int *pos;
    HeapNode *vetor;
};


MinHeap createMinHeap(int max_vertices){
    MinHeap h = (MinHeap) malloc(sizeof(struct MinHeap_s));
    if(!h){
        return NULL;
    }

    h->tamanho_atual = 0;
    h->capacidade = max_vertices;
    h->pos = (int*) malloc(max_vertices * sizeof(int));
    h->vetor = (HeapNode*) malloc(max_vertices * sizeof(HeapNode));

    if(!h->pos || !h->vetor){
        free(h->pos);
        free(h->vetor);
        free(h);
        return NULL;
    }

    for(int i = 0; i < max_vertices; i++){
        h->pos[i] = -1;
    }

    return h;
}


void freeMinHeap(MinHeap h){
    if(!h){
        return;
    }

    free(h->pos);
    free(h->vetor);
    free(h);
    return;
}

bool isMinHeapEmpty(MinHeap h){
    return (h->tamanho_atual == 0);
}

bool isVertexInHeap(MinHeap h, int vertice_idx){
    if(!h || vertice_idx < 0 || vertice_idx >= h->capacidade){
        return false;
    }else{
        return (h->pos[vertice_idx] != -1);
    }
}



