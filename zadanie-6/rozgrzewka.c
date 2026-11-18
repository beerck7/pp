#include <stdio.h>
#include <stdlib.h>

// 1. Czujniki

// Zdefiniuj strukturę Sensor zawierającą identyfikator czujnika (liczba całkowita), temperatura (liczba rzeczywista) oraz stan aktywności czujnika (0 lub 1).

// Napisz program, który:

// Tworzy zmienną typu Sensor i inicjalizuje jej pola.
// Definiuje funkcję void print_sensor(const Sensor *s), wyświetlającą dane czujnika.
// Definiuje funkcję void deactivate_sensor(Sensor *s), ustawiającą stan aktywności czujnika na 0.
// Wywołuje funkcję print_sensor(), następnie deactivate_sensor() i ponownie print_sensor().
// Zastanów się:

// Dlaczego do funkcji przekazujemy adres struktury, a nie samą strukturę?
// Do czego służy operator ->?
// Dlaczego parametr funkcji print_sensor() jest oznaczony słowem const?

// typedef struct{
//     int sensor_id;
//     double temperature;
//     int activity;
// } Sensor;

// void print_sensor(const Sensor *s){
//     printf("id: %d\n", s->sensor_id);
//     printf("temperatura: %.2f\n", s->temperature);
//     printf("aktywnosc: %d\n", s->activity);
// }

// void deactivate_sensor(Sensor *s){
//     s->activity = 0;
// }

// int main(){
//     Sensor sensor = {1, 25.5, 1};

//     print_sensor(&sensor);

//     deactivate_sensor(&sensor);

//     print_sensor(&sensor);

//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>

// int global_counter = 0;

// int *create_value(int x) {
//     int *p = malloc(sizeof(*p));

//     if (p != NULL) {
//         *p = x;
//     }

//     return p;
// }

// int main(void) {
//     int local = 10;
//     static int count = 0;

//     int *result = create_value(local);

//     if (result != NULL) {
//         printf("%d\n", *result);
//         free(result);
//         result = NULL;
//     }

//     return 0;
// }

// Wykonaj następujące polecenia:

// Określ, gdzie w pamięci przechowywane są:
// global_counter,
// local,
// count,
// wskaźnik result,
// wskaźnik p wewnątrz funkcji create_value(),
// obiekt utworzony przez malloc().
// Wyjaśnij, dlaczego obiekt utworzony w create_value() pozostaje dostępny po zakończeniu tej funkcji.
// Co się stanie, jeśli usuniemy instrukcję free(result)?
// Czy można wywołać free(&local)? Uzasadnij odpowiedź.
// Jaką rolę pełni instrukcja result = NULL?
