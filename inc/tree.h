#ifndef TREE_H
#define TREE_H
#include "std.h"
#include "list.h"
#include "decode.h"
#include "encode.h"

/* Verifica se é uma folha*/
bool is_leaf(NODE*);

/* Retorna o byte do no*/
uint8_t get_data(NODE*);

/*  Exibe a arvore em pre-ordem */
void pre_order_trasversal(NODE*);

/*
    monta a árvore de huffman com a lista ordenada
*/
void huffmanTree(HEAD* myStruct,int *currentSize);

#endif
