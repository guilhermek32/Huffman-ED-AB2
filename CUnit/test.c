#include "std.h"
#include "decode.h"
#include "encode.h"
#include "list.h"
#include "tree.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Função de teste simples
void free_linked_list(NODE* root) {

    // Libere a lista encadeada
    while(root != NULL) {
        NODE* temp = root; 
        root = root->next;
        free(temp->data); 
        free(temp->frequency);  
        free(temp);
    }
}
void free_tree(NODE* root) {
     if (root == NULL) {
        return;
    }

    // Limpa a subárvore esquerda
    free_tree(root->left);
    
    // Limpa a subárvore direita
    free_tree(root->right);
    
    // Libera o nó atual
    free(root->data); 
    free(root->frequency); 
    free(root);
}
void test_create_node(void) {
    NODE* new_node = create_node(); 

    CU_ASSERT_PTR_NULL(new_node->right); 
    CU_ASSERT_PTR_NULL(new_node->left);
    CU_ASSERT_PTR_NULL(new_node->next);
    CU_ASSERT_EQUAL(get_data(new_node), '*'); 
    CU_ASSERT_EQUAL(get_frequency(new_node), 0); 

    free_linked_list(new_node);
}
void test_init_struct(void) {
    HEAD* myStruct = malloc(sizeof(HEAD)); 
    init_struct(myStruct); 

    CU_ASSERT_EQUAL(myStruct->size, 0); 
    CU_ASSERT_PTR_NULL(myStruct->head);
 
}
void test_get_data(void) {
    NODE* new_node = create_node();
    *((uint8_t*)(new_node->data)) = 'A';

    CU_ASSERT_EQUAL(get_data(new_node), 'A');

    free_linked_list(new_node); 
}
void test_get_frequency(void) {
    NODE* new_node = create_node();
    *((int*)(new_node->frequency)) = 10;

    CU_ASSERT_EQUAL(get_frequency(new_node), 10);

    free(new_node); 
}
void test_insert_in_linked_list(void){
    unsigned int* frequency_table = init_frequency_table();
    HEAD* myStruct = malloc(sizeof(HEAD));
    init_struct(myStruct); 

    count_frequency(frequency_table, "teste.txt"); 
    insert_in_linked_list(myStruct, frequency_table);

    NODE* current = myStruct->head;
    
    CU_ASSERT_EQUAL(get_data(current), 'F');
    CU_ASSERT_EQUAL(get_frequency(current), 1); 
    current = current->next; 

    CU_ASSERT_EQUAL(get_data(current), 'E');
    CU_ASSERT_EQUAL(get_frequency(current), 2); 
    current = current->next; 

    CU_ASSERT_EQUAL(get_data(current), 'D'); 
    CU_ASSERT_EQUAL(get_frequency(current), 3);
    current = current->next; 

    CU_ASSERT_EQUAL(get_data(current), 'C');
    CU_ASSERT_EQUAL(get_frequency(current), 4); 
    current = current->next;

    CU_ASSERT_EQUAL(get_data(current), 'B');
    CU_ASSERT_EQUAL(get_frequency(current), 5);
    current = current->next; 

    CU_ASSERT_EQUAL(get_data(current), 'A');
    CU_ASSERT_EQUAL(get_frequency(current), 6);

    free_linked_list(myStruct->head); 

}

void test_is_leaf(void) {
    NODE* new_node = create_node(); 

    CU_ASSERT(is_leaf(new_node)); 

    free_linked_list(new_node); 
}

void test_huffmanTree(void) {
    unsigned int* frequency_table = init_frequency_table();
    HEAD* myStruct = malloc(sizeof(HEAD));
    init_struct(myStruct); 


    count_frequency(frequency_table, "teste.txt"); 
    insert_in_linked_list(myStruct, frequency_table);

    huffmanTree(myStruct, &myStruct->size); 

    CU_ASSERT_EQUAL(myStruct->size, 1);

    free_tree(myStruct->head); 
    
}
void test_removeFirst(void) {
    HEAD* myStruct = malloc(sizeof(HEAD));
    init_struct(myStruct); 
    unsigned int* frequency_table = init_frequency_table();

    frequency_table['A'] = 10; 
    frequency_table['C'] = 15; 
    frequency_table['E'] = 5; 

    insert_in_linked_list(myStruct, frequency_table);

    NODE* temp1 = myStruct->head;
    CU_ASSERT_EQUAL(removeFirst(&myStruct->head, &myStruct->size),'E');
    free(temp1); 

    NODE* temp2 = myStruct->head; 
    CU_ASSERT_EQUAL(removeFirst(&myStruct->head, &myStruct->size),'A');
    free(temp2);

    NODE* temp3 = myStruct->head; 
    CU_ASSERT_EQUAL(removeFirst(&myStruct->head, &myStruct->size),'C');
    free(temp3);
    
}
int init_suite() {
    return 0;
}

int clean_suite() {
    return 0; 
}
// Adiciona os testes à suite
int main() {
    CU_pSuite pSuite = NULL;
    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    // Adiciona uma suite de teste
    pSuite = CU_add_suite("Basic_Test", init_suite, clean_suite);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adiciona os testes à suite
    if((CU_add_test(pSuite, "Teste_create_node", test_create_node) == NULL) ||
       (CU_add_test(pSuite, "Teste_init_struct", test_init_struct) == NULL) ||
       (CU_add_test(pSuite, "Teste_get_data", test_get_data) == NULL) ||
       (CU_add_test(pSuite, "Teste_get_frequency", test_get_frequency) == NULL) ||
       (CU_add_test(pSuite, "Teste_insert_in_linked_list", test_insert_in_linked_list) == NULL) ||
       (CU_add_test(pSuite, "Teste_is_leaf", test_is_leaf) == NULL) ||
       (CU_add_test(pSuite, "Teste_huffmanTree", test_huffmanTree) == NULL) ||
       (CU_add_test(pSuite, "Teste_removeFirst", test_removeFirst) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Configura o modo de saída e executa os testes
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Limpa o registro de testes do CUnit
    CU_cleanup_registry();

    return CU_get_error();
}
