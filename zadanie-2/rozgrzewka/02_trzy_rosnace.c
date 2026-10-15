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
    int poprzedni = 0, przedpoprzedni = 0, odczyt;
    int odczyty = 0, seria = 0;

    while (odczyty < 1000000) {
        if (!wczytaj_liczbe("Odczyt: ", -1000000, 1000000, &odczyt))
            return 0;
        odczyty++;
        if (seria > 0 && odczyt > poprzedni)
            seria++;
        else
            seria = 1;
        if (seria == 3) {
            printf("Trojka: %d %d %d\nOdczyty: %d\n",
                   przedpoprzedni, poprzedni, odczyt, odczyty);
            return 0;
        }
        przedpoprzedni = poprzedni;
        poprzedni = odczyt;
    }
    puts("Osiagnieto limit 1000000 odczytow.");
    return 0;
}
