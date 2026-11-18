#include <stdio.h>

int interwencje = 0;

void limit_module(int *power, int limit){
    if(*power > limit){
        printf("Ograniczono pobor z %d do %d.\n", *power, limit);
        *power = limit;
        interwencje++;
    }
}

int emergency_limit(int *power, int n, int limit){
    int zmienione = 0;
    for(int i = 0; i < n; i++){
        if(*(power + i) > limit){
            printf("Modul %d: ", i + 1);
            limit_module(power + i, limit);
            zmienione++;
        }
    }
    return zmienione;
}

void analyze_power(const int *power, int n, int *sum, int *min, int *max){
    *sum = 0;
    *min = power[0];
    *max = power[0];
    for(int i = 0; i < n; i++){
        *sum = *sum + power[i];
        if(power[i] < *min){
            *min = power[i];
        }
        if(power[i] > *max){
            *max = power[i];
        }
    }
}

int next_control(void){
    static int licznik = 0;
    licznik++;
    return licznik;
}

void show_report(const int *power, int n, int control_number){
    int sum, min, max;
    analyze_power(power, n, &sum, &min, &max);

    printf("\nRAPORT ARGO\n");
    printf("Numer kontroli: %d\n", control_number);
    for(int i = 0; i < n; i++){
        printf("Modul %d: %d\n", i + 1, power[i]);
    }
    printf("Calkowity pobor: %d\n", sum);
    printf("Najmniejszy pobor: %d\n", min);
    printf("Najwiekszy pobor: %d\n", max);
    printf("Laczna liczba interwencji: %d\n", interwencje);
}

int main(void){
    int power[5] = {120, 85, 150, 60, 110};
    int n = 5;
    int limit = 100;
    int numer_kontroli;
    int zmienione;
    printf("Stan poczatkowy\n");
    show_report(power, n, 0);
    numer_kontroli = next_control();
    printf("\nKontrola nr %d - przed ograniczeniem\n", numer_kontroli);
    show_report(power, n, numer_kontroli);
    zmienione = emergency_limit(power, n, limit);
    printf("\nOgraniczono liczbe modulow: %d\n", zmienione);
    printf("\nKontrola nr %d - po ograniczeniu\n", numer_kontroli);
    show_report(power, n, numer_kontroli);
    printf("\nNowe zaklocenia\n");
    power[1] = 130;
    power[3] = 140;
    numer_kontroli = next_control();
    printf("\nKontrola nr %d - przed ograniczeniem\n", numer_kontroli);
    show_report(power, n, numer_kontroli);
    zmienione = emergency_limit(power, n, limit);
    printf("\nOgraniczono liczbe modulow: %d\n", zmienione);
    printf("\nKontrola nr %d - po ograniczeniu\n", numer_kontroli);
    show_report(power, n, numer_kontroli);
    numer_kontroli = next_control();
    printf("\nKontrola nr %d - wszystkie moduly w normie\n", numer_kontroli);
    zmienione = emergency_limit(power, n, limit);
    printf("Ograniczono liczbe modulow: %d\n", zmienione);
    show_report(power, n, numer_kontroli);

    return 0;
}
