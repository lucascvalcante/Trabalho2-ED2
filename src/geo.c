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
        }
    }

    fclose(file);
    return tabela;
}
