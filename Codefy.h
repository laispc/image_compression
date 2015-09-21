/*!		Codefy.h		*/
/*
Contem funcoes de leitura de uma imagem bmp, manipulacao de bytes para gravacao, leitura de uma arvore de Huffman,leitura de uma arquivo .huff(arquivo comprimido), escrita de uma arquivo .huff.
*/

#ifndef CODEFY__V10
#define CODEFY__V10

#include "DiferenceCoding.h"
#include "HuffmanCoding.h"
#include <math.h>
#include <stdio.h>

#pragma pack(1)

/* Armazena informacoes gerais do arquvo Bitmap */
typedef struct __attribute__((__packed__)) tagBITMAPFILEHEADER
{
    unsigned short bfType;          /*specifies the file type*/
    unsigned int bfSize;            /*specifies the size in bytes of the bitmap file*/
    unsigned short bfReserved1;     /*reserved; must be 0*/
    unsigned short bfReserved2;     /*reserved; must be 0*/
    unsigned int bOffBits;          /*species the offset in bytes from the bitmapfileheader to the bitmap bits*/
}BITMAPFILEHEADER;

/* Armazena informacoes da imagem do arquivo Bitmap */
typedef struct __attribute__((__packed__)) tagBITMAPINFOHEADER
{
    unsigned int biSize;            /*specifies the number of bytes required by the struct*/
    unsigned int biWidth;           /*specifies width in pixels*/
    unsigned int biHeight;          /*species height in pixels*/
    unsigned short biPlanes;        /*specifies the number of color planes, must be 1*/
    unsigned short biBitCount;      /*specifies the number of bit per pixel*/
    unsigned int biCompression;     /*spcifies the type of compression*/
    unsigned int biSizeImage;       /*size of image in bytes*/
    unsigned int biXPelsPerMeter;   /*number of pixels per meter in x axis*/
    unsigned int biYPelsPerMeter;   /*number of pixels per meter in y axis*/
    unsigned int biClrUsed;         /*number of colors used by th ebitmap*/
    unsigned int biClrImportant;    /*number of colors that are important*/
}BITMAPINFOHEADER;


/*!brief Leitura de um arquivo de extensao do tipo .bmp*/
unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader);
/*!brief Realiza a concatenacao dos dados e o tamanho final do arquivo gerado*/
unsigned char *getByteVector(Dlist_ *list,int listLen, int *finalLen,HuffmanNode *head, HuffmanTable **table, int *tableLen);
/*!brief Leitura da tabela de Huffman*/
unsigned int readHuffmanTable( Dlist_ *Dlist_r, HuffmanTable *table, int tableLen, unsigned char *toWrite, int toWriteLen);
/*!brief Grava os dados do arquivo a ser comprimido*/
void writeOn(unsigned char *vectorR, unsigned char *vectorG, unsigned char *vectorB,int sizeR, int sizeG, int sizeB,
 BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, char *filename,HuffmanTable *table_g, HuffmanTable *table_b, HuffmanTable *table_r,int tableLen_g,int tableLen_b,int tableLen_r);
/*!brief Le os dados do arquivo a ser comprimido*/
void readOff(unsigned char **vectorR, unsigned char **vectorG, unsigned char **vectorB,int *sizeR, int *sizeG, int *sizeB,
 BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader, char *filename,HuffmanTable **table_g, HuffmanTable **table_b, HuffmanTable **table_r,int *tableLen_g,int *tableLen_b,int *tableLen_r);


#endif
