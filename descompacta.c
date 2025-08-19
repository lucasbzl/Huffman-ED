#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "hash.h"
#include <time.h> 



int main(int agrgc , char *argv[]){

    long tamanho = 0;
    unsigned char *tester = getConteudoArq(argv[1], &tamanho);
    long n = 0;

    bitmap *bits = bitmapInit(tamanho*8);
    tArvore *r = leArvore(tester,NULL,&n);

     
    char *nomeArq = strcat(argv[1],".descomp");
    FILE *descomprimido = fopen(nomeArq,"wb");

    imprime(tester,tamanho,descomprimido,r,&n);




    fclose(descomprimido);
    free(tester);
    bitmapLibera(bits);
    desalocaArvore(r);


    return 0;
}