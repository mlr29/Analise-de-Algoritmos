#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMNOTAS 6
#define TAMATIVIDADES 5

typedef struct 
{
    char nome[50];
    int hInicio; // em segundos em relação a 0h
    int hFim;
} TAtividade;

int numeroMinimoDenotas(int valor, int notas[], int tamNotas, int nNotas[]){ 
    int r = 0;
    for (int i = tamNotas - 1; i >= 0 ; i--)
    {
        if (valor > notas[i])
        {   
            nNotas[i] = (valor / notas[i]);
            valor = valor % notas[i];
            r += nNotas[i]; 
        }
    }
    return r;
}

// Função pedida: imprime lista de atividades
void imprimeAtividades(TAtividade *a, int n, int *iAtividades) {
    printf("\n\nLista de Atividades:\n");
    for (int i = 0; i < n; i++) {
        if (iAtividades[i])
        {
            int hI = a[i].hInicio / 3600;
            int mI = (a[i].hInicio % 3600) / 60;

            int hF = a[i].hFim / 3600;
            int mF = (a[i].hFim % 3600) / 60;

            printf("%s - %02d:%02d ate %02d:%02d\n",
                a[i].nome, hI, mI, hF, mF);
        }
    }
}

int compara(const void *a, const void *b) {
    TAtividade *atv1 = (TAtividade *)a;
    TAtividade *atv2 = (TAtividade *)b;
    return atv1->hFim - atv2->hFim; // ordena pelo horário de término
}

int numeroMaximoAtividades(TAtividade *atividades, int n, int iAtividades[]){
    int nAtividades = n;
    TAtividade atividadeAtual;

    qsort(atividades, n, sizeof(TAtividade), compara);

    for (int i = 0; i < n - 1; i++)
    {
        atividadeAtual = atividades[i];
        
        for (int j = i + 1; j < n; j++)
        {
            if ((atividadeAtual.hFim > atividades[j].hInicio) && iAtividades[j] == 1)
            {
                nAtividades--;
                iAtividades[j] = 0;
            }
        }
    }
    
    return nAtividades;
}

int main()
{
    int notas[TAMNOTAS] = {1,5,10,25,50,100}, valor, nNotas[TAMNOTAS] = {0}, rNotas;

    printf("\n===============================");
    printf("\nEx 1: Calcular o numero de minimo de notas necessarias para devolver o troco.");
    printf("\n===============================");

    printf("\nnotas: [");
    for (int i = 0; i < TAMNOTAS; i++)
    {
        printf(" %d ", notas[i]);
    }
    printf("]");

    printf("\nDigite um valor como troco: ");
    scanf("%d",&valor);

    rNotas = numeroMinimoDenotas(valor,notas,TAMNOTAS, nNotas);
    
    printf("\nNumero de minimos de notas: %d", rNotas);

    for(int i = 0; i < TAMNOTAS; i++)
        printf("\nQuantidade R$ %d: %d", notas[i], nNotas[i]);
    

    int iAtividades[TAMATIVIDADES] = {1,1,1,1,1}, rAtividades;
    
    TAtividade atividades[] = {
        { "Aula 1", 7 * 60 *60, 9 * 60 * 60 }, //7h - 9h
        { "Aula 4", 11 * 60 *60, 12 * 60 * 60 }, // 11h - 12h
        { "Aula 2", 8 * 60 *60, 8 * 60 * 60 + 30 * 60 }, //8h - 8h30
        { "Aula 3", 8 * 60 *60 + 20 * 60, 10 * 60 * 60 }, // 8h20 - 10h
        { "Aula 5", 10 * 60 *60 + 30 * 60, 11 * 60 * 60 + 30 * 60}, // 10h30 - 11h30
    };

    printf("\n\n===============================");
    printf("\nEx 2: Calcular o numero maximo de atividades possiveis de realizar sem sobrepor horarios.");
    printf("\n===============================");

    imprimeAtividades(atividades, TAMATIVIDADES, iAtividades);

    rAtividades = numeroMaximoAtividades(atividades, TAMATIVIDADES, iAtividades);

    printf("\nNumero maximo de atividades possiveis: %d", rAtividades);
    
    imprimeAtividades(atividades, TAMATIVIDADES, iAtividades);

    return 0;
}
