/*!		DCT.h		*/
/*
Contém funções para a a aplicação do algoritmos de DCT em uma imagem.
*/

#ifndef DCTCODING_V1
#define DCTCODING_V1

#include <math.h>	
#include <complex.h>
#include <stdio.h>
#include <string.h>
#include "Dlist.h"
#include "DiferenceCoding.h"



/*!brief Funcao da equacao de da DCT*/
float C(int value);
/*!brief Multiplicacao entre duas matrizes*/
void MMatrix(double M1[8][8], double M2[8][8], double Mout[8][8]);
/*!brief Funcao que calcula os coeficientes de uma matriz 8x8, em duas dimensoes*/
void DCT_Coefficient_8x8_2d(double Coelist[8][8] , double DCTlist[8][8]);
/*!brief Funcao de decodificacao dos coeficientes gerados.*/
void DCT_NCoefficient_8x8_2d(double Coelist[8][8] , double DCTlist[8][8]);
/*!brief Funcao de arredondamento*/
unsigned char round(double num,double value);
/*!brief Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8.*/
void DCT_Mapping_Codify(Dlist_* image, unsigned int size, unsigned int width, unsigned int height);
/*!brief Funcao que mapeia a Dlist_ para gerar matrizes de tamanho 8x8.*/
void DCT_Mapping_Decodify(Dlist_* image, unsigned int size, unsigned int width, unsigned int height);
#endif
