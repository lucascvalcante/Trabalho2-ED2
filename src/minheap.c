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
    int *posicao;
    HeapNode *vetor;
};


/// -Funções internas auxiliares: -///
static void swapNodes(MinHeap h, int idx1, int idx2){
   HeapNode temp = h->vetor[idx1];
   
   h->vetor[idx1] = h->vetor[idx2];
   h->vetor[idx2] = temp;

   h->posicao[h->vetor[idx1].vertice_idx] = idx1;
   h->posicao[h->vetor[idx2].vertice_idx] = idx2;    
}


static void heapifyUp(MinHeap h, int idx){
    int parent_Idx = (idx - 1) / 2;
    
    while(idx > 0 && h->vetor[idx].distancia < h->vetor[parent_Idx].distancia){
        swapNodes(h, idx, parent_Idx);
        idx = parent_Idx;
        parent_Idx = (idx - 1) / 2;
    }
}



MinHeap createMinHeap(int max_vertices){
    MinHeap h = (MinHeap) malloc(sizeof(struct MinHeap_s));
    if(!h){
        return NULL;
    }

    h->tamanho_atual = 0;
    h->capacidade = max_vertices;
    h->posicao = (int*) malloc(max_vertices * sizeof(int));
    h->vetor = (HeapNode*) malloc(max_vertices * sizeof(HeapNode));

    if(!h->posicao || !h->vetor){
        free(h->posicao);
        free(h->vetor);
        free(h);
        return NULL;
    }

    for(int i = 0; i < max_vertices; i++){
        h->posicao[i] = -1;
    }

    return h;
}


void freeMinHeap(MinHeap h){
    if(!h){
        return;
    }

    free(h->posicao);
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
        return (h->posicao[vertice_idx] != -1);
    }
}

