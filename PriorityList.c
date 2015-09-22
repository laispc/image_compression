#include "PriorityList.h"

/*#define __DEBUG__*/

/* Compara duas estruturas PriorityCell. Esta funcao e usada na quicksort.
Retorno: > 0 if A > B, == 0 if A == B, < 0 if A < B */
int compareConstructCrescent(const void *A,const void *B){
	return (*(PriorityCell*)A).value - (*(PriorityCell*)B).value;
}

/* Compara duas estruturas PriorityCell. Esta funcao e usada na quicksort.
Retorno: > 0 if A < B, == 0 if A == B, < 0 if A > B*/
int compareConstructDecrescent(const void *A,const void *B){
	return (*(PriorityCell*)B).value - (*(PriorityCell*)A).value;
}

/* Gera lista de prioridades para a geracao da arvore de Huffman */
PriorityHead *generatePriorityList(HuffmanCell *cells, int numCells){
#ifdef __DEBUG__
	printf("Generating Priority List\n");
#endif
	PriorityHead *head = NULL;
	int i = 0;
	head = (PriorityHead *)malloc(sizeof(PriorityHead));
	head->numCells = numCells;
	head->list = (PriorityCell *)malloc(sizeof(PriorityCell)*numCells);
	for (i = 0; i < numCells; ++i)
	{
		head->list[i].box = cells+i;
		head->list[i].value = cells[i].frqcy;
		head->list[i].ref = 1;
#ifdef __DEBUG__
	printf("Insert Cell: %d\n", head->list[i].value);
#endif
	}
	return head;
}

/* Retorna numero de celulas da lista. */
int isEmptyPriorityList(PriorityHead *head){
	return head->numCells;
}

/* Desempilha uma celula da lista de prioridades. */
PriorityCell popPriorityList(PriorityHead *head){
	PriorityCell cell;
	head->numCells--;
	cell = head->list[head->numCells];
	return cell;
}

/* Insere uma celula na lista de prioridades. */
void insertPriorityCell(PriorityHead *head, PriorityCell cell){
	head->numCells++;
	head->list[head->numCells-1] = cell;
}