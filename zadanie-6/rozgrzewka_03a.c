#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main(){
    int n;
    printf("Podaj liczbe elementow: ");
    if(scanf("%d", &n) != 1 || n <= 0 || n > 46340 ||
       (size_t)n > SIZE_MAX / sizeof(int)){
        printf("Niepoprawny rozmiar (1-46340).\n");
        return 1;
    }
    int *tab = malloc((size_t)n * sizeof(int));
    if(tab == NULL){
        printf("Nie udalo sie przydzielic pamieci.\n");
        return 1;
    }
    for(int i = 0; i < n; i++){
        tab[i] = (i + 1) * (i + 1);
        printf("%d ", tab[i]);
    }
    printf("\n");
    free(tab);
    tab = NULL;
    /* Po free nie wolno odczytywac tablicy: wynik bylby niezdefiniowany.
       free nie zeruje wskaznika ani nie gwarantuje wyzerowania danych. */
    return 0;
}
