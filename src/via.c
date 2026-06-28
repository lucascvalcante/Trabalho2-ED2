#include "via.h"

Graph ler_caminho_via(const char* nome_arquivo){
    FILE* file = fopen(nome_arquivo, "r");
    if(file == NULL){
        printf("Não foi possível abrir o arquivo de vias: %s\n", nome_arquivo);
        return NULL;
    }

    char linha[256];
    Graph g = NULL;

    if(fgets(linha, sizeof(linha), file) != NULL){
        int num_vertices = atoi(linha);
        g = initGraph(num_vertices);
    }

    if(g == NULL){
        fclose(file);
        return NULL;
    }

    
    while(fgets(linha, sizeof(linha), file) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r') continue;

        char tipo;
        sscanf(linha, " %c", &tipo);
        if(tipo == 'v'){
            char id[50];
            double x, y;     
            sscanf(linha, "v %49s %lf %lf", id, &x, &y);
            insertVertex(g, id, x, y);
        }else if(tipo == 'e'){
            char id_origem[50], id_destino[50];
            char ldir[50], lesq[50], nome_rua[100];
            double cmp, vm;

            sscanf(linha, "e %49s %49s %49s %49s %lf %lf %99s", id_origem, id_destino, ldir, lesq, &cmp, &vm, nome_rua);

            int idx_origem = getVertexIndex(g, id_origem);
            int idx_destino = getVertexIndex(g, id_destino);

            if(idx_origem != -1 && idx_destino != -1){
                insertEdge(g, idx_origem, idx_destino, nome_rua, lesq, ldir, cmp, vm);
            }
        }
    }

    fclose(file);
    return g;
}