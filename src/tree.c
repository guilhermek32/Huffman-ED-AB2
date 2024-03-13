#include "std.h"
#include "list.h"
#include "tree.h"
#include "decode.h"
#include "encode.h"

bool is_leaf(NODE* node){
    return node->left == NULL && node->right == NULL; 
}

uint8_t get_data(NODE* node){
    if(node == NULL){
        puts("NO NULO");
    }
    uint8_t *data = (uint8_t*)node->data; 
    return *data; 
}

void pre_order_trasversal(NODE* root) {
    if (root == NULL) {
        return; 
    }

    printf("%c", get_data(root));
    pre_order_trasversal(root->left);
    pre_order_trasversal(root->right);
      
}

void huffmanTree(HEAD* myStruct,int *currentSize){
    while(*currentSize > 1){ 
        int frequency = (myStruct->head)->frequency + (myStruct->head)->next->frequency;// soma das frequências dos primeiros nós
        NODE* newNode = create_node();
        newNode->frequency = frequency;

        newNode->left = myStruct->head;// esquerda do novo nó vai receber o primeiro elemento
        removeFirst(&myStruct->head,currentSize);

        newNode->right = (myStruct->head);//direita do novo nó vai receber o segundo elemento
        removeFirst(&myStruct->head,currentSize);

        insert_sorted(myStruct, newNode);// adiciona o novo nó de maneira ordenada
    }
    return;
} 