#include "../unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "../list.h" 

void setUp(void) {}
void tearDown(void) {}

int* cria_inteiro(int valor) {
    int* novo = malloc(sizeof(int));
    *novo = valor;
    return novo;
}

void test_ListaGenerica_CriacaoEInsercao(void) {
    Lista l = createList();
    TEST_ASSERT_NOT_NULL(l);

    int* val1 = cria_inteiro(10);
    int* val2 = cria_inteiro(20);
    int* val3 = cria_inteiro(30);

    insertListHead(l, val1);
    insertListHead(l, val2);
    insertListHead(l, val3);

    TEST_ASSERT_EQUAL_INT(3, lengthList(l));

    Node pos_30 = getFirstList(l);     
    Node pos_20 = getNextList(l, pos_30); 
    int* valor_removido = (int*) removeList(l, pos_20); 
    TEST_ASSERT_NOT_NULL(valor_removido);
    TEST_ASSERT_EQUAL_INT(20, *valor_removido);    
    TEST_ASSERT_EQUAL_INT(2, lengthList(l));
    free(valor_removido); 

    Node atual = getFirstList(l);
    while (atual != NULL) {
        int* valor = (int*) getList(l, atual);
        free(valor); 
        atual = getNextList(l, atual);
    }
    
    freeList(l); 
}

int main(void) {
    UNITY_BEGIN(); 
    
    RUN_TEST(test_ListaGenerica_CriacaoEInsercao); 
    
    return UNITY_END(); 
}