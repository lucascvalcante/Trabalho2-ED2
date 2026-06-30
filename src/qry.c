#include "qry.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "quadra.h"
#include "svg.h"
#include "graph.h"
#include "dijkstra.h"
#include "list.h"

typedef struct {
    double x;
    double y;
    bool ativo;
} Registradores;

Registradores regs[32];

//-- FUNÇÕES ESTÁTICAS DE COMANDOS: --//

static void cmd_o(FILE *qry, FILE *txt, FILE *svg, exHash quadras) {
    char cep[50], face;
    int num, reg_num;
    fscanf(qry, "%d %s %c %d", &reg_num, cep, &face, &num);
    
    Quadra q = search_exHash(quadras, cep);

    if (q == NULL) {
        fprintf(txt, "@o?: Quadra com CEP %s nao encontrada.\n", cep);
        return;
    }

    double qx = get_quadra_x(q);
    double qy = get_quadra_y(q);
    double qw = get_quadra_w(q);
    double qh = get_quadra_h(q);
    double x_end = 0.0;
    double y_end = 0.0;

    if (face == 'N' || face == 'n') {
        x_end = qx + num;
        y_end = qy;
    } else if (face == 'S' || face == 's') {
        x_end = qx + num;
        y_end = qy + qh;
    } else if (face == 'L' || face == 'l') {
        x_end = qx + qw;
        y_end = qy + num;
    } else if (face == 'O' || face == 'o') {
        x_end = qx;
        y_end = qy + num;
    }

    regs[reg_num].x = x_end;
    regs[reg_num].y = y_end;
    regs[reg_num].ativo = true;     

    fprintf(txt, "@o? reg %d -> CEP: %s, Face: %c, Num: %d | Coordenadas: X=%.2f, Y=%.2f\n", 
            reg_num, cep, face, num, x_end, y_end);

    desenhar_linha_tracejada(svg, x_end, y_end, x_end, 0.0, "red", "1.0px");
    
    char txt_reg[10];
    sprintf(txt_reg, "R%d", reg_num);
    desenhar_texto_svg(svg, x_end, 10.0, txt_reg, "red"); 
}

static void cmd_mvm(FILE *qry, Graph g) {
    double vm, x, y, h, w;
    fscanf(qry, "%lf %lf %lf %lf %lf", &vm, &x, &y, &w, &h);
    
    int total_vertices = getNumVertices(g);

    for (int i = 0; i < total_vertices; i++) {
        double ox = getVertexX(g, i);
        double oy = getVertexY(g, i);

        if (ox >= x && ox <= (x + w) && oy >= y && oy <= (y + h)) {            
            Edge_t aresta = getFirstEdge(g, i);
            while (aresta != NULL) {
                int dest = getEdgeDest(aresta);
                double dx = getVertexX(g, dest);
                double dy = getVertexY(g, dest);

                if (dx >= x && dx <= (x + w) && dy >= y && dy <= (y + h)) {
                    setEdgeVm(aresta, vm);
                }
                aresta = getNextEdge(aresta);
            }
        }
    }
}

static void cmd_regs(FILE *qry, FILE *txt, FILE *svg, Graph g) {
    double vl;
    fscanf(qry, "%lf", &vl);

    int total_vertices = getNumVertices(g);
    int *componentes = (int*) malloc(total_vertices * sizeof(int));

    int qtd_componentes = encontrar_componentes_conexos(g, vl, componentes);
    fprintf(txt, "regs: Foram encontrados %d componentes conexos com velocidade inferior a %.2f.\n", qtd_componentes, vl);            
    
    const char* cores[] = {"#FF0000", "#00FF00", "#0000FF", "#FFA500", "#800080", "#00FFFF", "#FF00FF", "#FFFF00"};
    int num_cores = 8;

    for (int c = 1; c <= qtd_componentes; c++) {
        double min_x = 9999999.0, min_y = 9999999.0;
        double max_x = -9999999.0, max_y = -9999999.0;
        bool possui_vertices = false;

        for (int i = 0; i < total_vertices; i++) {
            if (componentes[i] == c) {
                double vx = getVertexX(g, i);
                double vy = getVertexY(g, i);
                
                if (vx < min_x) min_x = vx;
                if (vy < min_y) min_y = vy;
                if (vx > max_x) max_x = vx;
                if (vy > max_y) max_y = vy;
                
                possui_vertices = true;
            }
        }

        if (possui_vertices) {
            double largura = max_x - min_x;
            double altura = max_y - min_y;
            const char* cor = cores[c % num_cores];
            
            desenhar_bounding_box(svg, min_x, min_y, largura, altura, cor, 0.5);
        }
    }
    free(componentes); 
}


static void cmd_exp(FILE *qry, FILE *svg, Graph g){
double vl;
    fscanf(qry, "%lf", &vl);

    calcular_mst_kruskal(g);

    int ruas_atualizadas = 0;
    int total_vertices = getNumVertices(g);

    for (int i = 0; i < total_vertices; i++) {
        double ox = getVertexX(g, i);
        double oy = getVertexY(g, i);

        Edge_t aresta = getFirstEdge(g, i);
        while (aresta != NULL) {
            if (isEdgeActive(aresta)) {                
                if (getEdgeVm(aresta) < vl) {
                    double nova_vm = getEdgeVm(aresta) * 1.5; 
                    setEdgeVm(aresta, nova_vm);
                    ruas_atualizadas++;

                    int dest = getEdgeDest(aresta);
                    double dx = getVertexX(g, dest);
                    double dy = getVertexY(g, dest);

                    desenhar_linha_svg(svg, ox, oy, dx, dy, "red", "4.0px");
                }
            }
            aresta = getNextEdge(aresta);
        }
    }
}

static void cmd_p(FILE *qry, FILE *txt, FILE *svg, Graph g) {
    int r1, r2;
    char cc[30], cr[30]; 
    
    fscanf(qry, "%d %d %s %s", &r1, &r2, cc, cr);

    if (!regs[r1].ativo || !regs[r2].ativo) {
        fprintf(txt, "p?: Erro. Registradores R%d ou R%d nao estao ativos.\n", r1, r2);
        return;
    }

    int start_v = obter_vertice_mais_proximo(g, regs[r1].x, regs[r1].y);
    int end_v = obter_vertice_mais_proximo(g, regs[r2].x, regs[r2].y);
    Lista caminho_curto = dijkstra(g, start_v, end_v, false);
    Lista caminho_rapido = dijkstra(g, start_v, end_v, true);

    if (caminho_curto == NULL || lengthList(caminho_curto) == 0) {
        fprintf(txt, "p?: Destino inacessivel entre R%d e R%d.\n", r1, r2);
        if (caminho_curto) freeList(caminho_curto);
        if (caminho_rapido) freeList(caminho_rapido);
        return;
    }

    iniciar_path_svg(svg, "id_curto", cc, "4.0px");

    Node no_atual = getFirstList(caminho_curto);
    bool eh_inicio = true;
    int passos_curto = 0;

    while (no_atual != NULL) {
        int *dado = (int*) getList(caminho_curto, no_atual);
        int v = *dado;
        
        double x = getVertexX(g, v);
        double y = getVertexY(g, v);

        adicionar_ponto_path_svg(svg, x, y, eh_inicio);
        eh_inicio = false;
        passos_curto++;

        no_atual = getNextList(caminho_curto, no_atual);
    }
    fechar_path_svg(svg);
    desenhar_animacao_svg(svg, "id_curto", "6s"); 
    iniciar_path_svg(svg, "id_rapido", cr, "4.0px");

    no_atual = getFirstList(caminho_rapido);
    eh_inicio = true;
    int passos_rapido = 0;

    while (no_atual != NULL) {
        int *dado = (int*) getList(caminho_rapido, no_atual);
        int v = *dado;
        
        double x = getVertexX(g, v);
        double y = getVertexY(g, v);

        adicionar_ponto_path_svg(svg, x, y, eh_inicio);
        eh_inicio = false;
        passos_rapido++;

        no_atual = getNextList(caminho_rapido, no_atual);
    }
    fechar_path_svg(svg);
    desenhar_animacao_svg(svg, "id_rapido", "4s"); 
    desenhar_texto_svg(svg, regs[r1].x, regs[r1].y - 5, "I", "black");
    desenhar_texto_svg(svg, regs[r2].x, regs[r2].y - 5, "F", "black");

    fprintf(txt, "p?: Trajetos calculados entre R%d e R%d.\n", r1, r2);
    fprintf(txt, "   -> Caminho mais curto (%s): %d vertices percorridos.\n", cc, passos_curto);
    fprintf(txt, "   -> Caminho mais rapido (%s): %d vertices percorridos.\n", cr, passos_rapido);

    no_atual = getFirstList(caminho_curto);
    while (no_atual != NULL) {
        int *dado = (int*) getList(caminho_curto, no_atual);
        free(dado);
        no_atual = getNextList(caminho_curto, no_atual);
    }
    freeList(caminho_curto);

    no_atual = getFirstList(caminho_rapido);
    while (no_atual != NULL) {
        int *dado = (int*) getList(caminho_rapido, no_atual);
        free(dado);
        no_atual = getNextList(caminho_rapido, no_atual);
    }
    freeList(caminho_rapido);
}

//-- FUNÇÃO PRINCIPAL: --//

void processar_qry(const char *arquivo_qry, Graph g, exHash quadras, FILE *svg, FILE *txt) {
    FILE *qry = fopen(arquivo_qry, "r");
    if (!qry) {
        printf("Não foi possível realizar a leitura do arquivo qry: %s\n", arquivo_qry);
        return;
    }
    
    char comando[10];

    while (fscanf(qry, "%s", comando) != EOF) {
        if (strcmp(comando, "@o?") == 0) {
            cmd_o(qry, txt, svg, quadras);
        } else if (strcmp(comando, "mvm") == 0) {
            cmd_mvm(qry, g);
        } else if (strcmp(comando, "regs") == 0) {
            cmd_regs(qry, txt, svg, g);
        } else if(strcmp(comando, "exp") == 0){
            cmd_exp(qry, svg, g);
        } else if(strcmp(comando, "p?") == 0){
            cmd_p(qry, txt, svg, g);
        } else{
            printf("Comando do qry inválido: %s\n", comando);
        }
    }
    
    fclose(qry); 
}