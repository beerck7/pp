#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj_rok(int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("Podaj rok: ");
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
    int rok;
    if (!wczytaj_rok(&rok))
        return 0;

    if ((rok % 400 == 0) || (rok % 4 == 0 && rok % 100 != 0)) {
        printf("Rok %d jest przestepny.\n", rok);
    } else {
        printf("Rok %d nie jest przestepny.\n", rok);
    }
    return 0;
}
