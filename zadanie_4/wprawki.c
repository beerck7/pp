#include <stdio.h>
#include <stdlib.h>

// 1. Min–max w jednym wywołaniu

// System analizy wyników zawodów sportowych przechowuje punkty uzyskane przez uczestników w tablicy liczb całkowitych. Napisz funkcję:

// void find_min_max(const int *data, int n, int *min, int *max);

// Funkcja powinna znaleźć najmniejszą i największą wartość w tablicy oraz przekazać oba wyniki za pomocą wskaźników.

// W funkcji main() utwórz tablicę wyników, wywołaj funkcję i wyświetl znalezione wartości. Przyjmij, że tablica zawiera co najmniej jeden element.

// Zastanów się:

// Dlaczego funkcja nie musi zwracać wartości przez return?
// Dlaczego zastosowano const int *data?

// void find_min_max(const int *data, int n, int *min, int *max){
//     for(int i=0; i<n;i++){
//         if(data[i]<*min){
//             *min = data[i];
//         }
//         if(data[i]>*max){
//             *max = data[i];
//         }
//     }
// }

// int main(){
//     int data[5] = {1,2,3,4,5};
//     int n = 5;
//     int min = data[0], max=data[0];
//     find_min_max(data, n, &min, &max);
//     printf("Minimum: %d, Maksimum: %d", min, max);
//     return 0;
// }


// 2. Odwracanie tablicy

// W systemie archiwizacji danych należy odwrócić kolejność zapisanych identyfikatorów. Napisz funkcję:

// void reverse_array(int *data, int n);

// Funkcja powinna odwrócić kolejność elementów tablicy bez używania dodatkowej tablicy.

// Wykorzystaj dwa wskaźniki: jeden wskazujący na pierwszy element, drugi na ostatni. Przesuwaj je w przeciwnych kierunkach, zamieniając wskazywane wartości.

// W main() przetestuj funkcję na tablicach o parzystej i nieparzystej liczbie elementów.

// Zastanów się:

// Kiedy należy zakończyć zamienianie elementów?
// Czy funkcja będzie działała poprawnie dla tablicy jednoelementowej?

// void reverse_array(int *data, int n){
//     if (n <= 1) return;

//     int *left = data;
//     int *right = data + n - 1;
//     while (left < right) {
//         int tmp = *left;
//         *left = *right;
//         *right = tmp;
//         left++;
//         right--;
//     }
// }

// int main(void){
//     int odd[] = {1, 2, 3, 4, 5};
//     int even[] = {1, 2, 3, 4};
//     int odd_n = sizeof odd / sizeof odd[0];
//     int even_n = sizeof even / sizeof even[0];
//     reverse_array(odd, odd_n);
//     reverse_array(even, even_n);

//     printf("Nieparzysta: ");
//     for (int i = 0; i < odd_n; i++) printf("%d ", odd[i]);
//     printf("\nParzysta: ");
//     for (int i = 0; i < even_n; i++) printf("%d ", even[i]);
//     printf("\n");
//     return 0;
// }

// 3. Licznik prób dostępu

// Moduł autoryzacji rejestruje kolejne próby uzyskania dostępu do systemu. Napisz funkcję:

// int check_access(int access_code);

// Przyjmij, że poprawny kod dostępu to 1234. Funkcja powinna zwracać 1 dla poprawnego kodu i 0 dla niepoprawnego.

// Dodatkowo funkcja powinna zapamiętywać liczbę wszystkich dotychczasowych wywołań i po każdej próbie wyświetlać jej numer. Licznik ma zachowywać wartość między wywołaniami, ale nie powinien być bezpośrednio dostępny poza funkcją.

// W main() wykonaj kilka prób dostępu, w tym udanych i nieudanych.

// Zastanów się:

// Jakiego rodzaju zmiennej należy użyć do przechowywania licznika?
// Dlaczego nie trzeba przekazywać licznika jako argumentu?

int check_access(int access_code){
    static int licznik = 0;
    licznik++;
    printf("\nTo jest %d proba", licznik);
    if(access_code==1234){return 1;};
    return 0;
}

int main(){
    int code = 1234;
    int test[5] = {1212,1221,3333,1234,5555};
    int i =0;
    while(i<5){
    if(check_access(test[i])){
        printf("\nKod poprawny");
    }
    else{
        printf("\nKod bledny");
    }
    i++;
}
    return 0;

}


// 4. Przesuwanie wskaźnika

// W tablicy przechowywane są kolejne wartości pomiarów. Napisz funkcję:

// int sum_selected(const int *data, int n);

// Funkcja powinna obliczać sumę elementów znajdujących się na indeksach parzystych: 0, 2, 4, ....

// Do przechodzenia po tablicy wykorzystaj wskaźnik, przesuwając go o dwa elementy w każdej iteracji. Zadbaj o to, aby nie wykonywać arytmetyki wskaźników poza dozwolonym zakresem tablicy.

// W main() przetestuj funkcję na tablicach o różnej długości.

// Zastanów się:

// O ile bajtów przesuwa się wskaźnik typu int * po wykonaniu ptr += 2?
// Dlaczego musimy uwzględnić liczbę elementów tablicy?
// 5. Niebezpieczny adres

// Przeanalizuj poniższy program:

// #include <stdio.h>

// int *get_value(void) {
//     int value = 100;
//     return &value;
// }

// int main(void) {
//     int *ptr = get_value();
//     printf("%d\n", *ptr);
//     return 0;
// }

// Wyjaśnij, dlaczego program jest niepoprawny, mimo że może się skompilować.

// Następnie przygotuj dwie poprawne wersje funkcji:

// pierwszą, która zwraca wynik przez return,
// drugą, która zapisuje wynik pod adresem przekazanym przez argument.
// Porównaj obie wersje pod względem czasu życia wykorzystywanych obiektów.
