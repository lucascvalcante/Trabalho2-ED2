#include "dijkstra.h"
#include <float.h>

Lista dijkstra(Graph g, int origem, int destino){
    int num_vertices = getNumVertices(g);

    double *dist = (double*) malloc(num_vertices * sizeof(double));
    int *pai = (int*) malloc(num_vertices * sizeof(int)); 

    for(int i = 0; i < num_vertices; i++){
        dist[i] = DBL_MAX;
        pai[i] = -1;
    }

    MinHeap fila = createMinHeap(num_vertices);
    dist[origem] = 0.0;
    updateDistance(fila, origem, 0.0);

    while(!isMinHeapEmpty(fila)){
        int u = extractMin(fila);
        if(u == destino){
            break;
        }

        Edge_t edge = getFirstEdge(g, u);

        while(edge != NULL){
            int v = getEdgeDest(edge);
            double comprimento = getEdgeCmp(edge);
            double vm = getEdgeVm(edge);

            double tempo = comprimento / vm;
            
            if(dist[u] + tempo < dist[v]){
                dist[v] = dist[u] + tempo;
                pai[v] = u;
                updateDistance(fila, v, dist[v]);
            
            }
            edge = getNextEdge(edge);
        }
    }
    
    Lista caminho = createList();

    if(dist[destino] != DBL_MAX || origem == destino){
        int atual = destino;

        while(atual != -1){
            insertListStart(caminho, atual);
            atual = pai[atual];
        }
    }

    free(dist);
    free(pai);
    freeMinHeap(fila);
    return caminho;
}
