#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 2.1 - Dzienny licznik zużycia energii

// Podczas testów urządzenia rejestrowane jest dzienne zużycie energii. Technik wprowadza kolejne dodatnie wartości, a 0 oznacza zakończenie pomiarów. Program powinien obliczyć:

// sumę wszystkich wprowadzonych wartości,
// liczbę pomiarów,
// największy pojedynczy pomiar.
// Jeżeli użytkownik od razu poda 0, program powinien poprawnie obsłużyć brak danych.

// int main(){
//     int pomiar;
//     int suma = 0, licznik = 0, max = 0;
//     int wynik, c;

//     while(1){
//         printf("Podaj zuzycie energii (0 - koniec): ");
//         wynik = scanf("%d", &pomiar);

//         if(wynik != 1){
//             printf("Niepoprawne dane\n");
//             while((c = getchar()) != '\n' && c != EOF);
//             if(c == EOF) return 1;
//         }

//         if(pomiar == 0){
//             break;
//         }

//         if(pomiar < 0){
//             printf("Pomiar musi byc dodatni\n");
//         }

//         suma += pomiar;
//         licznik++;

//         if(pomiar > max){
//             max = pomiar;
//         }
//     }

//     if(licznik == 0){
//         printf("Brak danych pomiarowych\n");
//     }
//     else{
//         printf("Suma pomiarow: %d\n", suma);
//         printf("Liczba pomiarow: %d\n", licznik);
//         printf("Najwiekszy pomiar: %d\n", max);
//     }

//     return 0;
// }


// 2.2 - Analiza kodu liczbowego

// W prostym systemie identyfikacyjnym kod dostępu zapisany jest jako dodatnia liczba całkowita. Przed dalszym przetwarzaniem system analizuje jej cyfry. Dla podanej liczby program powinien obliczyć:

// sumę cyfr,
// największą cyfrę,
// liczbę cyfr parzystych.
// Przykładowo dla liczby 58342 analizowane są kolejno cyfry 5, 8, 3, 4, 2.

// // int main(){
//     int liczba, dzielnik=1, cyfra;
//     int suma=0, max=0, parzyste=0;

//     printf("Podaj dodatnia liczbe calkowita: ");
//     if(scanf("%d", &liczba)!=1 || liczba<=0){
//         printf("Niepoprawna liczba\n");
//         return 1;
//     }

//     while(liczba/dzielnik>=10){
//         dzielnik *= 10;
//     }

//     while(dzielnik>0){
//         cyfra = liczba/dzielnik;

//         printf("Cyfra: %d\n", cyfra);

//         suma += cyfra;

//         if(cyfra>max){
//             max = cyfra;
//         }

//         if(cyfra%2==0){
//             parzyste++;
//         }

//         liczba = liczba%dzielnik;
//         dzielnik /= 10;
//     }

//     printf("Suma cyfr: %d\n", suma);
//     printf("Najwieksza cyfra: %d\n", max);
//     printf("Liczba cyfr parzystych: %d\n", parzyste);

//     return 0;
// }

// 2.3 - Zmiany odczytów sensora

// System monitorujący zapisuje kolejne odczyty jednego z sensorów. Użytkownik podaje 8 wartości całkowitych, które należy zapisać w tablicy. Następnie program powinien przeanalizować zmiany pomiędzy kolejnymi pomiarami i wyznaczyć:

// największy wzrost,
// największy spadek.
// Przykładowo: dla odczytów 40 44 41 52 50 kolejne zmiany wynoszą: +4 -3 +11 -2.

// int main(){
//     int i=0;
//     int tab[8];
//     int max_wzrost=0, max_spadek=0;
//     int tmp = 0;
  
//     while(i<8){
//         printf("Podaj kolejna liczbe: \n");
//         scanf("%d", &tab[i]);
//         i++;    
//     }
//     i = 0;
//     while(i<7){
//         tmp = tab[i+1];
//         if(tmp>tab[i]){
//             if(tmp-tab[i]>max_wzrost){
//                 max_wzrost = tmp-tab[i];
//             }
//         }
//         if(tmp<tab[i]){
//             if(tab[i]-tmp>max_spadek){
//                 max_spadek = tab[i]-tmp;
//             }
//         }
//         i++;
//     }
//     printf("Najwiekszy wzrost %d\n", max_wzrost);
//     printf("Najwiekszy spadek %d\n", max_spadek);
//     return 0;
// }

// 2.4 - Bufor ostatnich pomiarów

// Urządzenie przechowuje tylko 8 ostatnich odczytów. Początkowa tablica jest już wypełniona danymi. Pojawia się nowy pomiar, który należy dopisać do bufora. Program powinien:

// usunąć najstarszy odczyt,
// przesunąć pozostałe wartości o jedno miejsce,
// zapisać nową wartość na końcu tablicy,
// wyświetlić zawartość tablicy przed i po aktualizacji.

// Przykład:

// przed:
// 12 15 17 14 20 21 19 18

// nowy odczyt:
// 25

// po:
// 15 17 14 20 21 19 18 25

// int main(){
//     int tab[8] = {12,15,17,14,20,21,19,18};
//     int i=0, nowy;
//     printf("Tablica przed:\n");

//     while(i<8){
//         printf("%d ", tab[i]);
//         i++;
//     }

//     printf("\nPodaj nowy pomiar: ");
//     scanf("%d", &nowy);

//     i=0;
//     while(i<7){
//         tab[i] = tab[i+1];
//         i++;
//     }
//     tab[7] = nowy;
//     printf("Tablica po \n");
//     i=0;
//     while(i<8){
//         printf("%d ", tab[i]);
//         i++;
//     }
//     return 0;
// }


// 2.5 - Histogram wyników testu

// Podczas testów generatora losowego wykonano 50 symulowanych rzutów sześciościenną kostką. Program powinien:

// wygenerować 50 wyników z zakresu 1-6,
// policzyć, ile razy wystąpiła każda wartość,
// zapisać wyniki zliczania w tablicy,
// wyświetlić prosty histogram tekstowy.
// Przykład:

// 1: ********
// 2: **********
// 3: *****
// 4: *********
// 5: *******
// 6: ***********

// Liczba gwiazdek powinna odpowiadać liczbie wystąpień danej wartości.

// int main(){
//     int n =50;
//     int i=0;
//     srand(time(NULL));
//     int tab_testy[50];
//     int tab_zliczanie[6] = {0};
//     while(i<n){
//         tab_testy[i] = rand() % 6 + 1;
//         tab_zliczanie [tab_testy[i]-1] += 1;
//         i++;
//     }
//     i = 0;
//     int k =0;
//     while(i<6){
//         printf("%d: ", i+1);
//         while(k<tab_zliczanie[i]){
//             printf("*");
//             k++;
//         }
//         printf("\n");
//         k = 0;
//         i++;
//     }
//     return 0;
// }



// 2.6 - Najdłuższa seria wzrostowa

// Podczas obserwacji parametru systemowego zapisano serię kolejnych pomiarów. Użytkownik wprowadza 12 wartości całkowitych, które należy przechować w tablicy. Program powinien znaleźć najdłuższy fragment, w którym każdy kolejny pomiar jest większy od poprzedniego.

// Dla przykładowych danych: 4 6 9 3 5 7 8 2 10 11 1 0 najdłuższa seria rosnąca to: 3 5 7 8.

// Program powinien wyświetlić:

// długość najdłuższej serii,
// indeks jej początku,
// indeks jej końca.

// int main(){
//     int tab[12] = {0};
//     int i = 0;

//     int s_rosnaca = 1;
//     int idx_p = 0, idx_k = 0;

//     int tmp_s_rosnaca = 1;
//     int tmp_idx_p = 0;

//     while(i<12){
//         printf("Podaj kolejna wartosc: ");

//         if(scanf("%d", &tab[i])!=1){
//             printf("Nieprawidlowe dane\n");
//             return 1;
//         }
//         i++;
//     }

//     i = 0;

//     while(i<11){
//         if(tab[i]<tab[i+1]){
//             tmp_s_rosnaca++;
//         }
//         else{
//             tmp_s_rosnaca = 1;
//             tmp_idx_p = i+1;
//         }

//         if(tmp_s_rosnaca>s_rosnaca){
//             s_rosnaca = tmp_s_rosnaca;
//             idx_p = tmp_idx_p;
//             idx_k = i+1;
//         }

//         i++;
//     }

//     printf("Najdluzsza seria: %d\n", s_rosnaca);
//     printf("Indeks poczatku: %d\n", idx_p);
//     printf("Indeks konca: %d\n", idx_k);

//     return 0;
// }