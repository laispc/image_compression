/*!		DCT.c		*/
/*
Contem funcoes para a a aplicacao do algoritmos de DCT em uma imagem.
*/
#include <math.h>
#include <complex.h>
#include "DCT.h"

#define M_PI 3.14159265359
#define quantify MQuantify_50


/*!brief Funcao da equacao de da DCT*/
/*
	Caso a '0' a saida sera 1/sqrt(2), caso contrario a saida e 1. 
*/
float C(int value){
    if(value == 0)
            return 0.707107;
else
            return 1;
}

/*!brief Multiplicacao entre duas matrizes*/
/*
	Multiplicacao entre duas matrizes.
*/
void MMatrix(double M1[8][8], double M2[8][8], double Mout[8][8]){
int i = 0, j = 0, k = 0;
double sum = 0;
for (i = 0; i < 8; i++) {
	for (j = 0; j < 8; j++) {
		for (k = 0; k < 8; k++) {
			sum = sum + M1[i][k]*M2[k][j];
		}

		Mout[i][j] = sum;
		sum = 0;
	}
}
}


/*!brief Funcao que calcula os coeficientes de uma matriz 8x8, em duas dimensoes*/
/*
	Funcao que calcula os coeficientes de uma matriz 8x8, em duas dimensoes.
*/
void DCT_Coefficient_8x8_2d(double Coelist[8][8] , double DCTlist[8][8]){
int i = 0,j = 0;
double tmp[8][8];

for (i = 0; i < 8; i++) {
	for (j = 0; j < 8; j++) {
		tmp[i][j] = 0;
	}
}


MMatrix(T,DCTlist,tmp);
MMatrix(tmp,T_,Coelist);



}

/*!brief Funcao de decodificacao dos coeficientes gerados.*/
/*
	Funcao que decodifica os coeficientes de uma matriz 8x8, em duas dimensoes, para retornar a imagem a ser gerada posteriormente
*/
void DCT_NCoefficient_8x8_2d(double Coelist[8][8] , double DCTlist[8][8]){
int i = 0, j = 0;
double tmp[8][8];

for (i = 0; i < 8; i++) {
	for (j = 0; j < 8; j++) {
		tmp[i][j] = 0;
	}
}

MMatrix(T_,Coelist,tmp);
MMatrix(tmp,T,DCTlist);
}


/*!brief Funcao de arredondamento*/
/*
	Funcao de arredondamento
*/
unsigned char round(double num,double value){
double tmp = 0;
int sign = 1;

if(num < 0){
	sign = -1;
	num = num*sign;
}

tmp = (num - (int)num);

if(tmp >= value){
	num++;
	return (num)*sign;
}
else{
	return num*sign;
}
}



/*!brief Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8.*/
/*
	Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8, para posterior manipulacao.
*/
void DCT_Mapping_Codify(Dlist_* image, unsigned int size, unsigned int width, unsigned int height){
    int i = 0, j = 0,x = 0,y = 0;
    double DCTlist[8][8];
    double Coelist[8][8];
    double tmp = 0;

       
    for(i = 0; i < height; i+=8){
        for(j = 0; j < width; j+=8){

		for(x = 0; x < 8; x++){
			for(y = 0; y < 8; y++){
				tmp = (unsigned char)image[i*width+j+x*width+y].value;
	
				DCTlist[x][y] = tmp - 128;


			}

		}
		DCT_Coefficient_8x8_2d(Coelist, DCTlist);
	
		for(x = 0; x < 8; x++){
			for(y = 0; y < 8; y++){
				image[i*width+j+x*width+y].value = round(Coelist[x][y]/quantify[x][y],0.90);
				image[i*width+j+x*width+y].numBits = numberSize(image[i*width+j+x*width+y].value);
				printf("%d ", (signed char)image[i*width+j+x*width+y].value);

			}
	printf("\n");
		}
            
	printf("\n");
        }
    }
		

}


/*!brief Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8.*/
/*
Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8, para posterior manipulacao.
*/
void DCT_Mapping_Decodify(Dlist_* image, unsigned int size, unsigned int width, unsigned int height){

unsigned int i = 0, j = 0, x = 0, y = 0;
double DCTlist[8][8];
double Coelist[8][8];
double tmp = 0;


for(i = 0; i < height; i+=8){
	for(j = 0; j < width; j+=8){
		for(x = 0; x < 8; x++){
			for(y = 0; y < 8; y++){
			tmp = (signed char)image[i*width+j+x*width+y].value;
			Coelist[x][y] = quantify[x][y] * tmp;
			}
		}
		DCT_NCoefficient_8x8_2d(Coelist, DCTlist);
		for(x = 0; x < 8; x++){
			for(y = 0; y < 8; y++){
				 image[i*width+j+x*width+y].value =  round(DCTlist[x][y],0.90) + 128;
			}


		}
	}
		
}	
	
}


