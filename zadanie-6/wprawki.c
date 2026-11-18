#include <stdio.h>
#include <stdlib.h>

// Napisz program, który:

// Tworzy dwie dynamiczne tablice po 10 liczb całkowitych: pierwszą za pomocą malloc(), drugą za pomocą calloc().
// Sprawdza poprawność obu alokacji.
// Wyświetla zawartość tablicy utworzonej przez calloc().
// Wypełnia obie tablice wartościami od 1 do 10 i wyświetla ich zawartość.
// Zwalnia przydzieloną pamięć.
// Zastanów się:

// Czym różnią się funkcje malloc() i calloc()? Dlaczego nie należy odczytywać elementów pierwszej tablicy przed ich zainicjalizowaniem?


// int main(){
//     int *tab1 = malloc(10 * sizeof(int));
//     int *tab2 = calloc(10, sizeof(int));

//     if(tab1 == NULL || tab2 == NULL){
//         printf("Blad przydzielania pamieci.\n");

//         free(tab1);
//         free(tab2);

//         return 1;
//     }

//     printf("Tablica po calloc:\n");

//     for(int i = 0; i < 10; i++){
//         printf("%d ", tab2[i]);
//     }

//     printf("\n");

//     for(int i = 0; i < 10; i++){
//         tab1[i] = i + 1;
//         tab2[i] = i + 1;
//     }

//     printf("\nTablica z malloc:\n");

//     for(int i = 0; i < 10; i++){
//         printf("%d ", tab1[i]);
//     }

//     printf("\n\nTablica z calloc:\n");

//     for(int i = 0; i < 10; i++){
//         printf("%d ", tab2[i]);
//     }

//     printf("\n");

//     free(tab1);
//     free(tab2);

//     return 0;
// }

// Obie funkcje przydzielają pamięć w trakcie działania programu. Różnią się tym, jak podajemy rozmiar i co dzieje się z pamięcią na początku:
// int *tab1 = malloc(10 * sizeof(int));
// int *tab2 = calloc(10, sizeof(int));
// - malloc() otrzymuje łączną liczbę bajtów i nie inicjalizuje pamięci.
// - calloc() otrzymuje liczbę elementów i rozmiar jednego elementu, a przydzieloną pamięć wypełnia zerowymi bajtami. Dla tablicy int elementy mają więc początkowo wartość 0.
// Elementów tablicy z malloc() nie wolno odczytywać przed zapisaniem do nich wartości: są niezainicjalizowane, a ich odczyt prowadzi do niezdefiniowanego zachowania. Najpierw trzeba np. zrobić:
// tab1[0] = 10;
// printf("%d\n", tab1[0]);
// Po użyciu pamięć z obu funkcji zwalniamy przez free().

// 2. Dynamiczna tablica struktur

// Wykorzystaj strukturę Sensor z rozgrzewki. Napisz program, który:

// Wczytuje liczbę czujników n.
// Dynamicznie przydziela pamięć na n struktur typu Sensor.
// Wypełnia tablicę danymi:
// identyfikatory: kolejne liczby od 1,
// temperatura: wartości wczytywane od użytkownika,
// stan aktywności: domyślnie 1.
// Wyświetla wszystkie czujniki, korzystając z funkcji print_sensor().
// Dezaktywuje wszystkie czujniki, których temperatura przekracza 80.
// Ponownie wyświetla zawartość tablicy i zwalnia pamięć.
// Zastanów się:

// Czy elementy dynamicznej tablicy struktur są rozmieszczone w pamięci jeden za drugim?


// typedef struct{
//     int sensor_id;
//     double temperature;
//     int activity;
// } Sensor;

// void print_sensor(const Sensor *s){
//     printf("id: %d\n", s->sensor_id);
//     printf("Temperatura: %.2f\n", s->temperature);
//     printf("Aktywnosc: %d\n\n", s->activity);
// }

// int main(){
//     int n;

//     printf("Podaj liczbe czujnikow: ");

//     if(scanf("%d", &n) != 1 || n <= 0){
//         printf("Niepoprawna liczba czujnikow.\n");
//         return 1;
//     }

//     Sensor *sensor = calloc((size_t)n, sizeof(Sensor));

//     if(sensor == NULL){
//         printf("Nie udalo sie przydzielic pamieci.\n");
//         return 1;
//     }

//     for(int i = 0; i < n; i++){
//         sensor[i].sensor_id = i + 1;
//         sensor[i].activity = 1;

//         printf("Podaj temperature czujnika %d: ", i + 1);

//         if(scanf("%lf", &sensor[i].temperature) != 1){
//             printf("Niepoprawna temperatura.\n");
//             free(sensor);
//             return 1;
//         }
//     }

//     printf("\nPrzed dezaktywacja:\n\n");

//     for(int i = 0; i < n; i++){
//         print_sensor(&sensor[i]);
//     }

//     for(int i = 0; i < n; i++){
//         if(sensor[i].temperature > 80){
//             sensor[i].activity = 0;
//         }
//     }

//     printf("Po dezaktywacji:\n\n");

//     for(int i = 0; i < n; i++){
//         print_sensor(&sensor[i]);
//     }

//     free(sensor);
//     sensor = NULL;

//     return 0;
// }


// 3. Powiększanie tablicy – realloc()

// Napisz program, który:

// Tworzy dynamiczną tablicę trzech liczb całkowitych i zapisuje w niej wartości 10, 20, 30.
// Wyświetla zawartość tablicy oraz adres jej pierwszego elementu.
// Powiększa tablicę do sześciu elementów za pomocą realloc().
// Sprawdza, czy operacja się powiodła.
// W nowych elementach zapisuje wartości 40, 50, 60.
// Ponownie wyświetla zawartość tablicy oraz jej adres.
// Zwalnia pamięć.
// Zastanów się:

// Czy po wywołaniu realloc() adres tablicy musi pozostać taki sam?
// Co dzieje się z wcześniej zapisanymi wartościami?
// Dlaczego do przechowywania wyniku realloc() warto użyć dodatkowego wskaźnika?


// int main(){

//     int *tab1 = calloc(3, sizeof(int));

//     if(tab1 ==NULL){
//         printf("Nie udalo sie przydzielic pamieci\n");
//         return 1;
//     }
//     tab1[0] = 10;
//     tab1[1] = 20;
//     tab1[2] = 30;

//     printf("Tablica przed powiekszeniem\n");

//     for(int i = 0; i < 3; i++){
//         printf("%d ", tab1[i]);
//     }

//     printf("\nAdres: %p\n", (void *)tab1);

//     int *tab2 = realloc(tab1, 6*sizeof(int));

//     if(tab2 == NULL){
//         printf("Nie udalo sie powiekszyc tablicy\n");
//         free(tab1);
//         return 1;
//     }

//     tab1 = tab2;
//     tab1[3] = 40;
//     tab1[4] = 50;
//     tab1[5] = 60;

//     printf("tablica po powiekszeniu\n");

//     for(int i =0;i<6;i++){
//         printf("%d ", tab1[i]);
//     }

//     printf("Adres %p\n", (void *)tab1);

//     free(tab1);
//     tab1=NULL;

//     return 0;
// }

// 4. Zmniejszanie tablicy

// Napisz program, który:

// Tworzy dynamiczną tablicę ośmiu liczb całkowitych.
// Wypełnia ją wartościami od 1 do 8.
// Zmniejsza tablicę do czterech elementów za pomocą realloc().
// Wyświetla wszystkie elementy pozostałej tablicy.
// Zwalnia pamięć.
// Zastanów się:

// Które wartości powinny zostać zachowane?
// Czy po zmniejszeniu tablicy można odczytać element arr[5]?
// Czy zmniejszenie tablicy musi spowodować zmianę jej adresu?

// int main(){
//     int *tab1 = calloc(8, sizeof(int));

//     if(tab1 == NULL){
//         printf("nie udalo sie przydzielic pamieci\n");
//         return 1;
//     }

//     for(int i=0;i<8;i++){
//         tab1[i] = i+1;
//     }
//     printf("\nTablica przed zmniejszeniem\n");

//     for(int i =0;i<8;i++){
//         printf("%d ", tab1[i]);
//     }

//     printf("\nTablica po zmiejszeniu\n");

//     int *tab2 = realloc(tab1, 4*sizeof(int));

//     for(int i=0;i<4;i++){
//         printf("%d ", tab2[i]);
//     }
//     free(tab1);
//     tab1=NULL;
//     return 0;
// }

// 5. Dopisywanie kolejnych elementów

// Napisz program, który wczytuje kolejne liczby całkowite aż do wprowadzenia zera. Program powinien:

// Utworzyć dynamiczną tablicę o początkowej pojemności 2 elementów.
// Zapisywać w niej kolejne wprowadzane wartości (bez kończącego zera).
// Gdy zabraknie miejsca, dwukrotnie zwiększać pojemność tablicy.
// Po zakończeniu wczytywania wyświetlić:
// wszystkie zapisane liczby,
// liczbę zapisanych elementów,
// aktualną pojemność tablicy,
// liczbę wykonanych operacji powiększenia.
// Zwolnić przydzieloną pamięć.
// Przykładowe dane wejściowe:

// 5 8 12 3 7 0
// Przykładowy wynik:

// Elements: 5 8 12 3 7
// Count: 5
// Capacity: 8
// Reallocations: 2
// Zastanów się:

// Czym różni się liczba zapisanych elementów od pojemności tablicy?
// Dlaczego nie powiększamy tablicy o jeden element przy każdym dodaniu?
// Co powinien zrobić program, jeśli realloc() nie powiedzie się?


// int main(){
//     int pojemnosc = 2;
//     int licznik = 0;
//     int powiekszenia = 0;
//     int liczba;

//     int *tab1 = calloc(pojemnosc, sizeof(int));

//     if(tab1 == NULL){
//         printf("Nie udalo sie przydzielic pamieci.\n");
//         return 1;
//     }

//     while(1){
//         printf("Podaj liczbe (0 konczy): ");

//         if(scanf("%d", &liczba) != 1){
//             printf("Niepoprawna liczba.\n");
//             free(tab1);
//             return 1;
//         }

//         if(liczba == 0){
//             break;
//         }

//         if(licznik == pojemnosc){
//             pojemnosc = pojemnosc * 2;

//             int *tab2 = realloc(tab1, pojemnosc * sizeof(int));

//             if(tab2 == NULL){
//                 printf("Nie udalo sie powiekszyc tablicy.\n");
//                 free(tab1);
//                 return 1;
//             }

//             tab1 = tab2;
//             powiekszenia++;
//         }

//         tab1[licznik] = liczba;
//         licznik++;
//     }

//     printf("\nLiczby: ");

//     for(int i = 0; i < licznik; i++){
//         printf("%d ", tab1[i]);
//     }

//     printf("\nLiczba elementow: %d\n", licznik);
//     printf("Pojemnosc: %d\n", pojemnosc);
//     printf("Liczba powiekszen: %d\n", powiekszenia);

//     free(tab1);
//     tab1 = NULL;

//     return 0;
// }

// 6. Usuwanie elementu z dynamicznej tablicy

// Napisz program, który:

// Tworzy dynamiczną tablicę sześciu liczb: 10, 20, 30, 40, 50, 60.
// Wczytuje indeks elementu, który należy usunąć.
// Przesuwa pozostałe elementy tak, aby w tablicy nie powstała luka.
// Zmniejsza liczbę zapisanych elementów o jeden.
// Wyświetla zmodyfikowaną tablicę.
// Zmniejsza zaalokowany obszar pamięci do nowej liczby elementów, o ile tablica nie jest pusta.
// Zwalnia pamięć.
// Przykład:

// Before: 10 20 30 40 50 60
// Index to remove: 2
// After: 10 20 40 50 60
// Zastanów się:

// Dlaczego samo wywołanie realloc() nie wystarczy do usunięcia elementu ze środka tablicy?
// Co należy zrobić, jeśli użytkownik poda nieprawidłowy indeks?
// Czy zawsze trzeba zmniejszać zaalokowaną pamięć po usunięciu elementu?

int main(){
    int n = 6;
    int indeks;

    int *tab = malloc(n * sizeof(int));

    if(tab == NULL){
        printf("Nie udalo sie przydzielic pamieci.\n");
        return 1;
    }

    tab[0] = 10;
    tab[1] = 20;
    tab[2] = 30;
    tab[3] = 40;
    tab[4] = 50;
    tab[5] = 60;

    printf("Przed: ");

    for(int i = 0; i < n; i++){
        printf("%d ", tab[i]);
    }

    printf("\nPodaj indeks do usuniecia: ");

    if(scanf("%d", &indeks) != 1 || indeks < 0 || indeks >= n){
        printf("Niepoprawny indeks.\n");
        free(tab);
        return 1;
    }

    for(int i = indeks; i < n - 1; i++){
        tab[i] = tab[i + 1];
    }

    n--;

    printf("Po usunieciu: ");

    for(int i = 0; i < n; i++){
        printf("%d ", tab[i]);
    }

    printf("\n");

    if(n > 0){
        int *nowa = realloc(tab, n * sizeof(int));

        if(nowa == NULL){
            printf("Nie udalo sie zmniejszyc przydzielonej pamieci.\n");
        }
        else{
            tab = nowa;
        }
    }

    free(tab);
    tab = NULL;

    return 0;
}
