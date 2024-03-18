#ifndef TREE_H
#define TREE_H
#include "std.h"
#include "list.h"
#include "decode.h"
#include "encode.h"

/**
 * @brief Verifica se o nó é uma folha
 * 
 * @param tree_node: Nó da árvore de Huffman
 * 
 * @return Se é ou não uma folha
*/
bool is_leaf(NODE* tree_node);

/**
 * @brief Pega o byte do nó x
 * 
 * @param node: Nó da estrutura
 * 
 * @return byte do nó
*/
uint8_t get_data(NODE* node);

/**
 * @brief Exibe a árvore em pré-ordem
*/
void pre_order_trasversal(NODE* tree_root);

/**
 * @brief Constrói a árvore de Huffman
 * 
 * @details Constrói a árvore a partir da lista encadeada
 * 
 * @param myStruct: Estrutura da lista/árvore
 * @param currentSize: Ponteiro para o tamanho da estrutura
*/
void huffmanTree(HEAD* myStruct,int *currentSize);

/**
 * @brief Pega a frquência do nó x
 * 
 * @param node: Nó lista/árvore
 * 
 * @return A frequência do nó x
*/
int get_frequency(NODE* node); 

#endif
