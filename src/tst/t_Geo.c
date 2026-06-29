#include "../unity.h"
#include "../geo.h"
#include "../exHash.h"
#include "../quadra.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_leitura_arquivo_geo(void) {
    const char* nome_arquivo = "mapa_teste_temp.geo";

    FILE* file = fopen(nome_arquivo, "w");
    TEST_ASSERT_NOT_NULL(file);

    fprintf(file, "q 86010-000 10.0 10.0 100.0 100.0\n");    
    fprintf(file, "cq 3px green yellow\n");    
    fprintf(file, "q 86020-111 150.0 10.0 50.0 50.0\n");
    fprintf(file, "q 86030-222 250.0 10.0 80.0 80.0\n");
    
    fclose(file);
    exHash tabela = ler_arquivo_geo(nome_arquivo, 10);
    TEST_ASSERT_NOT_NULL(tabela);

    Quadra q1 = (Quadra) search_exHash(tabela, "86010-000");
    TEST_ASSERT_NOT_NULL(q1);
    TEST_ASSERT_EQUAL_STRING("1px", get_quadra_sw(q1));
    TEST_ASSERT_EQUAL_STRING("white", get_quadra_cfill(q1));
    TEST_ASSERT_EQUAL_STRING("black", get_quadra_cstrk(q1));

    Quadra q2 = (Quadra) search_exHash(tabela, "86020-111");
    TEST_ASSERT_NOT_NULL(q2);
    TEST_ASSERT_EQUAL_STRING("3px", get_quadra_sw(q2));
    TEST_ASSERT_EQUAL_STRING("green", get_quadra_cfill(q2));
    TEST_ASSERT_EQUAL_STRING("yellow", get_quadra_cstrk(q2));

    Quadra q3 = (Quadra) search_exHash(tabela, "86030-222");
    TEST_ASSERT_NOT_NULL(q3);
    TEST_ASSERT_EQUAL_STRING("3px", get_quadra_sw(q3));
    TEST_ASSERT_EQUAL_STRING("green", get_quadra_cfill(q3));
    TEST_ASSERT_EQUAL_STRING("yellow", get_quadra_cstrk(q3));
    
    close_exHash(tabela);
    
    remove(nome_arquivo); 
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_leitura_arquivo_geo);
    return UNITY_END();
}