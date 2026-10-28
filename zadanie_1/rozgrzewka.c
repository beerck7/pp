// 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// int main() {
//     int a, b;

//     printf("Podaj dwie liczby calkowite: ");
//     scanf("%d %d", &a, &b);

//     printf("Suma: %d\n", a+b);
//     printf("Srednia: %f\n", (a+b)/2.0);

//     return 0;
// }

// 2

// int main(){
//     int a,b;

//     printf("Podaj dwie liczby:");
//     scanf("%d %d", &a, &b);
//     if(a%2==0 && b%2==0){
//         printf("Obie liczby sa parzyste\n");
//     }
//     else if(a%2==0 || b%2==0){
//         printf("Jedna z liczb jest nieparzysta\n");
//     }
//     else{
//         printf("Obie liczby sa nieparzyste\n");
//     }
//     return 0;
// }

// 3

// int main(){
//     int a;
//     printf("Podaj rok:");
//     scanf("%d", &a);
//     if(a<1 || a>2027){
//         printf("Niepoprawny rok\n");
//         while(a<0 || a>2027){
//             printf("Podaj rok:");
//             scanf("%d", &a);
//         }
//     }
//     if(a%400==0 || (a%4==0 && a%100!=0)){
//         printf("Rok %d jest przestepny\n", a);
//     }
//     else{
//         printf("Rok %d nie jest przestepny\n", a);
//     }
// }

// 4

// int main(){
//     int a,b;
//     printf("Podaj liczbe scian kostki wieksza niz 4: ");
//     scanf("%d", &a);
//     if(a<4){
//         printf("Niepoprawna liczba scian\n");
//         while(a<4){
//             printf("Podaj liczbe scian kostki wieksza niz 4: ");
//             scanf("%d", &a);
//         }
//     }
//     srand(time(NULL));
//     b = rand() % a + 1;
//     printf("Wylosowano liczbe: %d\n", b);
// }