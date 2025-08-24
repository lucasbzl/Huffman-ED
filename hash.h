/**
 * @file hash.h
 * @author Lucas Bastos
 *          Mateus Lizardo
 * @brief TAD que contém as funções da tabela Hash, que armazena as informações da árvore de Huffman
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HASH_H
#define HASH_H

/**
 * @brief Estrutura da célula da hash.
 */
typedef struct hash Cel;

/**
 * @brief Ponteiro para função de desalocação de dados.
 */
typedef void (*desalocadado)(void *dado);

/**
 * @brief Cria uma nova célula da hash.
 * 
 * @param dado Ponteiro para o dado a ser armazenado.
 * @param desal Função para desalocar o dado.
 * @return Cel* Ponteiro para a célula criada.
 */
Cel *criaCel(void *dado,desalocadado desal);

/**
 * @brief Cria uma tabela hash.
 * 
 * @param tamanho Tamanho da tabela.
 * @return Cel** Ponteiro para o vetor de ponteiros de células.
 */
Cel **criaHash(int tamanho);

/**
 * @brief Desaloca uma célula da hash.
 * 
 * @param h Ponteiro para a célula.
 */
void desalocaCel(Cel *h);

/**
 * @brief Insere uma célula em outra (lista encadeada).
 * 
 * @param h Ponteiro para a célula principal.
 * @param h2 Ponteiro para a célula a ser inserida.
 */
void insereCel(Cel *h, Cel *h2);

/**
 * @brief Função de hash para obter o índice a partir de um byte.
 * 
 * @param dado Byte a ser usado como chave.
 * @param tamanho Tamanho da tabela hash.
 * @return int Índice calculado.
 */
int funcHash(unsigned char dado,int tamanho);

/**
 * @brief Insere uma célula no vetor da tabela hash.
 * 
 * @param hash Ponteiro para o vetor da hash.
 * @param c Ponteiro para a célula a ser inserida.
 * @param tamanho Tamanho da tabela hash.
 */
void insereVetor(Cel **hash,Cel *c,int tamanho);

/**
 * @brief Desaloca toda a tabela hash.
 * 
 * @param hash Ponteiro para o vetor da hash.
 * @param tamanho Tamanho da tabela hash.
 */
void desalocaHash(Cel **hash,int tamanho);

/**
 * @brief Busca uma célula na hash pelo byte.
 * 
 * @param hash Ponteiro para o vetor da hash.
 * @param byte Byte a ser buscado.
 * @param tamanho Tamanho da tabela hash.
 * @return Cel* Ponteiro para a célula encontrada ou NULL.
 */
Cel *getCelHash(Cel **hash, unsigned char byte,int tamanho);

/**
 * @brief Obtém o dado armazenado em uma célula.
 * 
 * @param c Ponteiro para a célula.
 * @return void* Ponteiro para o dado.
 */
void *getdadoCel(Cel *c);

#endif