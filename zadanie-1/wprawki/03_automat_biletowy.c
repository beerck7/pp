#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int wczytaj_int(const char *monit, int min, int max, int *wynik)
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
            !isfinite(liczba) || liczba < min || liczba > max) {
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

static int wczytaj_kwote(long long *wynik_grosze)
{
    char wiersz[256], koniec;
    double kwota;
    int znak;

    while (1) {
        printf("Podaj wplacana kwote (zl): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &kwota, &koniec) != 1 ||
            !isfinite(kwota) || kwota < 0.0 || kwota > 10000000.0) {
            puts("Niepoprawne dane.");
            continue;
        }
        if (fabs(kwota * 100.0 - llround(kwota * 100.0)) > 0.000001) {
            puts("Niepoprawne dane.");
            continue;
        }
        char *kropka = strchr(wiersz, '.');
        if (kropka != NULL) {
            int d = 0;
            char *p = kropka + 1;
            while (*p >= '0' && *p <= '9') {
                d++;
                p++;
            }
            if (d > 2) {
                puts("Niepoprawne dane.");
                continue;
            }
        }
        *wynik_grosze = (long long)llround(kwota * 100.0);
        return 1;
    }
}

int main(void)
{
    int typ, liczba;
    if (!wczytaj_int("Rodzaj biletu (1 - normalny, 2 - ulgowy): ", 1, 2, &typ))
        return 0;
    if (!wczytaj_int("Liczba biletow: ", 1, 1000000, &liczba))
        return 0;

    long long cena_jedn = (typ == 1) ? 400 : 200;
    long long cena_laczna = (long long)liczba * cena_jedn;
    printf("Laczna cena: %lld.%02lld zl\n", cena_laczna / 100, cena_laczna % 100);

    long long wplata;
    if (!wczytaj_kwote(&wplata))
        return 0;

    if (wplata < cena_laczna) {
        puts("Niewystarczajaca kwota.");
    } else if (wplata == cena_laczna) {
        puts("Wydano bilety.");
    } else {
        long long reszta = wplata - cena_laczna;
        printf("Wydano bilety. Reszta: %lld.%02lld zl\n", reszta / 100, reszta % 100);
    }
    return 0;
}
