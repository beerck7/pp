// Zadanie główne
// Na pokładzie statku badawczego ARGO działa centralny system rejestrowania zdarzeń bezpieczeństwa. Dotychczas rejestr wykorzystywał tablicę o stałej pojemności, co ograniczało liczbę przechowywanych wpisów i prowadziło do nieefektywnego wykorzystania pamięci.

// Inżynierowie postanowili przebudować system tak, aby pamięć była przydzielana dynamicznie, a rejestr mógł zwiększać swoją pojemność wraz z napływem kolejnych zdarzeń. System powinien również umożliwiać usuwanie nieaktualnych wpisów oraz analizowanie zgromadzonych informacji. Twoim zadaniem jest opracowanie i przetestowanie systemu rejestrowania zdarzeń

// 1. Reprezentacja zdarzeń

// Zaprojektuj strukturę opisującą pojedyncze zdarzenie, zawierającą identyfikator, numer modułu, poziom zagrożenia (0–3) oraz wartość pomiaru.

// Rejestr powinien wykorzystywać dynamicznie alokowaną tablicę struktur. Program musi przechowywać informację o liczbie zarejestrowanych zdarzeń oraz aktualnej pojemności tablicy.

// Początkowa pojemność rejestru powinna wynosić 2 zdarzenia.

// 2. Rejestrowanie nowych zdarzeń

// Opracuj funkcję umożliwiającą dodawanie kolejnych zdarzeń do rejestru. Każde poprawnie zarejestrowane zdarzenie powinno otrzymać kolejny, unikalny identyfikator.

// Jeżeli liczba zdarzeń osiągnie aktualną pojemność tablicy, program powinien automatycznie zwiększyć ją dwukrotnie.

// Rozszerzanie rejestru musi zachowywać dotychczasowe dane. Niepowodzenie alokacji nie może powodować utraty wcześniej zapisanych zdarzeń.

// 3. Przeglądanie i wyszukiwanie zdarzeń

// Opracuj funkcje umożliwiające:

// wyświetlenie wszystkich zdarzeń w kolejności ich dodawania,
// wyszukanie zdarzenia na podstawie identyfikatora,
// wyświetlenie zdarzeń pochodzących ze wskazanego modułu,
// wyszukanie zdarzeń o określonym poziomie zagrożenia.
// Funkcje służące do odczytu danych nie mogą modyfikować zawartości rejestru.

// 4. Usuwanie zdarzeń

// Opracuj funkcję umożliwiającą usunięcie zdarzenia o wskazanym identyfikatorze.

// Po usunięciu wpisu pozostałe zdarzenia powinny zachować kolejność, a liczba zapisanych elementów powinna zostać odpowiednio zmniejszona.

// Usunięcie zdarzenia nie musi powodować natychmiastowego zmniejszenia zaalokowanego obszaru pamięci.

// 5. Raport bezpieczeństwa

// Opracuj funkcję generującą raport obejmujący:

// całkowitą liczbę zarejestrowanych zdarzeń,
// liczbę zdarzeń dla poszczególnych poziomów zagrożenia,
// średnią wartość zarejestrowanych pomiarów,
// identyfikator zdarzenia o najwyższej wartości pomiaru,
// liczbę zdarzeń pochodzących ze wskazanego modułu.
// Raport powinien prawidłowo obsługiwać również pusty rejestr.

// 6. Zarządzanie pamięcią i testowanie

// Program powinien poprawnie obsługiwać dynamiczną alokację i zmianę rozmiaru tablicy oraz zwalniać całą przydzieloną pamięć po zakończeniu pracy.

// W funkcji main() przygotuj sekwencję testów obejmującą:

// dodawanie zdarzeń i wielokrotne zwiększanie pojemności rejestru,
// przeglądanie i wyszukiwanie wpisów,
// usuwanie pierwszego, ostatniego i wybranego środkowego zdarzenia,
// generowanie raportu dla pustego i niepustego rejestru,
// obsługę niepoprawnych danych oraz sytuacji, w której operacja alokacji pamięci zakończy się niepowodzeniem.
// Sprawdź, czy operacje dodawania i usuwania zdarzeń nie prowadzą do utraty lub niezamierzonej modyfikacji pozostałych danych.

// Nie jest wymagane tworzenie menu ani wczytywanie danych od użytkownika. Dane testowe mogą być przygotowane bezpośrednio w programie, a poszczególne operacje wykonywane za pomocą odpowiednich wywołań funkcji w main().a

#include <stdio.h>
#include <stdlib.h>

/* Pozwala sprawdzic zachowanie przy niepowodzeniu alokacji. */
int test_bledu_alokacji = 0;

typedef struct{
    int id;
    int modul;
    int zagrozenie;
    double pomiar;
} Event;

typedef struct{
    Event *tab;
    int liczba;
    int pojemnosc;
    int kolejne_id;
} Rejestr;

int dodaj(Rejestr *r, int modul, int zagrozenie, double pomiar){
    /* Przyjete granice techniczne dla przykladowego programu. */
    if(modul <= 0 || zagrozenie < 0 || zagrozenie > 3 ||
       !(pomiar >= -1000000 && pomiar <= 1000000)){
        printf("Niepoprawne dane.\n");
        return 0;
    }

    if(r->kolejne_id > 1000000){
        printf("Brak dostepnych identyfikatorow.\n");
        return 0;
    }

    if(r->liczba == r->pojemnosc){
        if(r->pojemnosc >= 32768){
            printf("Rejestr jest zbyt duzy.\n");
            return 0;
        }
        int nowa_pojemnosc = r->pojemnosc * 2;

        Event *nowa = NULL;
        if(!test_bledu_alokacji){
            nowa = realloc(r->tab, (size_t)nowa_pojemnosc * sizeof(Event));
        }

        if(nowa == NULL){
            printf("Nie udalo sie powiekszyc rejestru.\n");
            return 0;
        }

        r->tab = nowa;
        r->pojemnosc = nowa_pojemnosc;

        printf("Nowa pojemnosc: %d\n", r->pojemnosc);
    }

    int i = r->liczba;

    r->tab[i].id = r->kolejne_id;
    r->tab[i].modul = modul;
    r->tab[i].zagrozenie = zagrozenie;
    r->tab[i].pomiar = pomiar;

    r->liczba++;
    r->kolejne_id++;

    return 1;
}

void pokaz_jedno(const Event *e){
    printf("ID: %d, modul: %d, zagrozenie: %d, pomiar: %.2f\n",
           e->id, e->modul, e->zagrozenie, e->pomiar);
}

void pokaz_wszystkie(const Rejestr *r){
    if(r->liczba == 0){
        printf("Rejestr jest pusty.\n");
    }

    for(int i = 0; i < r->liczba; i++){
        pokaz_jedno(&r->tab[i]);
    }
}

void szukaj_id(const Rejestr *r, int id){
    for(int i = 0; i < r->liczba; i++){
        if(r->tab[i].id == id){
            pokaz_jedno(&r->tab[i]);
            return;
        }
    }

    printf("Nie znaleziono ID %d.\n", id);
}

void szukaj_modulu(const Rejestr *r, int modul){
    int znaleziono = 0;

    for(int i = 0; i < r->liczba; i++){
        if(r->tab[i].modul == modul){
            pokaz_jedno(&r->tab[i]);
            znaleziono = 1;
        }
    }

    if(znaleziono == 0){
        printf("Nie znaleziono zdarzen z modulu %d.\n", modul);
    }
}

void szukaj_zagrozenia(const Rejestr *r, int poziom){
    int znaleziono = 0;

    for(int i = 0; i < r->liczba; i++){
        if(r->tab[i].zagrozenie == poziom){
            pokaz_jedno(&r->tab[i]);
            znaleziono = 1;
        }
    }

    if(znaleziono == 0){
        printf("Nie znaleziono zdarzen o poziomie %d.\n", poziom);
    }
}

int usun(Rejestr *r, int id){
    for(int i = 0; i < r->liczba; i++){
        if(r->tab[i].id == id){

            for(int j = i; j < r->liczba - 1; j++){
                r->tab[j] = r->tab[j + 1];
            }

            r->liczba--;
            return 1;
        }
    }

    return 0;
}

void raport(const Rejestr *r, int modul){
    int poziomy[4] = {0, 0, 0, 0};
    int liczba_modulu = 0;
    int indeks_max = 0;
    double suma = 0;

    printf("Liczba zdarzen: %d\n", r->liczba);

    if(r->liczba == 0){
        printf("Rejestr jest pusty. Brak pomiarow.\n");

        for(int i = 0; i < 4; i++){
            printf("Poziom %d: 0\n", i);
        }

        printf("Liczba zdarzen z modulu %d: 0\n", modul);
        return;
    }

    for(int i = 0; i < r->liczba; i++){
        poziomy[r->tab[i].zagrozenie]++;

        suma = suma + r->tab[i].pomiar;

        if(r->tab[i].pomiar > r->tab[indeks_max].pomiar){
            indeks_max = i;
        }

        if(r->tab[i].modul == modul){
            liczba_modulu++;
        }
    }

    for(int i = 0; i < 4; i++){
        printf("Poziom %d: %d\n", i, poziomy[i]);
    }

    printf("Srednia pomiarow: %.2f\n", suma / r->liczba);
    printf("ID najwyzszego pomiaru: %d\n", r->tab[indeks_max].id);
    printf("Liczba zdarzen z modulu %d: %d\n",
           modul, liczba_modulu);
}

int main(){
    Rejestr r;

    r.liczba = 0;
    r.pojemnosc = 2;
    r.kolejne_id = 1;
    r.tab = malloc(r.pojemnosc * sizeof(Event));

    if(r.tab == NULL){
        printf("Nie udalo sie utworzyc rejestru.\n");
        return 1;
    }

    printf("=== PUSTY REJESTR ===\n");
    pokaz_wszystkie(&r);
    raport(&r, 1);

    printf("\n=== DODAWANIE ZDARZEN ===\n");

    dodaj(&r, 1, 0, 20);
    dodaj(&r, 2, 1, 45);
    printf("\n=== TEST BLEDU ALOKACJI ===\n");
    test_bledu_alokacji = 1;
    if(!dodaj(&r, 3, 2, 70)){
        printf("Wpis nie zostal dodany. Wczesniejsze dane:\n");
        pokaz_wszystkie(&r);
    }
    test_bledu_alokacji = 0;
    dodaj(&r, 3, 2, 70);
    dodaj(&r, 1, 3, 110);
    dodaj(&r, 2, 1, 55);
    dodaj(&r, 1, 2, 80);

    pokaz_wszystkie(&r);

    printf("\n=== SZUKANIE PO ID ===\n");
    szukaj_id(&r, 3);
    szukaj_id(&r, 99);

    printf("\n=== ZDARZENIA MODULU 1 ===\n");
    szukaj_modulu(&r, 1);

    printf("\n=== ZAGROZENIE POZIOMU 2 ===\n");
    szukaj_zagrozenia(&r, 2);

    printf("\n=== RAPORT ===\n");
    raport(&r, 1);

    printf("\n=== NIEPOPRAWNE DANE ===\n");
    dodaj(&r, 1, 5, 30);
    dodaj(&r, 0, 1, 30);

    printf("\n=== USUWANIE ===\n");

    if(usun(&r, 1)){
        printf("Usunieto pierwsze zdarzenie: ID 1.\n");
    }

    if(usun(&r, 6)){
        printf("Usunieto ostatnie zdarzenie: ID 6.\n");
    }

    if(usun(&r, 3)){
        printf("Usunieto srodkowe zdarzenie: ID 3.\n");
    }

    if(usun(&r, 99) == 0){
        printf("Nie znaleziono ID 99.\n");
    }

    printf("\n=== REJESTR PO USUNIECIU ===\n");
    pokaz_wszystkie(&r);

    printf("\n=== DODANIE PO USUNIECIU ===\n");
    dodaj(&r, 3, 3, 95);
    pokaz_wszystkie(&r);

    printf("\n=== RAPORT KONCOWY ===\n");
    raport(&r, 1);

    free(r.tab);
    r.tab = NULL;

    return 0;
}
