#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

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
    int tablica[10], min, max, maksimum, ile = 0;

    if (!wczytaj_liczbe("Minimum: ", -1000000, 1000000, &min) ||
        !wczytaj_liczbe("Maksimum przedzialu: ", min, 1000000, &max))
        return 0;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
        tablica[i] = min + rand() % (max - min + 1);
    printf("Tablica:");
    for (int i = 0; i < 10; i++)
        printf(" %d", tablica[i]);
    puts("");
    maksimum = tablica[0];
    for (int i = 0; i < 10; i++) {
        if (tablica[i] > maksimum) {
            maksimum = tablica[i];
            ile = 1;
        } else if (tablica[i] == maksimum) {
            ile++;
        }
    }
    printf("Maksimum: %d\nWystapienia: %d\n", maksimum, ile);
    return 0;
}
