#include "geo.h"
#include "quadra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


exHash ler_arquivo_geo(const char* nome_arquivo, int tamanho_hash){
    FILE *file = fopen(nome_arquivo, "r");
    if(file == NULL){
        printf("Não foi possível abrir o arquivo .geo: %s\n", nome_arquivo);
        return NULL;
    }

    char linha[256];

    exHash tabela = init_exHash(tamanho_hash, get_tamanho_quadra());

    char atual_sw[20] = "1px";
    char atual_cfill[50] = "white";
    char atual_cstrk[50] = "black";
    
    while(fgets(linha, sizeof(linha), file) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r') continue;

        char comando[10];
        sscanf(linha, "%9s", comando);

        if(strcmp(comando, "cq") == 0){
            sscanf(linha, "cq %19s %49s %49s", atual_sw, atual_cfill, atual_cstrk);

        } else if(strcmp(comando, "q") == 0){
            char cep[50];
            double x, y, w, h;
            sscanf(linha, "q %49s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            Quadra quadra = cria_quadra(cep, x, y, w, h, atual_sw, atual_cfill, atual_cstrk);
            insert_exHash(tabela, get_quadra_cep(quadra), quadra);
            free_quadra(quadra);
        }
    }

    fclose(file);
    return tabela;
}


typedef struct {
    double min_x, min_y, max_x, max_y;
} BBox;

static void calcular_bbox_cb(const char* chave, void* dado, void* extra) {
    (void)chave;
    if (dado == NULL || extra == NULL) return;

    BBox* bb = (BBox*)extra;
    
    double qx = get_quadra_x(dado);
    double qy = get_quadra_y(dado);
    double qw = get_quadra_w(dado);
    double qh = get_quadra_h(dado);

    if (qx < bb->min_x) bb->min_x = qx;
    if (qy < bb->min_y) bb->min_y = qy;
    if (qx + qw > bb->max_x) bb->max_x = qx + qw;
    if (qy + qh > bb->max_y) bb->max_y = qy + qh;
}

void geo_calcular_limites(exHash mapa, double *min_x, double *min_y, double *max_x, double *max_y) {
    BBox bb = {999999.0, 999999.0, -999999.0, -999999.0};
    
    if (mapa != NULL) {
        foreach_exHash(mapa, calcular_bbox_cb, &bb);
    }
    
    if (bb.min_x == 999999.0) {
        *min_x = 0.0; *min_y = 0.0; *max_x = 15000.0; *max_y = 15000.0;
    } else {
        *min_x = bb.min_x - 50.0;
        *min_y = bb.min_y - 50.0;
        *max_x = bb.max_x + 50.0;
        *max_y = bb.max_y + 50.0;
    }
}
