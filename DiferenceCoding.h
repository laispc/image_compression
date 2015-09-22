/*!		DiferenceCoding.h		*/
/*
Contem funções para a aplicação do código de diferenças.
*/

#ifndef DIFERENCECODING_V1
#define DIFERENCECODING_V1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dlist.h"

/*
Estrutura de dado que guarda o valor obtido no algorimo de diferença e o número de bits que esse  valor ocupa. 
*/
/*
typedef struct Dlist_{
	unsigned char value;
	unsigned char numBits;
}Dlist_;
*/

/*Determina o tamanho de bits que um determinado valor possui*/
int numberSize(unsigned char value);
/*Divide a imagem em RGB, a cor a ser salva depende da entrada da função*/
Dlist_* divRGB(unsigned char *image, unsigned int size, char c);
/*Aplicação do algoritmo de diferenças,e determina o tamanho de cada valor obtido na diferença*/
void diferenceCoding(Dlist_ *Dlist, unsigned int size);
/*Aplicação do inversa do algoritmo de diferenças*/
void DCoding( Dlist_ *Dlist_r,Dlist_ *Dlist_g, Dlist_ *Dlist_b,unsigned int size);
/*Concatena os arquivos RGB em uma imagem*/
void concRGB(unsigned char* image, Dlist_ *Dlist_r,Dlist_ *Dlist_g, Dlist_ *Dlist_b,unsigned int size);

#endif
