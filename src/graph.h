/**
 * @file graph.h
 * @brief Definição do Tipo Abstrato de Dados (TAD) para um Grafo Direcionado.
 /** Este módulo fornece a interface para a criação, manipulação e liberação de 
 * um grafo baseado em Listas de Adjacência. Ele oculta a implementação interna 
 * (Struct Opaca), garantindo o encapsulamento dos dados. O grafo é focado em 
 * representar uma malha viária, onde os vértices são cruzamentos e as arestas 
 * são os trechos de rua que os conectam.
 /** @note As estruturas internas (Graph_s, Vertex, Edge) estão definidas apenas
 * no arquivo graph.c para manter a opacidade do TAD.
 */


#ifndef GRAPH_H
#define GRAPH_H


/// @brief Tipo opaco de uma struct que representa o grafo
typedef struct Graph_s *Graph;


/// @brief Cria um novo grafo com 'n' vértices
/// @param n Número de vértices que serão criados
/// @return Ponteiro para o novo grafo
Graph initGraph(int n);


/// @brief Adiciona um vérticec no grafo
/// @param g Grafo onde o vértice será inserido
/// @param id Id no vértice
/// @param x Coordenada X do vértice
/// @param y Coordenada Y do vértice
void insertVertex(Graph g, char* id, double x, double y);


/// @brief Liga uma aresta entre dois vértices 
/// @param g Grafo onde será inserida a aresta
/// @param origem Vértice de origem
/// @param destino Vértice de destino
/// @param rua Nome da rua(aresta)
/// @param lesq Cep da quadra que está do lado esquerdo da rua
/// @param ldir Cep da quadra que está do lado direito da rua
/// @param cmp Comprimento da rua
/// @param vm Velocidade média que os carros trafegam na rua
void insertEdge(Graph g, int origem, int destino, char* rua, char* lesq, char* ldir, double cmp, double vm);


/// @brief Libera toda a memória alocada pelo grafo
/// @param g Ponteiro para ao grafo que será liberado
void freeGraph(Graph g);


/// @brief Retorna o index de um vertex específico
/// @param g Parametro para o grafo
/// @param id Id do grafo que terá o index retornado 
/// @return o index
int getVertexIndex(Graph g, char *id);


#endif