#include <stdio.h>
#include <string.h>
#define TAM 4
int c = 0;

int visitado[TAM][TAM]; 
typedef struct
{
    int x, y;
} TPos;

TPos caminho[TAM][TAM];
int tamCaminho = 0; 
char *resultadoPosicaoBacktracking(int labirinto[][TAM], int n, int i, int k)
{   
    if (i >= n || k >= n || i < 0 || k < 0) 
        return "Nao";
    
    if (labirinto[i][k] == 1 || visitado[i][k]) 
        return "Nao"; // parede ou já visitado
    
    if (i == n - 1 && k == n - 1) 
        return "Sim"; // chegou no fim
    
    visitado[i][k] = 1; // marca como visitado

    caminho[tamCaminho]->x = i;
    caminho[tamCaminho]->y = k;
    tamCaminho++;

    if(strcmp(resultadoPosicaoBacktracking(labirinto, n, i + 1, k), "Sim") == 0) return "Sim";
    if(strcmp(resultadoPosicaoBacktracking(labirinto, n, i, k + 1), "Sim") == 0) return "Sim";
    if(strcmp(resultadoPosicaoBacktracking(labirinto, n, i - 1, k), "Sim") == 0) return "Sim";
    if(strcmp(resultadoPosicaoBacktracking(labirinto, n, i, k - 1), "Sim") == 0) return "Sim";

    visitado[i][k] = 0; // desfaz a escolha (backtracking)
    tamCaminho--;
    return "Nao";
}

char *encontraCaminhoBacktracking(int labirinto[][TAM], int n)
{
    return resultadoPosicaoBacktracking(labirinto, n, 0, 0);
}

void imprimeMatrizCaminho(int labirinto[][TAM], int n) {
    int matrizCopia[TAM][TAM];
    // copia a matriz original
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrizCopia[i][j] = labirinto[i][j];

    printf("\nMatriz %d x %d:\n",TAM,TAM);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrizCopia[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    int labirinto[][TAM] = {
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {1, 1, 0, 0}, 
        {0, 0, 0, 0}
    };

   
    printf("\n\n=======================================================================");
    printf("\nEx 3: Verificar se existe caminho livre em uma matriz labirinto NxN de [0][0] ate [n-1][n-1].");
    printf("\n0 = vazio, 1 = parede");
    printf("\n=======================================================================");
    
    imprimeMatrizCaminho(labirinto,TAM);

    printf("\nResultado: ");
    if (encontraCaminhoBacktracking(labirinto, TAM) == "Sim") {
        printf("Sim\nCaminho encontrado:\n");
        for (int i = 0; i < tamCaminho; i++) {
            printf("[%d][%d] -> ", caminho[i]->x, caminho[i]->y);
        }
        printf("FIM\n");
    } else {
        printf("Nao\n");
    }

    return 0;
}
