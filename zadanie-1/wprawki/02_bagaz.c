#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj_wage(double *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("Podaj wage bagazu (kg): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < 0.0 || liczba > 200.0) {
            puts("Niepoprawne dane.");
            continue;
        }
        *wynik = liczba;
        return 1;
    }
}

int main(void)
{
    double waga;
    if (!wczytaj_wage(&waga))
        return 0;

    if (waga <= 23.0) {
        puts("Bagaz zaakceptowany bez doplaty.");
    } else if (waga <= 32.0) {
        puts("Wymagany jest dodatkowy koszt za nadbagaz.");
    } else {
        puts("Bagaz nie moze zostac przyjety.");
    }
    return 0;
}
