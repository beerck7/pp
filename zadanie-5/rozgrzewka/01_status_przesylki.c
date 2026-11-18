#include <stdio.h>

typedef enum {
    PREPARED,
    SHIPPED,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
} parcel_status;

int is_final_status(parcel_status status){
    if(status == DELIVERED || status == CANCELLED){
        return 1;
    }
    return 0;
}

int main(){
    int code;
    parcel_status status;

    printf("Podaj kod statusu (0-4): ");
    if(scanf("%d", &code) != 1){
        printf("Niepoprawny kod statusu.\n");
        return 1;
    }

    if(code < PREPARED || code > CANCELLED){
        printf("Niepoprawny status.\n");
        return 1;
    }

    status = (parcel_status)code;

    switch(status){
        case PREPARED:
            printf("Status: PREPARED\nPrzesylka jest przygotowana.\n");
            break;
        case SHIPPED:
            printf("Status: SHIPPED\nPrzesylka zostala wyslana.\n");
            break;
        case OUT_FOR_DELIVERY:
            printf("Status: OUT_FOR_DELIVERY\nPrzesylka jest w doreczeniu.\n");
            break;
        case DELIVERED:
            printf("Status: DELIVERED\nPrzesylka zostala dostarczona.\n");
            break;
        case CANCELLED:
            printf("Status: CANCELLED\nPrzesylka zostala anulowana.\n");
            break;
    }

    if(is_final_status(status)){
        printf("Jest to status koncowy.\n");
    }
    else{
        printf("Przesylka jest w trakcie obslugi.\n");
    }

    return 0;
}
