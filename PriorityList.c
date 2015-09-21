#include "PriorityList.h"

/*#define __DEBUG__*/

/*Compare two PriorityCell__ structures. This is used in quicksort
Return: > 0 if A > B, == 0 if A == B, < 0 if A < B*/
int compareConstructCrescent(const void *A,const void *B){
	return (*(PriorityCell*)A).value - (*(PriorityCell*)B).value;
}

/*Compare two PriorityCell__ structures. This is used in quicksort
Return: > 0 if A < B, == 0 if A == B, < 0 if A > B*/
int compareConstructDecrescent(const void *A,const void *B){
	return (*(PriorityCell*)B).value - (*(PriorityCell*)A).value;
}

/*Generate PriorityList*/
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

int isEmptyPriorityList(PriorityHead *head){
	return head->numCells;
}

/*Pop an Auxiliar cell of the list*/
PriorityCell popPriorityList(PriorityHead *head){
	head->numCells--;
	PriorityCell cell = head->list[head->numCells];
	return cell;
}

void insertPriorityCell(PriorityHead *head, PriorityCell cell){
	head->numCells++;
	head->list[head->numCells-1] = cell;
}