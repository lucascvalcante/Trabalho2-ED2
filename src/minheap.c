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


static void heapifyDown(MinHeap h, int idx){
    int menor, esquerda, direita;

    while(1){
        menor = idx;
        esquerda = 2 * idx + 1;
        direita = 2 * idx + 2;

        if(esquerda < h->tamanho_atual && h->vetor[esquerda].distancia < h->vetor[menor].distancia){
            menor = esquerda;
        }    

        if(direita < h->tamanho_atual && h->vetor[direita].distancia < h->vetor[menor].distancia){
            menor = direita;
        }

        if(menor != idx){
            swapNodes(h, idx, menor);
            idx = menor;
        }else{
            break;
        }
    }
}



/// --Funções principais: --///

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



void updateDistance(MinHeap h, int vertice_idx, double nova_distancia){
    if(!h || vertice_idx < 0 || vertice_idx >= h->capacidade){
        return;
    } 

    int i = h->posicao[vertice_idx];

    if(i == -1){
        i = h->tamanho_atual;
        h->tamanho_atual++;

        h->vetor[i].vertice_idx = vertice_idx;
        h->vetor[i].distancia = nova_distancia;
        h->posicao[vertice_idx] = i;

        heapifyUp(h, i);

    }else if(nova_distancia < h->vetor[i].distancia){
        h->vetor[i].distancia = nova_distancia;
        heapifyUp(h, i);
    }
}


int extractMin(MinHeap h){
    if(isMinHeapEmpty(h)){
        return -1;
    }

    int vertice_menor = h->vetor[0].vertice_idx;
    HeapNode ultimo_no = h->vetor[h->tamanho_atual - 1];
    h->posicao[vertice_menor] = -1;
    h->tamanho_atual--;

    if(h->tamanho_atual > 0){
        h->vetor[0] = ultimo_no;
        h->posicao[ultimo_no.vertice_idx] = 0;
        heapifyDown(h, 0);
    }
    return vertice_menor;
}