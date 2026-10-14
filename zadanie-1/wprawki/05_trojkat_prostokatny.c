#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj_bok(const char *monit, int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("%s", monit);
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < 1 || liczba > 1000000) {
            puts("Niepoprawne dane.");
            continue;
        }
        *wynik = (int)liczba;
        if (liczba != *wynik) {
            puts("Niepoprawne dane.");
            continue;
        }
        return 1;
    }
}

int main(void)
{
    int a, b, c;
    if (!wczytaj_bok("Podaj dlugosc pierwszego boku: ", &a) ||
        !wczytaj_bok("Podaj dlugosc drugiego boku: ", &b) ||
        !wczytaj_bok("Podaj dlugosc trzeciego boku: ", &c))
        return 0;

    int x = a, y = b, z = c;
    if (x > z) { int t = x; x = z; z = t; }
    if (y > z) { int t = y; y = z; z = t; }

    long long sq1 = (long long)x * x;
    long long sq2 = (long long)y * y;
    long long sq_hyp = (long long)z * z;

    if (sq1 + sq2 == sq_hyp) {
        puts("Pomiary potwierdzaja kat prosty.");
    } else {
        puts("Pomiary nie potwierdzaja kata prostego.");
    }
    return 0;
}
