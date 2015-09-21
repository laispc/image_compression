
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "HuffmanCoding.h"
#include "DiferenceCoding.h"
#include "Codefy.h"


#define     DIF         1
#define     DCT         2
#define     DIF_DCT     3
#define     DCT_DIF     4

#define     COMPRESS	1
#define     DECOMPRESS	2

/* Funçõe de teste. Imprime um vetor. */
void printv(unsigned char* vector,unsigned int num){
	int i = 0;
	for (i = 0; i < num; ++i)
	{
		printf("%d ", vector[i]);
	}
}

/* Funçõe de teste. Imprime uma lista. */
void printd(Dlist_* vector,unsigned int num){
    int i;
    for (i = 0; i < num; ++i)
    {
        printf("%d " ,vector[i].value);
    }
}

/* Funçõe de teste. Imprime uma tabela. */
void printTable(HuffmanTable *table, int tableLen){
    int i = 0;
    printf("Huffman Table\n");
    for (i = 0; i < tableLen; ++i)
    {
        printf("[%d] - nBits: %d - huffCode: %d - huffLen: %d\n", i, table[i].nBits,
            table[i].huffCode, table[i].huffLen);
    }
}

/* Funçõe de teste. Compara imagens, imprimindo suas diferenças. */
int compare_image(Dlist_ *a,Dlist_ *b, int size){
    int i = 0 ;
    while(i < size){

        if(a[i].value != b[i].value){

            printf("a = %d, b = %d\n",a[i].value,b[i].value);
            printf("i = %d\n",i);
        }

        i++;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
	/* Tratamento dos argumentos de entrada*/
	
	/* Verifica numero de argumentos */
	if (argc != 4)
	{
		printf("ERRO: Numero de argumentos invalido.\n");
		return -1;
	}

	/* Verifica existencia do arquivo de entrada*/
	char *inputFile = argv[1];

	if( access(inputFile, F_OK) == -1 )
	{
		printf("ERRO: Arquivo de entrada nao encontrado.\n");
	}

	/* Verifica extensoes do arquivos de entrada e saida para escolher entre compressao e descompressao */
	char *inputExtension;
	inputExtension = strrchr(inputFile,'.');
	printf("Arquivo de entrada: %s\n", inputFile);

	char *outFile = argv[2];
	printf("Arquivo de saida: %s\n", outFile);
	char *outExtension;
	outExtension = strrchr(outFile,'.');

	int requestedAction;
	if (inputExtension == NULL || outExtension == NULL)
	{
		printf("ERRO: Extensao de arquivo nao esfecificada. \n");
	}
	else if (strcmp(inputExtension,".bmp") == 0 && strcmp(outExtension,".huff") == 0)
	{
		requestedAction = COMPRESS;
	}
	else if (strcmp(inputExtension,".huff") == 0 && strcmp(outExtension,".bmp") == 0)
	{
		requestedAction = DECOMPRESS;
	}
	else
	{
		printf("ERRO: Extensao de um ou mais arquivos invalida.\n");
		return -1;
	}

	/* Verifica o tipo de algoritmo escolhido */

	char *algType = argv[3];
	int requetedAlg;
	if (strcmp(algType,"-DIF") == 0 || strcmp(algType,"-dif") == 0)
	{
		requetedAlg = DIF;
		printf("Algoritmo selecionado: Diferencas\n");
	}
	else if (strcmp(algType,"-DCT") == 0 || strcmp(algType,"-dct") == 0)
	{
		requetedAlg = DCT;
		printf("Algoritmo selecionado: DCT\n");
	}
	else if (strcmp(algType,"-DIF+DCT") == 0 || strcmp(algType,"-dif+dct") == 0)
	{
		requetedAlg = DIF_DCT;
		printf("Algoritmo selecionado: Diferencas + DCT\n");
	}
	else if (strcmp(algType,"-DCT+DIF") == 0 || strcmp(algType,"-dct+dif") == 0)
	{
		requetedAlg = DCT_DIF;
		printf("Algoritmo selecionado: DCT + Diferencas\n");
	}
	else
	{
		printf("ERRO: Algoritmo invalido.\n");
		return -1;
	}

	/* Declaracao de estruturas necessarias */

    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char* image = NULL;
    unsigned char* toWrite_g = NULL;
    unsigned char* toWrite_b = NULL;
    unsigned char* toWrite_r = NULL;
    int toWriteLen_g = 0, toWriteLen_b = 0, toWriteLen_r = 0;
    Dlist_ *image_g = NULL;
    Dlist_ *image_b = NULL;
    Dlist_ *image_r = NULL;

    Dlist_ *Dlist = (Dlist_*) malloc((bitmapInfoHeader.biSizeImage/3)*sizeof(Dlist_));
    int numCells_g = 0, numCells_b = 0, numCells_r = 0;
    HuffmanCell *list_g = NULL;
    HuffmanCell *list_b = NULL;
    HuffmanCell *list_r = NULL;
    HuffmanNode *head_g = NULL;
    HuffmanNode *head_b = NULL;
    HuffmanNode *head_r = NULL;
    HuffmanTable *table_g = NULL;
    HuffmanTable *table_b = NULL;
    HuffmanTable *table_r = NULL;
    int tableLen_g = 0, tableLen_b = 0, tableLen_r = 0;

/* Escolha entre compressao e descompressao */
switch (requestedAction){
case COMPRESS:
	printf("Compressão iniciada\n");
	/* Leitura da imagem */
	image = LoadBitmapFile(argv[1],&bitmapFileHeader , &bitmapInfoHeader);

	if (image == NULL) 
		return 1;

	/* Separacao dos canais */
	image_g = divRGB( image,bitmapInfoHeader.biSizeImage, 'g');
	image_b = divRGB( image,bitmapInfoHeader.biSizeImage, 'b');
	image_r = divRGB( image,bitmapInfoHeader.biSizeImage, 'r');

	printf("\n");

	/* Escolha do algoritmo de codificacao*/
	switch(requetedAlg){
		case DIF:
			diferenceCoding(image_g, bitmapInfoHeader.biSizeImage);	
			diferenceCoding(image_b, bitmapInfoHeader.biSizeImage);
			diferenceCoding(image_r, bitmapInfoHeader.biSizeImage);
		break;
		case DCT:
		/*
		DCT_Mapping_Codify(x,64,8,8);
		DCT_Mapping_Decodify(x,64,8,8);*/

			DCT_Mapping_Codify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
		break;	
		case DIF_DCT:
			diferenceCoding(image_g, bitmapInfoHeader.biSizeImage);	
			diferenceCoding(image_b, bitmapInfoHeader.biSizeImage);
			diferenceCoding(image_r, bitmapInfoHeader.biSizeImage);
			DCT_Mapping_Codify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
		break;
		case DCT_DIF:
			DCT_Mapping_Codify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Codify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			diferenceCoding(image_g, bitmapInfoHeader.biSizeImage);	
			diferenceCoding(image_b, bitmapInfoHeader.biSizeImage);
			diferenceCoding(image_r, bitmapInfoHeader.biSizeImage);
		break;
	}

	/*printv(image,bitmapInfoHeader.biSizeImage);*/
	/*printd(image_r, bitmapInfoHeader.biSizeImage/3);*/
	/*printf("Huffman\n");*/

	/* Algoritmo de Huffman */
	list_g = generateCellList(image_g, bitmapInfoHeader.biSizeImage/3, &numCells_g);
	list_b = generateCellList(image_b, bitmapInfoHeader.biSizeImage/3, &numCells_b);
	list_r = generateCellList(image_r, bitmapInfoHeader.biSizeImage/3, &numCells_r);

	qsort(list_g, numCells_g, sizeof(HuffmanCell), compareHuffmanDecrescent);
	qsort(list_b, numCells_b, sizeof(HuffmanCell), compareHuffmanDecrescent);
	qsort(list_r, numCells_r, sizeof(HuffmanCell), compareHuffmanDecrescent);


	/*printHuffmanList(list, numCells);*/
	head_g = generateTree(head_g, list_g, numCells_g);
	head_b = generateTree(head_b, list_b, numCells_b);
	head_r = generateTree(head_r, list_r, numCells_r);
	printf("End Huffman\n");
	/*if (head == NULL)
	{
	return 1;
	}*/

	/*printf("Before lenght: %d\n", bitmapInfoHeader.biSizeImage/3);*/


	toWrite_g = getByteVector(image_g ,bitmapInfoHeader.biSizeImage/3, &toWriteLen_g, head_g, &table_g, &tableLen_g);

	toWrite_b = getByteVector(image_b ,bitmapInfoHeader.biSizeImage/3, &toWriteLen_b, head_b, &table_b, &tableLen_b);

	toWrite_r = getByteVector(image_r ,bitmapInfoHeader.biSizeImage/3, &toWriteLen_r, head_r, &table_r, &tableLen_r);

	printf("Saving...\n");

	writeOn(toWrite_r, toWrite_g, toWrite_b, toWriteLen_r, toWriteLen_g, toWriteLen_b,
	bitmapInfoHeader, bitmapFileHeader, argv[2], table_g, table_b, table_r, tableLen_g, tableLen_b, tableLen_r);

	printf("End\n");
break;
case DECOMPRESS:
	printf("Descompressão iniciada\n");
	readOff(&toWrite_r, &toWrite_g, &toWrite_b, &toWriteLen_r, &toWriteLen_g, &toWriteLen_b,
		&bitmapInfoHeader, &bitmapFileHeader, argv[1], &table_g, &table_b, &table_r, &tableLen_g, &tableLen_b, &tableLen_r);

	unsigned char *total = (unsigned char*)malloc((toWriteLen_g+toWriteLen_b+toWriteLen_r)*sizeof(unsigned char));

	(image_r) = (Dlist_*)malloc((bitmapInfoHeader.biSizeImage/3)*sizeof(Dlist_));
	(image_g) = (Dlist_*)malloc((bitmapInfoHeader.biSizeImage/3)*sizeof(Dlist_));
	(image_b) = (Dlist_*)malloc((bitmapInfoHeader.biSizeImage/3)*sizeof(Dlist_));

	readHuffmanTable( image_r, table_r, tableLen_r, toWrite_r, toWriteLen_r);
	readHuffmanTable( image_g, table_g, tableLen_g, toWrite_g, toWriteLen_g);
	readHuffmanTable( image_b, table_b, tableLen_b, toWrite_b, toWriteLen_b);

	switch(requetedAlg){
		case DIF:
			printf("Decoder Differencial\n");
			DCoding( image_r,image_g, image_b,bitmapInfoHeader.biSizeImage);
			printf("End Decoder DCT\n");	
		break;
		case DCT:
			printf("Decoder DCT\n");
			DCT_Mapping_Decodify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);


		break;	
		case DIF_DCT:
			DCT_Mapping_Decodify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCoding( image_r,image_g, image_b,bitmapInfoHeader.biSizeImage);	
		break;
		case DCT_DIF:
			DCoding( image_r,image_g, image_b,bitmapInfoHeader.biSizeImage);	
			DCT_Mapping_Decodify(image_g,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_b,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
			DCT_Mapping_Decodify(image_r,bitmapInfoHeader.biSizeImage,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight);
		break;
	} 

	image = (unsigned char*)malloc((bitmapInfoHeader.biSizeImage)*sizeof(unsigned char));
	concRGB(image, image_r,image_g, image_b,bitmapInfoHeader.biSizeImage);

	/*printv(image,bitmapInfoHeader.biSizeImage);*/

	printf("Saving...\n");
	FILE *f;

	f = fopen(argv[2],"w+");
	fwrite(&(bitmapFileHeader.bfType), sizeof(unsigned short),1,f);
	fwrite(&(bitmapFileHeader.bfSize), sizeof(unsigned int),1,f);
	fwrite(&(bitmapFileHeader.bfReserved1), sizeof(unsigned short),1,f);
	fwrite(&(bitmapFileHeader.bfReserved2), sizeof(unsigned short),1,f);
	fwrite(&(bitmapFileHeader.bOffBits), sizeof(unsigned int),1,f);
	/*fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,f);*/


	/*read the bitmap info header*/
	/*The header must be read parameter per parameter*/
	fwrite(&(bitmapInfoHeader.biSize), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biWidth), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biHeight), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biPlanes), sizeof(unsigned short),1,f);
	fwrite(&(bitmapInfoHeader.biBitCount), sizeof(unsigned short),1,f);
	fwrite(&(bitmapInfoHeader.biCompression), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biSizeImage), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biXPelsPerMeter), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biYPelsPerMeter), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biClrUsed), sizeof(unsigned int),1,f);
	fwrite(&(bitmapInfoHeader.biClrImportant), sizeof(unsigned int),1,f);
	fseek(f, bitmapFileHeader.bOffBits, SEEK_SET);
	fwrite(image, sizeof(unsigned char),bitmapInfoHeader.biSizeImage,f);
	fclose(f);
	printf("End\n");
break;
}	
    return 0;
}
