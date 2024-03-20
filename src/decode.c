#include "std.h"
#include "list.h"
#include "tree.h"
#include "decode.h"
#include "encode.h"

unsigned long long int find_file_size(FILE* file){ 

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    unsigned long long int current_postition = ftell(file);

    fseek(file, 0, SEEK_END); // Move o indicador de posição para o final do arquivo
    unsigned long long int file_size = ftell(file);   // Obtém a posição atual, que é o tamanho do arquivo em bytes
    fseek(file, current_postition, SEEK_SET); // Move o indicador de posição de volta para o início do arquivo

    return file_size;
}

void get_tree_and_trash_size(FILE* compressed_file, int* trashSize, int* treeSize){
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

NODE *getTree(FILE *archive, int *treeSize){
    uint8_t byte;
    NODE *huffTree = NULL;

    //tratando caractere especial (sempre folha)
    if(*treeSize > 0){
        fread(&byte,sizeof(uint8_t),1,archive);
        if(byte == '\\'){
            (*treeSize)--;
            fread(&byte,sizeof(uint8_t),1,archive);
            huffTree = create_node();
            *(uint8_t*)huffTree->data = byte; 
            (*treeSize)--;
            return huffTree;
        }
        huffTree = create_node();
        *(uint8_t*)huffTree->data = byte; 
        (*treeSize)--;

        //se for um nó intermediario
        if(byte == '*'){
            //busca primeiro na esquerda até acha uma folha
            huffTree->left = getTree(archive,treeSize);
            huffTree->right = getTree(archive,treeSize);
        }
        return huffTree;      
    }
    return huffTree;
}

bool is_seted(uint8_t byte, int i){
    uint8_t mask = 1; // coloca o bit 1 na posicao i
    mask <<= i; 
    return byte & mask; // Se o bit nao estiver setado retorna 0
}

void unzip(FILE* compressed_file, FILE* fileOut, unsigned long long coded_size, NODE* treeRoot, int trashSize){ 
    unsigned long long int index; 
    uint8_t cmpByte; 
    NODE* aux = treeRoot;
    int j = 7;   

    for(index = 0; index < coded_size; index++) { 
        j = 7;
        cmpByte = fgetc(compressed_file);

        while(j >= 0){
            if(is_seted(cmpByte, j))
                treeRoot = treeRoot->right;           
            else
                treeRoot = treeRoot->left;          

            if(is_leaf(treeRoot)){
                uint8_t byte = get_data(treeRoot); 
                fprintf(fileOut, "%c", byte);
                treeRoot = aux; 
            }
            if ((index == coded_size - 1) && (j == trashSize))
                break; 
            j--; 
        }
    }
}