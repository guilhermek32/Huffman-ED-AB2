#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bTree.c"
#include "list.c"

int genRand(int lower, int upper) {

    int num = rand() % (upper - lower + 1); /* Gera um número aleatório no intervalo [lower, upper] */
    return num;
}

int main() {

    srand(time(NULL));
    system("clear");
    printf("Contagem e Plotagem: Lista x Árvore de Busca Binária\n");
    printf("Inciando...\n");
    FILE* output = fopen("out.txt", "w");

    int lower = 1;
    int upper = 100000;
    printf("Gerando numeros e fazendo a Contagem...\n");
    for (int n = 0; n <= 100000; n += 100)
    {
        NodeList* head = initList();
        bTree* root = initBT();
        for (int i = 0; i < n; i++)
        {
            int num = genRand(lower, upper);

            insertList(&head, num);

            root = addBT(root, num);
        }
        
        int target = genRand(lower, upper);

        int ListActCount = 0;
        int TreeActCount = 0;

        searchList(head, target, &ListActCount);
        searchBT(root, target, &TreeActCount);

        fprintf(output, "%d %d %d\n", n, ListActCount,TreeActCount);
    }

    fclose(output);
    printf("Finalizado!\n");
    
    return 0;
}
