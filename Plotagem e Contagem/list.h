/** 
 * list ADT
*/

//
// Structs
//

/**
 * @brief Estrutura de uma Árvore de Busca Binária.
 * 
 */
typedef struct NodeList NodeList;



//
// Return - list function()
//

/**
 * @brief Cria um no da lista vazio.
 * 
 * @return list* 
 */
NodeList* initList();


/**
 * @brief 
 * retornando o novo nó.
 * 
 * @param data 
 * @param left 
 * @param right 
 * @return list* 
 */
NodeList* createList(int data, NodeList *next);

/**
 * @brief Adiciona um dado elemento (data) em uma árvore binária informada (bt).
 * 
 * @param list
 * @param data 
 * @return list* 
 */
void insertList(struct NodeList** head, int data);

void searchList(struct NodeList *head, int data, int *count);

//
// Return - int function()
//
int isEmptyList(struct NodeList *head);