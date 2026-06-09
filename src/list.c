#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node_s{
    void* dado;
    struct Node_s *prox;
    struct Node_s *ant;
}nodeStruct;


struct Lista_s{
    nodeStruct* inicio;
    nodeStruct* fim;
    int tamanho;
};


Lista createList(){
    Lista l = malloc(sizeof(struct Lista_s));
    if(!l){
        return NULL;
    }

    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;

    return l;
}


Node insertList(Lista l, Node n){
    if(!l || !n){
        return NULL;
    }

    nodeStruct *novo = malloc(sizeof(nodeStruct));
    if(!novo){
        return NULL;
    }

    novo->dado = n;
    novo->prox = NULL;
    if(l->inicio == NULL){
        l->inicio = novo;
        l->fim = novo;
        novo->ant = NULL;
        l->tamanho++;
        return novo;
    }else{
        l->fim->prox = novo;
        novo->ant = l->fim;
        l->fim = novo;
        l->tamanho++;
        return novo;
    }
}


int lengthList(Lista l){
    if(!l){
        return -1;
    }
    return l->tamanho;
}


void* getList(Lista l, Node n){
    if(!l || !n){
        return NULL;
    }

    nodeStruct *node = (nodeStruct*) n;
    return node->dado;
}


Node getFirstList(Lista l){
    if(!l){
        return NULL;
    }
    return l->inicio;
}


Node getNextList(Lista l, Node n){
    if(!l || !n){
        return NULL;
    }
    nodeStruct *node = (nodeStruct*) n;
    return node->prox;
}


Node getLastList(Lista l){
    if(!l){
        return NULL;
    }
    return l->fim;
}


Node getPreviousList(Lista l, Node n){
    if(!l || !n){
        return NULL;
    }
    nodeStruct *node = (nodeStruct*) n;
    return node->ant;
}


void* removeList(Lista l, Node n){
    if(!l || !n){
        return NULL;
    }


    nodeStruct *node = (nodeStruct*) n;
    void* dado_salvo = node->dado;

    if(node->ant != NULL){
        node->ant->prox = node->prox;
    }else{
        l->inicio = l->inicio->prox;
    }

    if(node->prox != NULL){
        node->prox->ant = node->ant;
    }else{
        l->fim = l->fim->ant;
    }

    free(node);
    l->tamanho--;

    return dado_salvo;
}


void freeList(Lista l){
    if(!l){
        return;
    }

    nodeStruct *atual = l->inicio;
    while(atual != NULL){
        nodeStruct *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(l);
}