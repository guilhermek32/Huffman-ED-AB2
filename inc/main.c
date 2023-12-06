#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    int i;

    printf("Codificação de Huffman\n\n");
    printf("Selecione qual operação deseja realizar:\n");
    printf("1 - Codificar\n");
    printf("2 - Decodificar\n");
    printf("3 - Sair\n");

    scanf("%d", &i);

    switch (i)
    {
    case 1:
        printf("Codificar\n");
        break;
    case 2:
        printf("Decodificar\n");
        break;
    case 3:
        printf("Sair\n");
        break;
    }

    return 0;
}