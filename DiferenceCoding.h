#ifndef DIFERENCECODING_V1
#define DIFERENCECODING_V1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Dlist_{
	unsigned char value;
	unsigned char numBits;
}Dlist_;

unsigned char subtractValue(Dlist_* bitmapImage, int i);
void diferenceCoding(Dlist_ *Dlist, unsigned int size);
Dlist_* divRGB(unsigned char* image, unsigned int size, char c);
int numberSize(unsigned char value);
unsigned char sumValue(unsigned char image, Dlist_ *Dlist, int imageIdx);
void DCoding(Dlist_ *Dlist_r,Dlist_ *Dlist_g,Dlist_ *Dlist_b,unsigned int size);
void concRGB(unsigned char* image, Dlist_ *Dlist_r,Dlist_ *Dlist_g, Dlist_ *Dlist_b,unsigned int size);

#endif
