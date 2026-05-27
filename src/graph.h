#ifdef GRAPH_H
#define #GRAPH_H


/// @brief Tipo opaco de uma struct
typedef struct graph_s *Graph;


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



#endif