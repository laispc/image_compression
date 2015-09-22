/*!		DCT.c		*/
/*
Contêm funções para a a aplicação do algoritmo DCT em uma imagem.
*/
#include <math.h>
#include <complex.h>
#include "DCT.h"


/*Valor de PI*/
#define M_PI 3.14159265359

/*Determina qual matrix de quantificação esta sendo utilizado.*/
#define quantify MQuantify_50

/*!Matrix de quantificação de 50%*/
unsigned int MQuantify_50[8][8] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99}
    };

/*!Matrix de quantificação de 90%*/
unsigned int MQuantify_90[8][8] = {
    {3, 2, 2, 3, 5, 8, 10, 12},
    {2, 2, 3, 4, 5, 12, 12, 11},
    {3, 3, 3, 5, 8, 11, 14, 11},
    {3, 3, 4, 6, 10, 17, 16, 12},
    {4, 4, 7, 11, 14, 22, 21, 15},
    {5, 7, 11, 13, 16, 12, 23, 18},
    {10, 13, 16, 17, 21, 44, 24, 21},
    {14, 18, 19, 20, 22, 20, 20, 20}
    };


/*!Matrix para o cálculo da DCT de uma imagem 8x8*/
double T[8][8] = {
	{0.3536,     0.3536,     0.3536,   0.3536,   0.3536,    0.3536,   0.3536,  0.3536},
	{0.4904,     0.4157,     0.2778,   0.0975,  -0.0975,   -0.2778,  -0.4157, -0.4904},
	{0.4619,     0.1913,    -0.1913,  -0.4619,  -0.4619,   -0.1913,   0.1913,  0.4619},
	{0.4157,    -0.0975,    -0.4904,  -0.2778,   0.2778,    0.4904,   0.0975, -0.4157},
	{0.3536,    -0.3536,    -0.3536,   0.3536,   0.3536,   -0.3536,  -0.3536,  0.3536},
	{0.2778,    -0.4904,     0.0975,   0.4157,  -0.4157,   -0.0975,   0.4904, -0.2778},
	{0.1913,    -0.4619,     0.4619,  -0.1913,  -0.1913,    0.4619,  -0.4619,  0.1913},
	{0.0975,    -0.2778,     0.4157,  -0.4904,   0.4904,   -0.4157,   0.2778, -0.0975}
    };

/*!Matrix transposta de T*/
double T_[8][8] = {
	{0.3536,    0.4904,    0.4619,    0.4157,   0.3536,    0.2778,    0.1913,    0.0975},
    {0.3536,    0.4157,    0.1913,   -0.0975,  -0.3536,   -0.4904,   -0.4619,   -0.2778},
	{0.3536,    0.2778,   -0.1913,   -0.4904,  -0.3536,    0.0975,    0.4619,    0.4157},
	{0.3536,    0.0975,   -0.4619,   -0.2778,   0.3536,    0.4157,   -0.1913,   -0.4904},
	{0.3536,   -0.0975,   -0.4619,    0.2778,   0.3536,   -0.4157,   -0.1913,    0.4904},
	{0.3536,   -0.2778,   -0.1913,    0.4904,  -0.3536,   -0.0975,    0.4619,   -0.4157},
	{0.3536,   -0.4157,    0.1913,    0.0975,  -0.3536,    0.4904,   -0.4619,    0.2778},
	{0.3536,   -0.4904,    0.4619,   -0.4157,   0.3536,   -0.2778,    0.1913,   -0.0975}
};



/*!Funcão da equação da DCT, caso a '0' a saida sera 1/sqrt(2), caso contrario a saida e 1. */
float C(int value){
    if(value == 0)
            return 0.707107;
else
            return 1;
}

/*!Multiplicacao entre duas matrizes.*/
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


/*!Função que calcula os coeficientes de uma matriz 8x8, em duas dimensões.*/
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

/*!Função que decodifica os coeficientes de uma matriz 8x8, em duas dimensões, para retornar a imagem a ser gerada posteriormente*/
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


/*!Função de arredondamento*/
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


/*Função que mapeia a Dlist_ para gerar matrizes de tamanho 8x8, para posterior manipulação.*/
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
			}
		}
        }
    }
		

}


/*Função que mapeia a Dlist_ para gerar matrizes de tamanho 8x8, para posterior manipulacao.*/
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


