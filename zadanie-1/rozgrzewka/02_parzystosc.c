#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj(const char *pytanie, int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("%s", pytanie);
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < -1000000 || liczba > 1000000) {
            puts("Niepoprawne dane.");
            continue;
        }
        *wynik = (int)liczba;
        if (liczba != *wynik) {
            puts("Podaj liczbe calkowita.");
            continue;
        }
        return 1;
    }
}

int main(void)
{
    int a, b;
    if (!wczytaj("Pierwsza liczba: ", &a) ||
        !wczytaj("Druga liczba: ", &b))
        return 0;

    int a_parzysta = (a % 2 == 0);
    int b_parzysta = (b % 2 == 0);

    if (a_parzysta && b_parzysta) {
        puts("obie liczby sa parzyste");
    } else if (!a_parzysta && !b_parzysta) {
        puts("obie liczby sa nieparzyste");
    } else {
        puts("jedna liczba jest parzysta, a druga nieparzysta");
    }
    return 0;
}
