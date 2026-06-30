#ifndef DIJKSTRA_H
#define DIJKSTRA_H

/**
 *
 * @brief Implementação do algoritmo de Dijkstra para cálculo de caminho mínimo.
 * @details Este módulo utiliza um Min-Heap otimizado para encontrar o caminho 
 * mais curto entre dois vértices em um grafo, garantindo eficiência O(E log V).
 */


#include "minheap.h"
#include "list.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/// @brief Retorna o caminho mais curto entre 2 pontos utilizando o algoritmo de dijkstra
/// @param g Ponteiro para o grafo analisado
/// @param origem Ponto de origem
/// @param destino Ponto de origem
/// @param por_tempo Decide se o calculo será feito por tempo ou por comprimento
/// @return Uma lista contendo os vértices do caminho mínimo
Lista dijkstra(Graph g, int origem, int destino, bool por_tempo);


#endif


