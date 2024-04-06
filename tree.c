#include "std.h"
#include "list.h"
#include "tree.h"
#include "decompress.h"
#include "compress.h"

bool is_leaf(NODE *node)
{
    return node->left == NULL && node->right == NULL;
}

uint8_t get_data(NODE *node)
{
    if (node == NULL)
    {
        puts("NO NULO");
    }
    uint8_t *data = (uint8_t *)node->data;
    return *data;
}

int get_frequency(NODE *node)
{
    if (node == NULL)
    {
        puts("NO NULO");
        return -1;
    }
    int *frequency = (int *)node->frequency;
    return *frequency;
}

NODE *removeMin(HEAD *myStruct)
{
    NODE *temp = myStruct->head;
    myStruct->head = myStruct->head->next;
    myStruct->size--;
    return temp;
}

void createHuffmanTree(HEAD *myStruct)
{
    while (myStruct->size > 1)
    {
        NODE *newNode = create_node();

        newNode->left = removeMin(myStruct);
        newNode->right = removeMin(myStruct);

        *((int *)(newNode->frequency)) = get_frequency(newNode->left) + get_frequency(newNode->right);

        insert_sorted(myStruct, newNode);
    }
}