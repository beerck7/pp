#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static int wczytaj_liczbe(int *wynik)
{
    char wiersz[256], *koniec;
    int znak;
    long liczba;

    while (1) {
        printf("Kod (1-2147483647): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strlen(wiersz) == sizeof(wiersz) - 1 && strchr(wiersz, '\n') == NULL) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane: za dlugi wiersz.");
            continue;
        }
        errno = 0;
        liczba = strtol(wiersz, &koniec, 10);
        if (koniec == wiersz || errno != 0) {
            puts("Niepoprawne dane: podaj liczbe calkowita.");
            continue;
        }
        while (isspace((unsigned char)*koniec))
            koniec++;
        if (*koniec != '\0' || liczba < 1 || liczba > 2147483647L) {
            puts("Niepoprawne dane: jedna liczba calkowita od 1 do 2147483647.");
            continue;
        }
        *wynik = (int)liczba;
        return 1;
    }
}

int main(void)
{
    int kod, suma = 0, maksimum = 0, parzyste = 0;

    if (!wczytaj_liczbe(&kod))
        return 0;
    while (kod > 0) {
        int cyfra = kod % 10;
        suma += cyfra;
        if (cyfra > maksimum)
            maksimum = cyfra;
        if (cyfra % 2 == 0)
            parzyste++;
        kod /= 10;
    }
    printf("Suma cyfr: %d\nNajwieksza cyfra: %d\nCyfry parzyste: %d\n",
           suma, maksimum, parzyste);
    return 0;
}
