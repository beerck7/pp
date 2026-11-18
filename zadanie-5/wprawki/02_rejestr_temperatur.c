#include <stdio.h>

#define MAX_SENSORS 100

typedef enum {
    ACTIVE,
    INACTIVE,
    FAILED
} sensor_status;

typedef struct {
    int id;
    double temperature;
    sensor_status status;
} sensor;

int read_sensors(sensor sensors[], int n){
    int i = 0;
    int status;

    while(i < n){
        printf("\nCzujnik %d\n", i + 1);
        printf("Podaj identyfikator: ");
        if(scanf("%d", &sensors[i].id) != 1){
            return 0;
        }
        printf("Podaj temperature: ");
        if(scanf("%lf", &sensors[i].temperature) != 1){
            return 0;
        }
        printf("Podaj stan (0 - ACTIVE, 1 - INACTIVE, 2 - FAILED): ");
        if(scanf("%d", &status) != 1 || status < ACTIVE || status > FAILED){
            return 0;
        }
        sensors[i].status = (sensor_status)status;
        i++;
    }
    return 1;
}

void print_sensors(const sensor sensors[], int n){
    int i = 0;
    while(i < n){
        printf("\nCzujnik %d: id = %d, temperatura = %.2f, stan = ",
               i + 1, sensors[i].id, sensors[i].temperature);
        if(sensors[i].status == ACTIVE){
            printf("ACTIVE\n");
        }
        else if(sensors[i].status == INACTIVE){
            printf("INACTIVE\n");
        }
        else{
            printf("FAILED\n");
        }
        i++;
    }
}

int average_temperature(const sensor sensors[], int n, double *average){
    int i = 0, count = 0;
    double sum = 0;
    while(i < n){
        if(sensors[i].status == ACTIVE){
            sum += sensors[i].temperature;
            count++;
        }
        i++;
    }
    if(count == 0){
        return 0;
    }
    *average = sum / count;
    return 1;
}

int find_warmest(const sensor sensors[], int n){
    int i = 0, index = -1;
    while(i < n){
        if(sensors[i].status == ACTIVE){
            if(index == -1 || sensors[i].temperature > sensors[index].temperature){
                index = i;
            }
        }
        i++;
    }
    return index;
}

int main(){
    sensor sensors[MAX_SENSORS];
    int n, index;
    double average;

    printf("Ile czujnikow (0-%d)? ", MAX_SENSORS);
    if(scanf("%d", &n) != 1 || n < 0 || n > MAX_SENSORS){
        printf("Niepoprawna liczba czujnikow.\n");
        return 1;
    }
    if(!read_sensors(sensors, n)){
        printf("Niepoprawne dane czujnika.\n");
        return 1;
    }

    print_sensors(sensors, n);
    if(average_temperature(sensors, n, &average)){
        index = find_warmest(sensors, n);
        printf("\nSrednia aktywnych czujnikow: %.2f\n", average);
        printf("Najwyzsza temperatura: %.2f, id czujnika: %d\n",
               sensors[index].temperature, sensors[index].id);
    }
    else{
        printf("\nBrak aktywnych czujnikow.\n");
    }
    return 0;
}
