#ifndef ENCODE_H
#define ENCODE_H
#include "list.h"

/**
 * @brief Está estrutura representa o byte codificado
 * 
*/
typedef struct ByteCodificado {
    unsigned long long int bitH;  /**< Codificação do byte. */
    int size;  /**< tamanho de quantos bits representam a codificação. */
} ByteCodificado; 

/**
 * @brief Inicializa a tabela de frequência de bytes
 * 
 * @details Todos os campos alocados são inicializados com zero
 * 
 * @return A tabela de frequência de bytes
 * 
*/
unsigned int* init_frequency_table();

/**
 * @brief Conta a frequencia de cada byte
 * 
 * @param frequency_table: A tabela de frequência dos bytes
 * @param file_name: Nome do camninho do arquivo de entrada (arquivo que será compactado)
 * 
*/
void count_frequency(unsigned int* frequency_table, char* file_name); 

/**
 * @brief Ativa o bit na posição j
 * 
 * @param j: Indice do bit a ser ativado
 * @param byte: Byte que terá seu bit ativado
 * 
*/
void set_bit(int j, uint8_t* byte); 

/**
 * @brief Escreve o header no arquivo compactado
 * 
 * @param cmp_file: O arquivo compactado
 * @param tree_and_trash_size: Os dois primeiros bytes do arquivo compactado (lixo e tamanho da árvore)
 * @param root: Raiz da árvore de Huffman
 * 
*/
void write_header(FILE* cmp_file, unsigned short int tree_and_trash_size, NODE* root, char* extension); 

/**
 * @brief Escreve a árvore de Huffman em pré-ordem no arquivo compactado
 * 
 * @param root: A raiz da árvore de Huffman
 * @param cmp_file: O arquivo compactado
 * @param table: Dicionário que mapeia cada byte a sua codificação
 * @param extension: A extensão do arquivo original 
 *
*/
void write_tree(NODE* root, FILE* cmp_file);

/**
 * @brief Inicializa os dois primeiros bytes
 * 
 * @param trash_size: O tamanho do lixo
 * @param tree_size: O tamanho da árvore
 * 
 * @details Tamanho do lixo: Primeiros 3 bits. Tamanho da árvore: próximos 13 bits
 * 
 * @return Um unsigned short setado com o tamanho do lixo e tamanho da árvore
 * 
*/
unsigned short int setFirstTwoBytes(unsigned short int trash_size, unsigned short int tree_size);

/**
 * @brief Constroi o dicionário que mapeia cada byte a sua codificação
 * 
 * @param tree_root: A raiz da árvore de Huffman
 * @param table: O dicionário
 * @param code: A codificação de Huffman
 * 
*/
void buildTable(NODE* tree_root, ByteCodificado table[], ByteCodificado code);

void build_table(NODE* treeRoot, unsigned long long **table, unsigned long long code, unsigned long long codeSize, int index); 

/**
 * @brief Calcula o tamanho do lixo
 * 
 * @param frequency: A tabela de frequência dos bytes
 * @param table: O dicionário
 * 
 * @return O tamanho do lixo
*/
unsigned short int getTrashSize(unsigned int frequency[], ByteCodificado table[]);

/**
 * @brief Ativa o bit da cosificação na posição index
 * 
 * @param bitCode: A codificação de Huffman de um byte
 * @param index: Indice da codificação que será ativado
 * 
*/

unsigned long long int setLong(unsigned long long int bitCode, int index);

/**
 * @brief Calcula o tamanho da árvore contabilizando também o scape
 * 
 * @param tree_root: A raiz da árvore de Huffman
 * @param treeSize: Ponteiro para o tamanho do lixo
*/
void getTreeSize(NODE* tree_root, unsigned short int* treeSize); 

/**
 * @brief Verifica se o bit no indice i da codificação de Huffman está ativado 
 * 
 * @param code: Codificação de Huffman de um byte x
 * @param i: Indice que será verificado
 * 
 * @return Se o bit na posição i está setado ou não
*/
bool isSetedLong(unsigned long long int code, int i); 


/**
 * @brief Escreve a codificação de Huffman completa no arquivo compactado
 * 
 * @details Lê o arquivo original byte por byte, busca a codificação do byte no dicionário,
            Cria um novo byte compactado, e escreve no compactado
 * 
 * @param fileIn: Arquivo de entrada (Que será compactado)
 * @param fileOut: Arquivo compactado
 * @param table: Dicionário com a codificação de Huffman de cada byte
*/
void setBytes(FILE *fileIn,FILE *fileOut, ByteCodificado table[]); 

void set_bytes(FILE *fileIn,FILE *fileOut, unsigned long long** table);

unsigned short int get_trash_size(unsigned int frequency[], unsigned long long int** table); 

void writeTree(NODE* root, FILE* cmp_file);

uint8_t getExtension(FILE* compressedFile, char* extension); 

#endif