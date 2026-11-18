#include <stdio.h>
#include <float.h>

#define MAX_EVENTS 100
#define TEXT_SIZE 100

typedef enum {
    TEMPERATURE,
    LOGIN_FAILURE,
    DIAGNOSTIC
} event_type;

typedef union {
    double temperature;
    int attempts;
    char text[TEXT_SIZE];
} event_data;

typedef struct {
    int id;
    event_type type;
    event_data data;
} event;

typedef struct {
    event events[MAX_EVENTS];
    int count;
} event_log;

int add_event(event_log *log, event_type type, event_data data){
    if(log->count >= MAX_EVENTS || log->count < 0){
        return 0;
    }
    if(type != TEMPERATURE && type != LOGIN_FAILURE && type != DIAGNOSTIC){
        return 0;
    }
    if(type == TEMPERATURE && !(data.temperature >= -DBL_MAX && data.temperature <= DBL_MAX)){
        return 0;
    }
    if(type == LOGIN_FAILURE && data.attempts < 0){
        return 0;
    }
    if(type == DIAGNOSTIC){
        int i = 0;

        while(i < TEXT_SIZE && data.text[i] != '\0'){
            i++;
        }

        if(i == 0 || i == TEXT_SIZE){
            return 0;
        }
    }

    log->events[log->count].id = log->count + 1;
    log->events[log->count].type = type;
    log->events[log->count].data = data;
    log->count++;
    return 1;
}

void print_event(const event *item){
    printf("id %d: ", item->id);
    switch(item->type){
        case TEMPERATURE:
            printf("Temperatura: %.2f C\n", item->data.temperature);
            break;
        case LOGIN_FAILURE:
            printf("Nieudane proby: %d\n", item->data.attempts);
            break;
        case DIAGNOSTIC:
            printf("Komunikat: %s\n", item->data.text);
            break;
        default:
            printf("Nieznany rodzaj zdarzenia.\n");
    }
}

void print_all(const event_log *log){
    if(log->count == 0){
        printf("Rejestr jest pusty\n");
    }
    for(int i = 0; i < log->count; i++){
        print_event(&log->events[i]);
    }
}

void find_type(const event_log *log, event_type type){
    int found = 0;
    for(int i = 0; i < log->count; i++){
        if(log->events[i].type == type){
            print_event(&log->events[i]);
            found = 1;
        }
    }
    if(!found){
        printf("Nie znaleziono zdarzen tego rodzaju\n");
    }
}

void find_id(const event_log *log, int id){
    for(int i = 0; i < log->count; i++){
        if(log->events[i].id == id){
            print_event(&log->events[i]);
            return;
        }
    }
    printf("Nie znaleziono zdarzenia o ID %d.\n", id);
}

int is_dangerous(const event *item){
    if(item->type == TEMPERATURE && item->data.temperature > 100){
        return 1;
    }
    if(item->type == LOGIN_FAILURE && item->data.attempts >= 3){
        return 1;
    }
    return 0;
}

void print_threats(const event_log *log){
    int found = 0;
    for(int i = 0; i < log->count; i++){
        if(is_dangerous(&log->events[i])){
            print_event(&log->events[i]);
            found = 1;
        }
    }
    if(!found){
        printf("Brak zagrozen\n");
    }
}

void report(const event_log *log){
    int temperatures = 0, logins = 0, messages = 0, threats = 0;
    long long attempts = 0;
    double max_temperature = 0;

    for(int i = 0; i < log->count; i++){
        const event *item = &log->events[i];
        if(item->type == TEMPERATURE){
            if(temperatures == 0 || item->data.temperature > max_temperature){
                max_temperature = item->data.temperature;
            }
            temperatures++;
        }
        else if(item->type == LOGIN_FAILURE){
            logins++;
            attempts += item->data.attempts;
        }
        else if(item->type == DIAGNOSTIC){
            messages++;
        }
        if(is_dangerous(item)){
            threats++;
        }
    }
    printf("Wszystkie zdarzenia: %d\n", log->count);
    printf("Temperatury: %d, logowania: %d, komunikaty: %d\n", temperatures, logins, messages);
    if(temperatures > 0){
        printf("Najwyzsza temperatura: %.2f C\n", max_temperature);
    }
    else{
        printf("Brak pomiarow temperatury\n");
    }
    printf("Suma nieudanych prob: %lld\n", attempts);
    printf("Liczba zagrozen: %d\n", threats);
}

int main(){
    event_log log = {0};
    event_data data;
    char komunikat[] = "Sprawdzic modul zasilania";

    printf("Pusty rejestr\n");
    print_all(&log);
    find_type(&log, DIAGNOSTIC);
    print_threats(&log);
    report(&log);

    data.temperature = 100;
    add_event(&log, TEMPERATURE, data);
    data.temperature = 101.5;
    add_event(&log, TEMPERATURE, data);
    data.attempts = 2;
    add_event(&log, LOGIN_FAILURE, data);
    data.attempts = 3;
    add_event(&log, LOGIN_FAILURE, data);
    int i = 0;
    while(komunikat[i] != '\0'){
        data.text[i] = komunikat[i];
        i++;
    }
    data.text[i] = '\0';
    add_event(&log, DIAGNOSTIC, data);

    printf("\nWszystkie zdarzenia\n");
    print_all(&log);
    printf("\nTemperatury\n");
    find_type(&log, TEMPERATURE);
    printf("\nWyszukiwanie ID 5 i 99\n");
    find_id(&log, 5);
    find_id(&log, 99);
    printf("\nZagrozenia\n");
    print_threats(&log);
    printf("\nRaport\n");
    report(&log);

    printf("\nNiepoprawne dane\n");
    data.attempts = -1;
    if(!add_event(&log, LOGIN_FAILURE, data)){
        printf("Odrzucono ujemna liczbe prob.\n");
    }
    if(!add_event(&log, (event_type)99, data)){
        printf("Odrzucono nieznany rodzaj.\n");
    }
    data.text[0] = '\0';
    if(!add_event(&log, DIAGNOSTIC, data)){
        printf("Odrzucono pusty komunikat.\n");
    }
    for(int i = 0; i < TEXT_SIZE; i++){
        data.text[i] = 'A';
    }
    if(!add_event(&log, DIAGNOSTIC, data)){
        printf("Odrzucono za dlugi komunikat.\n");
    }
    printf("Rejestr po odrzuceniu wpisow:\n");
    print_all(&log);

    printf("\nTest pelnego rejestru\n");
    data.attempts = 0;
    while(log.count < MAX_EVENTS){
        add_event(&log, LOGIN_FAILURE, data);
    }
    if(!add_event(&log, LOGIN_FAILURE, data)){
        printf("Odrzucono wpis rejestr jest pelny (%d zdarzen)\n", log.count);
    }

    // printf("\nRejestr koncowy\n");
    // print_all(&log);
    return 0;
}
