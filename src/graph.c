#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>

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


double getVertexX(Graph g, int index) {
    if (g == NULL || index < 0 || index >= g->inserido) return 0.0;
    return g->V[index].x;
}


double getVertexY(Graph g, int index) {
    if (g == NULL || index < 0 || index >= g->inserido) return 0.0;
    return g->V[index].y;
}


char* getVertexId(Graph g, int index) {
    if (g == NULL || index < 0 || index >= g->inserido) return NULL;
    return g->V[index].id;
}


int getNumVertices(Graph g) {
    if (g == NULL) return 0;
    return g->inserido;
}


int getNumEdges(Graph g) {
    if (g == NULL) return 0;
    return g->m;
}


Edge_t getFirstEdge(Graph g, int origem) {
    if (g == NULL || origem < 0 || origem >= g->n) return NULL;
    return g->E[origem]; 
}


Edge_t getNextEdge(Edge_t atual) {
    if (atual == NULL) return NULL;
    return atual->next; 
}


int getEdgeDest(Edge_t e) {
    if (e == NULL) return -1;
    return e->dest;
}


double getEdgeCmp(Edge_t e) {
    if (e == NULL) return 0.0;
    return e->cmp;
}


double getEdgeVm(Edge_t e) {
    if (e == NULL) return 0.0;
    return e->vm;
}

void setEdgeActivaded(Edge_t e, bool status){
    if(e) e->ativado = status;
}

bool isEdgeActive(Edge_t e) {
    if (e == NULL) return false;
    return e->ativado;
}

void deactivateEdge(Graph g, int origem, int destino) {
    if (g == NULL || origem < 0 || origem >= g->n) return;
    
    Edge *atual = g->E[origem];
    while(atual != NULL) {
        if(atual->dest == destino) {
            atual->ativado = false; 
            return; 
        }
        atual = atual->next;
    }
}


void setEdgeVm(Edge_t e, double vm){
    if(e != NULL){
        e->vm = vm;
    }
}


int obter_vertice_mais_proximo(Graph g, double x, double y){
    int n = getNumVertices(g);
    int closest = -1;
    double min_dist = 999999999.0;

    for (int i = 0; i < n; i++) {
        double vx = getVertexX(g, i);
        double vy = getVertexY(g, i);
        
        double dist_sq = (vx - x)*(vx - x) + (vy - y)*(vy - y);
        if (dist_sq < min_dist) {
            min_dist = dist_sq;
            closest = i;
        }
    }
    return closest;
}


/// --Funções e estruturas privadas para o algoritmo de tarjan: --- ///

typedef struct {
    int index;
    int lowlink;
    bool onStack;
} TarjanNode;


static void tarjan_strongconnect(Graph g, int v, double vl, int *idx, TarjanNode *nodes, int *pilha, int *topo, int *componentes, int *num_componentes) {
    nodes[v].index = *idx;
    nodes[v].lowlink = *idx;
    (*idx)++;
    
    pilha[++(*topo)] = v;
    nodes[v].onStack = true;

    Edge_t aresta = getFirstEdge(g, v);
    while (aresta != NULL) {
        if (getEdgeVm(aresta) < vl) {
            int w = getEdgeDest(aresta);
            
            if (nodes[w].index == -1) { 
                tarjan_strongconnect(g, w, vl, idx, nodes, pilha, topo, componentes, num_componentes);
                if (nodes[w].lowlink < nodes[v].lowlink) {
                    nodes[v].lowlink = nodes[w].lowlink;
                }
            } else if (nodes[w].onStack) { 
                if (nodes[w].index < nodes[v].lowlink) {
                    nodes[v].lowlink = nodes[w].index;
                }
            }
        }
        aresta = getNextEdge(aresta);
    }

    if (nodes[v].lowlink == nodes[v].index) {
        (*num_componentes)++; 
        int w;
        do {
            w = pilha[(*topo)--];
            nodes[w].onStack = false;
            componentes[w] = *num_componentes;
        } while (w != v);
    }
}

///--- Função pública: ---///

int encontrar_componentes_conexos(Graph g, double vl, int *componentes){
    int n = getNumVertices(g);

    TarjanNode *nodes = malloc(n * sizeof(TarjanNode));
    int *pilha = malloc(n * sizeof(int));
    int topo = -1;
    int idx = 0;
    int num_componentes = 0;

    for (int i = 0; i < n; i++) {
        nodes[i].index = -1;
        nodes[i].lowlink = -1;
        nodes[i].onStack = false;
        componentes[i] = 0; 
    }

    for (int i = 0; i < n; i++) {
        if (nodes[i].index == -1) {
            tarjan_strongconnect(g, i, vl, &idx, nodes, pilha, &topo, componentes, &num_componentes);
        }
    }

    free(nodes);
    free(pilha);
    
    return num_componentes;
}


//-- Funções e estruturas privadas para o algoritmo de Kruskal: --//


typedef struct {
    int u;
    int v;
    double peso;
    Edge *aresta;
} KruskalEdge;

static int comparar_arestas(const void *a, const void *b) {
    KruskalEdge *ea = (KruskalEdge *)a;
    KruskalEdge *eb = (KruskalEdge *)b;
    if (ea->peso < eb->peso) return -1;
    if (ea->peso > eb->peso) return 1;
    return 0;
}

static int buscar_conjunto(int v, int *pai) {
    if (v == pai[v]) return v;
    pai[v] = buscar_conjunto(pai[v], pai);
    return pai[v];
}

static void unir_conjuntos(int a, int b, int *pai, int *rank) {
    a = buscar_conjunto(a, pai);
    b = buscar_conjunto(b, pai);
    if (a != b) {
        if (rank[a] < rank[b]) {
            int temp = a; a = b; b = temp;
        }
        pai[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
    }
}

//-- Função Principal: --//

void calcular_mst_kruskal(Graph g) {
    int num_v = getNumVertices(g);
    
    int total_arestas = 0;
    for (int i = 0; i < num_v; i++) {
        Edge *e = getFirstEdge(g, i);
        while (e != NULL) {
            e->ativado = false; 
            total_arestas++;
            e = getNextEdge(e);
        }
    }

    if (total_arestas == 0) return;

    KruskalEdge *todas_arestas = malloc(total_arestas * sizeof(KruskalEdge));
    int k = 0;
    for (int i = 0; i < num_v; i++) {
        Edge *e = getFirstEdge(g, i);
        while (e != NULL) {
            todas_arestas[k].u = i;
            todas_arestas[k].v = getEdgeDest(e);
            todas_arestas[k].peso = getEdgeCmp(e);
            todas_arestas[k].aresta = e;
            k++;
            e = getNextEdge(e);
        }
    }
    qsort(todas_arestas, total_arestas, sizeof(KruskalEdge), comparar_arestas);

    int *pai = malloc(num_v * sizeof(int));
    int *rank = calloc(num_v, sizeof(int));
    for (int i = 0; i < num_v; i++) pai[i] = i;

    int mst_count = 0;
    for (int i = 0; i < total_arestas; i++) {
        int u = todas_arestas[i].u;
        int v = todas_arestas[i].v;
        
        if (buscar_conjunto(u, pai) != buscar_conjunto(v, pai)) {
            setEdgeActivaded(todas_arestas[i].aresta, true);
            mst_count++;
            
            unir_conjuntos(u, v, pai, rank);
            if (mst_count == num_v - 1) break;
        }
    }

    free(todas_arestas);
    free(pai);
    free(rank);
}