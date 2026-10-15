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
        printf("Nowy odczyt: ");
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
    int bufor[8] = {12, 15, 17, 14, 20, 21, 19, 18};
    int nowy;

    printf("Przed:");
    for (int i = 0; i < 8; i++)
        printf(" %d", bufor[i]);
    puts("");
    if (!wczytaj_liczbe(&nowy))
        return 0;
    for (int i = 0; i < 7; i++)
        bufor[i] = bufor[i + 1];
    bufor[7] = nowy;
    printf("Po:");
    for (int i = 0; i < 8; i++)
        printf(" %d", bufor[i]);
    puts("");
    return 0;
}
