#include "svg.h"
#include <stdlib.h>
#include <string.h>
#include "graph.h"


FILE *init_svg(const char* nome_arquivo, double min_x, double min_y, double max_x, double max_y){
    FILE *svg = fopen(nome_arquivo, "w");
    if(!svg){
        printf("Não foi possível abrir o arquivo svg: %s\n", nome_arquivo);
        return NULL;
    }

    double margem = SVG_MARGEM; 
    double vx = min_x - margem;
    double vy = min_y - margem;
    double vw = max_x - min_x + 2 * margem;
    double vh = max_y - min_y + 2 * margem;

    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" "
             "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
             "width=\"%.2f\" height=\"%.2f\" "
             "viewBox=\"%.2f %.2f %.2f %.2f\">\n",
             vw, vh, vx, vy, vw, vh);
    fprintf(svg, "<g>\n");    return svg;
}


void close_svg(FILE *svg){
    if(!svg) return;
    fprintf(svg, "</g>\n");
    fprintf(svg, "</svg>\n");
    fclose(svg);
}


void desenhar_texto_svg(FILE *svg, double x, double y, const char* txt, const char* cor){
    if(!svg) return;

    fprintf(svg, "    <text x=\"%f\" y=\"%f\" fill=\"%s\" font-family=\"sans-serif\" font-size=\"12px\">%s</text>\n", 
            x, y, cor, txt);    
}


void desenhar_retangulo_svg(FILE *svg, double x, double y, double w, double h, const char* cfill, const char* sw, const char* cstrk, double opacity){
    if(!svg) return;
    fprintf(svg, "    <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke-width=\"%s\" stroke=\"%s\" opacity=\"%f\" />\n", 
            x, y, w, h, cfill, sw, cstrk, opacity);
}

void desenhar_linha_svg(FILE *svg, double x1, double y1, double x2, double y2, const char* cor, const char* sw){
    if(!svg) return;
    fprintf(svg, "    <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%s\" />\n", 
            x1, y1, x2, y2, cor, sw);
}


void desenhar_circulo_svg(FILE *svg, double cx, double cy, double r, const char* corb, const char* corp){
    if(!svg) return;
    fprintf(svg, "    <circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n", 
            cx, cy, r, corb, corp);
}


void iniciar_path_svg(FILE *svg, const char* id_caminho, const char *cor, const char *sw){
    if(!svg) return;
    fprintf(svg, "    <path id=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"none\" d=\"", 
            id_caminho, cor, sw);
}


void adicionar_ponto_path_svg(FILE *svg, double x, double y, int eh_inicio){
    if(!svg) return;
    if (eh_inicio) {
        fprintf(svg, "M %f %f ", x, y); 
    } else {
        fprintf(svg, "L %f %f ", x, y); 
    }
}

void fechar_path_svg(FILE *svg){
    if(!svg) return;
    fprintf(svg, "\" />\n");
}

void desenhar_animacao_svg(FILE *svg, const char* id_caminho, const char* velocidade){
    if(!svg) return;

    fprintf(svg, "    <circle cx=\"0\" cy=\"0\" r=\"5\" fill=\"red\">\n");
    fprintf(svg, "        <animateMotion dur=\"%s\" repeatCount=\"indefinite\">\n", velocidade);
    fprintf(svg, "            <mpath xlink:href=\"#%s\"/>\n", id_caminho);
    fprintf(svg, "        </animateMotion>\n");
    fprintf(svg, "    </circle>\n");
}


void svg_rect_componente_conexo(FILE *svg, char *cor, double min_x, double min_y, double max_x, double max_y){
    if(!svg) return;

    double height = max_y - min_y;
    double width = max_x - min_x;

    fprintf(svg, "    <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" "
                 "fill-opacity=\"0.15\" stroke=\"%s\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n",
                 min_x, min_y, width, height, cor, cor);
}


    void svg_desenha_mapa_base(FILE *svg, Graph g){
        if (!svg || !g) return;

            fprintf(svg, "  <defs>\n");
            fprintf(svg, "    <marker id=\"mArrow\" markerWidth=\"4\" markerHeight=\"4\" refX=\"4.0\" refY=\"2.0\" orient=\"auto\">\n");
            fprintf(svg, "      <path d=\"M0,0 L0,4.0 L4.0,2.0 z\" style=\"fill: #000000;\" />\n");
            fprintf(svg, "    </marker>\n");
            fprintf(svg, "  </defs>\n\n");

            int total_vertices = getNumVertices(g);

            for (int i = 0; i < total_vertices; i++) {
                double ox = getVertexX(g, i);
                double oy = getVertexY(g, i);
                char *id_origem = getVertexId(g, i);

                fprintf(svg, "    <circle id=\"%s\" cx=\"%f\" cy=\"%f\" r=\"4.0\" fill=\"blue\" "
                            "stroke=\"black\" fill-opacity=\"0.5\" />\n", id_origem, ox, oy);

                fprintf(svg, "    <text x=\"%f\" y=\"%f\" fill=\"blue\" font-size=\"4\" "
                            "text-anchor=\"middle\">%s</text>\n", ox, oy - 6.0, id_origem);

                Edge_t aresta = getFirstEdge(g, i);
                while (aresta != NULL) {
                    int dest_index = getEdgeDest(aresta);
                    
                    double dx = getVertexX(g, dest_index);
                    double dy = getVertexY(g, dest_index);

                    fprintf(svg, "    <path d=\"M%f,%f L%f,%f\" "
                                "stroke=\"black\" fill=\"none\" stroke-width=\"1\" "
                                "marker-end=\"url(#mArrow)\" />\n",
                                ox, oy, dx, dy);

                    aresta = getNextEdge(aresta);
            }
        }    
    }


void desenhar_linha_tracejada(FILE *svg, double x1, double y1, double x2, double y2, const char* cor, const char* sw){
    if(!svg) return;

    fprintf(svg, "    <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%s\" stroke-dasharray=\"5,5\" />\n", 
            x1, y1, x2, y2, cor, sw);
}


void desenhar_bounding_box(FILE *svg, double x, double y, double largura, double altura, const char *cor, double opacidade){
    if(!svg) return;

    fprintf(svg, "    <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" fill-opacity=\"%f\" stroke=\"%s\" stroke-width=\"1.0px\" />\n",
            x, y, largura, altura, cor, opacidade, cor);
}
