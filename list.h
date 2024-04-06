#ifndef LIST_H
#define LIST_H

/**
 * @brief Estrutura de um nó
 * 
 * @details Esta estrutura representa o nó da lista encadeada e árvore
 * 
*/
typedef struct NODE {
  void *data; /**< Ponteiro que armazena o endereço do byte */
  void* frequency; /**< Ponteiro que armazena a frequencia do byte */
  struct NODE* left; /**< Filho esquerdo */
  struct NODE* right; /**< Filho direito */
  struct NODE* next; /**< Próximo nó da lista encadeada */
} NODE;

/**
 * @brief Estrutura da lista encadaeada e árvore
 * 
 * @details Esta estrutura representa tanto a cabeça da lista encadeada quanto a raiz da árvoreas
*/
typedef struct HEAD{
  struct NODE* head; /**< Ponteiro para a cabeça/raiz */
  int size; /**< Tamanho da estrutura */
} HEAD; 

/**
 * @brief Verifica se a alocação dinâmica foi bem sucedida
 * 
 * @param ptr: Ponteiro genérico
 * 
*/
void malloc_error_reporter(void* ptr);

/**
 * @brief Funcao para reportar possível erro ao abrir arquivos
 * 
 * @param file: Arquivo que será verificado
*/
void file_error_reporter(FILE* file);

/**
 * @brief Prepara a estrutura para uso

 * @param head: Estrutura que será preparada
*/
void init_struct(HEAD* head);

/**
 * @brief Cria um nó genérico
 * 
 * @details: Inicializa data com '*'. Inicializa frequency com zero
 * 
 * @return Retorna o novo nó
*/
NODE* create_node(); 

/**
 * @brief Prepara o nó que será inserido na lista encadeada
 * 
 * @details Funcao auxiliar de insert sorted. Esta funcao já
            prepara o novo no a ser inserido de maneira ordenada
 * 
 * @param Mystruct: A estrutura da lista/árvore
 * @param frequency_table: A tabela de freqência de bytes
*/
void insert_in_linked_list(HEAD* Mystruct, unsigned int* frequency_table); 

/**
 * @brief Insere o nó de maneira crescente
 *  
 * 
 * @param Mystruct: Estrutura da lista/árvore
 * @param new_node: Nó que será inserido
*/
void insert_sorted(HEAD* Mystruct, NODE* new_node); 

/**
 * @brief Remove logicamente o primeiro nó da lista
 * 
 * @param list: Ponteiro para a cabeça da lista
 * @param currentSize: Ponteiro para o tamanho da estrutura
 * 
 * @return byte do nó que foi removido
*/
uint8_t removeFirst(NODE **list, int *currentSize);


void print_linked_list(HEAD* Mystruct);
/**
 * @brief Retorna a frequência de um nó
 * 
 * @param node: Nó que será verificado
 * 
 * @return Retorna a frequência do nó
*/

#endif

