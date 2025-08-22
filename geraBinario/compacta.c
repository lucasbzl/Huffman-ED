#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "hash.h"
#include <time.h> 


int main(int agrgc , char *argv[]){

    clock_t start, end;
    start = clock();
    double cpu_time_used;
    

    long tamanho = 0;
    unsigned char *tester = getConteudoArq(argv[1], &tamanho);
    Cel **tabela = criaHash(256);

    tArvore *arv = transformaBinArv(tester, (int) tamanho);
   
    bitmap *bmarv = salvaArvore(arv,NULL);
    
    criaTabela(arv,NULL,tabela, 256);

    

    bitmap *bits = bitmapInit(bitmapGetLength(bmarv) + tamanho * 8);
    
    //coloca a arvore dentro do bitmap de saida
    for(int t=0;t<bitmapGetLength(bmarv);t++){

        bitmapAppendLeastSignificantBit(bits,bitmapGetBit(bmarv,t));

    }
   
    //percorre a string
    for(int i=0;i<tamanho;i++){

        //imprime no arquivo comprimido
            Cel *c = tabela[tester[i]];
        
            bitmap *temp = getBmCelula(getdadoCel(c));

            for(int q=0;q<bitmapGetLength(temp);q++)
                bitmapAppendLeastSignificantBit(bits,bitmapGetBit(temp,q));
    }

   

    char *nomeArq = strcat(argv[1],".comp");
    FILE *comprimido = fopen(nomeArq,"wb");

    bitmapLibera(bmarv);
    desalocaArvore(arv);
    desalocaHash(tabela,256);
    free(tester);
    
    char inutil = bitmapGetLength(bits)%8;
    
    fwrite(&inutil, 1, 1, comprimido);
    fwrite(bitmapGetContents(bits), 1, (bitmapGetLength(bits)+7)/8, comprimido);

    fclose(comprimido);
    bitmapLibera(bits);
    
    
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.3f segundos\n", cpu_time_used);


    return 0;
}