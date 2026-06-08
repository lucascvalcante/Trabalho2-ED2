#include "unity.h"
#include "quadra.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_criacao_e_getters_quadra(void) {
    Quadra q = cria_quadra("86010-000", 10.0, 20.0, 50.0, 40.0, "2.0px", "blue", "black");
    
    TEST_ASSERT_NOT_NULL(q);
    
    TEST_ASSERT_EQUAL_DOUBLE(10.0, get_quadra_x(q));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, get_quadra_y(q));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, get_quadra_w(q));
    TEST_ASSERT_EQUAL_DOUBLE(40.0, get_quadra_h(q));

    TEST_ASSERT_EQUAL_STRING("86010-000", get_quadra_cep(q));
    TEST_ASSERT_EQUAL_STRING("2.0px", get_quadra_sw(q));
    TEST_ASSERT_EQUAL_STRING("blue", get_quadra_cfill(q));
    TEST_ASSERT_EQUAL_STRING("black", get_quadra_cstrk(q));
    
    free_quadra(q);
}

void teste_ancora_quadra(void) {
    Quadra q = cria_quadra("123", 100.0, 100.0, 50.0, 25.0, "1", "red", "red");
    
    double ancora_x = 0;
    double ancora_y = 0;
    get_quadra_ancora(q, &ancora_x, &ancora_y);
    
    TEST_ASSERT_EQUAL_DOUBLE(150.0, ancora_x);
    TEST_ASSERT_EQUAL_DOUBLE(125.0, ancora_y);
    
    free_quadra(q);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_criacao_e_getters_quadra);
    RUN_TEST(teste_ancora_quadra);
    
    return UNITY_END();
}