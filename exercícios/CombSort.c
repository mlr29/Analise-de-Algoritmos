#include <stdio.h>
#include <stdlib.h>

void combSort(int arr[], int n){

    int intervalo = (int) (n / 1.3);
    int i;

    while (intervalo > 0)
    {
        i = 0;
        while (intervalo > 0 && i < n - intervalo)
        {
            if(arr[i] > arr[i + intervalo]){
                arr[i] += arr[i + intervalo] ;
                arr[i + intervalo] = arr[i] - arr[i + intervalo];
                arr[i] = arr[i] - arr[i + intervalo];
            }

            i++;
        }

        intervalo = (int) (intervalo / 1.3);
    }
    
}

int main(){
    
    int arr[] = {5,4,3,2,1}, tam = 5;

    combSort(arr, tam);

    printf("\nArray Ordenado: ");
    for (int i = 0; i < tam; i++)
    {
        printf("[%d]:%d ",i,arr[i]);
    }

    return 0;
}