#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
// 1

// int main(){
//     srand(time(NULL));
//     int a = rand()%46 - 10;
//     if(a<0){
//         printf("Frost. Wear warm clothes\n");
//     }
//     else if(a>=0 && a<=25){
//         printf("Weather conditions are comfortable\n");
//     }
//     else{
//         printf("High temperature. Avoid overheating\n");
//     }
// }

// 2

// int main() {
//     float a;
//     int b, c;

//     printf("Podaj wage bagazu w kg: ");
//     b = scanf("%f", &a);

//     while (b != 1 || (b == 1 && (a < 0 || a > 200))) {
//         printf("Niepoprawna waga bagazu\n");
//         while ((c = getchar()) != '\n' && c != EOF);
//         printf("Podaj wage bagazu w kg: ");
//         b = scanf("%f", &a);
//     }

//     if (a >= 0 && a <= 23) {
//         printf("Bagaz zaakceptowany bez doplaty\n");
//     }
//     else if (a > 23 && a <= 32) {
//         printf("Wymagany jest dodatkowy koszt za nadbagaz\n");
//     }
//     else {
//         printf("Bagaz nie moze zostac przyjety\n");
//     }

//     return 0;
// }

// 3

// int main() {
//     int rodzaj, ilosc, cena, suma, c, b;
//     float wplata;

//     printf("1 - bilet normalny (4 zl)\n");
//     printf("2 - bilet ulgowy (2 zl)\n");

//     printf("Wybierz rodzaj biletu: ");
//     b = scanf("%d", &rodzaj);

//     while (b != 1 || (rodzaj != 1 && rodzaj != 2)) {
//         while ((c = getchar()) != '\n' && c != EOF);

//         printf("Niepoprawny rodzaj biletu\n");
//         printf("Wybierz rodzaj biletu: ");
//         b = scanf("%d", &rodzaj);
//     }

//     if (rodzaj == 1) {
//         cena = 4;
//     }
//     else {
//         cena = 2;
//     }

//     printf("Podaj liczbe biletow: ");
//     b = scanf("%d", &ilosc);

//     while (b != 1 || ilosc <= 0) {
//         while ((c = getchar()) != '\n' && c != EOF);

//         printf("Niepoprawna liczba biletow\n");
//         printf("Podaj liczbe biletow: ");
//         b = scanf("%d", &ilosc);
//     }

//     suma = cena * ilosc;
//     printf("Do zaplaty: %d zl\n", suma);

//     printf("Podaj wplacona kwote: ");
//     if (scanf("%f", &wplata) != 1 || wplata < 0) {
//         printf("Niepoprawna kwota\n");
//         return 1;
//     }

//     if (wplata == suma) {
//         printf("Wydano bilety\n");
//     }
//     else if (wplata > suma) {
//         printf("Wydano bilety\n");
//         printf("Reszta: %.2f zl\n", wplata - suma);
//     }
//     else {
//         printf("Niewystarczajaca kwota\n");
//     }

//     return 0;
// }

// 4

// int main(){

//     int a, A, B;
//     int rzedya, rzedyb;

//     printf("Podaj liczbe pasazerow: ");
//     scanf("%d", &a);
//     if(a<=0){
//         printf("Niepoprawna liczba pasazerow\n");
//         while(a<=0){
//             printf("Podaj liczbe pasazerow: ");
//             scanf("%d", &a);
//         }
//     }
//     rzedya = (a+2)/3;
//     rzedyb = (a+4)/5;
//     A = (3-a%3)%3;
//     B = (5-a%5)%5;
//     if (A<B)
//     {
//         printf("Mniej pustych miejsc zostaje w wariancie A: %d\n ", A);
//         printf("Liczba rzedow w wariancie A: %d\n ", rzedya);
//     }
//     else if(B<A){
//         printf("Mniej pustych miejsc zostaje w wariancie B: %d\n ", B);
//         printf("Liczba rzedow w wariancie B: %d\n ", rzedyb);
//     }
//     else{
//         printf("Warianty A i B zostawiaja tyle samo pustych miejsc: %d\n ", A);
//         printf("Liczba rzedow w wariancie A: %d\n ", rzedya);
//         printf("Liczba rzedow w wariancie B: %d\n ", rzedyb);
//     }
//     if (A == 0) {
//         printf("W wariancie A wszystkie miejsca sa zajete\n");
//     }
    
//     if (B == 0) {
//         printf("W wariancie B wszystkie miejsca sa zajete\n");
//     }
//     return 0;
// }

// 5

int main() {
    int a, b, c;
    int najdluzszy, x, y;

    printf("Podaj dlugosci bokow trojkata: ");

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Niepoprawne dane\n");
        return 1;
    }

    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Boki musza byc dodatnie\n");
        return 1;
    }

    if (a >= b && a >= c) {
        najdluzszy = a;
        x = b;
        y = c;
    }
    else if (b >= a && b >= c) {
        najdluzszy = b;
        x = a;
        y = c;
    }
    else {
        najdluzszy = c;
        x = a;
        y = b;
    }

    if ((long long)x*x + (long long)y*y ==
        (long long)najdluzszy*najdluzszy) {
        printf("Pomiary potwierdzaja kat prosty\n");
    }
    else {
        printf("Pomiary nie potwierdzaja kata prostego\n");
    }

    return 0;
}
