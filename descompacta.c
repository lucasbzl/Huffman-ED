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
    long n = 0;

    bitmap *bits = bitmapInit(tamanho*8);
    printf("passou\n");
    Cel **hash = criaHash(256);
    tArvore *r = leArvore(tester,NULL,&n);
    criaTabela(r,bits,hash,tamanho);
     printf("passou2\n");
    
    FILE *descomprimido = fopen("descomprimido.bin","wb");

    imprime(tester,tamanho,descomprimido,r,&n);




    fclose(descomprimido);
    free(tester);
    desalocaArvore(r);
    desalocaHash(hash,256);
    //bitmapLibera(bits);
    return 0;
}