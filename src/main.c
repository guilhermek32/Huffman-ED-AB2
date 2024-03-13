#include "std.h"
#include "list.h"
#include "tree.h"
#include "decode.h"
#include "encode.h"

int main(){
    int option; 

    puts("DIGITE A OPCAO: ");
    puts("COMPACTAR[1]"); 
    puts("DESCOMPACTAR[2]");

    scanf("%d", &option);

    if(option == 1){

        HEAD Mystruct;
        init_struct(&Mystruct);
        unsigned int* frequency_table = init_frequency_table(); 
        char file_name[50];
        unsigned short int trash_size, tree_size = 0;    

        printf("Informe o nome do arquivo a ser compactado\n");
        scanf("%s", file_name);

        char inPath[TAM]; // Caminho do input
        strcpy(inPath, INPUT_DIR); // Copia o diretorio padrao de inputs para inPath
        strcat(inPath, file_name); // Adciona o nome do arquivo

        // Parte 1: Mapeia a frequência de cada caractere
        printf("\nPARTE 1\n"); 
        count_frequency(frequency_table, inPath);
        
        // Parte 2: Cria a lista encadeada ordenada
        printf("\nPARTE 2\n");
        insert_in_linked_list(&Mystruct, frequency_table); 

        // Parte 3: Cria a ávore de Huffman e sua string
        printf("\nPARTE 3\n");
        huffmanTree(&Mystruct, &Mystruct.size);
        puts("Saiu tree"); 

        // Parte 4: Cria um dicionário que mapeia cada caractere
        BitHuff code;
        BitHuff *table = malloc(sizeof(BitHuff) * 256);  
        code.bitH = 0;
        code.size = 0; 
        memset(table,0,sizeof(BitHuff) * 256); //
        printf("\nPARTE 4\n");
        buildTable(Mystruct.head, table, code); //

        // Parte 5: Compactar
        printf("\nPARTE 5\n");
        puts("Comprimindo arquivo");
        trash_size = getTrashSize(frequency_table, table); 
        getTreeSize(Mystruct.head, &tree_size); 
        unsigned short int tree_and_trash_size = setFirstTwoBytes(trash_size, tree_size);

        char *remove = strrchr(file_name,'.'); // remove o '.'
        if(remove != NULL) *remove = '\0'; // Adciona a char terminal onde era o '.'
        char out_path[TAM];
        sprintf(out_path, "%s%s%s",ZIPED_OUT_DIR, file_name, ".huff"); // Caminho completo
        FILE* compressed_file = fopen(out_path, "wb");
        file_error_reporter(compressed_file);

        
        FILE* fileIn = fopen(inPath, "rb"); 
        file_error_reporter(fileIn); 

        write_header(compressed_file, tree_and_trash_size, Mystruct.head);
        
        setBytes(fileIn, compressed_file, table);   

        puts("FIM"); 
 
    }
    else if(option == 2){
        char file_name[50];
        char file_format[10];
        char out_file_path[TAM];

        puts("Digite o nome do arquivo: "); 
        scanf("%s", file_name);

        puts("Digite o formato do arquivo: ");
        scanf("%s", file_format);
        //strcat(out_file_name, file_format);  

        char inPath[TAM];
        // Adciona o diretorio do nosso arquivo de entrada que esta no diretorio padrao de arquivos comprimidos
        sprintf(inPath, "%s%s", ZIPED_OUT_DIR, file_name);
        FILE* compressed_file = fopen(inPath, "rb");
        file_error_reporter(compressed_file);

        int trashSize, treeSize;
        get_tree_and_trash_size(compressed_file, &trashSize, &treeSize);

        printf("Tamanho da arvore: %d\n", treeSize);
        printf("Tamanho do lixo: %d\n", trashSize); 

        unsigned long long int codedSize = find_file_size(compressed_file) - 2 - treeSize;

        NODE* treeRoot = getTree(compressed_file, &treeSize);

        char *remove = strrchr(file_name,'.');
        if(remove != NULL) *remove = '\0';
        sprintf(out_file_path, "%s%s%s", UNZIPED_OUT_DIR, file_name, file_format);
        FILE* fileOut = fopen(out_file_path, "wb");
        file_error_reporter(fileOut);

        unzip(compressed_file, fileOut, codedSize, treeRoot, trashSize);

        fclose(compressed_file);
        fclose(fileOut); 
    }
    else {
        puts("OPCACO INVALIDA");
        puts("TERMINANDO PROGRAMA");
        return 0; 
    }
    
    return 0; 
}