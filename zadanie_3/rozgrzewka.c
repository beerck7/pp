#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double brew_potion(double ingredient_a, double ingredient_b){
    return ((0.6*ingredient_a)+(0.4*ingredient_b));
}

void strengthen_potion(double power){
    printf("Moc mikstury po zmianie: %.2lf", power * 1.2);
}

void strengthen_potion2(double *power){
    *power = *power * 1.2;
}

void strengthen_all(double potions[], int n){
    int i =0;
    while(i<n){
        potions[i] = potions[i]*1.2;
        i++;
    }
}


int main(){
    double potions[5] = {0};
    int n = 5, i=0;
    srand(time(NULL));
    double ingredient_a, ingredient_b;
    printf("\nPodaj pierwszy skladnik: \n");
    scanf("%lf", &ingredient_a);
    printf("Podaj drugi skladnik: \n");
    scanf("%lf", &ingredient_b);
    double power = brew_potion(ingredient_a, ingredient_b);
    printf("Wartosc wynosi %.2f\n", power);
    printf("Moc mikstury przed zmiana: %.2lf\n", power);
    strengthen_potion(power);
    printf("\nMoc mikstury przed zmiana: %.2lf\n", power);
    strengthen_potion2(&power);
    printf("Moc mikstury po zmianie: %.2lf\n", power);
    while(i<n){
        potions[i] = ((double)rand() / RAND_MAX) * 10.0;
        printf("\nWartosc %d mocy mikstur przed zmiana wynosi: %.2lf", i+1, potions[i]);
        i++;
    }
    i = 0;
    strengthen_all(potions, n);
    while(i<n){
        printf("\nWartosc %d mocy mikstur po zmianie wynosi: %.2lf", i+1, potions[i]);
        i++;
    }

    return 0;
}