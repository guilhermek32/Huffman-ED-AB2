#include "std.h"
#include "list.h"
#include "tree.h"
#include "decompress.h"
#include "compress.h"

unsigned long long int find_file_size(FILE *file)
{
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    unsigned long long int current_postition = ftell(file);

    fseek(file, 0, SEEK_END);                       // Move o indicador de posição para o final do arquivo
    unsigned long long int file_size = ftell(file); // Obtém a posição atual, que é o tamanho do arquivo em bytes
    fseek(file, current_postition, SEEK_SET);       // Move o indicador de posição de volta para o início do arquivo

    return file_size;
}

void get_tree_and_trash_size(FILE *compressed_file, int *trashSize, int *treeSize)
{
    uint16_t first_byte = fgetc(compressed_file);
    uint16_t second_byte = fgetc(compressed_file);

    uint16_t trash_and_tree_size = 0;
    trash_and_tree_size |= first_byte;
    trash_and_tree_size <<= 8;

    trash_and_tree_size |= second_byte;

    *trashSize = trash_and_tree_size >> 13;

    trash_and_tree_size <<= 3;

    *treeSize = trash_and_tree_size >> 3;
}

NODE *get_tree(FILE *archive, int *treeSize)
{
    uint8_t byte;

    // Verifica se há dados restantes no cabeçalho
    if (*treeSize <= 0)
    {
        return NULL;
    }

    // Lê o próximo byte do cabeçalho
    fread(&byte, sizeof(uint8_t), 1, archive);
    NODE *huffTree = create_node();
    (*treeSize)--;

    // Verifica se o byte é um caractere especial (folha)
    if (byte == '\\')
    {
        // Se for um caractere especial, lê o próximo byte que representa o valor do nó folha
        fread(&byte, sizeof(uint8_t), 1, archive);
        (*treeSize)--;
        // Define o valor do nó folha
        *(uint8_t *)huffTree->data = byte;
    }
    else
    {
        // Se não for um caractere especial, define o valor do nó atual como o byte lido
        *(uint8_t *)huffTree->data = byte;
        // Se for um nó intermediário ('*'), continua recursivamente para criar os filhos
        if (byte == '*')
        {
            huffTree->left = get_tree(archive, treeSize);
            huffTree->right = get_tree(archive, treeSize);
        }
    }
    return huffTree;
}
bool is_seted(uint8_t byte, int i)
{
    uint8_t mask = 1; // coloca o bit 1 na posicao i
    mask <<= i;
    return byte & mask; // Se o bit nao estiver setado retorna 0
}

void unzip(FILE *compressed_file, FILE *fileOut, unsigned long long coded_size, NODE *treeRoot, int trashSize)
{
    unsigned long long int index;
    uint8_t cmpByte;
    NODE *aux = treeRoot;
    int j = 7;

    for (index = 0; index < coded_size; index++)
    {
        j = 7;
        cmpByte = fgetc(compressed_file);

        while (j >= 0)
        {
            if (is_seted(cmpByte, j))
                treeRoot = treeRoot->right;
            else
                treeRoot = treeRoot->left;

            if (is_leaf(treeRoot))
            {
                uint8_t byte = get_data(treeRoot);
                fprintf(fileOut, "%c", byte);
                treeRoot = aux;
            }
            if ((index == coded_size - 1) && (j == trashSize)) // j
            {
                break;
            }
            j--;
        }
    }
}

uint8_t getExtension(FILE *compressedFile, char *extension)
{
    uint8_t extensionSize = fgetc(compressedFile); // Pega o byte da extensão
    extensionSize >>= 5;                           // Pega o tamanho da extensão

    // printa o byte da extensão
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", is_seted(extensionSize, i));
    }

    // Loop para pegar cada caractere da extensão
    for (int i = 0; i < extensionSize; i++)
    {
        extension[i] = (char)fgetc(compressedFile);
    }

    for (int i = 0; i < extensionSize; i++)
    {
        printf("%c", extension[i]);
    }
    printf("\n");
    printf("Tamanho da extensão: %d\n", extensionSize);

    return extensionSize;
}
