#ifndef GRAPH_H
#define GRAPH_H

/**
 * @file graph.h
 * @brief Definição do Tipo Abstrato de Dados (TAD) para um Grafo Direcionado.
 * Este módulo fornece a interface para a criação, manipulação e liberação de 
 * um grafo baseado em Listas de Adjacência. Ele oculta a implementação interna 
 * (Struct Opaca), garantindo o encapsulamento dos dados. O grafo é focado em 
 * representar uma malha viária, onde os vértices são cruzamentos e as arestas 
 * são os trechos de rua que os conectam.
 * @note As estruturas internas (Graph_s, Vertex, Edge) estão definidas apenas
 * no arquivo graph.c para manter a opacidade do TAD.

 */
#include <stdbool.h>


/// @brief Tipo opaco de uma struct que representa o grafo
typedef struct Graph_s *Graph;


/// @brief Tipo opaca para representar uma aresta(rua)
typedef struct Edge *Edge_t;


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


/// @brief Retorna a coordenada 'X' do vértice
/// @param g Ponteiro para o grafo que contém o vértice
/// @param index Index do vértice que retornará a coordenada 'X'
/// @return A coordenada 'X'
double getVertexX(Graph g, int index);


/// @brief Retorna a coordenada 'Y' do vértice
/// @param g Ponteiro para o grafo que contém o vértice
/// @param index Index do vértice que retornará a coordenada 'Y'
/// @return A coordenada 'Y'
double getVertexY(Graph g, int index);


/// @brief Retorna o ID em formato de texto (string) de um vértice
/// @param g Ponteiro para o grafo
/// @param index Index do vértice procurado
/// @return String contendo o ID do vértice
char* getVertexId(Graph g, int index);


/// @brief Retorna o número total de vértices atualmente inseridos no grafo
/// @param g Ponteiro para o grafo
/// @return A quantidade de vértices inseridos
int getNumVertices(Graph g);


/// @brief Retorna o número total de arestas (ruas) inseridas no grafo
/// @param g Ponteiro para o grafo
/// @return A quantidade de arestas no grafo
int getNumEdges(Graph g);


/// @brief Retorna a primeira aresta (rua) da lista de adjacência de um vértice
/// @param g Ponteiro para o grafo
/// @param origem Index do vértice de onde a rua parte
/// @return Ponteiro opaco para a primeira aresta, ou NULL se não houver ruas saindo daqui
Edge_t getFirstEdge(Graph g, int origem);


/// @brief Retorna a próxima aresta da lista encadeada de ruas
/// @param atual Ponteiro opaco para a rua atual no laço de repetição
/// @return Ponteiro opaco para a próxima rua, ou NULL se for o fim da lista
Edge_t getNextEdge(Edge_t atual);


/// @brief Retorna o index do vértice de destino para onde esta rua leva
/// @param e Ponteiro opaco para a aresta (rua)
/// @return O index do vértice de destino
int getEdgeDest(Edge_t e);


/// @brief Retorna o comprimento (distância) da rua
/// @param e Ponteiro opaco para a aresta (rua)
/// @return O valor do comprimento
double getEdgeCmp(Edge_t e);


/// @brief Retorna a velocidade média máxima permitida na rua
/// @param e Ponteiro opaco para a aresta (rua)
/// @return O valor da velocidade média
double getEdgeVm(Edge_t e);


/// @brief Verifica se a rua está ativada e liberada para o trânsito
/// @param e Ponteiro opaco para a aresta (rua)
/// @return true se a rua puder ser usada, false se estiver bloqueada/desativada
bool isEdgeActive(Edge_t e);


/// @brief Desativa uma rua específica, bloqueando o tráfego nela
/// @param g Ponteiro para o grafo
/// @param origem Index do vértice de origem da rua
/// @param destino Index do vértice de destino da rua
void deactivateEdge(Graph g, int origem, int destino);

#endif