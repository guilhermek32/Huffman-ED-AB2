#ifndef DECODE_H
#define DECODE_H
#include "list.h"

/* Retorna o tamanho do arquivo */
unsigned long long int find_file_size(FILE* file);

/* Verifica se o bit na posição i esta setado*/
bool is_seted(uint8_t byte, int i);

/* Escreve o tamanho do lixo e da arvore em trashSize e TreeSize respectivamente */
void get_tree_and_trash_size(FILE* compressed_file, int* trashSize, int* treeSize);

/* Refaz a arvore de huffman a partir do cabecalho */
NODE *getTree(FILE *archive,int *treeSize);

/* Descomprimi o arquivo */
void unzip(FILE* compressed_file, FILE* fileOut, unsigned long long coded_size, NODE* treeRoot, int trashSize);

#endif