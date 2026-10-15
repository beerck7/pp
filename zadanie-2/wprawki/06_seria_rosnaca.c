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
        printf("Pomiar: ");
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
        if (*koniec != '\0' || liczba < -1000000 || liczba > 1000000) {
            puts("Niepoprawne dane: jedna liczba calkowita od -1000000 do 1000000.");
            continue;
        }
        *wynik = (int)liczba;
        return 1;
    }
}

int main(void)
{
    int pomiary[12];
    int poczatek = 0, najlepszy_poczatek = 0, najlepsza_dlugosc = 1;

    for (int i = 0; i < 12; i++) {
        if (!wczytaj_liczbe(&pomiary[i]))
            return 0;
    }
    for (int i = 1; i < 12; i++) {
        if (pomiary[i] <= pomiary[i - 1])
            poczatek = i;
        int dlugosc = i - poczatek + 1;
        if (dlugosc > najlepsza_dlugosc) {
            najlepsza_dlugosc = dlugosc;
            najlepszy_poczatek = poczatek;
        }
    }
    printf("Dlugosc: %d\nPoczatek: %d\nKoniec: %d\n", najlepsza_dlugosc,
           najlepszy_poczatek, najlepszy_poczatek + najlepsza_dlugosc - 1);
    return 0;
}
