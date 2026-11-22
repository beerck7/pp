#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *create_array(int n){
    if(n <= 0 || n > 46340 || (size_t)n > SIZE_MAX / sizeof(int)){
        return NULL;
    }
    return malloc((size_t)n * sizeof(int));
}

void fill_array(int tab[], int n){
    for(int i = 0; i < n; i++){
        tab[i] = (i + 1) * (i + 1);
    }
}

void print_array(const int tab[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Podaj liczbe elementow: ");
    if(scanf("%d", &n) != 1){
        printf("Niepoprawne dane.\n");
        return 1;
    }
    int *tab = create_array(n);
    if(tab == NULL){
        printf("Niepoprawny rozmiar (1-46340) lub blad alokacji.\n");
        return 1;
    }
    fill_array(tab, n);
    print_array(tab, n);
    free(tab);
    tab = NULL;
    return 0;
}
