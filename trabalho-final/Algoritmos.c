#include <stdio.h>
#include <stdlib.h>

void combSort(int arr[], int n){
    const double shrink = 1.3;
    int gap = n;
    int swapped = 1;
    while (gap > 1 || swapped) {
        gap = (int)(gap / shrink);
        if (gap < 1) gap = 1;
        swapped = 0;
        for (int i = 0; i + gap < n; ++i) {
            if (arr[i] > arr[i + gap]) {
                int tmp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = tmp;
                swapped = 1;
            }
        }
    }
}



/* merge usando buffer temporário (índices inclusivos l..r) */
static void merge(int a[], int temp[], int l, int m, int r){
    int i = l, j = m + 1;
    int len = r - l + 1;
    
    int k = 0;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    /* copiar de volta para a posição correta */
    for (int t = 0; t < len; ++t) a[l + t] = temp[t];
    
}

/* recursiva que usa um único buffer; inclui cutoff e verificação de já-ordenado */
void mergeSort(int a[], int temp[], int l, int r){
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, temp, l, m);
    mergeSort(a, temp, m + 1, r);
    if (a[m] <= a[m + 1]) return; /* já ordenado */
    merge(a, temp, l, m, r);
}


void combMergeSortHybrid(int a[], int temp[], int l, int r, int cutoff) {
    if (l >= r) return;
    int size = r - l + 1;
    if (size <= cutoff) {
        combSort(a + l, size); /* ordenar somente o subvetor a[l..r] */
        return;
    }
    
    int m = l + (r - l) / 2;
    /* chamar recursivamente o híbrido para propagar o cutoff */
    combMergeSortHybrid(a, temp, l, m, cutoff);
    combMergeSortHybrid(a, temp, m + 1, r, cutoff);

    if (a[m] <= a[m + 1]) return; /* já ordenado */
    merge(a, temp,l, m, r); /* fazer o merge correto */
}

