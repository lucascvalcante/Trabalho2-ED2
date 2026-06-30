#include "../unity.h"
#include "../exHash.h"
#include "../quadra.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_fluxo_completo_hash_ram(void) {
    exHash tabela = init_exHash(10, get_tamanho_quadra());
    TEST_ASSERT_NOT_NULL(tabela);

    Quadra q1 = cria_quadra("86010-000", 10.0, 20.0, 100.0, 50.0, "1px", "red", "black");
    Quadra q2 = cria_quadra("90000-123", 500.0, 600.0, 80.0, 80.0, "2px", "blue", "white");

    TEST_ASSERT_TRUE(insert_exHash(tabela, get_quadra_cep(q1), q1));
    TEST_ASSERT_TRUE(insert_exHash(tabela, get_quadra_cep(q2), q2));
    TEST_ASSERT_FALSE(insert_exHash(tabela, "86010-000", q1));

    Quadra buscada1 = (Quadra) search_exHash(tabela, "86010-000");
    TEST_ASSERT_NOT_NULL(buscada1);
    TEST_ASSERT_EQUAL_STRING("86010-000", get_quadra_cep(buscada1));
    TEST_ASSERT_EQUAL_DOUBLE(10.0, get_quadra_x(buscada1));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, get_quadra_w(buscada1));

    Quadra buscada2 = (Quadra) search_exHash(tabela, "90000-123");
    TEST_ASSERT_NOT_NULL(buscada2);
    TEST_ASSERT_EQUAL_DOUBLE(500.0, get_quadra_x(buscada2));

    Quadra nao_existe = (Quadra) search_exHash(tabela, "00000-000");
    TEST_ASSERT_NULL(nao_existe);

    TEST_ASSERT_TRUE(remove_exHash(tabela, "86010-000"));
    
    Quadra pos_remocao = (Quadra) search_exHash(tabela, "86010-000");
    TEST_ASSERT_NULL(pos_remocao);

    free_quadra(q1);
    free_quadra(q2);
    
    close_exHash(tabela);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_fluxo_completo_hash_ram);
    return UNITY_END();
}