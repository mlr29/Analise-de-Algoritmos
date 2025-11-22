#include <stdio.h>
#include <string.h>

long long int mapearCaminhosMxNDinamico(int m, int n){
    long long int cache[m][n];
    int i, j;

    if (m == 0 || n == 0 )
    {
        return 0;
    }
    
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {   
            if ((i == 1 ) || (j == 1) )
            {
                cache[i][j] = 1;
            } else {
                cache[i][j] = cache[i - 1][j] + cache[i][j - 1];
            }  
        }
        
    }
    
    return cache[m][n];
    
}

long long int nFormasSubirEscadaDinamico(int n){
    long long int nFormas[n];

    for(int i = 0; i <= n; i++){
        if (i == 0){
            nFormas[0] = 1;
        } else if(i == 1){
            nFormas[1] = 1;
        }else{
            nFormas[i] = nFormas[i-2] + nFormas[i-1];
        }    
        
    }   
        
    return nFormas[n];
    
}

char* somaSubconjuntoDinamico(int a[], int tam, int n){
    int dp[tam+1][n+1];

    // Inicializa a tabela
    for (int i = 0; i <= tam; i++)
        dp[i][0] = 1; // Soma zero sempre possível

    for (int j = 1; j <= n; j++)
        dp[0][j] = 0; // Com zero elementos, só soma zero é possível

    // Preenche a tabela
    for (int i = 1; i <= tam; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < a[i-1])
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] || dp[i-1][j-a[i-1]];
            
        }
    }

    if (dp[tam][n])
        return "True";
    else
        return "False";
}

int main()
{
    int i, m, n;
    long long int r = 0;
    
    printf("\n===============================");
    printf("\nEx 1: Calular a quantidade de formas para subir degraus com 1 ou 2 passos.");
    printf("\n===============================");

    printf("\nn: ");
    scanf("%d",&i);
    r = nFormasSubirEscadaDinamico(i);    
    printf("\nO numero de formas para subir %d degraus = %I64d", i, r);
    
    
    printf("\n\n===============================");
    printf("\nEx 2: Calular a quantidade de caminhos unicos possiveis em uma grade MxN.");
    printf("\n===============================");
    printf("\nm: ");
    scanf("%d",&m);
    printf("n: ");
    scanf("%d",&n);
    r = mapearCaminhosMxNDinamico(m,n);    
    printf("\nO numero de caminho para percorrer uma grade %d X %d = %I64d", m,n,r);
    
    int arr[] = {1, 2, 3, 4, 5}, tam = sizeof(arr)/sizeof(arr[0]);
    
    
    printf("\n\n===============================");
    printf("\nEx 3: Dado um conjunto de numeros inteiros, determine se existe um subconjunto cuja soma seja igual a um valor-alvo especifico.");
    printf("\n=================================");
    
    printf("\nArray: [");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("]");

    printf("\nSoma: ");
    scanf("%d",&n);

    printf("\nResultado Dinamico: %s", somaSubconjuntoDinamico(arr, tam, n));
    return 0;
}
