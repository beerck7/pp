#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static int wczytaj_wiersz(const char *pytanie, char wiersz[256])
{
    int znak;
    printf("%s", pytanie);
    if (fgets(wiersz, 256, stdin) == NULL)
        return 0;
    if (strlen(wiersz) == 255 && strchr(wiersz, '\n') == NULL) {
        while ((znak = getchar()) != '\n' && znak != EOF) { }
        puts("Niepoprawne dane: za dlugi wiersz.");
        return -1;
    }
    return 1;
}

static int wczytaj_liczbe(const char *pytanie, int min, int max, int *wynik)
{
    char wiersz[256], *koniec;
    long liczba;
    while (1) {
        int stan = wczytaj_wiersz(pytanie, wiersz);
        if (stan == 0)
            return 0;
        if (stan < 0)
            continue;
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

static int zaloguj(void)
{
    char wiersz_loginu[256], wiersz_hasla[256];
    char login[32], haslo[32], nadmiar;

    for (int proba = 0; proba < 3; proba++) {
        int stan_loginu = wczytaj_wiersz("Login: ", wiersz_loginu);
        if (stan_loginu == 0)
            return 0;
        int stan_hasla = wczytaj_wiersz("Haslo: ", wiersz_hasla);
        if (stan_hasla == 0)
            return 0;
        if (stan_loginu == 1 && stan_hasla == 1 &&
            sscanf(wiersz_loginu, "%31s %c", login, &nadmiar) == 1 &&
            sscanf(wiersz_hasla, "%31s %c", haslo, &nadmiar) == 1 &&
            strcmp(login, "argo") == 0 && strcmp(haslo, "1234") == 0) {
            puts("Zalogowano.");
            return 1;
        }
        puts("Bledne logowanie.");
    }
    puts("Limit prob logowania.");
    return 0;
}

static void statystyki(const int odczyty[], int ile)
{
    int suma = 0, powyzej = 0, wzrost = 0, spadek = 0;
    if (ile == 0) {
        puts("Brak odczytow.");
        return;
    }
    for (int i = 0; i < ile; i++)
        suma += odczyty[i];
    double srednia = (double)suma / ile;
    for (int i = 0; i < ile; i++) {
        if (odczyty[i] > srednia)
            powyzej++;
        if (i > 0) {
            int zmiana = odczyty[i] - odczyty[i - 1];
            if (zmiana > wzrost)
                wzrost = zmiana;
            if (-zmiana > spadek)
                spadek = -zmiana;
        }
    }
    printf("Srednia: %.2f\nPowyzej sredniej: %d\n", srednia, powyzej);
    if (wzrost > 0)
        printf("Najwiekszy wzrost: %d\n", wzrost);
    else
        puts("Brak wzrostow.");
    if (spadek > 0)
        printf("Najwiekszy spadek: %d\n", spadek);
    else
        puts("Brak spadkow.");
}

static void alarmy(const int odczyty[], int ile)
{
    int ile_alarmow = 0;
    if (ile == 0) {
        puts("Brak odczytow.");
        return;
    }
    for (int i = 0; i < ile; i++) {
        if (odczyty[i] < -40 || odczyty[i] > 40) {
            printf("Alarm [%d]: %d\n", i, odczyty[i]);
            ile_alarmow++;
        }
    }
    if (ile_alarmow == 0)
        puts("Brak alarmow.");
}

int main(void)
{
    int odczyty[8], ile = 0, zalogowany = 0;

    while (1) {
        int opcja, wartosc, indeks;
        if (!zalogowany) {
            if (!zaloguj())
                return 0;
            zalogowany = 1;
        }
        puts("1 - Dodaj\n2 - Zmien\n3 - Lista\n4 - Statystyki\n5 - Alarmy\n6 - Czysc\n7 - Wyloguj\n0 - Koniec");
        if (!wczytaj_liczbe("Opcja: ", 0, 7, &opcja) || opcja == 0)
            return 0;
        switch (opcja) {
        case 1:
            if (!wczytaj_liczbe("Odczyt: ", -50, 50, &wartosc))
                return 0;
            if (ile == 8) {
                for (int i = 0; i < 7; i++)
                    odczyty[i] = odczyty[i + 1];
                ile--;
            }
            odczyty[ile] = wartosc;
            ile++;
            puts("Dodano.");
            break;
        case 2:
            if (ile == 0) {
                puts("Brak odczytow.");
                break;
            }
            if (!wczytaj_liczbe("Indeks (0-7): ", 0, 7, &indeks))
                return 0;
            if (indeks >= ile) {
                puts("Nieistniejacy indeks.");
                break;
            }
            if (!wczytaj_liczbe("Nowy odczyt: ", -50, 50, &wartosc))
                return 0;
            odczyty[indeks] = wartosc;
            puts("Zmieniono.");
            break;
        case 3:
            if (ile == 0) {
                puts("Brak odczytow.");
                break;
            }
            puts("Odczyty (od najstarszego):");
            for (int i = 0; i < ile; i++)
                printf("[%d] %d\n", i, odczyty[i]);
            break;
        case 4:
            statystyki(odczyty, ile);
            break;
        case 5:
            alarmy(odczyty, ile);
            break;
        case 6:
            ile = 0;
            puts("Wyczyszczono.");
            break;
        case 7:
            zalogowany = 0;
            puts("Wylogowano.");
            break;
        default:
            puts("Niepoprawne dane: nieistniejaca opcja.");
        }
    }
}
