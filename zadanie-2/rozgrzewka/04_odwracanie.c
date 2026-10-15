#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static int wczytaj_liczbe(const char *pytanie, int min, int max, int *wynik)
{
    char wiersz[256], *koniec;
    int znak;
    long liczba;

    while (1) {
        printf("%s", pytanie);
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
        if (*koniec != '\0' || liczba < min || liczba > max) {
            printf("Niepoprawne dane: jedna liczba calkowita od %d do %d.\n", min, max);
            continue;
        }
        *wynik = (int)liczba;
        return 1;
    }
}

int main(void)
{
    int tablica[8];

    for (int i = 0; i < 8; i++) {
        if (!wczytaj_liczbe("Liczba: ", -1000000, 1000000, &tablica[i]))
            return 0;
    }
    printf("Od tylu:");
    for (int i = 7; i >= 0; i--)
        printf(" %d", tablica[i]);
    puts("");
    for (int i = 0; i < 4; i++) {
        int pomocnicza = tablica[i];
        tablica[i] = tablica[7 - i];
        tablica[7 - i] = pomocnicza;
    }
    printf("Po zamianach:");
    for (int i = 0; i < 8; i++)
        printf(" %d", tablica[i]);
    puts("");
    return 0;
}
