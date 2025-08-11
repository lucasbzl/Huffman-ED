#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_MAX 20000
#define NOME_ARQUIVO "entrada.bin"

int main() {
    FILE *arquivo;
    unsigned char byte;
    int i, tamanho;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Define um tamanho aleatório até 500 bytes
    tamanho = rand() % TAMANHO_MAX + 1; // de 1 a 500

    // Abre o arquivo para escrita binária
    arquivo = fopen(NOME_ARQUIVO, "wb");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        return 1;
    }

    // Escreve bytes aleatórios no arquivo
    for (i = 0; i < tamanho; i++) {
        byte = rand() % 256; // byte entre 0 e 255
        fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    }

    fclose(arquivo);

    printf("Arquivo '%s' criado com %d bytes.\n", NOME_ARQUIVO, tamanho);
    return 0;
}
