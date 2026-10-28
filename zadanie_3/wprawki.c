#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// 1. Wzmacnianie sygnału

// W systemie pomiarowym wartość sygnału zmienia się w kolejnych krokach zgodnie ze stałym współczynnikiem wzmocnienia. Napisz funkcję:

// double amplified_signal(double base_value, double gain, int steps);

// Funkcja powinna obliczać i zwracać wartość sygnału po steps krokach, zgodnie ze wzorem:Sn​=baseValue×(gain)steps
//  Obliczenia należy wykonać iteracyjnie, wykorzystując pętlę, bez korzystania z funkcji potęgowania.

// W funkcji main() wczytaj wartości początkowe, wywołaj funkcję i wyświetl wynik.



// double amplified_signal(double base_value, double gain, int steps){
//     int i = 0;
//     double result = 1;
//     while(i<steps){
//         result *= gain;
//         i++;
//     }
//     return base_value*result;
// }

// int main(){
//     double base_value, gain;
//     int steps;
//     printf("Podaj wartosc bazowa, wzmocnienie i ilosc krokow: \n");
//     scanf("%lf %lf %d", &base_value, &gain, &steps);
//     printf("Wynik wynosi: %.2lf", amplified_signal(base_value,gain,steps));
//     return 0;
// }

// 2. Identyfikatory pierwsze

// W systemie ewidencji urządzeń każde urządzenie ma unikalny identyfikator będący liczbą całkowitą. Na potrzeby testów wybrano urządzenia, których identyfikatory są liczbami pierwszymi.. Napisz funkcję:

// int is_prime(int id);

// która sprawdza, czy numer identyfikacyjny id spełnia warunek „liczby pierwszej”. Funkcja powinna zwrócić 1 dla numerów pierwszych i 0 dla pozostałych.

// W main() wczytaj numer produktu i wyświetl informację, czy należy do grupy „priorytetowej”.


// int is_prime(int id) {
//     if (id < 2) {
//         return 0;
//     }

//     for (int i = 2; i <= id / i; i++) {
//         if (id % i == 0) {
//             return 0;
//         }
//     }

//     return 1;
// }

// int main() {
//     int id;
//     printf("Podaj id: ");
//     scanf("%d", &id);

//     if (is_prime(id)) {
//         printf("Urzadzenie nalezy do grupy priorytetowej\n");
//     } else {
//         printf("Urzadzenie nie nalezy do grupy priorytetowej\n");
//     }

//     return 0;
// }

// 3. Zamiana odczytów

// W systemie akwizycji danych dwa czujniki zostały błędnie podłączone, przez co ich odczyty są przypisywane do niewłaściwych zmiennych. Aby skorygować dane, należy zamienić zapisane wartości miejscami. Napisz funkcję:

// void swap_values(int *a, int *b);

// która zamienia wartości dwóch zmiennych przekazanych przez wskaźniki.

// W funkcji main() wczytaj dwie wartości, wyświetl je przed i po wywołaniu funkcji.

// void swap_values(int *a, int *b){
//     int tmp;
//     tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// int main(){
//     int a,b;
//     printf("Podaj wartosc a:\n");
//     scanf("%d", &a);
//     printf("Podaj wartosc b:\n");
//     scanf("%d", &b);
//     printf("Wartosc a: %d i b: %d przed zmiana\n", a, b);
//     swap_values(&a,&b);
//     printf("Wartosc a: %d i b: %d po zmianie\n", a, b);

//     return 0;
// }

// 4. Weryfikacja hasła

// W aplikacji logowania należy sprawdzić, czy podane hasło spełnia określone wymagania.Napisz funkcję: 

// int is_password_valid(const char password[]);

// Funkcja powinna zwracać 1, jeśli hasło spełnia wszystkie wymagania, lub 0 w przeciwnym przypadku.

// Poprawne hasło musi:

// zawierać co najmniej 8 znaków;
// zawierać co najmniej jedną cyfrę;
// zawierać co najmniej jedną wielką literę;
// zawierać co najmniej jeden znak specjalny, np. !, @, #, $, %.
 
// W funkcji main() wczytaj hasło, wywołaj funkcję i wyświetl odpowiedni komunikat.

// Zadbaj o bezpieczne wczytywanie hasła do tablicy znaków, z uwzględnieniem rozmiaru dostępnego bufora.


// int is_password_valid(const char password[]) {
//     int length = 0;
//     int has_digit = 0;
//     int has_upper = 0;
//     int has_special = 0;

//     for (int i = 0; password[i] != '\0'; i++) {
//         length++;

//         if (password[i] >= '0' && password[i] <= '9') {
//             has_digit = 1;
//         }
//         else if (password[i] >= 'A' && password[i] <= 'Z') {
//             has_upper = 1;
//         }
//         else if (password[i] >= 'a' && password[i] <= 'z') {}
//         else {
//             has_special = 1;
//         }
//     }

//     if (length >= 8 && has_digit && has_upper && has_special) {
//         return 1;
//     }

//     return 0;
// }

// int main() {
//     char password[100];

//     printf("Podaj haslo: ");
//     if (scanf("%99s", password) != 1) {
//         return 1;
//     }

//     if (is_password_valid(password)) {
//         printf("Haslo jest poprawne.\n");
//     }
//     else {
//         printf("Haslo nie spelnia wymagan.\n");
//     }

//     return 0;
// }


// void read_measurements(double data[], int n){
//     int i = 0;
//     while(i<n){
//         printf("\nPodaj pomiar: ");
//         scanf("%lf", &data[i]);
//         i++;
//     }
// }
// void print_measurements(const double data[], int n){
//     int i =0;
//     while (i<n)
//     {
//         printf("Pomiar nr %d wynosi %.2lf\n", i+1, data[i]);
//         i++;
//     }
    
// }
// void normalize(double data[], int n){
//     int i =0;
//     double min=data[0], max=data[0];
//     int jednakowe = 1;
//     while(i<n-1){
//         if(data[i]==data[i+1]){
//             jednakowe++;
//         }
//         i++;
//     }
//     if(jednakowe == n){
//         i = 0;
//         while(i<n){
//             data[i] = 0;
//             i++;
//         }
//         return;
//     }
//     i = 0;
//     while (i<n)
//     {
//         if(data[i]>max){
//             max = data[i];
//         }
//         if(data[i]<min){
//             min = data[i];
//         }
//         i++;
//     }
//     i = 0;
//     while(i<n){
//         data[i] = (data[i]-min)/(max-min);
//         i++;
//     }
// }

// int main(){
//     double data[100];
//     int n;
//     read_measurements(data, 5);
//     print_measurements(data,5);
//     normalize(data,5);
//     print_measurements(data,5);
//     return 0;
// }