#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "bitmap.h"

#define Nomearq "biblia.txt"


int main(){
    long tamanho = 0;
    unsigned char *tester = getConteudoArq(Nomearq, &tamanho);
    Celula **tabela = (Celula**)malloc(sizeof(Celula*)*256);
    int n = 0,t=0;

    tArvore *arv = transformaBinArv(tester, (int) tamanho);
    criaTabela(arv,NULL,tabela, &n);
    
    FILE *comprimido = fopen("comprimido.bin","wb");

    bitmap *bits = bitmapInit(tamanho*8);

    //percorre a string
    for(int i=0;i<tamanho;i++){

        //acha a celula na tabela
        for(t=0;t<n;t++){
            if(getByueCelula(tabela[t])==tester[i]) break;
        }
        //imprime no arquivo comprimido
            bitmap *temp = getBmCelula(tabela[t]);
            for(int q=0;q<bitmapGetLength(temp);q++)
                bitmapAppendLeastSignificantBit(bits,bitmapGetBit(temp,q));
            
        
    }
    fwrite(bitmapGetContents(bits), 1, (bitmapGetLength(bits)+7)/8, comprimido);

    fclose(comprimido);


    return 0;
}