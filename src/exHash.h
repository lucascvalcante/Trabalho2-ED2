#ifndef EXHASH_H
#define EXHASH_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @file exHash.h
 * @brief Módulo de Tabela Hash em memória RAM com encadeamento separado.
 * * Este módulo implementa uma estrutura de tabela hash clássica armazenada
 * inteiramente na memória RAM. Ele é responsável por gerenciar a inserção, 
 * busca, remoção e atualização de registros utilizando chaves alfanuméricas 
 * (como CEPs e CPFs). O tratamento de colisões é feito por encadeamento 
 * separado (listas encadeadas nos slots) e permite gerar relatórios estruturais (.hfd).
 */


// Tipo opaco usando forward declaration. 
typedef struct exHash_s* exHash;


/// @brief Inicializa uma nova tabela hash na memória RAM
/// @param arquivo Caminho do arquivo (Mantido por compatibilidade, ignorado na RAM)
/// @param tamanho_bucket Capacidade máxima do bucket (Mantido por compatibilidade, ignorado na RAM)
/// @param tamanho_dado Tamanho em bytes do dado que será clonado/salvo (ex: sizeof(struct))
/// @return Um ponteiro para a estrutura hash inicializada, ou NULL em caso de erro
exHash init_exHash(const char* arquivo, uint32_t tamanho_bucket, size_t tamanho_dado);


/// @brief Insere um novo par chave-valor na tabela hash. Trata colisões via encadeamento.
/// @param hash Ponteiro para a estrutura da tabela hash
/// @param chave Chave alfanumérica (CEP ou CPF) usada para indexar o registro
/// @param dado Ponteiro genérico para a região de memória contendo o dado original a ser copiado
/// @return 'true' se a inserção ocorreu com sucesso, 'false' em caso de erro ou chave duplicada.
bool insert_exHash(exHash hash, const char* chave, void* dado);


/// @brief Busca um dado na tabela hash através da sua chave.
/// @param hash Ponteiro para a estrutura da tabela hash
/// @param chave Chave de busca (CEP ou CPF)
/// @return Ponteiro para uma cópia alocada dinamicamente do dado encontrado na memória RAM, ou NULL se não encontrado.
/// @note O chamador é responsável por dar free() no ponteiro retornado.
void* search_exHash(exHash hash, const char* chave);


/// @brief Remove um registro da tabela hash e desaloca sua memória correspondente
/// @param hash Ponteiro para a estrutura da tabela hash
/// @param chave Chave a ser removida (CEP ou CPF)
/// @return 'true' se o registro foi encontrado e removido, 'false' caso contrário
bool remove_exHash(exHash hash, const char* chave);


/// @brief Produz um arquivo-texto com a representação esquemática dos slots e nós da tabela
/// @param hash Ponteiro para a estrutura da tabela hash
/// @param arquivo_saida_hfd Caminho para o arquivo .hfd/.txt que detalhará o estado da tabela
void dump_exHash(exHash hash, const char* arquivo_saida_hfd);


/// @brief Desaloca toda a memória RAM utilizada pela tabela, pelas listas encadeadas e pelas cópias dos dados
/// @param hash Ponteiro para a estrutura da tabela hash
void close_exHash(exHash hash);


/// @brief Atualiza os bytes de um dado associado a uma chave já existente na tabela
/// @param h Ponteiro para a estrutura da tabela hash
/// @param chave String da chave a ser atualizada
/// @param novo_dado Ponteiro contendo os novos dados que vão sobrescrever o conteúdo antigo por cópia
/// @return true se atualizado com sucesso, false se a chave não for encontrada
bool update_exHash(exHash h, const char* chave, void* novo_dado);


/// @brief Percorre todos os registros válidos da tabela hash executando uma função de callback para cada um
/// @param h Ponteiro para a estrutura da tabela hash
/// @param func Função de callback chamada para cada registro (recebe chave, ponteiro pro dado e um ponteiro extra)
/// @param extra Ponteiro genérico para passar variáveis ou contadores auxiliares adicionais
void foreach_exHash(exHash h, void (*func)(const char* chave, void* dado, void* extra), void* extra);


#endif