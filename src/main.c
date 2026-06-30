#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "svg.h"
#include "geo.h" 
#include "via.h"
#include "qry.h"
#include "exHash.h"

#define MAX_PATH 512
#define TAMANHO_HASH 1000

static void extrair_nome_base(const char *caminho, char *nome_base) {
    const char *ultimo_slash = strrchr(caminho, '/');
    strcpy(nome_base, ultimo_slash ? ultimo_slash + 1 : caminho);

    char *ponto_ext = strrchr(nome_base, '.');
    if (ponto_ext) {
        *ponto_ext = '\0';
    }
}

static void montar_caminho(char *path_completo, const char *base_dir, const char *nome_arquivo) {
    if (base_dir != NULL && strlen(base_dir) > 0) {
        if (base_dir[strlen(base_dir) - 1] == '/')
            sprintf(path_completo, "%s%s", base_dir, nome_arquivo);
        else
            sprintf(path_completo, "%s/%s", base_dir, nome_arquivo);
    } else {
        strcpy(path_completo, nome_arquivo);
    }
}


int main(int argc, char *argv[]) {
    char *dir_entrada = NULL;
    char *dir_saida = NULL;
    char *arq_geo = NULL;
    char *arq_via = NULL;
    char *arq_qry = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) dir_entrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) arq_geo = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) dir_saida = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) arq_qry = argv[++i];
        else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) arq_via = argv[++i];
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Uso: ./ted -f <arquivo.geo> -o <dir_saida> [-e <dir_entrada>] [-q <arquivo.qry>] [-v <arquivo.via>]\n");
            return 0;
        }
    }

    if (arq_geo == NULL || dir_saida == NULL) {
        printf("Erro: Parametros obrigatorios -f <arquivo.geo> ou -o <dir_saida> estao faltando.\n");
        return 1;
    }

    char nome_base_geo[MAX_PATH] = "";
    char nome_base_qry[MAX_PATH] = "";
    
    extrair_nome_base(arq_geo, nome_base_geo);
    if (arq_qry != NULL) {
        extrair_nome_base(arq_qry, nome_base_qry);
    }

    char path_geo[MAX_PATH], path_via[MAX_PATH], path_qry[MAX_PATH];
    montar_caminho(path_geo, dir_entrada, arq_geo);
    
    if (arq_via != NULL) montar_caminho(path_via, dir_entrada, arq_via);
    if (arq_qry != NULL) montar_caminho(path_qry, dir_entrada, arq_qry);

    char path_svg[MAX_PATH * 3], path_txt[MAX_PATH * 3];
    
    if (arq_qry != NULL) {
        snprintf(path_svg, sizeof(path_svg), "%s/%s-%s.svg", dir_saida, nome_base_geo, nome_base_qry);
        snprintf(path_txt, sizeof(path_txt), "%s/%s-%s.txt", dir_saida, nome_base_geo, nome_base_qry);
    } else {
        snprintf(path_svg, sizeof(path_svg), "%s/%s.svg", dir_saida, nome_base_geo);
        snprintf(path_txt, sizeof(path_txt), "%s/%s.txt", dir_saida, nome_base_geo); 
    }

    exHash mapa = ler_arquivo_geo(path_geo, TAMANHO_HASH);
    if (mapa == NULL) {
        printf("Erro: Nao foi possivel ler o arquivo geo: %s\n", path_geo);
        return 1;
    }

    Graph g = NULL;
    if (arq_via != NULL) {
        g = ler_caminho_via(path_via);
        if (g == NULL) {
            printf("Erro: Nao foi possivel ler o arquivo via: %s\n", path_via);
            close_exHash(mapa);
            return 1;
        }
    }
    
    double min_x = 0.0, min_y = 0.0, max_x = 15000.0, max_y = 15000.0;    
    FILE *svg = init_svg(path_svg, min_x, min_y, max_x, max_y);
    if (svg == NULL) {
        printf("Erro ao criar arquivo SVG: %s\n", path_svg);
        if (g != NULL) freeGraph(g);
        close_exHash(mapa);
        return 1;
    }

    if (g != NULL) {
        svg_desenha_mapa_base(svg, g);
    }

    FILE *txt = NULL;
    if (arq_qry != NULL) {
        txt = fopen(path_txt, "w");
        if (txt == NULL) {
            printf("Erro ao criar arquivo TXT: %s\n", path_txt);
            close_svg(svg);
            if (g != NULL) freeGraph(g);
            close_exHash(mapa);
            return 1;
        }

        processar_qry(path_qry, g, mapa, svg, txt);
    }
    
    if (txt != NULL) fclose(txt);
    
    close_svg(svg);
    close_exHash(mapa);
    
    if (g != NULL) {
        freeGraph(g);
    }

    return 0;
}