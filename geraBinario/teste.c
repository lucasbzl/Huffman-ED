#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Quicksort com a lógica que você passou, mas em int
void ordenaInt(int *v, int n) {
    int i = 0, j;
    int temp; 

    if (n <= 1) return;

    // caminhando com o b
    for (j = 0, i = -1; j <n; j++) {
        if (v[j] <= v[n-1]) {
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            
        }
    }
    
    // ordenando recursivamente os subvetores
    ordenaInt(v, i);
    ordenaInt(v + i + 1, n - i - 1);
}

int main() {
    srand(time(NULL));
    int n = 20;  // quantidade de números aleatórios
    int *v = malloc(n * sizeof(int));

    // criando números aleatórios
    printf("Vetor original:\n");
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100; // valores entre 0 e 99
        printf("%d ", v[i]);
    }
    printf("\n");

    // ordenando
    ordenaInt(v, n);

    // imprimindo resultado
    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);
    return 0;
}
