
#include "HuffmanCoding.h"
#include "PriorityList.h"

/*#define __DEBUG__*/

/*Inicializa a cricao da arvore com uma raiz vaiza
Retorno: HuffmanNode para a raiz*/
HuffmanNode *initialazeTree(){
	HuffmanNode *root = NULL;
	root->value = 0;
	root->nChilds = 0;
	root->rightSon = NULL;
	root->leftSon = NULL;
	return root;
}

/* Comparacao entre duas HuffmanCells, que serve ser argumento para o quick sort
Returno: > 0 if A > B, == 0 if A == B, < 0 if A < B*/

int compareHuffmanCrescent(const void *A,const void *B){
	return (*(HuffmanCell*)A).frqcy - (*(HuffmanCell*)B).frqcy;
}

/*Comparacao entre duas HuffmanCells, que serve ser argumento para o quick sort
Return: > 0 if A < B, == 0 if A == B, < 0 if A > B*/
int compareHuffmanDecrescent(const void *A,const void *B){
	return (*(HuffmanCell*)B).frqcy - (*(HuffmanCell*)A).frqcy;
}


/* Insere uma celula em um HuffmanNode
Return: 0 se a operacao foi correta, 1 caso contrario*/
int insertChildCell(HuffmanNode *node,HuffmanChild *child){
	/* Verifica se esta cheio */
	if (node->nChilds >= 2)
		return 1;

	/* Decide qual filho escolher */
	if(node->rightSon == NULL){
		node->rightSon = child;
		node->rightSon->rl = 1;
	} else if (node->leftSon == NULL){
		node->leftSon = child;
		node->leftSon->rl = 0;
	}
	/*Calcula o valor*/
	if (child->ref == 1)
	{
		node->value += ((HuffmanCell *)child->box)->value;
	}else if(child->ref == 0){
		node->value += ((HuffmanNode *)child->box)->value;
	}
	node->nChilds++;
	return 0;
}


/* Gera a arvore de Huffman 
Retorno: cabeca da arvore */
HuffmanNode *generateTree(HuffmanNode *head, HuffmanCell *cells, int numCells){
	PriorityHead *priorityList = NULL;
	PriorityCell auxPriorityCell;
	HuffmanNode *auxA = NULL;
	HuffmanChild *auxChild = NULL;
	int frqcySum = 0;

	auxA = (HuffmanNode *)malloc(sizeof(HuffmanNode));
	auxA->rightSon = NULL;
	auxA->leftSon = NULL;
	auxA->value = 0;

	/* Organiza a arvore pela frequencia em ordem decrescente */
	qsort(cells, numCells, sizeof(HuffmanCell), compareHuffmanDecrescent);

	/*Inicializa celular auxiliares*/
	priorityList = generatePriorityList(cells, numCells);

	/*Cria a arvore*/
	do{

		auxA = (HuffmanNode *)malloc(sizeof(HuffmanNode));
		auxA->rightSon = NULL;
		auxA->leftSon = NULL;
		auxA->value = 0;
		auxA->nChilds = 0;

		/* Pega o primeiro filho*/
		auxPriorityCell = popPriorityList(priorityList);
		auxChild = (HuffmanChild *)malloc(sizeof(HuffmanChild));
		auxChild->ref = auxPriorityCell.ref;
		auxChild->box = auxPriorityCell.box;
		frqcySum = auxPriorityCell.value;

#ifdef __DEBUG__
		printf("Incerted Cell: \n");
		if (auxChild->ref == 1)
		{
			printf("HuffmanCell\n" );
			printf("Value: %d\n", ((HuffmanCell *)auxChild->box)->value);
		}else{
			printf("HuffmanNode\n" );
			printf("Value: %d\n", ((HuffmanNode *)auxChild->box)->value);
		}
		printf("Frequency: %d\n",auxPriorityCell.value);
#endif

		/*Inserir filho*/
		insertChildCell(auxA, auxChild);

		/*Pega o segundo filho*/
		auxPriorityCell = popPriorityList(priorityList);
		auxChild = (HuffmanChild *)malloc(sizeof(HuffmanChild));
		auxChild->ref = auxPriorityCell.ref;
		auxChild->box = auxPriorityCell.box;
		frqcySum += auxPriorityCell.value;

#ifdef __DEBUG__
		printf("Incerted Cell: \n");
		if (auxChild->ref == 1)
		{
			printf("HuffmanCell\n" );
			printf("Value: %d\n", ((HuffmanCell *)auxChild->box)->value);
		}else{
			printf("HuffmanNode\n" );
			printf("Value: %d\n", ((HuffmanNode *)auxChild->box)->value);
		}
		printf("Frequency: %d\n",auxPriorityCell.value);
#endif
		/* Inserir filho */
		insertChildCell(auxA, auxChild);

		/* Adicionar o no a lista de prioridade */
		auxPriorityCell.ref = 0;
		auxPriorityCell.value = frqcySum;
		auxPriorityCell.box = auxA;

		insertPriorityCell(priorityList, auxPriorityCell);

		/* Organizar a lista de prioridade */
		qsort(priorityList->list, priorityList->numCells, sizeof(PriorityCell), compareConstructDecrescent);

	}while(priorityList->numCells > 1);

	auxPriorityCell = popPriorityList(priorityList);
	head = (HuffmanNode *)auxPriorityCell.box;

#ifdef __DEBUG__
	printf("Returning Head\n");
	printf("Value: %d\n", head->value);
#endif
	return head;
}

/* Insere uma celula na lista 
Retorno: lista atualizada */
HuffmanCell *insertCellOnList(HuffmanCell *list, int *numCells, HuffmanCell cell){
	/* Verifica se o valor da celula ja existe*/
	int i = 0;
	for (i = 0; i < (*numCells); ++i)
	{
		if(list[i].value == cell.value){
			list[i].frqcy++;
			return list;
		}
	}
	(*numCells)++;
	list = (HuffmanCell *)realloc(list, sizeof(HuffmanCell)*(*numCells));
	list[(*numCells)-1] = cell;
	return list;
}

/* Gera lista de celulas 
Retorno: cabeca da lista de celulas */
HuffmanCell *generateCellList(Dlist_ *list, unsigned int numElements, int *numCells){
	HuffmanCell *cells = NULL, newCell;
	int i = 0;
	(*numCells) = 0;

	cells = (HuffmanCell *)malloc(sizeof(HuffmanCell));
	newCell.value = list[0].numBits;
	newCell.frqcy = 1;
	cells[0] = newCell;
	(*numCells)++;
	for (i = 1; i < numElements; ++i)
	{
		newCell.value = list[i].numBits;
		newCell.frqcy = 1;
		cells = insertCellOnList(cells, numCells, newCell);
		/*printHuffmanList(cells,(*numCells));*/
	}
	return cells;
}

/*  */
void printHuffmanList(HuffmanCell *list, int numCells){
	int i = 0;
	for (i = 0; i < numCells; ++i)
	{
		printf("Cell[%d]: Value = %d, Frequency = %d\n",
			i ,list[i].value, list[i].frqcy);
	}
}

void zeros(int a[], int n){
	int i = 0;
	for (i = 0; i < n; ++i)
	{
		a[i]=0;
	}
}

void printv2(int a[],int n){
	int i = 0;
	for (i = 0; i < n; ++i)
	{
		printf("%d, ", a[i]);
	}
	printf("\n");
}

unsigned char searchHuffman(HuffmanNode *node ,unsigned char value, int *nMask){
	HuffmanChild *cells = NULL, auxCell;
	int numCells = 2, i = 0;
	unsigned char mask = 0;
	int masklen = 0;
	int deleteFlag[256], counter = 0;
	zeros(deleteFlag,256);
	/*unsigned char one = 1, zero = 0;*/
#ifdef __DEBUG__
	printf("Start Search\n");
	printf("Head value: %d\n", node->value);
#endif
	switch(node->nChilds){
		case 1 :{
			cells = (HuffmanChild *)malloc(sizeof(HuffmanChild));
			cells[0] = *(node->rightSon);
			if (cells[0].ref == 1)
			{
				deleteFlag[0]++;
			}
#ifdef __DEBUG__
			if (node->rightSon->ref == 1)
			{
				printf("First Son value: %d\n", ((HuffmanCell *)node->rightSon->box)->value);
			}else if(node->rightSon->ref == 0){
				printf("First Son value: %d\n", ((HuffmanNode *)node->rightSon->box)->value);
			}
#endif
		}
		case 2 :{
			cells = (HuffmanChild *)malloc(sizeof(HuffmanChild)*2);
			cells[0] = *(node->rightSon);	
			cells[1] = *(node->leftSon);
			deleteFlag[0] =+ 2;

#ifdef __DEBUG__
			if (node->rightSon->ref == 1)
			{
				printf("First Son value: %d\n", ((HuffmanCell *)node->rightSon->box)->value);
			}else if(node->rightSon->ref == 0){
				printf("First Son value: %d\n", ((HuffmanNode *)node->rightSon->box)->value);
			}
			if (node->leftSon->ref == 1)
			{
				printf("Second Son value: %d\n", ((HuffmanCell *)node->leftSon->box)->value);
			}else if(node->leftSon->ref == 0){
				printf("Second Son value: %d\n", ((HuffmanNode *)node->leftSon->box)->value);
			}
#endif
		}
	}
	while(numCells > 0){
#ifdef __DEBUG__
		printf("Mask %x\n", mask);
		/*printv2(deleteFlag,256);*/
#endif
		if (counter > 0 && deleteFlag[counter] == 0)
		{
			mask = mask & ~(1);
			mask >>= 1;
			masklen--;
			counter--;
		}else if (cells[0].ref == 1){

			if (cells[0].rl == 1)
			{
				/* Adiciona 0 */
				mask <<= 1;
				masklen++;
			}else if(cells[0].rl == 0){
				/* Adiciona 1 */
				mask <<= 1;
				mask = mask | 1;
				masklen++;
			}

			/*printf("%d == %d ?\n",((HuffmanCell *)(cells[i].box))->value, value );*/
			if(((HuffmanCell *)(cells[i].box))->value == value){
				(*nMask) = masklen;
				return mask;
			}else{
				/* Remove primeiro */
				memmove(cells, cells+1,sizeof(HuffmanChild)*(numCells-1));
				numCells--;
				cells = realloc(cells, sizeof(HuffmanChild)*numCells);
				/* Remove ultimo */
				mask = mask & ~(1);
				mask >>= 1;
				masklen--;
				deleteFlag[counter]--;
				if (deleteFlag[counter] == 0)
				{
					mask = mask & ~(1);
					mask >>= 1;
					masklen--;
					counter--;
				}
			}
		}else if (cells[0].ref == 0)
		{
			
			if (cells[0].rl == 1)
			{
				/*Add a zero*/
				mask <<= 1;
				masklen++;
			}else if(cells[0].rl == 0){
				/*Add a 1*/
				mask <<= 1;
				mask = mask | 1;
				masklen++;
			}
			auxCell = cells[i];
			switch(((HuffmanNode *)auxCell.box)->nChilds){
				case 1 :{
					cells[0] = *(((HuffmanNode *)auxCell.box)->rightSon);
					deleteFlag[counter]--;
					if (cells[0].ref == 1)
					{
						counter++;
						deleteFlag[counter]++;
					}
#ifdef __DEBUG__
					if (cells[0].ref == 1)
					{
						printf("First Son value: %d\n", ((HuffmanCell *)cells[0].box)->value);
					}else if(cells[0].ref == 0){
						printf("First Son value: %d\n", ((HuffmanNode *)cells[0].box)->value);
					}
#endif
				}
				case 2 :{
					numCells = numCells + 1;
					cells = realloc(cells, sizeof(HuffmanChild)*numCells);
					memmove(cells+1, cells,sizeof(HuffmanChild)*(numCells-1));
					cells[0] = *(((HuffmanNode *)auxCell.box)->rightSon);
					cells[1] = *(((HuffmanNode *)auxCell.box)->leftSon);
					deleteFlag[counter]--;
					counter++;
					deleteFlag[counter] =+ 2;
#ifdef __DEBUG__
					if (cells[0].ref == 1)
					{
						printf("First Son value: %d\n", ((HuffmanCell *)cells[0].box)->value);
					}else if(cells[0].ref == 0){
						printf("First Son value: %d\n", ((HuffmanNode *)cells[0].box)->value);
					}
					if (cells[1].ref == 1)
					{
						printf("Second Son value: %d\n", ((HuffmanCell *)cells[1].box)->value);
					}else if(cells[1].ref == 0){
						printf("Second Son value: %d\n", ((HuffmanNode *)cells[1].box)->value);
					}
#endif
				}
			}
		}else{
			/*ERROR*/
		}
	}
	(*nMask) = masklen;
	return mask;
}

int searchTableHuff(unsigned char *nBits, unsigned char huff, int huffLen, HuffmanTable *table, int tableLen){
	int i = 0;
	for (i = 0; i < tableLen; ++i)
	{
		if (table[i].huffCode == huff && huffLen == table[i].huffLen)
		{
			(*nBits) = table[i].nBits;
			return 0;
		}
	}
    return 1;
}

HuffmanTable *insertOnHuffmanTable(unsigned char nBits, unsigned char huff, int huffLen, HuffmanTable *table, int *tableLen){
	if(table == NULL){
		(*tableLen) = 1;
		table = (HuffmanTable *)malloc(sizeof(HuffmanTable)*(*tableLen));
	}else{
		if (searchTableHuff(&nBits, huff, huffLen, table, (*tableLen)) == 0){
			return table;
		}
		(*tableLen)++;
		table = realloc(table, sizeof(HuffmanTable)*(*tableLen));
	}
	table[(*tableLen) - 1].nBits = nBits;
	table[(*tableLen) - 1].huffCode = huff;
	table[(*tableLen) - 1].huffLen = huffLen;
	return table;
}
