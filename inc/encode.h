#ifndef ENCODE_H
#define ENCODE_H
#include "list.h"

typedef struct BitHuff {
    unsigned long long int bitH;  
    int size;  
} BitHuff; 

/* Retorna a tabela de frequencia. Todos os campos sao inicializados como zero */
unsigned int* init_frequency_table();

/* Contabiliza a frequencia de cada byte do arquivo na tabela de frequencia*/
void count_frequency(unsigned int*, char*);

/* Ativa o bit na posição j */
void set_bit(int, uint8_t*);

/*  Escreve o cabeçalho do arquivo, escrevendo 
    cada campo individualmente. Retorna o tamanho
    da árvore em pre pordem*/
void write_header(FILE* cmp_file, unsigned short int tree_and_trash_size, NODE* root); 

/* Percorre a arvore e escreve seus bytes no arquivo compactado */
void write_tree(NODE* root, FILE* cmp_file);

/*  Recebe o tamanho do lixo, o tamanho da árvore, a string
    da árvore e retorna os primeiros 2 bytes do header. Utiliza
    operações bit wise para armazenar o tamanho do lixo e da
    árvore em uma variável de 2 bytes */
unsigned short int setFirstTwoBytes(unsigned short int trash_size, unsigned short int tree_size);

// Constroi a tabela de bytes codficados
void buildTable(NODE* tree_node, BitHuff table[], BitHuff code);

// void build_Table(NODE* tree_node,bitHff table[], char path[], int i);

/*
  Recebe a tabela de frequencua para calcular o lixo
 */
 unsigned short int getTrashSize(unsigned int frequency[], BitHuff table[]);

/*
    Calcula o tamanho da arvore, contabilizando os 
    caracteres de escape
*/
void getTreeSize(NODE* tree_root, unsigned short int* treeSize); 


bool isSetedLong(unsigned long long int code, int i); 

/* Le o arquivo original byte a byte, busca a codificacao do byte no dicionario,
   Cria um novo byte compactado, e escreve no novo arquivo compactado*/
void setBytes(FILE *fileIn,FILE *fileOut,BitHuff table[]); 

// void compress(bitHff code_table[], char* file_name, HEADER header, NODE* root, FILE* cmp_file); 

#endif