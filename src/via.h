#ifndef VIA_H
#define VIA_H

/**
 * @brief Módulo responsável pela leitura e processamento do arquivo de vias (.via).
 * Este arquivo define a interface para extrair os dados geográficos e 
 * topológicos (vértices e arestas/ruas) do arquivo de texto especificado 
 * e populá-los na estrutura principal do Grafo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


/// @brief Lê e executa as ações do arquivo .via
/// @param nome_arquivo Nome do arquivo .via
/// @return Retorna o grafo criado e populado
Graph ler_caminho_via(const char* nome_arquivo);


#endif