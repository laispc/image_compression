#ifndef PRIORITYLIST__V10
#define PRIORITYLIST__V10

#include <string.h>
#include "HuffmanCoding.h"

/* Estrutura da celula da lista de prioridades. */
typedef struct PriorityCell__{
	char ref; 		/* Cell(1) ou node(0)*/
	int value;		/* Frequencia*/
	void* box;
}PriorityCell;

/* Cabecalho da lista de prioridades.*/
typedef struct PriorityHead__{
	int numCells;
	PriorityCell *list;
}PriorityHead;

/* Compara duas estruturas PriorityCell. Esta funcao e usada na quicksort.
Retorno: > 0 if A > B, == 0 if A == B, < 0 if A < B */
int compareConstructCrescent(const void *A,const void *B);
/* Compara duas estruturas PriorityCell. Esta funcao e usada na quicksort.
Retorno: > 0 if A < B, == 0 if A == B, < 0 if A > B*/
int compareConstructDecrescent(const void *A,const void *B);
/* Gera lista de prioridades para a geracao da arvore de Huffman */
PriorityHead *generatePriorityList(HuffmanCell *cells, int numCells);
/* Retorna numero de celulas da lista. */
int isEmptyPriorityList(PriorityHead *head);
/* Desempilha uma celula da lista de prioridades. */
PriorityCell popPriorityList(PriorityHead *head);
/* Insere uma celula na lista de prioridades. */
void insertPriorityCell(PriorityHead *head, PriorityCell cell);

#endif