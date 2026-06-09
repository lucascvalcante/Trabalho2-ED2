#ifndef LIST_H
#define LIST_H

/// @brief Tipos opacos de escapsulamento   
typedef struct Lista_s* Lista;
typedef void* Node;

/// @brief Cria uma lista vazia
/// @return Ponteiro para a lista
Lista createList();


/// @brief Libera toda a memória alocada pela lista 
/// @param l Ponteiro para a lista que será liberada
void freeList(Lista l);


/// @brief Insere um novo elementot genérico no fim da lista 
/// @param l Ponteiro para a lista
/// @param n Ponteiro para o novo nó(elemento) que será inserido
/// @return A posição que o elemento foi inserido
Node insertList(Lista l, Node n);


/// @brief Retorna o tamanho atual da lista
/// @param l Ponteiro para a lista
/// @return O tamanho da lista
int lengthList(Lista l);


/// @brief Retorna determinado dado em um nó da lista
/// @param l Ponteiro para a lista
/// @param n Posição do dado
/// @return O dado 
void* getList(Lista l, Node n);


/// @brief Retorna o nó da primeira posição da lista
/// @param l Ponteiro para a lista
/// @return O primeiro nó
Node getFirstList(Lista l);


/// @brief Retorna o nó presente após um nó fornecido
/// @param l Ponteiro para a lista
/// @param n Ponteiro para o nó base
/// @return O nó
Node getNextList(Lista l, Node n);


/// @brief Retorna o último nó da lista
/// @param l Ponteiro para a lista
/// @return O último nó
Node getLastList(Lista l);


/// @brief Retorna o nó anterior a um fornecido
/// @param l Ponteiro para a lista
/// @param n Nó fornecido
/// @return O nó anterior
Node getPreviousList(Lista l, Node n);


/// @brief Remove um nó específico da lista
/// @param l Ponteiro a lista
/// @param n Nó que será removido
/// @return o dado do nó removido, para que se possa dar 'free'
void* removeList(Lista l, Node n);


#endif