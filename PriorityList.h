#ifndef PRIORITYLIST__V10
#define PRIORITYLIST__V10

#include <string.h>
#include "HuffmanCoding.h"

typedef struct PriorityCell__{
	char ref; /* reference to know if is a cell(1) or a node(0)*/
	int value; /* Frequência*/
	void* box;
}PriorityCell;

typedef struct PriorityHead__{
	int numCells;
	PriorityCell *list;
}PriorityHead;

PriorityHead *generatePriorityList(HuffmanCell *cells, int numCells);
int isEmptyPriorityList(PriorityHead *head);
PriorityCell popPriorityList(PriorityHead *head);
int compareConstructCrescent(const void *A,const void *B);
int compareConstructDecrescent(const void *A,const void *B);
void insertPriorityCell(PriorityHead *head, PriorityCell cell);

#endif