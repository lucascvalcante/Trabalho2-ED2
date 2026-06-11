/**
 * 
 * @brief Fila de Prioridades (Min-Heap) otimizada por índices para o Dijkstra.
 * 
 */

#ifndef MINHEAP_H
#define MINHEAP_H


#include <stdbool.h>


// Tipo opaco para a estrutura do Min-Heap
typedef struct MinHeap_s* MinHeap;


/// @brief Cria uma fila de prioridade baseada em min-heap
/// @param max_vertices Número máximo de vértices do grafo
/// @return Ponteiro para o heap criado
MinHeap createMinHeap(int max_vertices);


/// @brief Libera toda a memória alocada pelo heap
/// @param h Ponteiro para o heap que será liberado
void freeMinHeap(MinHeap h);


/// @brief Atualiza a distância de um vértice na fila
/// @param h Ponteiro para o heap
/// @param vertice_idx índice do vértice que será alterado
/// @param nova_distancia Nova menor distância do vértice
void updateDistance(MinHeap h, int vertice_idx, double nova_distancia);


/// @brief Retorna o índice do vértice que possui a menor distância atualmente
/// @param h Ponteiro para o heap
/// @return O índice do vértice
int extractMin(MinHeap h);


/// @brief Verifica se a fila de prioridade está vazia
/// @param h Ponteiro para o heap
/// @return 'true' se estiver vazia
bool isMinHeapEmpty(MinHeap h);


/// @brief Verifica se um vértice específico ainda está na lista
/// @param h Ponteiro para o heap
/// @param vertice_idx Id do vértice que será visitado
/// @return 'true' se ainda estiver na lista
bool isVertexInHeap(MinHeap h, int vertice_idx);



#endif