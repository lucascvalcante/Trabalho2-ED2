#include "../unity.h"
#include "../svg.h"
#include "../graph.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_inicializacao_e_fechamento_svg(void) {
    FILE *svg = init_svg("teste_saida.svg", 0.0, 0.0, 100.0, 100.0);
    
    TEST_ASSERT_NOT_NULL(svg);
    close_svg(svg);

    FILE *check = fopen("teste_saida.svg", "r");
    TEST_ASSERT_NOT_NULL(check);
    fclose(check);
    
    remove("teste_saida.svg");
}

void teste_desenhos_estaticos_svg(void) {
    FILE *svg = init_svg("teste_formas.svg", 0.0, 0.0, 100.0, 100.0);
    TEST_ASSERT_NOT_NULL(svg);

    desenhar_retangulo_svg(svg, 10.0, 10.0, 50.0, 40.0, "blue", "2.0px", "black", 1.0);
    desenhar_linha_svg(svg, 0.0, 0.0, 100.0, 100.0, "red", "1.0px");
    desenhar_circulo_svg(svg, 50.0, 50.0, 5.0, "black", "yellow");
    svg_rect_componente_conexo(svg, "green", 5.0, 5.0, 95.0, 95.0);

    close_svg(svg);
    remove("teste_formas.svg");
}

void teste_mapa_base_svg(void) {
    FILE *svg = init_svg("teste_mapa.svg", 0.0, 0.0, 200.0, 200.0);
    TEST_ASSERT_NOT_NULL(svg);

    Graph g = initGraph(2);
    insertVertex(g, "V0", 20.0, 20.0);
    insertVertex(g, "V1", 150.0, 150.0);
    insertEdge(g, 0, 1, "Av. Principal", "100", "200", 180.0, 60.0);

    svg_desenha_mapa_base(svg, g);

    close_svg(svg);
    freeGraph(g);
    remove("teste_mapa.svg");
}

void teste_animacao_e_path_svg(void) {
    FILE *svg = init_svg("teste_animacao.svg", 0.0, 0.0, 100.0, 100.0);
    TEST_ASSERT_NOT_NULL(svg);

    iniciar_path_svg(svg, "rota_dijkstra", "purple", "3.0px");
    adicionar_ponto_path_svg(svg, 20.0, 20.0, 1);
    adicionar_ponto_path_svg(svg, 150.0, 150.0, 0);
    fechar_path_svg(svg);

    desenhar_animacao_svg(svg, "rota_dijkstra", "2s");

    close_svg(svg);
    remove("teste_animacao.svg");
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_inicializacao_e_fechamento_svg);
    RUN_TEST(teste_desenhos_estaticos_svg);
    RUN_TEST(teste_mapa_base_svg);
    RUN_TEST(teste_animacao_e_path_svg);
    
    return UNITY_END();
}