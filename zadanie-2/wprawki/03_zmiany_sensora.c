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
        printf("Odczyt: ");
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
    int odczyty[8], wzrost = 0, spadek = 0;

    for (int i = 0; i < 8; i++) {
        if (!wczytaj_liczbe(&odczyty[i]))
            return 0;
    }
    for (int i = 1; i < 8; i++) {
        int zmiana = odczyty[i] - odczyty[i - 1];
        if (zmiana > wzrost)
            wzrost = zmiana;
        if (-zmiana > spadek)
            spadek = -zmiana;
    }
    if (wzrost > 0)
        printf("Najwiekszy wzrost: %d\n", wzrost);
    else
        puts("Brak wzrostow.");
    if (spadek > 0)
        printf("Najwiekszy spadek: %d\n", spadek);
    else
        puts("Brak spadkow.");
    return 0;
}
