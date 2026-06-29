#ifndef GEO_H
#define GEO_H

/**
 * @brief Módulo responsável pela leitura e processamento do arquivo geográfico (.geo).
 * Este arquivo define a interface para extrair os dados das quadras e suas 
 * respectivas propriedades visuais (cores e espessura de borda). O módulo 
 * atua como uma máquina de estados para as cores e armazena os elementos 
 * extraídos em uma Tabela Hash, utilizando o CEP como chave de busca.
 */

#include "exHash.h"


/// @brief Lê o arquivo .geo e popula uma tabela hash populada 
/// @param nome_arquivo Nome do arquivo .geo
/// @param tamanho_hash Tamanho inicial da tabela hash
/// @return A tabela hash populada
exHash ler_arquivo_geo(const char* nome_arquivo, int tamanho_hash);



#endif