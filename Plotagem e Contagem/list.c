#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct NodeList {
    int data;
    struct NodeList* next;
};

int isEmptyList(struct NodeList *head)
{
    return (head == NULL);
}

struct NodeList* initList()
{
    return NULL;
}

void insertList(struct NodeList** head, int valor) {
    // Aloca memória para um novo nó
    struct NodeList* newNode = (struct NodeList*)malloc(sizeof(struct NodeList));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (newNode == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        return;
    }
    
    // Define o valor do novo nó
    newNode->data = valor;
    
    // Define o próximo nó como o atual cabeçalho da lista
    newNode->next = *head;
    
    // Atualiza o cabeçalho da lista para apontar para o novo nó
    *head = newNode;
}

void searchList(struct NodeList *head, int data, int *count)
{
    struct NodeList *aux = head;
    while(aux != NULL)
    {
        *count += 1;
        if(aux->data == data)
        {
            return;
        }
        aux = aux->next;
    }
}

