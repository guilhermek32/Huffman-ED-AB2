#include "std.h"
#include "list.h"
#include "tree.h"
#include "decompress.h"
#include "compress.h"

void print_binary(unsigned long long n, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        unsigned long long bit = (n >> i) & 1;
        printf("%llu", bit);
    }
}

int main()
{
    int option;

    puts("DIGITE A OPCAO: ");
    puts("COMPACTAR[1]");
    puts("DESCOMPACTAR[2]");
    puts("FINALIZAR[3]");

    scanf("%d", &option);

    if (option == 1)
    {
        HEAD Mystruct;
        init_struct(&Mystruct);
        unsigned int *frequency_table = init_frequency_table();
        char file_name[50];
        unsigned short int trash_size, tree_size = 0;

        printf("Informe o nome do arquivo a ser compactado\n");
        scanf("%s", file_name);

        if (strrchr(file_name, '.') == NULL)
        {
            printf("Finalizando programa!\n");
            perror("Erro ao ler o arquivo! Talvez o arquivo não tenha extensão!");
            return 0;
        }

        // Pega a extensão do arquivo
        char *temp = strrchr(file_name, '.');
        char extension[10] = {'\0'};
        // Copia a extensão do arquivo para a variável extension
        sprintf(extension, "%s", (temp + 1));
        printf("Extensao do arquivo: %s\n", extension);
        printf("Tamanho da extensao: %ld\n", strlen(extension));

        if (strlen(extension) > 6)
        {
            puts("Extensão não suportada!");
            puts("Terminando programa!");
            return 1;
        }

        char inPath[TAM];          // Caminho do input
        strcpy(inPath, INPUT_DIR); // Copia o diretorio padrao de inputs para inPath
        strcat(inPath, file_name); // Adciona o nome do arquivo

        // Parte 1: Mapeia a frequência de cada caractere
        printf("\nPARTE 1\n");
        count_frequency(frequency_table, inPath);

        // Parte 2: Cria a lista encadeada ordenada
        printf("\nPARTE 2\n");
        insert_in_linked_list(&Mystruct, frequency_table);

        print_linked_list(&Mystruct);

        // Parte 3: Cria a ávore de Huffman
        printf("\nPARTE 3\n");

        createHuffmanTree(&Mystruct);
        puts("Saiu tree");

        // Parte 4
        puts("PARTE 4");

        //  inicializando tabela
        unsigned long long int **table = malloc(sizeof(unsigned long long int *) * 256);
        // Inicializa a tabela com 0 e 0 para cada byte e tamanho da codificação do byte
        for (int i = 0; i < 256; i++)
        {
            // Aloca 2 espaços para cada byte da tabela (cada byte tem um código e um tamanho)
            table[i] = calloc(2, sizeof(unsigned long long int));
        }
        // Cria a tabela de codificação de Huffman para cada byte da árvore de Huff e armazena na tabela table
        build_table(Mystruct.head, table, 0L, 0L, 63);

        // Printar tabela criada
        for (int i = 0; i < TAM; i++)
        {
            if (frequency_table[i] > 0)
            {
                printf("Byte[%c]: code: ", i);
                print_binary(table[i][0], table[i][1]);
                printf(", size: %llu\n", table[i][1]);
            }
        }

        // Parte 5: Compactar
        printf("\nPARTE 5\n");
        puts("Comprimindo arquivo");
        trash_size = get_trash_size(frequency_table, table);
        printf("Tamanho do lixo: %d\n", trash_size);
        getTreeSize(Mystruct.head, &tree_size);
        printf("Tamanho da árvore: %d\n", tree_size);
        unsigned short int tree_and_trash_size = setFirstTwoBytes(trash_size, tree_size);

        char *remove = strrchr(file_name, '.'); // remove o '.'
        if (remove != NULL)
        {
            *remove = '\0';
        }
        char out_path[TAM];
        sprintf(out_path, "%s%s%s", ZIPED_OUT_DIR, file_name, ".huff");
        FILE *compressed_file = fopen(out_path, "wb");
        file_error_reporter(compressed_file);

        FILE *fileIn = fopen(inPath, "rb");
        file_error_reporter(fileIn);

        write_header(compressed_file, tree_and_trash_size, Mystruct.head, extension);

        // setBytes(fileIn, compressed_file, table);
        set_bytes(fileIn, compressed_file, table);

        puts("FIM");
    }
    else if (option == 2)
    {
        char file_name[50];
        // char file_format[10];
        char out_file_path[TAM];

        puts("Digite o nome do arquivo: ");
        scanf("%s", file_name);

        char inPath[TAM];
        sprintf(inPath, "%s%s", ZIPED_OUT_DIR, file_name);
        FILE *compressed_file = fopen(inPath, "rb");
        file_error_reporter(compressed_file);

        int trashSize, treeSize;
        get_tree_and_trash_size(compressed_file, &trashSize, &treeSize);

        printf("Tamanho da arvore: %d\n", treeSize);
        printf("Tamanho do lixo: %d\n", trashSize);

        int temp = treeSize;
        NODE *treeRoot = get_tree(compressed_file, &temp);

        char *remove = strrchr(file_name, '.');
        if (remove != NULL)
            *(remove + 1) = '\0';
        char extension[10] = {'\0'};
        int ExtensionSize = getExtension(compressed_file, extension);
        unsigned long long int codedSize = find_file_size(compressed_file) - 2 - treeSize - 1 - ExtensionSize;

        sprintf(out_file_path, "%s%s%s", UNZIPED_OUT_DIR, file_name, extension);
        FILE *fileOut = fopen(out_file_path, "wb");
        file_error_reporter(fileOut);

        unzip(compressed_file, fileOut, codedSize, treeRoot, trashSize);

        fclose(compressed_file);
        fclose(fileOut);
    }
    else
    {
        puts("OPCACO INVALIDA");
        puts("TERMINANDO PROGRAMA");
        return 0;
    }

    return 0;
}