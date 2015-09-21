/*!		Codefy.c		*/
/*
Contem funcoes de leitura de uma imagem bmp, manipulacao de bytes para gravacao, leitura de uma arvore de Huffman,leitura de uma arquivo .huff(arquivo comprimido), escrita de uma arquivo .huff.
*/

#include "Codefy.h"

/*!brief Leitura de um arquivo de extensao do tipo .bmp*/
/*!
	Leitura do cabecalho do arquivo e grava em dois tipos de estrutura de dados, o bitmapFileHeader e o bitmapInfoHeader. Apos a leitura do cabecalho, o arquivo da imagem e lido.	
*/
unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; /*our file pointer*/
    /*BITMAPFILEHEADER bitmapFileHeader; */
    /*our bitmap file header*/
    unsigned char *bitmapImage;  /*store image data*/

    /*open filename in read binary mode*/
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    /*read the bitmap file header*/
    /*The header must be read parameter per parameter*/
    fread(&(bitmapFileHeader->bfType), sizeof(unsigned short),1,filePtr);
    fread(&(bitmapFileHeader->bfSize), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapFileHeader->bfReserved1), sizeof(unsigned short),1,filePtr);
    fread(&(bitmapFileHeader->bfReserved2), sizeof(unsigned short),1,filePtr);
    fread(&(bitmapFileHeader->bOffBits), sizeof(unsigned int),1,filePtr);
    /*fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);*/

    /*verify that this is a bmp file by check bitmap id*/
    if (bitmapFileHeader->bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    /*read the bitmap info header*/
    /*The header must be read parameter per parameter*/
    fread(&(bitmapInfoHeader->biSize), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biWidth), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biHeight), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biPlanes), sizeof(unsigned short),1,filePtr);
    fread(&(bitmapInfoHeader->biBitCount), sizeof(unsigned short),1,filePtr);
    fread(&(bitmapInfoHeader->biCompression), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biSizeImage), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biXPelsPerMeter), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biYPelsPerMeter), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biClrUsed), sizeof(unsigned int),1,filePtr);
    fread(&(bitmapInfoHeader->biClrImportant), sizeof(unsigned int),1,filePtr);
    /*fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);*/

    /*move file point to the begging of bitmap data*/
    fseek(filePtr, bitmapFileHeader->bOffBits, SEEK_SET);

    /*allocate enough memory for the bitmap image data*/
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
    printf("Size of File: %u\n", bitmapFileHeader->bfSize);
    printf("Size of Image: %u\n", bitmapInfoHeader->biSizeImage);
    /*verify memory allocation*/
    if (bitmapImage == NULL)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    /*read in the bitmap image data*/
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);

    /*make sure bitmap image data was read*/
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    /*swap the r and b values to get RGB (bitmap is BGR)*/
    /*
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    */
    /*close file and return bitmap iamge data*/
    fclose(filePtr);
    return bitmapImage;
}

/*!brief Realiza a concatenacao dos dados e o tamanho final do arquivo gerado*/
/*!
	Realiza a contagem de bytes do arquivo a ser comprimido utilizando mascaras, utilizacao da tabela de Huffman para a compressao.
*/
unsigned char *getByteVector(Dlist_ *list,int listLen, int *finalLen,HuffmanNode *head, HuffmanTable **table, int *tableLen){

	unsigned char *vector = (unsigned char *)malloc(sizeof(unsigned char));
	int vectorLen = 0;
	unsigned char byte = 0, aux = 0, auxMask = 0, andMask = 0;
	int nMask = 0, offsetBits = 0, bitsOnByte = 0, remain = 0, i = 0, j = 0;
	short int flagHuffInf = 0;
	while (i < listLen)
	{
		if(flagHuffInf == 0){

			if (remain > 0)
			{
				offsetBits = 8 - bitsOnByte - remain;
				byte = byte | (auxMask << offsetBits);
				bitsOnByte += remain;
				auxMask = 0;
				remain = 0;
				flagHuffInf = 1;
			}else{
				aux = searchHuffman(head, list[i].numBits, &nMask);
				/*printf("Numbits = %d, Value = %d\n", list[i].numBits, list[i].value);*/
				(*table) = insertOnHuffmanTable(list[i].numBits, aux, nMask, *table, tableLen);
				offsetBits = 8 - bitsOnByte - nMask;

				if (offsetBits >= 0)
				{
					byte = byte | (aux << offsetBits);
					bitsOnByte += nMask;
					flagHuffInf = 1;
					remain = 0;
				}else{
					andMask = 0;
					/* Calcula a mascara para fazer o and dos bits que restaram*/
					for (j = 0; j < -offsetBits; ++j)
					{
						andMask += pow(2,j);
					}
					auxMask = andMask & aux;
					aux = ~(andMask) & aux;
					aux = aux >> -offsetBits;
					remain = -offsetBits;
					byte = byte | aux;
					bitsOnByte = 8;
				}
			}
			if (bitsOnByte == 8)
			{

				vectorLen++;
				if (vectorLen != 1)
				{
					vector = realloc(vector, sizeof(unsigned char)*vectorLen);
				}
				/*printf("byte = %d\n", byte);*/
				vector[vectorLen-1] = byte;
				byte = 0;
				bitsOnByte = 0;
				
			}
		}else{
			if (remain > 0)
			{
				offsetBits = 8 - bitsOnByte - remain;
				byte = byte | (auxMask << offsetBits);
				bitsOnByte += remain;
				auxMask = 0;
				remain = 0;
				flagHuffInf = 0;
				i++;
			}else{
				aux = list[i].value;
				offsetBits = 8 - bitsOnByte - list[i].numBits;
				if (aux !=0)
				{
					
					if (offsetBits >= 0)
					{
						byte = byte | (aux << offsetBits);
						bitsOnByte += list[i].numBits;
						flagHuffInf = 0;
						remain = 0;
						i++;
					}else{
						andMask = 0;
						/* Calcula a mascara para fazer o and dos bits que restaram*/

						for (j = 0; j < -offsetBits; ++j)
						{
							andMask += pow(2,j);
						}
						auxMask = andMask & aux;
						aux = ~(andMask) & aux;
						aux = aux >> -offsetBits;
						remain = -offsetBits;
						byte = byte | aux;
						bitsOnByte = 8;
					}
				}else{
					flagHuffInf = 0;
					i++;
				}
			}
			if (bitsOnByte == 8)
			{
				vectorLen++;
				/*printf("byte = %d\n", byte);*/
				vector = realloc(vector, sizeof(unsigned char)*vectorLen);
				vector[vectorLen-1] = byte;
				byte = 0;
				bitsOnByte = 0;
			}
		}
	}
	(*finalLen) = vectorLen;

	printf("\nFinal length: %d \n",vectorLen );
	return vector;
}

/*!brief Leitura da tabela de Huffman*/
/*!
	Le da tabela de Huffman os valor dos respectivas frequencias de cada informacao a ser compactado.
*/
unsigned int readHuffmanTable( Dlist_ *Dlist_r, HuffmanTable *table, int tableLen, unsigned char *toWrite, int toWriteLen){         
	unsigned char aux=0, aux2=0;
	int posToWrite=0;
	int huffLen = 1; 
	int posList=0, posBit = 0;
	unsigned char nBits = 0;
	int sizeUC = 7;

	posBit = sizeUC;
	for(posToWrite = 0;posToWrite < toWriteLen;){
		aux2 = toWrite[posToWrite];
		aux =  aux | ((aux2 >> posBit) & 1);
		posBit--;
		if(posBit < 0){
			posToWrite++;
			posBit = sizeUC;
			aux2 = toWrite[posToWrite];
		}
		if(searchTableHuff( &nBits, aux, huffLen, table, tableLen)){
			aux  <<= 1;
			huffLen++;
		}
		else{
			aux = 0;
			
			while(nBits > 0){
				aux <<= 1;
				aux = aux | ((aux2 >> posBit) & 1);
				posBit--;
				if(posBit < 0){
					posToWrite++;
					posBit = sizeUC;
					aux2 = toWrite[posToWrite];
				}
				nBits--;
			}

				Dlist_r[posList++].value = aux;
        	        
        		if(posBit <0){
        			posToWrite++;
        			posBit = sizeUC;
        			aux2 = toWrite[posToWrite];
        		}
        		aux = 0;
        		huffLen = 1; 
        	}
        }
        return 1;
    }


/*!brief Grava os dados do arquivo a ser comprimido*/
/*!
	Grava o cabecalho no arquivo a ser comprimido, e os dados BGR.
*/
void writeOn(unsigned char *vectorR, unsigned char *vectorG, unsigned char *vectorB,int sizeR, int sizeG, int sizeB,
 BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, char *filename, HuffmanTable *table_g, HuffmanTable *table_b, HuffmanTable *table_r,int tableLen_g,int tableLen_b,int tableLen_r){
	FILE *f;
	f = fopen(filename, "w+");

	fwrite(&(bitmapFileHeader.bfType), sizeof(unsigned short),1,f);
    fwrite(&(bitmapFileHeader.bfSize), sizeof(unsigned int),1,f);
    fwrite(&(bitmapFileHeader.bfReserved1), sizeof(unsigned short),1,f);
    fwrite(&(bitmapFileHeader.bfReserved2), sizeof(unsigned short),1,f);
    fwrite(&(bitmapFileHeader.bOffBits), sizeof(unsigned int),1,f);
    /*fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,f);*/


    /*read the bitmap info header*/
    /*The header must be read parameter per parameter*/
    fwrite(&(bitmapInfoHeader.biSize), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biWidth), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biHeight), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biPlanes), sizeof(unsigned short),1,f);
    fwrite(&(bitmapInfoHeader.biBitCount), sizeof(unsigned short),1,f);
    fwrite(&(bitmapInfoHeader.biCompression), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biSizeImage), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biXPelsPerMeter), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biYPelsPerMeter), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biClrUsed), sizeof(unsigned int),1,f);
    fwrite(&(bitmapInfoHeader.biClrImportant), sizeof(unsigned int),1,f);
    fseek(f, bitmapFileHeader.bOffBits, SEEK_SET);
    	fwrite(&sizeR, sizeof(int),1,f);
	fwrite(&sizeG, sizeof(int),1,f);
	fwrite(&sizeB, sizeof(int),1,f);
	fwrite(&tableLen_r, sizeof(int),1,f);
	fwrite(&tableLen_g, sizeof(int),1,f);
	fwrite(&tableLen_b, sizeof(int),1,f);
	fwrite(vectorR, sizeof(unsigned char),sizeR,f);
	fwrite(vectorG, sizeof(unsigned char),sizeG,f);
	fwrite(vectorB, sizeof(unsigned char),sizeB,f);

	fwrite(table_r, sizeof(HuffmanTable),tableLen_r,f);
	fwrite(table_g, sizeof(HuffmanTable),tableLen_g,f);
	fwrite(table_b, sizeof(HuffmanTable),tableLen_b,f);

	fclose(f);
}

/*!brief Le os dados do arquivo a ser comprimido*/
/*!
	Le o cabecalho do arquivo comprimido, e os dados BGR.
*/
void readOff(unsigned char **vectorR, unsigned char **vectorG, unsigned char **vectorB,int *sizeR, int *sizeG, int *sizeB,
 BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader, char *filename,HuffmanTable **table_g, HuffmanTable **table_b, HuffmanTable **table_r,int *tableLen_g,int *tableLen_b,int *tableLen_r){
    FILE *f;
    f = fopen(filename, "r+");
    fread(&(bitmapFileHeader->bfType), sizeof(unsigned short),1,f);
    fread(&(bitmapFileHeader->bfSize), sizeof(unsigned int),1,f);
    fread(&(bitmapFileHeader->bfReserved1), sizeof(unsigned short),1,f);
    fread(&(bitmapFileHeader->bfReserved2), sizeof(unsigned short),1,f);
    fread(&(bitmapFileHeader->bOffBits), sizeof(unsigned int),1,f);
    /*fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,f);*/

    /*verify that this is a bmp file by check bitmap id*/
    if (bitmapFileHeader->bfType !=0x4D42)
    {
        fclose(f);
        return;
    }
    /*read the bitmap info header*/
    /*The header must be read parameter per parameter*/

    fread(&(bitmapInfoHeader->biSize), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biWidth), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biHeight), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biPlanes), sizeof(unsigned short),1,f);
    fread(&(bitmapInfoHeader->biBitCount), sizeof(unsigned short),1,f);
    fread(&(bitmapInfoHeader->biCompression), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biSizeImage), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biXPelsPerMeter), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biYPelsPerMeter), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biClrUsed), sizeof(unsigned int),1,f);
    fread(&(bitmapInfoHeader->biClrImportant), sizeof(unsigned int),1,f);
   /*fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,f);*/

    /*move file point to the begging of bitmap data*/
    fseek(f, bitmapFileHeader->bOffBits, SEEK_SET);
    	fread(sizeR, sizeof(int),1,f);
	fread(sizeG, sizeof(int),1,f);
	fread(sizeB, sizeof(int),1,f);

	fread(tableLen_r, sizeof(int),1,f);
	fread(tableLen_g, sizeof(int),1,f);
	fread(tableLen_b, sizeof(int),1,f);
		
	(*vectorR) = (unsigned char *)malloc((*sizeR)*sizeof(unsigned char));
	(*vectorG) = (unsigned char *)malloc((*sizeG)*sizeof(unsigned char));
	(*vectorB) = (unsigned char *)malloc((*sizeB)*sizeof(unsigned char));
	fread((*vectorR), sizeof(unsigned char),(*sizeR),f);
	fread((*vectorG), sizeof(unsigned char),(*sizeG),f);
	fread((*vectorB), sizeof(unsigned char),(*sizeB),f);

	(*table_r) = (HuffmanTable*)malloc((*tableLen_r)*sizeof(HuffmanTable));
	(*table_g) = (HuffmanTable*)malloc((*tableLen_g)*sizeof(HuffmanTable));
	(*table_b) = (HuffmanTable*)malloc((*tableLen_b)*sizeof(HuffmanTable));

	fread((*table_r), sizeof(HuffmanTable),(*tableLen_r),f);
	fread((*table_g), sizeof(HuffmanTable),(*tableLen_g),f);
	fread((*table_b), sizeof(HuffmanTable),(*tableLen_b),f);


	fclose(f);
}




