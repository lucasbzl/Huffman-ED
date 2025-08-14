#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "bitmap.h"
#include "hash.h"
#include <time.h> 

#define Nomearq "comprimido.bin"


int main(){

    long tamanho = 0;
    unsigned char *tester = getConteudoArq(Nomearq, &tamanho);
    long *n = 0;

    bitmap *bits = bitmapInit(tamanho*8);
    tArvore *r = leArvore(tester,NULL,n);
    
    
    FILE *descomprimido = fopen("descomprimido.bin","wb");

    imprime(tester,tamanho,descomprimido,r,n);




    fclose(descomprimido);
    free(tester);
    desalocaArvore(r);
    return 0;
}