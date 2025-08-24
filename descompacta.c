/**
 * @file descompacta.c
 * @author Lucas Bastos
 *          Mateus Lizardo
 * @brief Descompacta um arquivo previamente compactado
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "hash.h"
#include <time.h> 



int main(int argc , char *argv[]){

    long tamanho = 0;
    //Le o arquivo compactado
    unsigned char *tester = getConteudoArq(argv[1], &tamanho);
    long n = 8;

    int inuteis = tester[0];
    tamanho--;

    //le a arvore que foi escrita no começo do arquivo comprimido
    tArvore *r = leArvore(tester,NULL,&n);

     //traduz a codificação de huffman para o arquivo descomprimido
   
    for(int i=strlen(argv[1])-5;i<strlen(argv[1]);i++){
            argv[1][i] = '\0';
        }

    FILE *descomprimido = fopen(argv[1],"wb");
    

    imprime(tester,tamanho,descomprimido,r,&n,inuteis);




    fclose(descomprimido);
    free(tester);
    desalocaArvore(r);


    return 0;
}