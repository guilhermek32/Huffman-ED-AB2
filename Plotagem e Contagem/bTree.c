#include <stdio.h>
#include <stdlib.h>
#include "bTree.h"

struct bTree
{
    int data;
    bTree *left;
    bTree *right;
};

int isEmptyBT(bTree *bt)
{
    return (bt == NULL);
}

bTree* initBT()
{
    return NULL;
}

bTree* createBT(int data, bTree *left, bTree *right)
{
    bTree *new_bTree = (bTree*) malloc(sizeof(bTree));
    
    new_bTree->data = data;
    new_bTree->left = left;
    new_bTree->right = right;

    return new_bTree;
}

bTree* addBT(bTree *bt, int data)
{
    if(isEmptyBT(bt))
    {
        bt = createBT(data, NULL, NULL);
    }
    else if(bt->data > data)
    {
        bt->left = addBT(bt->left, data);
    }
    else
    {
        bt->right = addBT(bt->right, data);
    }

    return bt;
}

bTree* searchBT(bTree *bt, int data, int *comp)
{
    *comp += 1;

    if(isEmptyBT(bt) || (bt->data == data))
    {
        return bt;
    }
    else if(bt->data > data)
    {
        return searchBT(bt->left, data, comp);
    }
    else
    {
        return searchBT(bt->right, data, comp);
    }
}

void printBTPO(bTree *bt)
{
    if(!isEmptyBT(bt))
    {
        printf(" %d ", bt->data);
        printBTPO(bt->left);
        printBTPO(bt->right);
    }
}