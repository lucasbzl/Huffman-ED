#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "hash.h"

struct arvore{

    struct arvore *dir;
    struct arvore *esq;
    unsigned char letra;
    int n;

};

struct celula{

    unsigned char byte;
    bitmap *reduzido;

};

unsigned char getByueCelula(Celula *c){
    return c->byte;
}
bitmap *getBmCelula(Celula *c){
    return c->reduzido;
}
void desalocaCelula(void *c){
    Celula *c2 = c;
    bitmapLibera(c2->reduzido);
    free(c2);
}

Celula *criaCelula(unsigned char byte, bitmap *bm){

    Celula *c = (Celula*)malloc(sizeof(Celula));

    c->byte = byte;
    c->reduzido = bm;

    return c;
}

tArvore *criaArvore(char letra, int n,tArvore *dir, tArvore *esq){

    tArvore *a = (tArvore*)malloc(sizeof(tArvore)); 

    a->letra = letra;
    a->dir = dir;
    a->esq = esq;
    a->n = n;
    return a;
}

void desalocaArvore(tArvore *a){
    if(a->dir!=NULL) desalocaArvore(a->dir);
    if(a->esq!=NULL) desalocaArvore(a->esq);
    free(a);


}

void ordenaArvores(tArvore **arvores,int n){

    int a=0,b;
    tArvore *temp; //pivos

    if(n<=1) return;
    //caminhando com o b
    for(b=n-1;b>0;b--){
        if(arvores[b]->n < arvores[a]->n){
            //trocando
            temp = arvores[a];
            arvores[a] = arvores[b];
            arvores[b] = temp;
            break;
        }
    }
        //caminhando com o a
        for(a=0;a<b;a++){

            if(arvores[b]->n < arvores[a]->n){
                //trocando
                temp = arvores[a];
                arvores[a]= arvores[b];
                arvores[b] = temp;
            }

        }

    
    //ordenando subvetores
    ordenaArvores(arvores,a);
    ordenaArvores(arvores+a+1,n-a-1);
}

tArvore *juntaArvores(tArvore **arvores,int n){

    if(n<=1) return arvores[0];
    tArvore *temp = criaArvore('\0',arvores[0]->n + arvores[1]->n,arvores[1],arvores[0]);

    
    for(int i=0;i<n-2;i++){
        arvores[i] = arvores[i+2];
    }
    arvores[n-2] = temp;

    return juntaArvores(arvores,n-1);
}

tArvore *transformaStringArv(char *string){

    int x =0,repetidos = 0;
    int tamanho = (int)strlen(string);
    int *indices = calloc(128,sizeof(int)); //inicializados como 0
    
    //contando quantos caracteres tem de cada e vendo quantos repetidos
    while (x<tamanho){
        indices[(int)string[x]]+=1;
        if(indices[(int)string[x]]>1) repetidos++;
        x++;
    }

    //fazendo a reducao de um vetor de 128 pra um menor
    tArvore **arvores = malloc(sizeof(tArvore*)*(tamanho-repetidos));
    int ind = 0;

    for(int i=0;i<128;i++){

        if(indices[i]!=0){
            arvores[ind] = criaArvore((char)i,indices[i],NULL,NULL);
            ind++;
        } 
        
    }
    free(indices);

    //ordenando o vetor de arvores
    ordenaArvores(arvores,tamanho-repetidos);
    tArvore *temp;
    temp = juntaArvores(arvores,tamanho-repetidos);
    free(arvores);


    return temp;
}

tArvore *transformaBinArv(unsigned char *conteudo, int tamanho){
    int x =0, repetidos = 0;
    
    int *indices = calloc(256,sizeof(int)); //inicializados como 0

    //contando quantos caracteres tem de cada e vendo quantos repetidos
    while (x<tamanho){
        indices[conteudo[x]]+=1;
        if(indices[(int)conteudo[x]]>1) repetidos++;
        x++;
    }

    tArvore **arvores = malloc(sizeof(tArvore*)*(tamanho - repetidos));
    int ind = 0;

    for(int i=0;i<256;i++){

        if(indices[i] > 0){
            arvores[ind] = criaArvore((char)i,indices[i],NULL,NULL);
            ind++;
        } 
        
    }

    free(indices);

    //ordenando o vetor de arvores
    ordenaArvores(arvores,tamanho-repetidos);
    tArvore *temp;
    temp = juntaArvores(arvores,tamanho-repetidos);
    free(arvores);


    return temp;
}

int ehFolha(tArvore *a){

    if(a->dir==NULL && a->esq==NULL) return 1;
    else return 0;

}

void criaTabela(tArvore *r, bitmap  *bm, Cel **hash, int tamanho){

    if(ehFolha(r)){

        Celula *c = criaCelula(r->letra,bm);
        Cel *c2 = criaCel(c,desalocaCelula);
        insereVetor(hash,c2,tamanho);

        printf("(%c) %d- ",r->letra,bitmapGetLength(bm));
        
        for(int i=0;i<bitmapGetLength(bm);i++){
            printf("%d",bitmapGetBit(bm,i));
        }
        printf("\n");
        //bitmapLibera(bm);
    }
    else{
        bitmap *bdir = bitmapInit(8);
        if(bm != NULL){
            for(int i=0;i<bitmapGetLength(bm);i++){
                bitmapAppendLeastSignificantBit(bdir,bitmapGetBit(bm,i));
            }
        }
        bitmapAppendLeastSignificantBit(bdir,1);
        criaTabela(r->dir,bdir, hash, tamanho);

        bitmap *besq = bitmapInit(8);
        if(bm != NULL){
            for(int i=0;i<bitmapGetLength(bm);i++){
                bitmapAppendLeastSignificantBit(besq,bitmapGetBit(bm,i));
            }
        }
        bitmapAppendLeastSignificantBit(besq,0);
        criaTabela(r->esq,besq,hash,tamanho);

        if(bm!=NULL)bitmapLibera(bm);
    }
    
}


unsigned char *getConteudoArq(char *nomeArq, long *tamanho){
    FILE *f = fopen(nomeArq, "rb");
    fseek(f, 0, SEEK_END);
    *tamanho = ftell(f);
    rewind(f);

    unsigned char *dados = malloc(*tamanho);
    fread(dados, 1, *tamanho, f);

    fclose(f);

    return dados;
}

//<*<*<A><*<B><C>>><D>>
// < 01
// > 10
bitmap *salvaArvore(tArvore *r, bitmap *bm){
    bitmap *bm2;

    if(bm==NULL) bm2 = bitmapInit(6132);
    else bm2 = bm;

    //escreve <
    bitmapAppendLeastSignificantBit(bm2,0);
    bitmapAppendLeastSignificantBit(bm2,1); 

    //escreve a letra
    for(int i=7; i>=0; i--){
        int bit = (r->letra >> i) & 1;
        bitmapAppendLeastSignificantBit(bm2, bit);
    }
    //faz na esquerda e depois na direita
    if(r->esq!=NULL)salvaArvore(r->esq,bm2);
    if(r->dir!=NULL)salvaArvore(r->dir,bm2);
    //escreve >
    bitmapAppendLeastSignificantBit(bm2,1);
    bitmapAppendLeastSignificantBit(bm2,0);

    return bm2;
}

unsigned char getBitString(unsigned char *string,long index){
    return (string[index/8] >> (7-(index%8))) & 0x01;

}
//<*<*<A><*<B><C>>><D>>
tArvore *leArvore(unsigned char *string,tArvore *r,long *bitslidos){
   
    if(r==NULL){
        r = criaArvore('\0',0,NULL,NULL);
    }
    
    //comeca com 0 1 = <

    if(getBitString(string,*bitslidos)==0 && getBitString(string,*bitslidos+1)==1){
        
        bitmap *bm = bitmapInit(8);
        for(int i =2; i< 10; i++){
            bitmapAppendLeastSignificantBit(bm,getBitString(string,*bitslidos+i));
        }
        *bitslidos += 10;

        unsigned char c = *(bitmapGetContents(bm));
        r->letra = c;
        printf("char :%c, bitslidos: %ld\n",c,*bitslidos);
        bitmapLibera(bm);
        r->esq = leArvore(string,r->esq,bitslidos);
        r->dir = leArvore(string,r->dir,bitslidos);
        *bitslidos += 2;
        return r;
    }
    else  return NULL;
     
}



void imprime(unsigned char *string, long tamanho,FILE *f,tArvore *r,long *lidos){


    tArvore *ar = r;
    bitmap *bm = bitmapInit(tamanho*16);
    for(long i=*lidos;i<tamanho*8;i++){
        
        if(getBitString(string,i)==0) ar = ar->esq;
        else ar = ar->dir;

        if(ehFolha(ar)){
            for(int q=7; q>=0; q--){
                bitmapAppendLeastSignificantBit(bm, (ar->letra >> q) & 1);
            }
            ar = r;
        }


    }

    fwrite(bitmapGetContents(bm), 1, (bitmapGetLength(bm)+7)/8, f);
    bitmapLibera(bm);

}