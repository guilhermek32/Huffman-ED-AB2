# <p align="center">Projeto Huffman | Estrutura de Dados</p>

<p align="center">
  <img src="https://github.com/guilhermek32/Huffman-ED-AB2/assets/128178415/20ce32fa-608b-451b-b8d6-c4ce4b70300f" alt="ufal"width="105" height="105"/>
 <img src="https://github.com/guilhermek32/Huffman-ED-AB2/assets/128178415/c9a3e548-c5c6-469e-9a00-7b2135deb9c1" alt="ic"/>
</p>

### <p align="center">Universidade Federal de Alagoas</p>
### <p align="center">Instituto da Computação</p>

###

<p align="center">Professor: <b>Márcio Ribeiro</b></p>


<p align="center"> Alunos: </p>
<p align="center"><b>Antonio Guilherme da Silva | Felipe Lira Da Silva | Kauã Lessa</b></p>
<p align="center"> <b>AB2 2023.2</b></p>

#


## Algoritmo de compactação e descompactação
A codificação de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo.

- Compilar e executar huffman
  
Clone esse projeto em seu computador com o comando:

`git clone https://github.com/guilhermek32/Huffman-ED-AB2/`

Acesse a pasta do projeto seu terminal.


Já na pasta da aplicação em seu terminal, digite o seguinte comando:

`gcc -Wall -Iinc src/main.c src/list.c src/tree.c src/encode.c src/decode.c -o app/Kzip.exe`

- Execução do programa:

Ao inicializar o programa, você terá direito de escolha de 2 opções:

-Compactar um arquivo

-Descompactar o arquivo

##  Contagem e plotagem
### Lista x Árvore Busca Binária

Contagem realizada em C e plotagem em python utilizando a biblioteca Matplotlib.
##

**Dependências:**

-Matplotlib

-numpy

-Tkinter

Execute o comando:

`pip install numpy && pip install python3.8-TK && pip install matplotlib`


**Compilação e execução:**

mude o diretório para plotagem 

`cd plotagem`

Execute o comando:

`gcc plotagem.c list.c bTree.c -o plot && ./plot`

#

## Seminário: Árvore Trie

Arquivo .pptx no git

#

## Testes CUnit

comando: 

`gcc -Wall -Iinc src/list.c src/tree.c src/encode.c src/decode.c CUnit/test.c -o CUnit/run -lcunit`
#
