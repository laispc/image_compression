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

/* Child: Elemento genérico da árvore. Pode ser uma Cell ou Node. Armazena um valor (0 ou 1).*/
typedef struct HuffmanChild__{
	unsigned char ref; 				/* Indica uma Cell (1) ou um Node (0)*/
	unsigned char rl; 				/* Direita(0) ou esquerda (1)*/
	void* box;
}HuffmanChild;

/*// Node: Elemento que está no meio da árvore (não folha). Aponta para outros dois elementos filhos. Armazena frequências intermediárias. */
typedef struct HuffmanNode__
{
	int value;
	unsigned char nChilds;
	HuffmanChild *rightSon;
	HuffmanChild *leftSon;
}HuffmanNode;

/* Cell: Elemento folha. Armazena valor final correspondente ao código. */
typedef struct HuffmanCell__
{
	unsigned char value;
	int frqcy;
}HuffmanCell;



/*Inicializa a cricao da arvore com uma raiz vaiza
Retorno: HuffmanNode para a raiz*/
HuffmanNode *initialazeTree();

/* Comparacao entre duas HuffmanCells, que serve ser argumento para o quick sort
Returno: > 0 if A > B, == 0 if A == B, < 0 if A < B*/
int compareHuffmanCrescent(const void *A,const void *B);

/*Comparacao entre duas HuffmanCells, que serve ser argumento para o quick sort
Return: > 0 if A < B, == 0 if A == B, < 0 if A > B*/
int compareHuffmanDecrescent(const void *A,const void *B);

/* Insere uma celula em um HuffmanNode
Return: 0 se a operacao foi correta, 1 caso contrario*/
int insertChildCell(HuffmanNode *node, HuffmanChild *child);

/* Gera a arvore de Huffman 
Retorno: cabeca da arvore */
HuffmanNode *generateTree(HuffmanNode *head, HuffmanCell *cells, int numCells);

/* Gera lista de celulas 
Retorno: cabeca da lista de celulas */
HuffmanCell *generateCellList(Dlist_ *list, unsigned int numElements, int *numCells);

/* Imprime uma lista de Huffman */
void printHuffmanList(HuffmanCell *list, int numCells);

/* Busca uma mascara na arvore de Huffman, que serve de referencia par ajuntar bits. 
Retorno: mascara*/
unsigned char searchHuffman(HuffmanNode *node,unsigned char value,int *nMask);

/*  Busca um codigo na tabela de Huffman.
Retorno: 0 se encontrado, 1 caso contrario*/
int searchTableHuff(unsigned char *nBits, unsigned char huff, int huffLen, HuffmanTable *table, int tableLen); 

/* Insere codigo na tabela Huffman. 
Retorno: tabela atualizada.*/
HuffmanTable *insertOnHuffmanTable(unsigned char nBits, unsigned char huff, int huffLen, HuffmanTable *table, int *tableLen);

#endif
