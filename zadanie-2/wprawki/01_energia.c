#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

static int wczytaj_energie(double *wynik)
{
    char wiersz[256], *koniec;
    int znak;
    double liczba;

    while (1) {
        printf("Zuzycie (0 = koniec): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strlen(wiersz) == sizeof(wiersz) - 1 && strchr(wiersz, '\n') == NULL) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane: za dlugi wiersz.");
            continue;
        }
        errno = 0;
        liczba = strtod(wiersz, &koniec);
        if (koniec == wiersz || errno != 0 || !isfinite(liczba)) {
            puts("Niepoprawne dane: podaj liczbe.");
            continue;
        }
        while (isspace((unsigned char)*koniec))
            koniec++;
        if (*koniec != '\0' || liczba < 0 || liczba > 1000000) {
            puts("Niepoprawne dane: jedna liczba od 0 do 1000000.");
            continue;
        }
        *wynik = liczba;
        return 1;
    }
}

int main(void)
{
    int ile = 0;
    double pomiar, suma = 0, maksimum = 0;

    while (ile < 1000000) {
        if (!wczytaj_energie(&pomiar))
            return 0;
        if (pomiar == 0)
            break;
        suma += pomiar;
        ile++;
        if (pomiar > maksimum)
            maksimum = pomiar;
    }
    if (ile == 1000000)
        puts("Osiagnieto limit 1000000 pomiarow.");
    if (ile == 0)
        puts("Brak danych.");
    else
        printf("Suma: %.2f\nPomiary: %d\nMaksimum: %.2f\n", suma, ile, maksimum);
    return 0;
}
