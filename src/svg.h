#ifndef SVG_H
#define SVG_H


/**
 * @brief Módulo de Geração e Manipulação de Imagens Vetoriais (SVG).
 * Este módulo abstrai a complexidade da sintaxe XML do formato SVG, fornecendo
 * uma interface simples (em C) para desenhar os elementos visuais do mapa da cidade.
 * Ele suporta a renderização de elementos estáticos (quadras, ruas, focos, placas) 
 * e a construção de caminhos dinâmicos (paths e animações) utilizados para 
 * ilustrar o resultado do cálculo de rotas e consultas complexas do sistema.
 */


#include "graph.h"
#include <stdio.h>

/// @brief Inicia o arquivo svg com a tag de início
/// @param nome_arquivo Nome do arquivo svg
/// @param min_x Coordenada 'x' mínima para desenhar a bounding-box
/// @param min_y Coordenada 'y' mínima para desenhar a bounding-box
/// @param max_x Coordenada 'x' máxima para desenhar a bounding-box
/// @param max_y Coordenada 'y' máxima para desenhar a bounding-box
/// @return Ponteiro para o arquivo svg
FILE *init_svg(const char* nome_arquivo, double min_x, double min_y, double max_x, double max_y);


/// @brief Fecha o arquivo svg
/// @param svg Ponteiro para o arquivo svg
void close_svg(FILE *svg);


/// @brief Desenha um retângulo no svg, usado para representatr as quadras
/// @param svg Ponteiro para o arquivo SVG
/// @param x Coordenada 'X' do retângulo(canto superior esquerdo)
/// @param y Coordenada 'Y' do retângulo(Canto superior esquerdo)
/// @param w Largura do retângulo
/// @param h Altura do retângulo
/// @param cfill Cor de preenchimento do retângulo
/// @param sw Espessura da borda do retângulo
/// @param cstrk Cor da borda do retângulo
/// @param opacity Opacidade do retangulo
void desenhar_retangulo_svg(FILE *svg, double x, double y, double w, double h, const char* cfill, const char* sw, const char* cstrk, double opacity);


/// @brief Escreve um texto no SVG 
/// @param f Ponteiro para o arquivo SVG
/// @param x Coordenada X do texto
/// @param y Coordenada Y do texto
/// @param txt Conteudo do texto
/// @param cor Cor do texto
void desenhar_texto_svg(FILE *svg, double x, double y, const char* txt, const char* cor);


/// @brief Desenha uma linha do svg
/// @param svg Ponteiro para o arquivo svg
/// @param x1 Primeira Coordenada 'x' da linha 
/// @param y1 Primeiro coordenada 'y' da linha
/// @param x2 Segunda coordenada 'x' da linha
/// @param y2 Segunda coordenada 'y' da linha
/// @param cor Cor da linha
/// @param sw Espessura de bordo da linha
void desenhar_linha_svg(FILE *svg, double x1, double y1, double x2, double y2, const char* cor, const char* sw);


/// @brief Desenha um círculo no svg
/// @param svg Ponteiro para o arquivo svg
/// @param cx Coordenada 'x' do centro do círculo
/// @param cy Coordenada 'y' do centro do círculo
/// @param r Raio do círculo
/// @param corb Cor de borda
/// @param corp Cor de preenchimento
void desenhar_circulo_svg(FILE *svg, double cx, double cy, double r, const char* corb, const char* corp);


/// @brief Inicia a escrita uma tag path no svg
/// @param svg Ponteiro para o svg
/// @param id_caminho identificador do caminho
/// @param cor Cor do caminho
/// @param sw Espessura do caminho
void iniciar_path_svg(FILE *svg, const char* id_caminho, const char *cor, const char *sw);


/// @brief Adiciona um segmento de reta no caminho atual
/// @param svg Ponteiro para o svg
/// @param x Coordenada 'X' do segmento
/// @param y Coordenada 'Y' do segmento
/// @param eh_inicio '1' se for o primeiro ponto do path, '0' para os demais
void adicionar_ponto_path_svg(FILE *svg, double x, double y, int eh_inicio);


/// @brief Fecha o path svg
/// @param svg Ponteiro para o arquivo svg
void fechar_path_svg(FILE *svg);


/// @brief Faz a animaçao do caminho do svg
/// @param svg Ponteiro para o svg
/// @param id_caminho identificador do caminho
/// @param velocidade Velocidade da animação
void desenhar_animacao_svg(FILE *svg, const char* id_caminho, const char* velocidade);


/// @brief Desenha um retângulo tracejado para delimitar uma componente fortemente conexa (ilha viária)
/// @param svg Ponteiro para o arquivo svg
/// @param cor Cor da borda e preenchimento do retângulo
/// @param min_x Coordenada X mínima da componente
/// @param min_y Coordenada Y mínima da componente
/// @param max_x Coordenada X máxima da componente
/// @param max_y Coordenada Y máxima da componente
void svg_rect_componente_conexo(FILE *svg, char *cor, double min_x, double min_y, double max_x, double max_y);


/// @brief Renderiza a malha viária base desenhando os cruzamentos e as ruas com setas direcionais
/// @param svg Ponteiro para o arquivo svg
/// @param g Ponteiro para a estrutura do Grafo que contém as vias
void svg_desenha_mapa_base(FILE *svg, Graph g);


/// @brief Desenha uma linha tracejada no svg
/// @param svg Ponteiro para o arquivo svg
/// @param x1 Primeira coordenada 'x' da linha
/// @param y1 Primeira coordenada 'y' da linha
/// @param x2 Segunda coordeanda 'x' da linha
/// @param y2 Segunda coordenada 'y' da linha
/// @param cor Cor da linha
/// @param sw Espessura da borda da linha
void desenhar_linha_tracejada(FILE *svg, double x1, double y1, double x2, double y2, const char* cor, const char* sw);



/// @brief Desenha uma bouding box no svg
/// @param svg Ponteiro para o svg
/// @param x Coordenada 'x' da bounding box
/// @param y Coordenada 'y' da bounding box
/// @param largura Largura da bounding box
/// @param altura Altura da bouding box
/// @param cor Cor da bouding box
/// @param opacidade Opacidade da bouding box
void desenhar_bounding_box(FILE *svg, double x, double y, double largura, double altura, const char *cor, double opacidade);

#endif