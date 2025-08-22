#ifndef ARVORE_H
#define ARVORE_H

#include "bitmap.h"
#include "hash.h"
typedef struct arvore tArvore;
typedef struct celula Celula;

tArvore *criaArvore(char letra, int n, tArvore *dir, tArvore *esq);
void desalocaArvore(tArvore *a);
void ordenaArvores(tArvore **arvores, int n);
tArvore *juntaArvores(tArvore **arvores, int n);
tArvore *transformaBinArv(unsigned char *conteudo, int tamanho);
int ehFolha(tArvore *a);
void criaTabela(tArvore *r, bitmap  *bm, Cel **hash, int tamanho);
unsigned char *getConteudoArq(char *nomeArq, long *tamanho);
unsigned char getByueCelula(Celula *c);
bitmap *getBmCelula(Celula *c);
void desalocaCelula(void *c);
bitmap *salvaArvore(tArvore *r, bitmap *bm);
unsigned char getBitString(unsigned char *string,long index);
tArvore *leArvore(unsigned char *string,tArvore *r,long *bitslidos);
void imprime(unsigned char *string, long tamanho,FILE *f,tArvore *r,long *lidos,int inuteis);

#endif