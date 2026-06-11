#include "exHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAVE 32

typedef struct Node_s{
    char chave[MAX_CHAVE];
    void *dado;
    struct Node_s *prox;
}Node;


struct exHash_s {
    Node** tabelas;         
    uint32_t m;             
    size_t tamanho_dado;    
};

// --- Função interna de hash ---
static uint32_t hash_string(const char* str) {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}



exHash init_exHash(const char* arquivo, uint32_t tamanho_bucket, size_t tamanho_dado){
    exHash h = (exHash) malloc(sizeof(struct exHash_s));
    if(h == NULL){
        return NULL;
    }

    h->m = tamanho_bucket;
    h->tamanho_dado = tamanho_dado;

    h->tabelas = (Node**) calloc(h->m, sizeof(Node*));
    if(h->tabelas == NULL){
        free(h);
        return NULL;
    } 
    return h;
}

void close_exHash(exHash h){
    if(h == NULL){
        return;
    }

    for(uint32_t i = 0; i < h->m; i++){
        Node* atual = h->tabelas[i];
        while(atual != NULL){
            Node *prox = atual->prox;
            free(atual->dado);
            free(atual);
            atual = prox;
        }
    }

    free(h->tabelas);
    free(h);

}


bool insert_exHash(exHash h, const char* chave, void* dado){
    if(!h || !chave || !dado){
        return false;
    }

    uint32_t idx = hash_string(chave) % h->m;
    Node* atual = h->tabelas[idx];
    while(atual != NULL){
        if(strcmp(atual->chave, chave) == 0){
            return false;
        }        
        atual = atual->prox;
    }

    Node* novo = (Node*) malloc(sizeof(Node));
    if(!novo){
        return false;
    }

    strncpy(novo->chave, chave, MAX_CHAVE - 1);
    novo->chave[MAX_CHAVE - 1] = '\0';

    novo->dado= malloc(h->tamanho_dado);
    if(!novo->dado){
        free(novo);
        return false;
    }

    memcpy(novo->dado, dado, h->tamanho_dado);

    novo->prox = h->tabelas[idx];
    h->tabelas[idx] = novo;

    return true;
}


void* search_exHash(exHash h, const char* chave){
    if(!h || !chave){
        return NULL;
    }

    uint32_t idx = hash_string(chave) % h->m;
    Node* atual = h->tabelas[idx];
    while (atual){
        if(strcmp(atual->chave, chave)== 0){
            return atual->dado;
        }
        atual = atual->prox;
    }

    return NULL;
}

bool remove_exHash(exHash h, const char* chave){
    if(!h || !chave){return false;}

    uint32_t idx = hash_string(chave) % h->m;
    Node* atual = h->tabelas[idx];
    Node* anterior = NULL;
    
    while(atual != NULL){
        if(strcmp(atual->chave, chave)== 0){
            if(anterior == NULL){
                h->tabelas[idx] = atual->prox;
            }else{
                anterior->prox = atual->prox;
            }

            free(atual->dado);
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->prox;
    }

    return false;
}


bool update_exHash(exHash h, const char* chave, void* novo_dado){
    if(!h || !chave || !novo_dado){
        return false;
    }

    uint32_t idx = hash_string(chave) % h->m;
    Node* atual = h->tabelas[idx];
    while(atual != NULL){
        if(strcmp(atual->chave, chave)== 0){
            memcpy(atual->dado, novo_dado, h->tamanho_dado);
            return true;
        }
        atual = atual->prox;
    } 
    return false;
}

void foreach_exHash(exHash h, void (*func)(const char* chave, void* dado, void* extra), void* extra){
    if(!h || !func){
        return; 
    }

    for(uint32_t i = 0; i < h->m; i++){
        Node* atual = h->tabelas[i];
        while (atual != NULL){
            func(atual->chave, atual->dado, extra);
            atual = atual->prox;
        }
    }
}


void dump_exHash(exHash h, const char* arquivo_saida_hfd){
    if(!h || !arquivo_saida_hfd){
        return;
    }

    FILE* saida = fopen(arquivo_saida_hfd, "w");
    if(!saida){
        return;
    }

    fprintf(saida, "=== ESTRUTURA DA TABELA HASH EM RAM ===\n");
    fprintf(saida, "Total de Slots (Buckets): %u\n\n", h->m);

    for(uint32_t i = 0; i <h->m; i++){
        Node* atual = h->tabelas[i];
        if(atual != NULL){
            fprintf(saida, "Slot[%05u]:'\n", i);
            while(atual != NULL){
                fprintf(saida, "  -> Ocupado | Chave: %s\n", atual->chave);              
                atual = atual->prox;
            }
        }
    }

    fprintf(saida, "\n====================================\n");  
    fclose(saida);
}


