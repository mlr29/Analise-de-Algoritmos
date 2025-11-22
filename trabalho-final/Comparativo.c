
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Algoritmos.c"
#include <windows.h>
#include <math.h>
#include <stdbool.h>


typedef struct AlgoritmoTempos
{
    char nome[30];
    double *tOrdem, *tOrdemInversa;
}TAlgoritmoTempos;


/* Gera colecoes de teste */
void gerarColecaoOrdemInversa(int *colecao, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        colecao[i] = tamanho - i;
    }
}

void gerarColecao(int *colecao, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        colecao[i] = rand() % (tamanho * 10);
    }
}

/* comparador e mediana para double */
static int cmp_double(const void *pa, const void *pb)
{
    double a = *(const double *)pa;
    double b = *(const double *)pb;
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

static double mediana_array(double *v, int n)
{
    if (n <= 0)
        return -1.0;
    
    double *c = (double *)malloc(n * sizeof(double));
    if (!c)
        return 0;
    for (int i = 0; i < n; ++i)
    {
        c[i] = v[i];
    }
    qsort(c, n, sizeof(double), cmp_double);
    double med;
    if (n % 2 == 1)
        med = c[n / 2];
    else
        med = (c[n / 2 - 1] + c[n / 2]) / 2.0;
    free(c);
    return med;
}

/* int comparator + median for ints */
static int cmp_int(const void *pa, const void *pb)
{
    int a = *(const int *)pa;
    int b = *(const int *)pb;
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

static int mediana_inteiros(int *v, int n)
{
    if (n <= 0)
        return 0;
    int *c = (int *)malloc(n * sizeof(int));
    if (!c)
        return 0;
    for (int i = 0; i < n; ++i)
    {
        c[i] = v[i];
    }
    qsort(c, n, sizeof(int), cmp_int);
    qsort(v, n, sizeof(int), cmp_int);
    int med = c[n / 2];
    if (n % 2 == 0)
        med = (c[n / 2 - 1] + c[n / 2]) / 2;
    free(c);
    return med;
}

/* choose repetitions depending on n to keep timings stable and fast */
static int get_repeticoes_for_n(int n)
{
    if (n <= 50)
        return 500;
    if (n <= 200)
        return 200;
    if (n <= 2000)
        return 20;
    if (n <= 10000)
        return 5;
    return 10;
}

/* Medir tempo médio de CombSort com 'repeticoes' execuções sobre tamanhos 'n' */
double calcularTempoExecucaoCombSort(int *colecao, int n, int repeticoes)
{
    if (repeticoes <= 0)
        repeticoes = 1;
    const int amostras = 7;
    double times[amostras];
    int *tmp = (int *)malloc(n * sizeof(int));
    if (!tmp)
        return -1.0;

    LARGE_INTEGER inicio, fim, freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        free(tmp);
        return -1.0;
    }

    /* warm-up */
    memcpy(tmp, colecao, n * sizeof(int));
    combSort(tmp, n);
    memcpy(tmp, colecao, n * sizeof(int));
    combSort(tmp, n);
    memcpy(tmp, colecao, n * sizeof(int));
    combSort(tmp, n);

    /* medir overhead(custos) de memcpy */
    QueryPerformanceCounter(&inicio);
    for (int r = 0; r < repeticoes; ++r)
    {
        memcpy(tmp, colecao, n * sizeof(int));
    }
    QueryPerformanceCounter(&fim);
    double overhead = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    /* medir em amostras e subtrair overhead */
    for (int s = 0; s < amostras; ++s)
    {
        QueryPerformanceCounter(&inicio);
        for (int r = 0; r < repeticoes; ++r)
        {
            memcpy(tmp, colecao, n * sizeof(int));
            combSort(tmp, n);
        }
        QueryPerformanceCounter(&fim);
        double total = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
        double per = (total - overhead) / (double)repeticoes;
        times[s] = per > 0.0 ? per : 0.0;
    }

    free(tmp);
    double med = mediana_array(times, amostras);
    
    return med;
}

/* Medir tempo médio de MergeSort com 'repeticoes' execuções sobre tamanhos 'n' */
double calcularTempoExecucaoMergeSort(int *colecao, int n, int repeticoes )
{
    if (repeticoes <= 0)
        repeticoes = 1;
    const int amostras = 7;
    double times[amostras];
    int *tmp = (int *)malloc(n * sizeof(int));
    int *buffer = (int *)malloc(n * sizeof(int));

    if (!buffer || !tmp)
    {
        free(tmp);
        free(buffer);
        return -1.0;
    }

    LARGE_INTEGER inicio, fim, freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        free(tmp);
        return -1.0;
    }

    /* warm-up: executar algumas vezes para "aquecer" caches e iniciais */
    memcpy(tmp, colecao, n * sizeof(int));
    mergeSort(tmp, buffer, 0, n - 1);
    memcpy(tmp, colecao, n * sizeof(int));
    mergeSort(tmp, buffer, 0, n - 1);
    memcpy(tmp, colecao, n * sizeof(int));
    mergeSort(tmp, buffer, 0, n - 1);

    /* medir overhead de memcpy (inclui copia do buffer se desejar) */
    QueryPerformanceCounter(&inicio);
    for (int r = 0; r < repeticoes; ++r)
    {
        memcpy(tmp, colecao, n * sizeof(int));
    }
    QueryPerformanceCounter(&fim);
    double overhead = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    /* medir em amostras e subtrair overhead */
    for (int s = 0; s < amostras; ++s)
    {
        QueryPerformanceCounter(&inicio);
        for (int r = 0; r < repeticoes; ++r)
        {
            memcpy(tmp, colecao, n * sizeof(int));
            mergeSort(tmp, buffer, 0, n - 1);
        }
        QueryPerformanceCounter(&fim);
        double total = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
        double per = (total - overhead) / (double)repeticoes;
        times[s] = per > 0.0 ? per : 0.0;
    }

    free(tmp);
    free(buffer);
    return mediana_array(times, amostras);
}

/* Medir tempo médio de CombMergeHybrid com 'repeticoes' execuções sobre tamanhos 'n' */
double calcularTempoExecucaoCombMergeHybrid(int *colecao, int n, int cutoff, int repeticoes )
{
    if (repeticoes <= 0)
        repeticoes = 1;
    const int amostras = 7;
    double times[amostras];
    int *tmp = (int *)malloc(n * sizeof(int));
    int *buffer = (int *)malloc(n * sizeof(int));

    if (!buffer || !tmp)
    {
        free(tmp);
        free(buffer);
        return -1.0;
    }

    LARGE_INTEGER inicio, fim, freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        free(tmp);
        free(buffer);
        return -1.0;
    }

    /* warm-up */
    memcpy(tmp, colecao, n * sizeof(int));
    combMergeSortHybrid(tmp, buffer, 0, n - 1, cutoff);
    memcpy(tmp, colecao, n * sizeof(int));
    combMergeSortHybrid(tmp, buffer, 0, n - 1, cutoff);
    memcpy(tmp, colecao, n * sizeof(int));
    combMergeSortHybrid(tmp, buffer, 0, n - 1, cutoff);

    /* medir overhead de memcpy */
    QueryPerformanceCounter(&inicio);
    for (int r = 0; r < repeticoes; ++r)
    {
        memcpy(tmp, colecao, n * sizeof(int));
    }
    QueryPerformanceCounter(&fim);
    double overhead = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;

    /* medir em amostras e subtrair overhead */
    for (int s = 0; s < amostras; ++s)
    {
        QueryPerformanceCounter(&inicio);
        for (int r = 0; r < repeticoes; ++r)
        {
            memcpy(tmp, colecao, n * sizeof(int));
            combMergeSortHybrid(tmp, buffer, 0, n - 1, cutoff);
        }
        QueryPerformanceCounter(&fim);
        double total = (double)(fim.QuadPart - inicio.QuadPart) / (double)freq.QuadPart;
        double per = (total - overhead) / (double)repeticoes;
        times[s] = per > 0.0 ? per : 0.0;
    }

    free(tmp);
    return mediana_array(times, amostras);
}


int encontrar_n0(int maxTamanho, int runs)
{
   
    int *colecao = (int *)malloc(maxTamanho * sizeof(int));

    if (!colecao)
        return 1;

    gerarColecaoOrdemInversa(colecao, maxTamanho);

     /* executar a busca por n0 varias vezes e usar mediana */
    int results[runs];
    printf("Procurando n0 (tComb > tMerge) em %d execucoes...\n", runs);

    for (int run = 0; run < runs; ++run)
    {
        int n0 = 0;
        int consecutive = 0;
        double prev_tComb = 0.0, prev_tMerge = 0.0;
        for (int n = 1; n <= maxTamanho; n++)
        {
            int repeticoes = get_repeticoes_for_n(n);
            double tComb = calcularTempoExecucaoCombSort(colecao, n, repeticoes);
            double tMerge = calcularTempoExecucaoMergeSort(colecao, n, repeticoes);

            if (n % 500 == 0 || n <= 10)
            {
                printf("run=%d n=%d -> Comb: %.10f s, Merge: %.10f s\n", run + 1, n, tComb, tMerge);
            }

            if (tComb > 0.0 && tMerge > 0.0)
            {

                /* procurar tComb > tMerge (Merg mais rápido) */
                if (tMerge < tComb)
                {
                    consecutive++;
                    if (consecutive == 1)
                    {
                        prev_tComb = tComb;
                        prev_tMerge = tMerge;
                    }
                    else if (consecutive >= 2)
                    {
                        n0 = n - 1;
                        printf("run %d: n0 confirmado = %d (Comb %.10f > Merge %.10f)\n\n", run + 1, n0, prev_tComb, prev_tMerge);
                        break;
                    }
                }
                else
                {
                    consecutive = 0;
                }
            }
        }
        if (n0 == 0)
        {
            printf("run %d: nenhum n0 encontrado ate %d\n", run + 1, maxTamanho);
        }
        results[run] = n0;
    }
    
    int median_n0 = mediana_inteiros(results, runs);

    printf("\nResultados das execucoes:\n");
    for (int i = 0; i < runs; i++)
    {
        printf("%d ", results[i]);
    }

    printf("\n");
    printf("Mediana do n0 apos %d execucoes = %d\n", runs, median_n0);

    free(colecao);

    return median_n0;
}

double * executarTesteCombSort(int tamanho, void (*gerarColecao)(int *, int), int repeticoes)
{
    int *colecao = (int *)malloc(tamanho * sizeof(int));
    double *tempo = (double *)malloc(repeticoes * sizeof(double));
    if (!colecao) {
        if (tempo) free(tempo);
        return NULL;
    }
    if (!tempo) { free(colecao); return NULL; }
    if (!tempo) { free(colecao); return NULL; }

    printf("Calculando tempo CombSort n=%d repeticoes=%d...\n", tamanho, repeticoes);

    /* medir em 'repeticoes' execuções independentes (gerando nova coleção a cada vez)
       e usar um pequeno batch interno para reduzir ruído */
    int batch = get_repeticoes_for_n(tamanho);
    for (int r = 0; r < repeticoes; ++r) {
        gerarColecao(colecao, tamanho);
        tempo[r] = calcularTempoExecucaoCombSort(colecao, tamanho, batch);
    }

    return tempo;
}

double * executarTesteMergeSort(int tamanho, void (*gerarColecao)(int *, int), int repeticoes)
{
    int *colecao = (int *)malloc(tamanho * sizeof(int));
    double *tempo = (double *)malloc(repeticoes * sizeof(double));
    if (!colecao)
        return NULL;
    if (!tempo) { free(colecao); return NULL; }

    printf("Calculando tempo MergeSort n=%d repeticoes=%d...\n", tamanho, repeticoes);
    int batch = get_repeticoes_for_n(tamanho);
    for (int r = 0; r < repeticoes; ++r) {
        gerarColecao(colecao, tamanho);
        tempo[r] = calcularTempoExecucaoMergeSort(colecao, tamanho, batch);
    }

    return tempo;
}

double * executarTesteCombMergeHybrid(int tamanho, void (*gerarColecao)(int *, int), int cutoff, int repeticoes)
{
    int *colecao = (int *)malloc(tamanho * sizeof(int));
    double *tempo = (double *)malloc(repeticoes * sizeof(double));
    if (!colecao)
        return NULL;

    gerarColecao(colecao, tamanho);

    printf("Calculando tempo CombMergeHybrid n=%d cutoff=%d repeticoes=%d...\n", tamanho, cutoff, repeticoes);
    for(int r = 0; r < repeticoes; r++) {
        tempo[r] = calcularTempoExecucaoCombMergeHybrid(colecao, tamanho, cutoff, repeticoes);
    }

    double soma = 0.0;

    for(int r = 0; r < repeticoes; r++) {
        soma += tempo[r];
    }
    double media = soma / repeticoes;

    free(colecao);
    return tempo;
}

void resultadosGerarObjetoJSON(FILE *arquivo, const char *algoritmo, double *tempos, int tamanho, char* tipo)
{

    fprintf(arquivo, "{\n");
    fprintf(arquivo, "   \"algoritmo\": \"%s\",\n", algoritmo);
    fprintf(arquivo, "   \"tipo\": \"%s\",\n", tipo);
    fprintf(arquivo, "   \"iteracoes\": %d,\n", tamanho);
    fprintf(arquivo, "   \"tempos\": [\n");

    if (tamanho > 0) {
        for (int i = 0; i < tamanho; ++i) {
            fprintf(arquivo, "    %.10f%s\n", tempos[i], (i < tamanho - 1) ? "," : "");
        }
    }
    fprintf(arquivo, "  ]\n");
    fprintf(arquivo, "}\n");
}

/* Salvar resultados em arquivo */
void salvarResultados(TAlgoritmoTempos algoritmoTempos[], int numAlgoritmos, int tamanhoColecao, int repeticoes)
{
    FILE *arquivo = fopen("web\\resultados.json", "w"); // CSV coerente
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os resultados.\n");
        return;
    }
    int totalObjects = numAlgoritmos * 2;
    int written = 0;
    
    fprintf(arquivo, "{\n");
    fprintf(arquivo, "  \"tamanhoColecao\": %d,\n", tamanhoColecao);
    
    fprintf(arquivo, "  \"resultados\": [\n");
    for (int i = 0; i < numAlgoritmos; i++)
    {
        resultadosGerarObjetoJSON(arquivo, algoritmoTempos[i].nome, algoritmoTempos[i].tOrdem, repeticoes, "Ordem");
        written++;
        if (written < totalObjects) fprintf(arquivo, ",\n");
        
        resultadosGerarObjetoJSON(arquivo, algoritmoTempos[i].nome, algoritmoTempos[i].tOrdemInversa, repeticoes, "Ordem Inversa");
        written++;
        if (written < totalObjects) fprintf(arquivo, ",\n");
    }
    fprintf(arquivo, "\n]\n");
    fprintf(arquivo, "}\n");
    printf("\nResultados salvos em 'resultados.json'\n");
    fclose(arquivo);
}


int main()
{
    int numAlgoritmos = 3, tamanhoColecao = 10, repeticoes = 100, runs = 15;
    int n0 = encontrar_n0(tamanhoColecao, runs);

    TAlgoritmoTempos algoritmoTempos[] = {
        {"CombSort", (double*)NULL, (double*)NULL},
        {"MergeSort", (double*)NULL, (double*)NULL},
        {"CombMergeHybrid", (double*)NULL, (double*)NULL}
    };

    //Execução dos testes nos 3 algoritmos para os 2 tipos de coleção
    printf("\nEXECUCAO DE TESTES\n");
    printf("\n=======Ordem normal=======\n");
    algoritmoTempos[0].tOrdem = executarTesteCombSort(tamanhoColecao, gerarColecao, repeticoes);
    algoritmoTempos[1].tOrdem = executarTesteMergeSort(tamanhoColecao, gerarColecao, repeticoes);
    algoritmoTempos[2].tOrdem = executarTesteCombMergeHybrid(tamanhoColecao, gerarColecao, n0, repeticoes);
    
    printf("\n=======Ordem inversa=======\n");
    algoritmoTempos[0].tOrdemInversa = executarTesteCombSort(tamanhoColecao, gerarColecaoOrdemInversa, repeticoes);
    algoritmoTempos[1].tOrdemInversa = executarTesteMergeSort(tamanhoColecao, gerarColecaoOrdemInversa, repeticoes);
    algoritmoTempos[2].tOrdemInversa = executarTesteCombMergeHybrid(tamanhoColecao, gerarColecaoOrdemInversa, n0, repeticoes);
    

    salvarResultados(algoritmoTempos, numAlgoritmos, tamanhoColecao, repeticoes);
    
    /* liberar memória alocada para tempos */
    for (int i = 0; i < 3; ++i) {
        if (algoritmoTempos[i].tOrdem) free(algoritmoTempos[i].tOrdem);
        if (algoritmoTempos[i].tOrdemInversa) free(algoritmoTempos[i].tOrdemInversa);
    }

    return 0;
}
