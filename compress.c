#include "std.h"
#include "list.h"
#include "tree.h"
#include "decompress.h"
#include "compress.h"

unsigned int *init_frequency_table()
{
    unsigned int *frequency_table = calloc(TAM, sizeof(unsigned int));
    malloc_error_reporter(frequency_table);

    return frequency_table;
}

void count_frequency(unsigned int *frequency_table, char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    file_error_reporter(file);
    uint8_t byte;

    while (fread(&byte, sizeof(uint8_t), 1, file) == 1)
    { // Mudar vericacao?
        frequency_table[byte]++;
    }

    fclose(file);
}

void set_bit(int j, uint8_t *byte)
{
    uint8_t mask = 1; // 00000001
    mask = mask << j;
    // 10000000
    // 00000000
    // 10000000
    *byte = *byte | mask;
}

void write_header(FILE *cmp_file, unsigned short int tree_and_trash_size, NODE *root, char *extension)
{
    unsigned char first_byte = tree_and_trash_size >> 8;
    tree_and_trash_size <<= 8;
    tree_and_trash_size >>= 8;
    unsigned char second_byte = tree_and_trash_size;

    fwrite(&first_byte, sizeof(unsigned char), 1, cmp_file);
    fwrite(&second_byte, sizeof(unsigned char), 1, cmp_file);

    writeTree(root, cmp_file);

    uint8_t extensionSize = 0;
    extensionSize |= strlen(extension);
    extensionSize <<= 5;
    fwrite(&extensionSize, sizeof(uint8_t), 1, cmp_file);

    // Escreve a extensão do arquivo
    while (*extension)
    {
        fprintf(cmp_file, "%c", (unsigned char)(*extension));
        extension++;
    }
}

// Escreve a árvore de Huffman em pré - ordem tratando nós especiais 
void writeTree(NODE *root, FILE *cmp_file)
{

    if (!root)
    {
        return;
    }
    if (((get_data(root) == '*') || (get_data(root) == '\\')) && is_leaf(root))
    {
        fprintf(cmp_file, "%c", (unsigned char)'\\'); // escreve o escape
    }
    fprintf(cmp_file, "%c", get_data(root)); // escreve o byte do no

    writeTree(root->left, cmp_file);  // Percorre os filhos esquerdos
    writeTree(root->right, cmp_file); // Percorre os filhos direitos
}

unsigned short int setFirstTwoBytes(unsigned short int trash_size, unsigned short int tree_size)
{
    unsigned short int tree_and_trash_size = 0;
    trash_size <<= 13;
    tree_and_trash_size = tree_size | trash_size;
    return tree_and_trash_size;
}

void build_table(NODE *treeRoot, unsigned long long int **table, unsigned long long code, unsigned long long codeSize, int index)
{
    if (is_leaf(treeRoot))
    {
        code >>= (64 - codeSize);
        table[get_data(treeRoot)][0] = code;
        table[get_data(treeRoot)][1] = codeSize;

        return;
    }

    codeSize++;
    if (treeRoot->left)
    {
        build_table(treeRoot->left, table, code, codeSize, index - 1);
    }
    if (treeRoot->right)
    {
        code = setLong(code, index);
        build_table(treeRoot->right, table, code, codeSize, index - 1);
    }
}

unsigned short int get_trash_size(unsigned int frequency[], unsigned long long int **table)
{

    unsigned long long int codedSize = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            codedSize += frequency[i] * table[i][1];
        }
    }

    if (codedSize % 8 == 0)
        return 0;
    else
        return 8 - (codedSize % 8);
}

void getTreeSize(NODE *tree_root, unsigned short int *treeSize)
{
    if (tree_root != NULL)
    {
        if ((is_leaf(tree_root)) && (get_data(tree_root) == '*' || get_data(tree_root) == '\\'))
            (*treeSize) += 2;
        else
            (*treeSize)++;

        getTreeSize(tree_root->left, treeSize);
        getTreeSize(tree_root->right, treeSize);
    }
}

unsigned long long int setLong(unsigned long long int bitCode, int index)
{
    unsigned long long int mask = 1;
    mask <<= index;
    return bitCode |= mask;
}

bool isSetedLong(unsigned long long int code, int i)
{
    unsigned long long int mask = 1;
    mask <<= i;
    // 1000101 tam = 7
    // mask = 000000000000000001
    // 1000101
    // 1000000
    return code & mask;
}

void set_bytes(FILE *fileIn, FILE *fileOut, unsigned long long **table)
{
    unsigned char buffer = 0; // Buffer que sera escrito no arquivo quando cheio
    unsigned char original_byte;
    int buffer_index = 7;

    while (fread(&original_byte, sizeof(unsigned char), 1, fileIn) == 1)
    {
        unsigned long long int huffCode = table[original_byte][0];

        for (int i = table[original_byte][1]; i > 0; i--)
        {
            if (isSetedLong(huffCode, i - 1))
            {
                set_bit(buffer_index, &buffer);
            }
            buffer_index--;
            if (buffer_index < 0)
            {
                fprintf(fileOut, "%c", buffer);
                buffer = 0;
                buffer_index = 7;
            }
        }
    }
    if (buffer_index != 7)
    {
        fprintf(fileOut, "%c", buffer);
    }

    fclose(fileIn);
    fclose(fileOut);
}