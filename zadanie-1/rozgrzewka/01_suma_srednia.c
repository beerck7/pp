#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int wczytaj(const char *pytanie, int minimum, int maksimum, int *wynik)
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
            !isfinite(liczba) || liczba < minimum || liczba > maksimum) {
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
    if (!wczytaj("Pierwsza liczba: ", -1000000, 1000000, &a) ||
        !wczytaj("Druga liczba: ", -1000000, 1000000, &b))
        return 0;
    printf("Suma: %d\n", a + b);
    printf("Srednia: %.2f\n", (a + b) / 2.0);
    return 0;
}
