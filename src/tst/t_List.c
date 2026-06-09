#include "../unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "../list.h" 

void setUp(void) {
}

void tearDown(void) {
}

int* cria_inteiro(int valor) {
    int* novo = malloc(sizeof(int));
    *novo = valor;
    return novo;
}

void test_ListaGenerica_CriacaoEInsercao(void) {
    Lista l = createList();
    TEST_ASSERT_NOT_NULL(l);

    int* p1 = cria_inteiro(10);
    int* p2 = cria_inteiro(20);
    int* p3 = cria_inteiro(30);

    Node n1 = insertList(l, p1);
    Node n2 = insertList(l, p2);
    Node n3 = insertList(l, p3);

    TEST_ASSERT_NOT_NULL(n1);
    TEST_ASSERT_NOT_NULL(n2);
    TEST_ASSERT_NOT_NULL(n3);

    TEST_ASSERT_EQUAL_INT(3, lengthList(l));

    int* valor_removido = (int*) removeList(l, n2);
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