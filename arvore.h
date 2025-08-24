/**
 * @file arvore.h
 * @author Lucas Bastos
 *          Mateus Lizardo
 * @brief TAD que contém todas as funções relacionadas à árvore de codificação de Huffman
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ARVORE_H
#define ARVORE_H

#include "bitmap.h"
#include "hash.h"

//A árvore binária
typedef struct arvore tArvore;

typedef struct celula Celula;

/**
 * @brief Aloca um nó da árvore
 * 
 * @param letra 
 * @param n 
 * @param dir 
 * @param esq 
 * @return tArvore* 
 */
tArvore *criaArvore(char letra, int n, tArvore *dir, tArvore *esq);

/**
 * @brief Libera a memória alocada para a árvore de Huffman.
 * 
 * @param a Ponteiro para a raiz da árvore.
 */
void desalocaArvore(tArvore *a);

/**
 * @brief Ordena um vetor de árvores de acordo com a frequência dos nós.
 * 
 * @param arvores Vetor de ponteiros para árvores.
 * @param n Tamanho do vetor.
 */
void ordenaArvores(tArvore **arvores, int n);

/**
 * @brief Junta as duas árvores de menor frequência em uma nova árvore.
 * 
 * @param arvores Vetor de ponteiros para árvores.
 * @param n Tamanho do vetor.
 * @return tArvore* Ponteiro para a nova árvore criada.
 */
tArvore *juntaArvores(tArvore **arvores, int n);

/**
 * @brief Constrói uma árvore binária a partir de um conteúdo serializado.
 * 
 * @param conteudo Vetor de bytes representando a árvore.
 * @param tamanho Tamanho do vetor.
 * @return tArvore* Ponteiro para a árvore reconstruída.
 */
tArvore *transformaBinArv(unsigned char *conteudo, int tamanho);

/**
 * @brief Verifica se um nó da árvore é folha.
 * 
 * @param a Ponteiro para o nó da árvore.
 * @return int 1 se for folha, 0 caso contrário.
 */
int ehFolha(tArvore *a);

/**
 * @brief Cria a tabela de códigos de Huffman a partir da árvore.
 * 
 * @param r Ponteiro para a raiz da árvore.
 * @param bm Bitmap auxiliar para armazenar o caminho.
 * @param hash Tabela hash para armazenar os códigos.
 * @param tamanho Tamanho da tabela hash.
 */
void criaTabela(tArvore *r, bitmap  *bm, Cel **hash, int tamanho);

/**
 * @brief Lê o conteúdo de um arquivo e armazena em um vetor de bytes.
 * 
 * @param nomeArq Nome do arquivo.
 * @param tamanho Ponteiro para armazenar o tamanho do arquivo lido.
 * @return unsigned char* Vetor de bytes com o conteúdo do arquivo.
 */
unsigned char *getConteudoArq(char *nomeArq, long *tamanho);

/**
 * @brief Obtém o byte armazenado em uma célula.
 * 
 * @param c Ponteiro para a célula.
 * @return unsigned char Byte armazenado.
 */
unsigned char getByueCelula(Celula *c);

/**
 * @brief Obtém o bitmap armazenado em uma célula.
 * 
 * @param c Ponteiro para a célula.
 * @return bitmap* Ponteiro para o bitmap.
 */
bitmap *getBmCelula(Celula *c);

/**
 * @brief Função para desalocar uma célula (usada como callback).
 * 
 * @param c Ponteiro para a célula a ser desalocada.
 */
void desalocaCelula(void *c);

/**
 * @brief Serializa a árvore de Huffman em um bitmap.
 * 
 * @param r Ponteiro para a raiz da árvore.
 * @param bm Bitmap onde a árvore será salva.
 * @return bitmap* Bitmap resultante.
 */
bitmap *salvaArvore(tArvore *r, bitmap *bm);

/**
 * @brief Obtém o valor de um bit em uma string de bytes.
 * 
 * @param string Vetor de bytes.
 * @param index Índice do bit.
 * @return unsigned char Valor do bit (0 ou 1).
 */
unsigned char getBitString(unsigned char *string,long index);

/**
 * @brief Lê uma árvore serializada a partir de uma string de bits.
 * 
 * @param string Vetor de bytes com a árvore serializada.
 * @param r Ponteiro para a árvore (pode ser NULL).
 * @param bitslidos Ponteiro para o contador de bits lidos.
 * @return tArvore* Ponteiro para a árvore reconstruída.
 */
tArvore *leArvore(unsigned char *string,tArvore *r,long *bitslidos);

/**
 * @brief Imprime o conteúdo decodificado a partir de uma string de bits usando a árvore de Huffman.
 * 
 * @param string Vetor de bytes com os dados codificados.
 * @param tamanho Tamanho do vetor.
 * @param f Ponteiro para o arquivo de saída.
 * @param r Ponteiro para a árvore de Huffman.
 * @param lidos Ponteiro para o contador de bits lidos.
 * @param inuteis Número de bits inuteis no final.
 */
void imprime(unsigned char *string, long tamanho,FILE *f,tArvore *r,long *lidos,int inuteis);

#endif