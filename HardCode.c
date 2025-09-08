#include <stdio.h>

void parSoma(int a[], int tam, int n, int r[]){
    r[0] = -1; 
    r[1] = -1; //caso não exista o par

    
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = i + 1; j < tam; j++)
        {
            if(a[i] + a[j] == n){
                r[0] = i;
                r[1] = j;

                return;
            }
        }
        
    }
    
}

char* sePalindromo(char str[]){
    int iAntes,iDepois,tam = 0;

    while(str[tam] != '\0'){
        tam++;
    }
    

    if(tam % 2 == 0){
        iAntes = (tam/2) - 1;
        iDepois = (tam/2);
    }else{
        iAntes = (tam/2) - 1;
        iDepois = (tam/2) + 1;
    } 

    while((str[iAntes] == str[iDepois]) && (iAntes != -1 && iDepois != tam))
    {
        iAntes--;
        iDepois++;
    }
    
    
    if(iAntes == -1 && iDepois == tam)
        return "True";
    else    
        return "False";
    
}

int buscaNumeroDuplicado(int a[], int tam){
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = i + 1; j < tam; j++)
        {
            if(a[i] == a[j]){
                return a[i];
            }
        }        
    }

    return -1; 
}

int numeroParesDistintos(int a[], int tam){
    int n = 0;
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = i + 1; j < tam; j++)
        {
            if(a[i] != a[j]){
                n += 2; //Tanto par (a,b) como (b,a)
            }
        }        
    }

    return n; 
}

char* seAnagramas(char str1[], char str2[]){
    int tam1 = 0, tam2 = 0, stop = 1;

    for (int i = 0; str1[i] != '\0'; i++)
    {
        tam1++;
    }

    for (int i = 0; str2[i] != '\0'; i++)
    {
        tam2++;
    }

    if(tam1 != tam2) return "False";

    for (int i = 0; i < tam1 - 1; i++)
    {
        for (int j = 0; j < tam1; j++)
        {
            if (str1[i] == str2[j])
            {
                stop = 0;
            }
            
        }
        
        if(stop) return "False";
    }
    
    return "True";
    
}

int main()
{
    int arr[] = {1,3,2,6,4,9}, n;
    int tam = sizeof(arr)/sizeof(arr[0]);
    int r1[2];

    printf("===============================");
    printf("\nEx 1: Encontre se ha dois numeros no array cuja soma seja igual ao valor alvo..");
    printf("\n===============================");
    
    printf("\nArray: [");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("]");
    

    printf("\nDigite um valor: ");
    scanf("%d",&n);

    parSoma(arr, tam, n, r1);
    
    printf("\nResultado: [%d,%d]", r1[0],r1[1]);
    
    printf("\n\n===============================");
    printf("\nEx 2: Verificar se uma palavra eh palindromo.");
    printf("\n=================================");
    
    
    char str1[100], *r2; 
    printf("\nDigite uma palavra: ");
    scanf("%99s",str1);

    r2 = sePalindromo(str1);
    
    printf("\nResultado \"%s\": %s", str1, r2);

    printf("\n\n=================================");
    printf("\nEx 3: Verificar se existe um numero duplicado no array.");
    printf("\n=================================");
    
    int arr2[] = {2,3,56,2,23,51};
    tam = sizeof(arr2)/sizeof(arr2[0]);
    
    printf("\nArray: [");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d ", arr2[i]);
    }
    printf("]");
    
    int r3;
    r3 = buscaNumeroDuplicado(arr2, tam);
    
    printf("\nResultado (se -1, nao existe): %d", r3);


    printf("\n\n=================================");
    printf("\nEx 4: Numero de pares (a,b) diferentes formados por um array.");
    printf("\n=================================");
    
    int arr3[] = {1,3,4};
    tam = sizeof(arr3)/sizeof(arr3[0]);

    printf("\nArray: [");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d ", arr3[i]);
    }
    printf("]");
    
    int r4;
    r4 = numeroParesDistintos(arr3, tam);
    
    printf("\nResultado: %d", r4);


    printf("\n\n=================================");
    printf("\nEx 4: Verifica se uma string eh anagrama da outra.");
    printf("\n=================================");
    
    char str2[100], *r5;

    printf("\nDigite a palavra 1: ");
    scanf("%99s",str1);
    printf("\nDigite a palavra 2: ");
    scanf("%99s",str2);

    r5 = seAnagramas(str1,str2);
    
    printf("\nResultado se \"%s\" e \"%s\" sao anagramas: %s", str1,str2, r5);
    return 0;
}
