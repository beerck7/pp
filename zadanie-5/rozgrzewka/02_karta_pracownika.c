#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    double hours;
    double rate;
} employee;

int main(){
    employee worker;
    employee copy;

    printf("Podaj identyfikator: ");
    if(scanf("%d", &worker.id) != 1){
        printf("Niepoprawne dane.\n");
        return 1;
    }

    printf("Podaj imie: ");
    if(scanf("%49s", worker.name) != 1){
        printf("Niepoprawne dane.\n");
        return 1;
    }

    printf("Podaj liczbe godzin: ");
    if(scanf("%lf", &worker.hours) != 1 || worker.hours < 0){
        printf("Niepoprawna liczba godzin.\n");
        return 1;
    }

    printf("Podaj stawke godzinowa: ");
    if(scanf("%lf", &worker.rate) != 1 || worker.rate < 0){
        printf("Niepoprawna stawka.\n");
        return 1;
    }

    printf("\nDane pracownika:\n");
    printf("Id: %d\n", worker.id);
    printf("Imie: %s\n", worker.name);
    printf("Godziny: %.2f\n", worker.hours);
    printf("Stawka: %.2f\n", worker.rate);
    printf("Wynagrodzenie: %.2f\n", worker.hours * worker.rate);

    copy = worker;
    copy.rate = copy.rate * 1.2;

    printf("\nPo zmianie stawki w kopii:\n");
    printf("Stawka oryginalu: %.2f\n", worker.rate);
    printf("Stawka kopii: %.2f\n", copy.rate);

    return 0;
}
