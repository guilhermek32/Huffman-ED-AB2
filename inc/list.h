#ifndef LIST_H
#define LIST_H

/*  Esta estrutura representa tanto o no da lista encadeada
    assim como o no da arvore de huffman */
typedef struct NODE {
  void *data;
  unsigned int frequency; 
  struct NODE* left; 
  struct NODE* right; 
  struct NODE* next; 
} NODE;

/*  Esta estrutura representa tanto a cabeça da lista encadeada
    quanto a raiz da árvore*/
typedef struct HEAD{
  struct NODE* head; 
  int size; 
} HEAD; 

void malloc_error_reporter(void* ptr);

/* Funcao para reportar possivel erro ao abrir arquivos*/
void file_error_reporter(FILE* ptr);

/* Inicializa a struct retornando NULL. A mesma struct que será
usada para criar a lista encadeada também será usada para criar a 
árvore de Huffman*/
void init_struct(HEAD*);

/* Cria novo no para inserir na arvore de Huffman
 Observacao: Nós a serem inseridos na lista encadeada 
 serao preparados pela funcao insert_in_linked_list */
NODE* create_node(); 

/* Funcao auxiliar de insert sorted. Esta funcao ja
 prepara o novo no a ser inserido de maneira ordenada */
void insert_in_linked_list(HEAD*, unsigned int*);

/* Recebe o no ja preparado para insercao. Insere o no de maneira crescente */
void insert_sorted(HEAD*, NODE*);

/* Remove o no com menor frequencia da lista encadeada */
uint8_t removeFirst(NODE **list, int *currentSize);

#endif

