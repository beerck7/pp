#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

static int wczytaj_sciany(int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("Podaj liczbe scian kostki (min. 4): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < 4 || liczba > 1000000) {
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
    int sciany;
    if (!wczytaj_sciany(&sciany))
        return 0;

    srand((unsigned int)time(NULL));
    int wyrzucono = 1 + (rand() % sciany);
    printf("Wyrzucono: %d\n", wyrzucono);
    return 0;
}
