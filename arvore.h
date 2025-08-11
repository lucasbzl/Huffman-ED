#ifndef ARVORE_H
#define ARVORE_H

#include "bitmap.h"
typedef struct arvore tArvore;
typedef struct celula Celula;

tArvore *criaArvore(char letra, int n, tArvore *dir, tArvore *esq);
void desalocaArvore(tArvore *a);
void ordenaArvores(tArvore **arvores, int n);
tArvore *juntaArvores(tArvore **arvores, int n);
tArvore *transformaStringArv(char *string);
tArvore *transformaBinArv(unsigned char *conteudo, int tamanho);
int ehFolha(tArvore *a);
char *traduzBits(tArvore *r, bitmap *bm);
void criaTabela(tArvore *r, bitmap  *bm, Celula **tabela, int *n);
unsigned char *getConteudoArq(char *nomeArq, long *tamanho);
unsigned char getByueCelula(Celula *c);
bitmap *getBmCelula(Celula *c);

#endif