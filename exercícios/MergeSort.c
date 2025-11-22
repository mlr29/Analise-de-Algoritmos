#include <stdio.h>
#include <stdlib.h>

int passos = 0;

void merge(int a[], int inic, int meio, int fim) {
    int n1 = meio - inic + 1;
    int n2 = fim - meio;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; ++i) L[i] = a[inic + i];
    for (int j = 0; j < n2; ++j) R[j] = a[meio + 1 + j];

    int i = 0, j = 0, k = inic;
    while (i < n1 && j < n2) {
        passos++;
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int a[], int inic, int fim){
    
    int meio = (inic + fim)/2;
    if(inic >= fim) return;

    mergeSort(a, inic, meio);
    mergeSort(a, meio + 1, fim);

    merge(a, inic, meio, fim);

    return;
}

int main(){
    int array[] = {3,1,4,2,12,21,344,34,17,67}, tam = 10;
    printf("\n==== Ex5: Implementacao Merge Sort ========");
    printf("\n\nArray: ");

    for (int i = 0; i < tam; i++)
    {
        printf("[%d]:%d ",i,array[i]);
    }
    
    mergeSort(array,0,tam - 1);
    printf("\n\nApos ordenacao:\n");

    printf("\nArray: ");
    for (int i = 0; i < tam; i++)
    {
        printf("[%d]:%d ",i,array[i]);
    }

    printf("\n\nQuantidade de Passos: %d", passos);
    return 0;
}