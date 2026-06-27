#include "../unity.h"
#include <stdlib.h>
#include "../graph.h"


void setUp(void) {}
void tearDown(void) {}


void teste_criacao_grafo(void) {
    Graph g = initGraph(10);
    
    TEST_ASSERT_NOT_NULL(g); 
    TEST_ASSERT_EQUAL_INT(0, getNumVertices(g)); 
    TEST_ASSERT_EQUAL_INT(0, getNumEdges(g));    
    
    freeGraph(g); 
}


void teste_insercao_e_busca_vertice(void) {
    Graph g = initGraph(5);
    
    insertVertex(g, "v_centro", 100.5, 200.2);
    insertVertex(g, "v_norte", 300.0, 400.0);
    
    TEST_ASSERT_EQUAL_INT(2, getNumVertices(g)); 
    
    int idx_centro = getVertexIndex(g, "v_centro");
    int idx_norte = getVertexIndex(g, "v_norte");
    int idx_invalido = getVertexIndex(g, "v_fantasma");
    
    TEST_ASSERT_EQUAL_INT(0, idx_centro);
    TEST_ASSERT_EQUAL_INT(1, idx_norte);
    TEST_ASSERT_EQUAL_INT(-1, idx_invalido); 
    
    TEST_ASSERT_EQUAL_DOUBLE(100.5, getVertexX(g, idx_centro));
    TEST_ASSERT_EQUAL_STRING("v_norte", getVertexId(g, idx_norte));
    
    freeGraph(g);
}


void teste_insercao_e_navegacao_arestas(void) {
    Graph g = initGraph(3);
    insertVertex(g, "v0", 0, 0); 
    insertVertex(g, "v1", 0, 0); 
    insertVertex(g, "v2", 0, 0); 
    
    insertEdge(g, 0, 1, "Rua_A", "100", "101", 50.5, 60.0);
    insertEdge(g, 0, 2, "Rua_B", "200", "201", 30.0, 40.0);
    
    TEST_ASSERT_EQUAL_INT(2, getNumEdges(g));
    

    Edge_t rua1 = getFirstEdge(g, 0);
    TEST_ASSERT_NOT_NULL(rua1);
    

    TEST_ASSERT_EQUAL_INT(2, getEdgeDest(rua1));
    TEST_ASSERT_EQUAL_DOUBLE(30.0, getEdgeCmp(rua1));
    TEST_ASSERT_TRUE(isEdgeActive(rua1));
    
    Edge_t rua2 = getNextEdge(rua1);
    TEST_ASSERT_NOT_NULL(rua2);
    TEST_ASSERT_EQUAL_INT(1, getEdgeDest(rua2));
    
    Edge_t fim = getNextEdge(rua2);
    TEST_ASSERT_NULL(fim); 
    
    freeGraph(g);
}


void teste_desativar_rua(void) {
    Graph g = initGraph(2);
    insertVertex(g, "v0", 0, 0); 
    insertVertex(g, "v1", 0, 0); 
    
    insertEdge(g, 0, 1, "Rua_Teste", "0", "0", 10.0, 50.0);
    
    Edge_t rua = getFirstEdge(g, 0);
    TEST_ASSERT_TRUE(isEdgeActive(rua)); 
    
    deactivateEdge(g, 0, 1); 
    
    TEST_ASSERT_FALSE(isEdgeActive(rua)); 
    
    freeGraph(g);
}


int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_criacao_grafo);
    RUN_TEST(teste_insercao_e_busca_vertice);
    RUN_TEST(teste_insercao_e_navegacao_arestas);
    RUN_TEST(teste_desativar_rua);
    
    return UNITY_END();
}