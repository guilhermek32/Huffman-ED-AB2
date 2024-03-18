#include "std.h"
#include "list.h"
#include "tree.h"
#include "decode.h"
#include "encode.h"

unsigned int* init_frequency_table(){

  unsigned int* frequency_table = calloc(TAM, sizeof(unsigned int));
  malloc_error_reporter(frequency_table); 
  
  return frequency_table; 

}

void count_frequency(unsigned int* frequency_table, char* file_name){
    FILE* file = fopen(file_name, "rb");
    file_error_reporter(file); 
    uint8_t byte;

    while(fread(&byte, sizeof(uint8_t), 1, file) == 1){ // Mudar vericacao?
        frequency_table[byte]++; 
    } 

    fclose(file); 
}

void set_bit(int j, uint8_t* byte){
    uint8_t mask = 1; // 00000001
    mask = mask << j;
    // 10000000
    // 00000000
    // 10000000
    *byte = *byte | mask; 
}

void write_header(FILE* cmp_file, unsigned short int tree_and_trash_size, NODE* root){


    // 10100000 00100100
    // 00000000 10100000 first_byte
    // 00100100 00000000 <<= 8
    // >>= 8
    // 00000000 00100100 second_byte


    unsigned char first_byte = tree_and_trash_size >> 8;
    tree_and_trash_size <<= 8; 
    tree_and_trash_size >>= 8;
    unsigned char second_byte = tree_and_trash_size;  
   
    fwrite(&first_byte, sizeof(unsigned char), 1, cmp_file); 
    fwrite(&second_byte, sizeof(unsigned char), 1, cmp_file); 
    write_tree(root, cmp_file); 
}

void write_tree(NODE* root, FILE* cmp_file){

    if (root != NULL) {
        uint8_t data = get_data(root); // Pega o byte do no
        if(((data == '*') || (data == '\\')) && is_leaf(root)){
            uint8_t temp = '\\';
            fwrite(&temp, sizeof(uint8_t), 1, cmp_file); // Escreve scape 
        }

        fwrite(&data, sizeof(uint8_t), 1, cmp_file); // Escreve o byte no arquivo
        write_tree(root->left, cmp_file); // Percorre os filhos esquerdos
        write_tree(root->right, cmp_file); // Percorre os filhos direitos
    }  
}


unsigned short int setFirstTwoBytes(unsigned short int trash_size, unsigned short int tree_size){ 
    unsigned short int tree_and_trash_size = 0;
    trash_size <<= 13;
    tree_and_trash_size = tree_size | trash_size; 
    return tree_and_trash_size; 
}

void buildTable(NODE* tree_node,BitHuff table[],BitHuff code){         
    if(is_leaf(tree_node))
    {
        table[get_data(tree_node)] = code;
        return;
    }
    else
    {
        code.size++;
        code.bitH <<= 1;
        if(tree_node->left != NULL)
        buildTable(tree_node->left, table, code);
        code.bitH++;
        if(tree_node->right != NULL)
        buildTable(tree_node->right, table, code);
    }   
}


unsigned short int getTrashSize(unsigned int frequency[], BitHuff table[]){
    
    unsigned long long int totalBits = 0;
    for(int i = 0;i < 256;i++){
        if(frequency[i] > 0) {
            totalBits += frequency[i] * table[i].size;
        }
    }
    unsigned short int trash = (8 - (totalBits % 8)); 
    return trash;
}

void getTreeSize(NODE* tree_root, unsigned short int* treeSize){ 
   if(tree_root != NULL) {
        if((is_leaf(tree_root)) && (get_data(tree_root) == '*' || get_data(tree_root) == '\\'))
            (*treeSize) += 2; 
        else
            (*treeSize)++; 

        getTreeSize(tree_root->left, treeSize); 
        getTreeSize(tree_root->right, treeSize);
   }
}
bool isSetedLong(unsigned long long int code, int i) {
    unsigned long long int mask = 1; 
    mask <<= i;
    // 1000101 tam = 7
    // mask = 000000000000000001
    // 1000101
    // 1000000
    return code & mask; 
}

void setBytes(FILE *fileIn,FILE *fileOut,BitHuff table[]){
    unsigned char buffer = 0; // Buffer que sera escrito no arquivo quando cheio
    unsigned char original_byte;
    int buffer_index = 7;  

    while(fread(&original_byte, sizeof(unsigned char), 1, fileIn) == 1) { 
        unsigned long long int huffCode = table[original_byte].bitH;
        // 01011001
        // char exemplo[255]
        // 0 254

        for(int i = table[original_byte].size; i > 0; i--){
            if(isSetedLong(huffCode, i - 1)){
                set_bit(buffer_index, &buffer);
            }
            buffer_index--; 
            if(buffer_index < 0){
                fprintf(fileOut, "%c", buffer);
                buffer = 0; 
                buffer_index = 7;  
            }
        }
    }
    if(buffer_index != 7){
        fprintf(fileOut, "%c", buffer);
    }

    fclose(fileIn); 
    fclose(fileOut);
}


