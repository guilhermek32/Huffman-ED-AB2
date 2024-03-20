/** 
 * BinaryTree ADT
*/

//
// Structs
//

/**
 * @brief Estrutura de uma Árvore de Busca Binária.
 * 
 */
typedef struct bTree bTree;


//
// Return - bTree function()
//

/**
 * @brief Cria uma árvore binária vazia.
 * 
 * @return bTree* 
 */
bTree* initBT();

/**
 * @brief Cria e inicializa os componentes (data) , (left) , (right) de um nó de uma árvore binária,
 * retornando o novo nó.
 * 
 * @param data 
 * @param left 
 * @param right 
 * @return bTree* 
 */
bTree* createBT(int data, bTree *left, bTree *right);

/**
 * @brief Adiciona um dado elemento (data) em uma árvore binária informada (bt).
 * 
 * @param bt 
 * @param data 
 * @return bTree* 
 */
bTree* addBT(bTree *bt, int data);

bTree* searchBT(bTree *bt, int data, int *comp);


//
// Return - int function()
//

/**
 * @brief Verifica o estado de uma árvore binária informada (bt), retornando 1 se ela estiver vazia
 * ou 0 se ela não estiver vazia.
 *  
 * @param bt 
 * @return int 
 */
int isEmptyBT(bTree *bt);


//
// Return - void function()
//

/**
 * @brief Imprime uma dada árvore binária (bt) em pré-ordem.
 * 
 * @param bt 
 */
void printBTPO(bTree *bt);