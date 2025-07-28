#include <stdio.h>
#include <stdlib.h>

void ordena(int *numeros, int n){

    int a=0,b,temp;
    
    //caminhando com o b
    if (n <= 1) return;
    for(b=n-1;b>0;b--){
        if(numeros[b] < numeros[a]){
            //trocando
            temp = numeros[a];
            numeros[a] = numeros[b];
            numeros[b] = temp;
            break;
        }
    }
    for(int i=0; i<n;i++){
        printf("%d ",numeros[i]);
    }
    printf("\n");
    //caminhando com o a
    for(a=0;a<b;a++){
        if(numeros[b] < numeros[a]){
            //trocando
            temp = numeros[a];
            numeros[a]= numeros[b];
            numeros[b] = temp;

        }

    }
     for(int i=0; i<n;i++){
        printf("%d ",numeros[i]);
    }
    printf("\n");

    
    //ordenando subvetores
    ordena(numeros,a);
    ordena(numeros+a+1,n-a-1);



};



int main(){

    int numeros[11] = {7,1,1,2,2,5,3,10,9,8,6};

    ordena(numeros,11);

    for(int i=0; i<11;i++){
        printf("%d ",numeros[i]);
    }


    return 0;
}