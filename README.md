# HuffmanCompactor

## Introdução

O algoritmo foi desenvolvido durante o meu trabalho final da matéria "Estrutura de Dados" na UFMG. O problema proposto foi implementar um programa que recebe como argumento dois arquivos de texto e uma flag “-c” ou “-d”. O programa então deve ser capaz de ler a armazenar o texto presente no primeiro arquivo, e baseado na flag de comando, no caso “-c”, ele deve ser capaz de armazená-lo de forma compactada no segundo arquivo, ocupando menos espaço que o anterior, e no caso “-d”, deve ser capaz de descompactar o conteúdo do primeiro arquivo e reescrevê-lo em sua forma original no segundo. Para isso, o programa utiliza o método da Árvore de Huffman. Durante o desenvolvimento, não era permitido o uso de bibliotecas prontas para as estruturas de dados, sendo assim necessárias as implementações das mesmas.

## Instruções para compilação e execução

O programa requer os arquivos de entrada na pasta bin.

Basta escrever no terminal “make all” que o programa será compilado, serão gerados os arquivos .o na pasta “obj”, um executável na pasta “bin” e o gmon.out no diretório raiz. Caso deseje testar entradas diferentes das que já estão lá, é necessário adicionar arquivos de entrada e de saída na pasta bin e adicionar o comando de execução no Makefile no modelo:

    $(EXE) $(BIN)/arquivodeentrada.txt $(BIN)/arquivodesaida.txt <flag>

Sendo que:

1- $(EXE) é o executável

2- $(BIN) é o endereço da pasta bin

3- “arquivo.txt” é o nome do arquivo de texto fornecido

4- <flag> é o comando, que pode ser a opção de compactação (“-c”) ou descompactação (“-d”)

Para limpeza dos arquivos objetos e do .run, basta escrever “make clean” no terminal.

## Saiba mais

Para mais informações detalhadas sobre o programa basta abrir a documentação presente no diretório raiz.
