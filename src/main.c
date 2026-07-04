#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "svg.h"
#include "geo.h" 
#include "via.h"
#include "qry.h"
#include "exHash.h"
#include <math.h>
#include "quadra.h"

#define PATH_SIZE 1024
#define TAMANHO_HASH 1000


static void desenhar_quadra_cb(const char* chave, void* dado, void* extra) {
    (void)chave;
    FILE *svg = (FILE*) extra;
    Quadra q = (Quadra) dado;
    
    double qx = get_quadra_x(q);
    double qy = get_quadra_y(q);
    double qw = get_quadra_w(q);
    double qh = get_quadra_h(q);

    desenhar_retangulo_svg(svg,
        get_quadra_x(q), get_quadra_y(q),
        get_quadra_w(q), get_quadra_h(q),
        get_quadra_cfill(q), get_quadra_sw(q), get_quadra_cstrk(q),
        1.0);
    
    double centro_x = qx + qw / 2.0;
    double centro_y = qy + qh / 2.0;
    desenhar_texto_centralizado_svg(svg, centro_x, centro_y, get_quadra_cep(q), "black", 12.0);
}

static void calcular_limites_totais(exHash mapa, Graph g, double *min_x, double *min_y, double *max_x, double *max_y) {
    *min_x = INFINITY;
    *min_y = INFINITY;
    *max_x = -INFINITY;
    *max_y = -INFINITY;

    if (mapa != NULL) {
        geo_calcular_limites(mapa, min_x, min_y, max_x, max_y);
    }

    if (g != NULL) {
        int num_vertices = getNumVertices(g);
        for (int i = 0; i < num_vertices; i++) {
                double vx = getVertexX(g, i);
                double vy = getVertexY(g, i);

                if (vx < *min_x) *min_x = vx;
                if (vy < *min_y) *min_y = vy;
                if (vx > *max_x) *max_x = vx;
                if (vy > *max_y) *max_y = vy;
            
        }
    }
    if (*min_x != INFINITY) {
        *min_x -= 80.0;
        *min_y -= 80.0;
        *max_x += 80.0;
        *max_y += 80.0;
    } else {
        *min_x = 0.0; *min_y = 0.0; *max_x = 15000.0; *max_y = 15000.0;
    }
}

static void monta_caminho(char* destino, const char* dir, const char* arquivo) {
    if (dir != NULL && strlen(dir) > 0) {
        if (dir[strlen(dir) - 1] == '/') sprintf(destino, "%s%s", dir, arquivo);
        else sprintf(destino, "%s/%s", dir, arquivo);
    } else {
        strcpy(destino, arquivo);
    }
}

static void extrair_nome_base(const char *caminho, char *nome_base) {
    const char *ultimo_slash = strrchr(caminho, '/');
    const char *nome_com_ext = ultimo_slash ? ultimo_slash + 1 : caminho;
    strcpy(nome_base, nome_com_ext);

    char* ponto_ext = strrchr(nome_base, '.');
    if (ponto_ext) {
        *ponto_ext = '\0'; 
    }
}

int main(int argc, char *argv[]) {
    char *dir_in = "";
    char *dir_out = NULL;
    char *arq_geo = NULL;
    char *arq_qry = NULL;
    char *arq_via = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) dir_in = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) dir_out = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) arq_geo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) arq_qry = argv[++i];
        else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) arq_via = argv[++i];
    }

    if (arq_geo == NULL || dir_out == NULL) {
        fprintf(stderr, "ERRO: Parametros -f e -o sao obrigatorios!\n");
        return 1;
    }

    char nome_base_geo[256];
    extrair_nome_base(arq_geo, nome_base_geo);
    char path_geo_completo[PATH_SIZE];
    monta_caminho(path_geo_completo, dir_in, arq_geo);
    printf("[*] Processando GEO: %s\n", path_geo_completo);
    exHash mapa = ler_arquivo_geo(path_geo_completo, TAMANHO_HASH);

    Graph g = NULL;
    if (arq_via != NULL) {
        char path_via_completo[PATH_SIZE];
        monta_caminho(path_via_completo, dir_in, arq_via);
        
        printf("[*] Processando VIA: %s\n", path_via_completo);
        g = ler_caminho_via(path_via_completo);
    }

    char path_svg_out[PATH_SIZE];
    char path_txt_out[PATH_SIZE];

    if (arq_qry != NULL) {
        char nome_base_qry[256];
        extrair_nome_base(arq_qry, nome_base_qry);
        snprintf(path_svg_out, PATH_SIZE, "%s/%s-%s.svg", dir_out, nome_base_geo, nome_base_qry);
        snprintf(path_txt_out, PATH_SIZE, "%s/%s-%s.txt", dir_out, nome_base_geo, nome_base_qry);
    } else {
        snprintf(path_svg_out, PATH_SIZE, "%s/%s.svg", dir_out, nome_base_geo);
    }
    
    double min_x, min_y, max_x, max_y;
    calcular_limites_totais(mapa, g, &min_x, &min_y, &max_x, &max_y);

    printf("[*] Gerando SVG base: %s\n", path_svg_out);
    FILE *svg = init_svg(path_svg_out, min_x, min_y, max_x, max_y);
    
    if (mapa != NULL && svg != NULL) {
        foreach_exHash(mapa, desenhar_quadra_cb, svg);
    }

    if(g != NULL && svg != NULL){
        svg_desenha_mapa_base(svg, g);
    }

    if (arq_qry != NULL) {
        char path_qry_completo[PATH_SIZE];
        monta_caminho(path_qry_completo, dir_in, arq_qry);
        
        printf("[*] Executando consultas QRY: %s\n", path_qry_completo);
        FILE *txt = fopen(path_txt_out, "w");
        
        if (txt != NULL) {
            double topo_y = min_y - SVG_MARGEM;
            processar_qry(path_qry_completo, g, mapa, svg, txt, topo_y);
            fclose(txt);
        } else {
            fprintf(stderr, "Erro ao criar arquivo TXT: %s\n", path_txt_out);
        }
    }

    if (svg != NULL) {
        close_svg(svg);
    }

    printf("[*] Liberando memoria e finalizando...\n");
    
    if (mapa != NULL) {
        close_exHash(mapa);
    }
    
    if (g != NULL) {
        freeGraph(g);
    }

    printf("Finalizado com sucesso.\n");
    return 0;
}