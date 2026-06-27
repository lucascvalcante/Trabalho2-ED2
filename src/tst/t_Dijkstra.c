#include "../unity.h"
#include "../dijkstra.h"
#include "../graph.h"
#include "../list.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_dijkstra_caminho_simples(void) {
    Graph g = initGraph(5);
    
    insertVertex(g, "v_origem", 0.0, 0.0);
    insertVertex(g, "v_meio", 0.0, 0.0);
    insertVertex(g, "v_destino", 0.0, 0.0);    
    insertEdge(g, 0, 1, "Rua_A", "0", "0", 100.0, 10.0);    
    insertEdge(g, 1, 2, "Rua_B", "0", "0", 50.0, 10.0);    
    insertEdge(g, 0, 2, "Rua_Direta", "0", "0", 200.0, 10.0);
    Lista caminho = dijkstra(g, 0, 2); 
    
    TEST_ASSERT_NOT_NULL(caminho);
    
    TEST_ASSERT_EQUAL_INT(3, lengthList(caminho)); 
    
    Node atual = getFirstList(caminho);
    while (atual != NULL) {
        void* dado = getList(caminho, atual);
        if(dado != NULL) free(dado); 
        atual = getNextList(caminho, atual);
    }
    
    freeList(caminho);
    freeGraph(g);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_dijkstra_caminho_simples);
    
    return UNITY_END();
}