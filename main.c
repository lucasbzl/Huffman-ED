#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "bitmap.h"
#include "hash.h"
#include <time.h> 

#define Nomearq "biblia.txt"







int main(){

    clock_t start, end;
    start = clock();
    double cpu_time_used;

    long tamanho = 0;
    unsigned char *tester = getConteudoArq(Nomearq, &tamanho);
    Cel **tabela = criaHash(256);

    tArvore *arv = transformaBinArv(tester, (int) tamanho);
    criaTabela(arv,NULL,tabela, 256);
    
    FILE *comprimido = fopen("comprimido.bin","wb");

    bitmap *bits = bitmapInit(tamanho*8);

    //percorre a string
    for(int i=0;i<tamanho;i++){

        /*//acha a celula na tabela
        for(t=0;t<n;t++){
            if(getByueCelula(tabela[t])==tester[i]) break;
        }*/
        //imprime no arquivo comprimido
            Cel *c = tabela[tester[i]];
        
            bitmap *temp = getBmCelula(getdadoCel(c));

            for(int q=0;q<bitmapGetLength(temp);q++)
                bitmapAppendLeastSignificantBit(bits,bitmapGetBit(temp,q));
            
        
    }
    fwrite(bitmapGetContents(bits), 1, (bitmapGetLength(bits)+7)/8, comprimido);

    fclose(comprimido);

    desalocaHash(tabela,256);
    bitmapLibera(bits);
    desalocaArvore(arv);
    free(tester);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.3f segundos\n", cpu_time_used);


    return 0;
}