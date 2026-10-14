#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

static const char *nazwa_trybu(int tryb)
{
    if (tryb == 1)
        return "Plasma";
    if (tryb == 2)
        return "Cryo Shield";
    if (tryb == 3)
        return "EMP";
    return "Nieznany";
}

static int losuj_argo(void)
{
    return 1 + (rand() % 3);
}

static int wczytaj_wybor(int *wynik)
{
    char wiersz[256], koniec;
    double liczba;
    int znak;

    while (1) {
        printf("Wybierz tryb (1-3): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawne dane.");
            continue;
        }
        if (sscanf(wiersz, "%lf %c", &liczba, &koniec) != 1 ||
            !isfinite(liczba) || liczba < 1 || liczba > 3) {
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

static int czy_powtorzyc(void)
{
    char wiersz[256];
    int znak;

    while (1) {
        printf("Czy chcesz przeprowadzic kolejny test? (t/n): ");
        if (fgets(wiersz, sizeof(wiersz), stdin) == NULL)
            return 0;
        if (strchr(wiersz, '\n') == NULL && !feof(stdin)) {
            while ((znak = getchar()) != '\n' && znak != EOF) { }
            puts("Niepoprawna odpowiedz. Wpisz t lub n.");
            continue;
        }
        char odp[32], nadmiar;
        if (sscanf(wiersz, "%31s %c", odp, &nadmiar) != 1) {
            puts("Niepoprawna odpowiedz. Wpisz t lub n.");
            continue;
        }
        if (strcmp(odp, "t") == 0 || strcmp(odp, "T") == 0 ||
            strcmp(odp, "tak") == 0 || strcmp(odp, "Tak") == 0 ||
            strcmp(odp, "1") == 0) {
            return 1;
        }
        if (strcmp(odp, "n") == 0 || strcmp(odp, "N") == 0 ||
            strcmp(odp, "nie") == 0 || strcmp(odp, "Nie") == 0 ||
            strcmp(odp, "0") == 0) {
            return 0;
        }
        puts("Niepoprawna odpowiedz. Wpisz t lub n.");
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));

    puts("=== SYSTEM TESTOWANIA MODULOW OCHRONNYCH ARGO ===");
    puts("Dostepne tryby:");
    puts("1 - Plasma");
    puts("2 - Cryo Shield");
    puts("3 - EMP");

    while (1) {
        int gracz;
        if (!wczytaj_wybor(&gracz))
            break;

        int argo = losuj_argo();
        printf("Twoj wybor: %s\n", nazwa_trybu(gracz));
        printf("Wybor ARGO: %s\n", nazwa_trybu(argo));

        if (gracz == argo) {
            puts("Wynik testu: remis.");
        } else if ((gracz == 1 && argo == 2) ||
                   (gracz == 2 && argo == 3) ||
                   (gracz == 3 && argo == 1)) {
            puts("Wynik testu: zwyciestwo uzytkownika!");
        } else {
            puts("Wynik testu: zwyciestwo systemu!");
        }

        if (!czy_powtorzyc())
            break;
    }

    puts("Koniec testow ARGO.");
    return 0;
}
