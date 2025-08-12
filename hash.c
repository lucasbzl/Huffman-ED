#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

struct hash{
    void *dado;
    Cel *prox;
    desalocadado desaloca;
};


Cel *criaCel(void *dado,desalocadado desal){

    Cel *h = (Cel*) malloc(sizeof(Cel));
    h->dado = dado;
    h->prox = NULL;
    h->desaloca = desal;
    return h;

}
Cel **criaHash(int tamanho){

    Cel **hash = (Cel**)malloc(sizeof(Cel*)*tamanho);

    for(int i=0;i<tamanho;i++){
        hash[i] = NULL;
    }

    return hash;

}

void desalocaCel(Cel *h){

    if(h->prox!=NULL) desalocaCel(h->prox);
    
    if(h->desaloca!=NULL)h->desaloca(h->dado);
    free(h);
}


int funcHash(unsigned char dado,int tamanho){

    return dado%tamanho;

}

void insereVetor(Cel **hash,Cel *c,int tamanho){

    unsigned char *l = (c->dado);
    //printf("inserido na posição: %d\n",funcHash(*l,tamanho));
    unsigned char byte = *(unsigned char*)c->dado;
    Cel *h = hash[byte];

    if(h == NULL){
        //printf("inserindo no começo\n");
        hash[byte] = c;
    }else{
        Cel *temp, *temp2=NULL;

        for(temp = h;temp2!=NULL;temp = temp2){
            temp2 = temp->prox;
        }   

        temp->prox = c;
    }




}

void desalocaHash(Cel **hash,int tamanho){

    for(int i = 0; i<tamanho;i++){
        if(hash[i]!=NULL)desalocaCel(hash[i]);
    }
    free(hash);
}

Cel *getCelHash(Cel **hash, unsigned char byte,int tamanho){
   // printf("acessando posição: %d\n",funcHash(byte,tamanho));
   
    return hash[funcHash(byte,tamanho)];

}
void *getdadoCel(Cel *c){
    return c->dado;
}