#include "../unity.h"
#include "../via.h"
#include "../graph.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_leitura_arquivo_via(void) {
    const char* nome_arquivo = "mapa_teste_temp.via";

    FILE* file = fopen(nome_arquivo, "w");
    TEST_ASSERT_NOT_NULL(file); 

    fprintf(file, "3\n");
    fprintf(file, "v v0 10.0 10.0\n");
    fprintf(file, "v v1 110.0 10.0\n");
    fprintf(file, "v v2 210.0 10.0\n");
    fprintf(file, "e v0 v1 dir esq 100.0 60.0 Rua_A\n");
    fprintf(file, "e v1 v2 - - 50.0 40.0 Rua_B\n"); 
    fclose(file);

    Graph g = ler_caminho_via(nome_arquivo);
    TEST_ASSERT_NOT_NULL(g);    
    TEST_ASSERT_EQUAL_INT(3, getNumVertices(g));
    TEST_ASSERT_EQUAL_INT(2, getNumEdges(g));

    int idx_v0 = getVertexIndex(g, "v0");
    TEST_ASSERT_NOT_EQUAL(-1, idx_v0); 
    TEST_ASSERT_EQUAL_DOUBLE(10.0, getVertexX(g, idx_v0));

    freeGraph(g);
    remove(nome_arquivo); 
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_leitura_arquivo_via);
    
    return UNITY_END();
}