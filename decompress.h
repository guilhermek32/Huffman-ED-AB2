#ifndef DECODE_H
#define DECODE_H
#include "list.h"

/**
 * @brief retorna o tamanho do arquivo compactado
 * 
 * @param file: O arquivo compactado
 * 
 * @return O tamanho do arquivo compactado
*/
unsigned long long int find_file_size(FILE* file);

/**
 * @brief Verifica se o byte está setado na posição i
 * 
 * @param byte: O byte que será avaliado
 * @param i: O indice do byte que iremos verificar
 * 
 * @return Se está ou não setado
*/
bool is_seted(uint8_t byte, int i);

/**
 * @brief Pega o tamanho da árvore e o tamanho do lixo do cabeçalho
 * 
 * @param compressed_file: O arquivo compactado
 * @param trashSize: Ponteiro para o tamanho do lixo
 * @param treeSize: Ponteiro para o tamanho da árvore
 * 
*/
void get_tree_and_trash_size(FILE* compressed_file, int* trashSize, int* treeSize);

/**
 * @brief Refaz a árvore de Huffman a partir do cabeçalho
 * 
 * @param archive: Arquivo compactado
 * @param treeSize: Ponteiro para o arquivo compactado
 * 
 * @return A raiz da árvore de Huffman
*/
NODE *getTree(FILE *archive,int *treeSize);

/**
 * @brief Descomprimi o arquivo compactado
 * 
 * @param compressed_file: O arquivo compactado
 * @param FileOut: O arquivo descompactado
 * @param coded_size: O tamanho total da codificação
 * @param treeRoot: A raiz da árvore de Huffman
 * @param trashSize: O tamanho do lixo
 * 
*/
void unzip(FILE* compressed_file, FILE* fileOut, unsigned long long coded_size, NODE* treeRoot, int trashSize);

void print_last_byte(FILE* compressedFile, char* extension);

NODE *get_tree(FILE *archive, int *treeSize); 

#endif