#ifndef QRY_H
#define QRY_H

/**
 * 
 * @brief Módulo responsável pela interpretação e execução do arquivo de consultas (.qry).
 * Este módulo processa os comandos de busca de endereços, alterações de velocidade,
 * cálculo de componentes conexos, árvores geradoras mínimas e rotas (Dijkstra),
 * integrando a lógica do Grafo e gerando as saídas nos arquivos TXT e SVG.
 */

#include <stdio.h>
#include "graph.h"
#include "exHash.h"


/// @brief Lê e processa linha por linha dos arquivos .qry
/// @param arquivo_qry Nome do arquivo .qry
/// @param g Grafo contendo a malha viária
/// @param quadras Tabela hash contendo as quadras
/// @param svg Arquivo svg de saída
/// @param txt Arquivo txt de saída
void processar_qry(const char *arquivo_qry, Graph g, exHash quadras, FILE *svg, FILE *txt);

#endif