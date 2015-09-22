Nomes:
Laís Pessine do Carmo	nº usp: 7546760
Rafael Seiji Ishibe		nº usp: 7173570

/*--------------------------------- Utilização --------------------------------*/
	
	Para compilação em Linux, basta executar: 

	$ make

	Após compilação do arquivo MakeFile utilizando o comando make na linha de comando, a linha para a execução do código deve ter o seguinte formato:

	$ ./huff arquivo_entrada arquivo_saida alg

Onde

- caminho_entrada: caminho do arquivo de entrada com sua extensão (.bmp ou .huff),

- caminho_saida: caminho do arquivo de saida com sua extensão (.bmp ou .huff),

- alg: algoritmo que se deseja utilizar, podendo ser:
	-dif (ou -DIF): algoritmo de diferenças
	-dct (ou -DCT): algoritmo DCT
	-dif+dct (ou -DIF+DCT): algoritmo de diferenças + algoritmo DCT	
	-dct+dif (ou -DCT+DIF): algoritmo DCT + algoritmo de diferenças

- Compressão: arquivo_entrada .bmp e arquivo_saida .huff.
ex) $ ./huff testes/01_lena.bmp testes/01_lena.huff -dif

- Descompressão: arquivo_entrada .huff e arquivo_saida .bmp.
ex) $ ./huff testes/01_lena.huff testes/01_lena_out.bmp -dif

	Caso a entrada esteja em um formato diferente do descrito acima, o programa informará um erro indicando a falha encontrada.
	Caso a entrada esteja correta, o programa informará detalhes do tipo de procedimento escolhido e o realizará em seguida.
