# Análise de Algoritmos

Exercícios realizados na disciplina de Análise de Algoritmos no 8º Período de Ciência da Computação.

## Exercícios

### Programação Dinâmica

#### 1. Problema da escada

    Descrição: Você está subindo uma escada. Pode subir 1 ou 2 degraus de cada vez. De quantas formas diferentes você pode subir uma escada de `n` degraus?

    - Input: Um número inteiro `n` (o número de degraus)
    - Saída: O número de maneiras de subir a escada.

#### 2. Número de caminhos em um grade

    Descrição: Dado uma grade `m x n`, determine quantos caminhos únicos existem da célula superior esquerda até a célula inferior direita. Você só pode mover-se para a direita ou para baixo.

    - Input: Dois inteiros `m` e `n` representando as dimensões da grade.
    - Saída: O número de caminhos únicos possíveis.

#### 3. Problema da Soma de Subconjunto

    Descrição: Dado um conjunto de números inteiros, determine se existe um subconjunto cuja soma seja igual a um valor-alvo específico.

    - Entrada: Um array de inteiros e um valor-alvo.
    - Saída: `True` ou `False` indicando se tal subconjunto existe.

### Hard code

#### 1. Problema do Par de Soma

    Descrição: Dado um array de inteiros e um valor alvo, encontre se há dois números no array cuja soma seja igual ao valor alvo.

    - Input: Um array de inteiros e um valor alvo.
    - Saída: Os índices dos dois números que somam ao valor alvo, ou uma indicação de que não existe um par.

#### 2. Verificação de Palíndromo

    Descrição: Dada uma string, verifique se ela é um palíndromo (lê-se da mesma forma de trás para frente).

    - Input: Uma string.
    - Saída: Sim, se é um palíndromo, ou Não, caso contrário.

#### 3.Busca de Número Duplicado

    Descrição: Dado um array de números inteiros, descubra se existe algum número que aparece mais de uma vez.

    - Input: Um array de inteiros.
    - Saída: O número duplicado, ou uma indicação de que não existe números duplicados.

#### 4.Contagem de Pares Distintos

    Descrição: Dado um array de números, conte quantos pares distintos (a, b) existem, onde a ≠ b.

    - Input: Um array de inteiros.
    - Saída: O número de pares distintos.

#### 5.Verificação de Anagramas

    Descrição: Dadas duas strings, determine se uma é um anagrama da outra.

    - Input: Duas strings.
    - Saída: Sim, se são anagramas, ou Não, caso contrário.

### Backtracing

#### 1. Saída para labirinto

    Descrição: Você tem um labirinto representado por uma matriz de tamanho n x n. Onde:
    - `0` representa um caminho livre.
    - `1` representa uma parede ou obstáculo.
    
    O objetivo é começar na célula superior esquerda 0, 0 e encontrar um caminho até a célula inferior direita n-1, n-1, movendo-se apenas para a direita, para baixo, para a esquerda ou para cima (não é permitido movimentos em diagonal.
    
    Entrada: Uma matriz n x n de inteiros contendo 0s e 1s
    
    Saída: Imprima "Sim" se houver um caminho da posição `(0, 0)` até `(n-1, n-1)` e "Não" se não houver caminho possível.

    Exemplo:
    Entrada: n = 4, 
             labirinto = {{0, 1, 0, 0},
                          {0, 0, 0, 1},
                          {1, 1, 0, 0}, 
                          {0, 0, 0, 0}}
    Saída: Sim

### Guloso

#### 1. Troco mínimo dado

    Descrição: um valor de troco e um conjunto de denominações de moedas, determine o menor número de moedas necessárias para fornecer o troco

    - Entrada: Valor inteiro V e um conjunto de denominações de moedas {1,5,10,25,50,100}
    - Saída: O número mínimo de moedas

#### 2. Atividades compatíveis

    Descrição: Dado um conjunto de atividades, cada uma com um horário de início e de término, selecione o máximo número de atividades que podem ser realizadas sem sobreposição de tempo

    - Entrada: Lista de atividades com nome, horário de início e de término
    - Saída: O número máximo de atividades que podem ser selecionadas sem que nenhuma delas tenha sobreposição
