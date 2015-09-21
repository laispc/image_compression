#ifndef HUFFMANCODING__V10
#define HUFFMANCODING__V10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DiferenceCoding.h"

/* Tabela de referencia com os codigos Huffman e seus tamanhos, para salvar e carregar o arquivo*/
typedef struct HuffmanTable{
        unsigned char nBits;
        unsigned char huffCode;
        int huffLen;
}HuffmanTable;

/* As estrutuas a seguir formam a arvore de Huffman*/
/* Child: */
typedef struct HuffmanChild__{
	unsigned char ref; /* reference to know if is a cell(1) or a node(0)*/
	unsigned char rl; /* r(0) , l(1)*/
	void* box;
}HuffmanChild;

/*// Structure for a node of the tree*/
typedef struct HuffmanNode__
{
	int value;
	unsigned char nChilds;
	HuffmanChild *rightSon;
	HuffmanChild *leftSon;
}HuffmanNode;

/* Celula*/
typedef struct HuffmanCell__
{
	unsigned char value;
	int frqcy;
}HuffmanCell;




HuffmanNode *initialazeTree();
int compareHuffmanCrescent(const void *A,const void *B);
int compareHuffmanDecrescent(const void *A,const void *B);
int insertChildCell(HuffmanNode *node, HuffmanChild *child);
HuffmanNode *generateTree(HuffmanNode *head, HuffmanCell *cells, int numCells);
HuffmanCell *generateCellList(Dlist_ *list, unsigned int numElements, int *numCells);
void printHuffmanList(HuffmanCell *list, int numCells);
unsigned char searchHuffman(HuffmanNode *node,unsigned char value,int *nMask);
int searchTableHuff(unsigned char *nBits, unsigned char huff, int huffLen, HuffmanTable *table, int tableLen); 
HuffmanTable *insertOnHuffmanTable(unsigned char nBits, unsigned char huff, int huffLen, HuffmanTable *table, int *tableLen);

#endif
