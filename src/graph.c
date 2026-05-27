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


typedef struct{
    Edge **E;
    Vertex *V;
    int inserido;
    int n; //numero de vertives
    int m; //numero de arestas
}*Graph_s;


Graph_s initGraph(int n){
    Graph_s g = malloc(sizeof (*g));
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


void insertVertex(Graph_s g, char* id, double x, double y){
    g->V[g->inserido].id = strdup(id);
    g->V[g->inserido].x = x;
    g->V[g->inserido].y = y;
    g->inserido++;
}


void insertEdge(Graph_s g, int origem, int destino, char* rua, char* ldir, char* lesq, double cmp, double vm){
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


