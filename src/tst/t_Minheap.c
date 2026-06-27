#include "../unity.h"
#include "../minheap.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_criacao_minheap(void) {
    MinHeap h = createMinHeap(10);
    
    TEST_ASSERT_NOT_NULL(h);
    TEST_ASSERT_TRUE(isMinHeapEmpty(h));
    
    freeMinHeap(h);
}

void teste_insercao_e_extracao_minheap(void) {
    MinHeap h = createMinHeap(10);
    
    updateDistance(h, 2, 15.0);
    updateDistance(h, 5, 3.5);
    updateDistance(h, 8, 8.0);
    
    TEST_ASSERT_FALSE(isMinHeapEmpty(h));    
    TEST_ASSERT_EQUAL_INT(5, extractMin(h));
    updateDistance(h, 2, 1.0);    
    TEST_ASSERT_EQUAL_INT(2, extractMin(h));    
    TEST_ASSERT_EQUAL_INT(8, extractMin(h));    
    TEST_ASSERT_TRUE(isMinHeapEmpty(h));
    
    freeMinHeap(h);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_criacao_minheap);
    RUN_TEST(teste_insercao_e_extracao_minheap);
    
    return UNITY_END();
}
