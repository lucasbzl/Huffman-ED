#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

struct arvore{

    tArvore *dir;
    tArvore *esq;
    char letra;
    int n;

};

tArvore *criaArvore(char letra, int n,tArvore *dir, tArvore *esq){

    tArvore *a = (tArvore*)malloc(sizeof(tArvore)); 

    a->letra = letra;
    a->dir = dir;
    a->esq = esq;
    a->n = n;
    return a;
}

void desalocaArvore(tArvore *a){

    free(a);

}

void ordenaArvores(tArvore **arvores,int n){

    int a=0,b;
    tArvore *temp; //pivos

    if(n<=1) return;
    //caminhando com o b
    for(b=n-1,b>0;b--){
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
    int tamanho = (int)strlen[string];
    int *indices = calloc(128,sizeof(int)); //inicializados como 0
    
    //contando quantos caracteres tem de cada e vendo quantos repetidos
    while (x<tamanho){
        indices[(int)string[x]]+=1;
        if(indices[(int)string[x]]>1) repetidos++;
        x++;
    }

    //fazendo a reducao de um vetor de 128 pra um menor
    tArvore arvores = malloc(sizeof(tArvore*)*(tamanho-repetidos));
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



    tArvore *a = criaArvore(NULL,NULL);
    return a;
}











tArvore *insere(tArvore *r, int letra){

    if(r == NULL){
        r = (tArvore*)malloc(sizeof(tArvore));
        r->letra = letra;
        r->dir = r->esq = NULL;
    }
    else if(letra>r->letra) r->dir = insere(r->dir,letra);
    else r->esq = insere(r->esq,letra);
    return r;

}

tArvore *busca(tArvore *r,char letra){

    if(r==NULL) return NULL;
    else if(letra>r->letra) return busca(r->dir,letra);
    else return busca(r->esq,letra);

}


//folha
//um filho
//dois filhos

tArvore *retira(tArvore *r, int letra){

    if(r==NULL) return NULL;
    else if(letra>r->letra) r->dir = retira(r->dir,letra);
    else if(letra<r->letra) r->esq = retira(r->esq,letra);
    else{

        if(r->dir==NULL && r->esq==NULL){
            free(r);
            r=NULL;
        }
        else if(r->esq == NULL){
            tArvore *temp =r;
            r = r->dir;
            free(temp);

        }
        else if(r->dir == NULL){
            tArvore *temp =r;
            r = r->esq;
            free(temp);
        }
        else{

            tArvore *temp = r->esq;
            while(temp->dir!=NULL) temp = temp->dir;

            r->letra = temp->letra;
            temp->letra = letra;
            r->esq = retira(r->esq,letra);

        }
    }
    return r;

}