#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1

// int main(){
//     int i=0, proby=0, suma=0, max=0;
//     int pomiary[5];
//     int wynik, c;

//     while(i<5){
//         printf("Podaj pomiar nr %d: ", i+1);

//         wynik = scanf("%d", &pomiary[i]);
//         proby++;

//         if(wynik != 1){
//             printf("Niepoprawny pomiar\n");
//             while((c=getchar())!='\n' && c!=EOF);
//             if(c==EOF) return 1;
//         }
//         else if(pomiary[i]<=0){
//             printf("Niepoprawny pomiar\n");
//         }
//         else{
//             suma += pomiary[i];

//             if(pomiary[i]>max){
//                 max = pomiary[i];
//             }
//             i++;
//         }
//     }

//     i = 0;
//     while(i<5){
//         printf("Pomiar nr %d: %d\n", i+1, pomiary[i]);
//         i++;
//     }

//     printf("\nProbowano %d razy", proby);
//     printf("\nSuma pomiarow wynosi %d", suma);
//     printf("\nNajwieksza wartosc to %d\n", max);

//     return 0;
// }

// 2


// int main(){
//     int x, y, z;
//     int czy_rosnace = 0;
//     int l_odczytow = 0;

//     printf("Podaj pierwsza liczbe: ");
//     if(scanf("%d", &x) != 1) return 1;
//     l_odczytow++;

//     printf("Podaj druga liczbe: ");
//     if(scanf("%d", &y) != 1) return 1;
//     l_odczytow++;

//     while(czy_rosnace == 0){
//         printf("Podaj kolejna liczbe: ");
//         if(scanf("%d", &z) != 1) return 1;
//         l_odczytow++;

//         if(x < y && y < z){
//             czy_rosnace = 1;
//         }
//         else{
//             x = y;
//             y = z;
//         }
//     }

//     printf("Trzy czy_rosnace liczby: %d %d %d\n", x, y, z);
//     printf("Liczba wszystkich odczytow: %d\n", l_odczytow);

//     return 0;
// }

// 3 Napisz program, który wypełni tablicę 10 losowymi wartościami z przedziału [min, max] określonego przez użytkownika. Wyświetl ją na ekranie. Znajdź i podaj maksymalną wartość występującą w tablicy wraz z liczbą jej wystąpień.


// int main(){
//     int tab[10];
//     int i=0;
//     int min, max;
//     int najwieksza, ile=1;

//     printf("Podaj min wartosc przedzialu: \n");
//     if(scanf("%d", &min)!=1) return 1;

//     printf("Podaj max wartosc przedzialu: \n");
//     if(scanf("%d", &max)!=1) return 1;

//     while(max<min){
//         printf("Max musi byc >= min. Podaj max: ");
//         if(scanf("%d", &max)!=1) return 1;
//     }

//     srand(time(NULL));

//     while(i<10){
//         tab[i] = rand()%(max-min+1)+min;
//         printf("Wartosc %d to %d\n", i+1, tab[i]);
//         i++;
//     }

//     najwieksza = tab[0];
//     i = 1;

//     while(i<10){
//         if(tab[i]>najwieksza){
//             najwieksza = tab[i];
//             ile = 1;
//         }
//         else if(tab[i]==najwieksza){
//             ile++;
//         }
//         i++;
//     }

//     printf("Najwieksza wartosc: %d\n", najwieksza);
//     printf("Liczba wystapien: %d\n", ile);

//     return 0;
// }

// 4 Napisz program, który wczyta do tablicy 8 liczb całkowitych. Wyświetl tę tablicę w odwrotnej kolejności, bez tworzenia drugiej tablicy.
// Następnie zamień miejscami pierwszy element z ostatnim, drugi z przedostatnim itd., tak aby zawartość tablicy została rzeczywiście odwrócona. Wyświetl wynik.

// int main(){
//     int tab[8];
//     int i = 0;
//     int tmp;
//     while(i<8){
//         printf("Podaj %d wartosc tablicy liczb: ", i+1);
//         scanf("%d", &tab[i]);
//         i++;
//     }
//     printf("Odwracamy tablice bez przepisywania do drugiej: \n");
//     while(i>0){
//         printf("Wartosc %d tablicy to: %d\n", i, tab[i-1]);
//         i--;
//     }
//     while(i<4){
//         tmp = tab[i];
//         tab[i] = tab[7-i];
//         tab[7-i] = tmp;
//         i++;
//     }
//     i = 0;
//     printf("Faktycznie odwrocone elementy w tablicy: \n");
//     while(i<8){
//         printf("Wartosc %d tablicy to: %d\n", i+1, tab[i]);
//         i++;
//     }
//     return 0;
// }