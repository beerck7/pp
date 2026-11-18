#include <stdio.h>

typedef enum {
    TEMPERATURE,
    PULSES,
    STATUS_CODE
} measurement_type;

typedef union {
    double temperature;
    int pulses;
    char code;
} measurement_value;

typedef struct {
    measurement_type type;
    measurement_value value;
} measurement;

void print_measurement(const measurement *item){
    switch(item->type){
        case TEMPERATURE:
            printf("Temperatura: %.2f\n", item->value.temperature);
            break;
        case PULSES:
            printf("Liczba impulsow: %d\n", item->value.pulses);
            break;
        case STATUS_CODE:
            printf("Kod stanu: %c\n", item->value.code);
            break;
        default:
            printf("Nieznany rodzaj pomiaru.\n");
    }
}

int main(){
    measurement item;
    item.type = TEMPERATURE;
    item.value.temperature = 23.5;
    print_measurement(&item);
    item.type = PULSES;
    item.value.pulses = 42;
    print_measurement(&item);
    item.type = STATUS_CODE;
    item.value.code = 'A';
    print_measurement(&item);
    printf("Rozmiar unii: %zu bajtow\n", sizeof(measurement_value));
    printf("Rozmiar struktury: %zu bajtow\n", sizeof(measurement));
    return 0;
}
