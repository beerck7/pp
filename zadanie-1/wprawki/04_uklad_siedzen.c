#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj_pasazerow(int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("Podaj liczbe pasazerow: ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < 1 || liczba > 1000000) {
            puts("Niepoprawne dane.");
            continue;
        }
        *wynik = (int)liczba;
        if (liczba != *wynik) {
            puts("Niepoprawne dane.");
            continue;
        }
        return 1;
    }
}

int main(void)
{
    int n;
    if (!wczytaj_pasazerow(&n))
        return 0;

    int rzedy_a = (n + 2) / 3;
    int puste_a = rzedy_a * 3 - n;
    int rzedy_b = (n + 4) / 5;
    int puste_b = rzedy_b * 5 - n;

    printf("Wariant A: %d rzedow, %d pustych miejsc.\n", rzedy_a, puste_a);
    printf("Wariant B: %d rzedow, %d pustych miejsc.\n", rzedy_b, puste_b);

    if (puste_a == 0)
        puts("Wariant A: pasazerowie mieszcza sie bez pustych miejsc.");
    if (puste_b == 0)
        puts("Wariant B: pasazerowie mieszcza sie bez pustych miejsc.");

    if (puste_a < puste_b) {
        puts("Lepszy wariant: Wariant A (mniej pustych miejsc).");
    } else if (puste_b < puste_a) {
        puts("Lepszy wariant: Wariant B (mniej pustych miejsc).");
    } else {
        puts("Liczba pustych miejsc jest taka sama w obu wariantach.");
    }
    return 0;
}
