#include "DiferenceCoding.h"

unsigned char subtractValue(Dlist_* bitmapImage, int imageIdx) {

	return bitmapImage[imageIdx].value-bitmapImage[imageIdx-1].value;
}

int numberSize(unsigned char value){
  double bits=0, den = 0; 
  if(value<0) {
    value*=-1;
  } den=value;
  while(den>=2){
    den = den/2;
    bits++;
  } 
  if(den>0){
    bits++;
  }
  return (unsigned char) bits;
}


Dlist_* divRGB(unsigned char *image, unsigned int size, char c){
  int i = 0, imageIdx = 0, color = 0;
  Dlist_ *Dlist;
  Dlist = (Dlist_*) malloc((size/3)*sizeof(Dlist_));
  switch (c){
    case 'b':{
      color = 0;
      break;
    }
    case 'g':{
      color = 1;
      break;
    }
    case 'r':{
      color = 2;
      break;
    }
  }

  Dlist[0].value = image[color];
  Dlist[0].numBits = numberSize(Dlist[0].value);
 i = 1;
  /*printf("%d ", image[0]);*/
  for(imageIdx = 3; imageIdx < size; imageIdx += 3) {
    Dlist[i].value = image[imageIdx + color];
    Dlist[i].numBits = numberSize(Dlist[i].value);
    /*printf("%d ", image[imageIdx]);*/
    i++;
  }
  return Dlist;
}


void diferenceCoding(Dlist_ *Dlist, unsigned int size) {
  int imageIdx = 0;
  Dlist[0].value = Dlist[0].value;
  Dlist[0].numBits = numberSize(Dlist[0].value); 
  
for(imageIdx = size/3 - 1; imageIdx > 0; imageIdx--) {
    Dlist[imageIdx].value = Dlist[imageIdx].value - Dlist[imageIdx-1].value;
    Dlist[imageIdx].numBits = numberSize(Dlist[imageIdx].value);
    
}
  printf("\n ");
}



void DCoding( Dlist_ *Dlist_r,Dlist_ *Dlist_g, Dlist_ *Dlist_b,unsigned int size) {
  int imageIdx = 0;

  Dlist_b[0].value = Dlist_b[0].value;
  Dlist_g[0].value = Dlist_g[0].value;
  Dlist_r[0].value = Dlist_r[0].value;
  
  for(imageIdx = 1; imageIdx < size/3; imageIdx++) {  
        Dlist_b[imageIdx].value = Dlist_b[imageIdx-1].value + Dlist_b[imageIdx].value;
        Dlist_g[imageIdx].value = Dlist_g[imageIdx-1].value + Dlist_g[imageIdx].value;
        Dlist_r[imageIdx].value = Dlist_r[imageIdx-1].value + Dlist_r[imageIdx].value;
  }
}

void concRGB(unsigned char* image, Dlist_ *Dlist_r,Dlist_ *Dlist_g, Dlist_ *Dlist_b,unsigned int size){
  int i = 1, imageIdx = 0;  
  image[0] = Dlist_b[0].value;
  image[1] = Dlist_g[0].value;
  image[2] = Dlist_r[0].value;	

  for(imageIdx = 3; imageIdx < size; imageIdx += 3) {  
        image[imageIdx] = Dlist_b[i].value;
        image[imageIdx+1] = Dlist_g[i].value;
        image[imageIdx+2] = Dlist_r[i].value;
        i++;
  }
}
