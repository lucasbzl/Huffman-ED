#ifndef HASH_H
#define HASH_H




typedef struct hash Cel;
typedef void (*desalocadado)(void *dado);

Cel *criaCel(void *dado,desalocadado desal);
Cel **criaHash(int tamanho);
void desalocaCel(Cel *h);
void insereCel(Cel *h, Cel *h2);
int funcHash(unsigned char dado,int tamanho);
void insereVetor(Cel **hash,Cel *c,int tamanho);
void desalocaHash(Cel **hash,int tamanho);
Cel *getCelHash(Cel **hash, unsigned char byte,int tamanho);
void *getdadoCel(Cel *c);
#endif