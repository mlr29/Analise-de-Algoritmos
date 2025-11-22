#include <stdio.h>
#include <string.h>

int fibonacci(int n){
    if(n <= 0){
        printf("\n%d",n);
        return 0;
    }
    
    
    if(n == 1){
        printf("\n%d",n);
        return 1;
    }
    
    
    int x = fibonacci(n-2) + fibonacci(n-1);
    
    printf("\n%d",x);
        
    return x;
    
}

int fibonacciDinamico(int n){
    int cache[n];
    
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
  
    
    for(int i = 0; i < n; i++){
        if (i == 0){
            cache[0] = 0;
        } else if(i == 1){
            cache[1] = 1;
        }else{
            cache[i] = cache[i-2] + cache[i-1];
        }    
        
    }   
    //printf("\n%d",x);
        
    return cache[n - 1];
    
}

int subStr(char s[], char r[]){
    
    //printf("%s",s);
    int j;
    int i, k;
    for(i = 0; s[i] != '\0'; i++){
        
        k = i;
        for (j = 0; s[k] == r[j] && r[j] != '\0'; j++){
            k++;
            printf("passou ");
        }
        
        if(r[j] == '\0'){
            return 1;
        }
        
    }
    
    return 0;
}


int quebraSenha(char s[]){
    char t[5] = "0000";
    int i;
    
    for(i = 0; strcmp(s,t) != 0; i++){
        printf(" %d ", strcmp(s,t));
        memset(t, 0, sizeof(t));
        sprintf(t, "%d", i);
        printf("\nrr = %s", t);
    }
    
    return i;
}

int arr[] = {-1,-1,-1}, r = 0;

int somaNumero1s(int n){

    if(arr[0] != -1 && arr[1] != -1 && arr[2] != -1)
        return arr[0] + arr[1] + arr[2] >= n ? 1 : 0;
    
    
}
int main()
{
    //int r = fibonacciDinamico(7);    
    
    //printf("\nfim");

    //subStr("Matheus","th");
    
    //printf("\nr = %d", r);
    
    
    //printf("\nr = %d", subStr("Matheus","Matheus1435"));
    
    
    printf("\nr = %d", quebraSenha("7199"));
    
    
    
    return 0;
}