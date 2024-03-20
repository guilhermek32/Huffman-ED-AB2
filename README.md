# Huffman-ED-AB2
Universidade Federal de Alagoas
Instituto da Computação

Orientador: Márcio Ribeiro

Alunos: Antonio Guilherme da Silva, Felipe Lira Da Silva, Kauã Lessa

Comandos de execução:



gcc -Wall -Iinc src/main.c src/list.c src/tree.c src/encode.c src/decode.c -o app/zip.exe

gcc -Wall -Iinc src/list.c src/tree.c src/encode.c src/decode.c tests/test.c -o tests/run -lcunit

gcc plotagem.c list.c bTree.c -o plot && ./plot
