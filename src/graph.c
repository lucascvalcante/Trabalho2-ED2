#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>
#include <string.h>

typedef struct Edge{
    char* rua;
    char* ldir;
    char* lesq;
    double cmp;
    double vm;
    int dest;
    bool ativado;
    struct Edge *next;
}Edge;


typedef struct Vertex{
    char* id; 
    double x, y;
}Vertex;


struct Graph_s{
    Edge **E;
    Vertex *V;
    int inserido;
    int n; //numero de vertives
    int m; //numero de arestas
};


Graph initGraph(int n){
    Graph g = malloc(sizeof (*g));
    if(g == NULL){
        return NULL;
    }

    g->V = malloc(n * sizeof(Vertex));
    g->E = calloc(n, sizeof(Edge*));
    g->n = n;
    g->m = 0;
    g->inserido = 0;
    return g;
}


void insertVertex(Graph g, char* id, double x, double y){
    g->V[g->inserido].id = strdup(id);
    g->V[g->inserido].x = x;
    g->V[g->inserido].y = y;
    g->inserido++;
}


void insertEdge(Graph g, int origem, int destino, char* rua, char* ldir, char* lesq, double cmp, double vm){
    Edge *novo = malloc(sizeof(Edge));
    if(novo == NULL){
        return;
    }

    novo->rua = strdup(rua);
    novo->ldir = strdup(ldir);
    novo->lesq = strdup(lesq);
    novo->cmp = cmp;
    novo->vm = vm;
    novo->dest = destino;
    novo->next = g->E[origem];
    g->E[origem] = novo;
    novo->ativado = true;
    g->m++;
}


void freeGraph(Graph g){
    if(g == NULL){
        return;
    }

    for(int i = 0; i < g->n; i++){
        Edge *atual = g->E[i];

        while(atual != NULL){
            Edge *next = atual->next;

            free(atual->rua);
            free(atual->ldir);
            free(atual->lesq);
            free(atual);

            atual = next;
        }
    }

    for(int i = 0; i < g->inserido; i++){
        free(g->V[i].id);
    }
    free(g->V);
    free(g->E);
    free(g);
}


int getVertexIndex(Graph g, char *id){
    if(g == NULL){
        return -1;
    }

    for(int i = 0; i < g->inserido; i++){
        if(strcmp(id, g->V[i].id) == 0){
            return i;
        }
    }
    return -1;
}