#include "std.h"
#include "list.h"
#include "tree.h"
#include "decompress.h"
#include "compress.h"

void malloc_error_reporter(void *ptr)
{
    if (ptr == NULL)
    {
        perror("Erro na alocação de memória");
        exit(EXIT_FAILURE);
    }
}

void file_error_reporter(FILE *ptr)
{
    if (ptr == NULL)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
}

void init_struct(HEAD *Mystruct)
{
    Mystruct->head = NULL;
    Mystruct->size = 0;
}

NODE *create_node()
{
    NODE *new_node = malloc(sizeof(NODE));
    malloc_error_reporter(new_node);

    new_node->data = malloc(sizeof(uint8_t));
    malloc_error_reporter(new_node->data);
    new_node->frequency = malloc(sizeof(int));
    malloc_error_reporter(new_node->frequency);

    *(uint8_t *)new_node->data = '*';
    *(int *)new_node->frequency = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->next = NULL;

    return new_node;
}

void insert_in_linked_list(HEAD *Mystruct, unsigned int *frequency_table)
{
    for (unsigned int i = 0; i < TAM; i++)
    {
        if (frequency_table[i] > 0)
        {

            NODE *new_node = create_node();     // '*'
            *((uint8_t *)(new_node->data)) = i; // Desrreferencia o ponteiro e converte um int para byte
            *((int *)(new_node->frequency)) = frequency_table[i];

            insert_sorted(Mystruct, new_node);
        }
    }
}

void insert_sorted(HEAD *Mystruct, NODE *new_node)
{
    NODE *current = Mystruct->head;
    NODE *prev = NULL;

    // Encontre o local adequado para inserir o novo nó com base na frequência
    while (current != NULL && get_frequency(current) < get_frequency(new_node))
    {
        prev = current;
        current = current->next;
    }

    // Insira o novo nó na posição correta
    if (prev == NULL)
    {
        new_node->next = Mystruct->head;
        Mystruct->head = new_node;
    }
    else
    {
        prev->next = new_node;
        new_node->next = current;
    }
    Mystruct->size++;
}

void print_linked_list(HEAD *Mystruct)
{
    NODE *current = Mystruct->head;
    while (current != NULL)
    {
        printf("Byte: %c, Frequência: %d\n", *(uint8_t *)current->data, *(int *)current->frequency);
        current = current->next;
    }
}