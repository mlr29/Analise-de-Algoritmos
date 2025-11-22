# Trabalho Final — Análise e Comparação de Algoritmos de Ordenação

Este diretório contém o código e os artefatos para o trabalho final da disciplina de Análise de Algoritmos. O objetivo é comparar algoritmos de ordenação (CombSort, MergeSort e um híbrido Comb+Merge) medindo tempos de execução e gerando um gráfico interativo com estatísticas.

Conteúdo

- `comparativo.c` — programa em C que executa os experimentos, mede tempos usando `QueryPerformanceCounter` (alta resolução no Windows), e grava `resultados.json`.
- `Algoritmos.c` — implementação dos algoritmos: `combSort`, `mergeSort`, e `combMergeSortHybrid`.
- `index.html` — página de teste que carrega Chart.js e `script.js` para visualizar `resultados.json`.
- `script.js` — código frontend que carrega `resultados.json`, plota um gráfico (Chart.js) e mostra estatísticas (mínimo, máximo, moda, média e desvio padrão em ms).
- `resultados.json` — arquivo gerado pelo `comparativo.exe` contendo as séries de tempos (cada objeto contém `algoritmo`, `tipo`, `iteracoes` e `tempos`).

Requisitos

- Um compilador C compatível com Windows (MinGW-w64 / GCC recomendado).
- Python 3 para servir os arquivos localmente com `python -m http.server` (opcional, para visualizar `index.html`).
- Navegador moderno com suporte a Chart.js (Chrome/Edge/Firefox).

Como compilar (Windows PowerShell)

1. Abra o PowerShell e navegue até esta pasta:

    ```powershell
    Set-Location 'c:\Users\limar\OneDrive\Documentos\Arquivos da faculdade\8º Período\Análise de Algoritmos\trabalho-final'
    ```

2. Compile com GCC (MinGW):

    ```powershell
    gcc -O2 -std=c11 -Wall -Wextra comparativo.c -o comparativo.exe
    ```

Observação: se você incluir `Algoritmos.c` via `#include "Algoritmos.c"` em `comparativo.c`, não compile `Algoritmos.c` separadamente; compile apenas `comparativo.c`. Se preferir separar, ajuste `comparativo.c` para `#include "Algoritmos.h"` e compile ambos.

Como executar os testes

- Execução simples (gera `resultados.json`):

```powershell
.\comparativo.exe
```

- Parâmetros sensíveis no código:
  - `tamanho` e `repeticoes` estão definidos em `main()` de `comparativo.c`. Ajuste conforme necessário para experimentos maiores/menores.
  - `get_repeticoes_for_n(int n)` determina o número de repetições internas e tenta equilibrar precisão vs tempo de execução.

Sobre as medições

- O programa faz warm-up, executa blocos de medições para reduzir ruído, subtrai overhead de `memcpy` e usa a mediana de amostras para cada ponto.
- Para decidir o `n0` (ponto de corte entre algoritmos) o programa pode executar várias tentativas e usar mediana + regra de confirmação (2 confirmações consecutivas).

Visualizar o gráfico (frontend)

1. Inicie um servidor HTTP simples no diretório `trabalho-final` (necessário para o navegador carregar localmente o JSON de forma confiável).

    ```powershell
    python -m http.server 8000
    ```

    - Você pode também utilizar a extensão Live Server do VsCode no `index.html`.

2. Abra o navegador em: <http://localhost:8000/index.html>

O `index.html` usa Chart.js via CDN e o `script.js` para:

- Carregar `resultados.json` (o script tenta corrigir alguns problemas comuns de formatação).
- Converter tempos de segundos para milissegundos.
- Desenhar a série por iteração/tamanho.
- Exibir uma tabela com estatísticas por série: N (n pontos), Mín, Máx, Média, Moda e Desvio Padrão (amostral).

Interpretação das estatísticas

- Mín / Máx: menor/maior tempo medido (ms).
- Média: tempo médio (ms).
- Moda: valor mais frequente (agrupado por arredondamento a 6 casas decimais para evitar ruído extremo em floats).
- Desvio Padrão: desvio padrão amostral (ms) — indica variabilidade das medições.

Dicas de experimento

- Para medições mais estáveis, aumente `repeticoes` e execute em um sistema pouco carregado.
- Execute múltiplas execuções do `comparativo.exe` e compare os `resultados.json` (ou modifique o programa para gravar múltiplos arquivos com timestamp).

Problemas comuns e solução

- `resultados.json` vazio ou com arrays vazios: verifique se o programa não falhou durante a execução (imprima mensagens de debug) e se `tamTempOrdem` foi setado corretamente.
- Erro de ligação (multiple definition): verifique se `Algoritmos.c` não está sendo compilado duas vezes ou incluído em header; preferível usar `#include "Algoritmos.c"` apenas se não compilar `Algoritmos.c` separadamente.
