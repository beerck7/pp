#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

static int wczytaj_pomiar(double *wynik)
{
    char wiersz[256], *koniec;
    int znak;
    double liczba;

    printf("Pomiar: ");
    if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
        return 0;
    if (strlen(wiersz) == sizeof(wiersz) - 1 && strchr(wiersz, '\n') == NULL) {
        while ((znak = getchar()) != '\n' && znak != EOF) { }
        puts("Niepoprawne dane: za dlugi wiersz.");
        return -1;
    }
    errno = 0;
    liczba = strtod(wiersz, &koniec);
    if (koniec == wiersz || errno != 0 || !isfinite(liczba)) {
        puts("Niepoprawne dane: podaj liczbe.");
        return -1;
    }
    while (isspace((unsigned char)*koniec))
        koniec++;
    if (*koniec != '\0' || liczba < -1000000 || liczba > 1000000) {
        puts("Niepoprawne dane: zakres od -1000000 do 1000000, jedna liczba.");
        return -1;
    }
    *wynik = liczba;
    return 1;
}

int main(void)
{
    int proby = 0, przyjete = 0;
    double suma = 0, maksimum = 0, pomiar;

    while (przyjete < 5 && proby < 1000000) {
        int stan = wczytaj_pomiar(&pomiar);
        if (stan == 0)
            return 0;
        proby++;
        if (stan < 0)
            continue;
        if (pomiar <= 0) {
            puts("Pomiar musi byc dodatni.");
            continue;
        }
        suma += pomiar;
        if (pomiar > maksimum)
            maksimum = pomiar;
        przyjete++;
    }
    if (przyjete < 5) {
        puts("Osiagnieto limit 1000000 prob.");
        return 0;
    }
    printf("Proby: %d\nSuma: %.2f\nMaksimum: %.2f\n", proby, suma, maksimum);
    return 0;
}
