#include <stdio.h>
#include <math.h>
#include <string.h>

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
    if(type == TEMPERATURE && !isfinite(data.temperature)){
        return 0;
    }
    if(type == LOGIN_FAILURE && data.attempts < 0){
        return 0;
    }
    if(type == DIAGNOSTIC &&
       (data.text[0] == '\0' || memchr(data.text, '\0', TEXT_SIZE) == NULL)){
        return 0;
    }

    log->events[log->count].id = log->count + 1;
    log->events[log->count].type = type;
    log->events[log->count].data = data;
    log->count++;
    return 1;
}

void print_event(const event *item){
    printf("ID %d: ", item->id);
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
    int i = 0;
    if(log->count == 0){
        printf("Rejestr jest pusty.\n");
    }
    while(i < log->count){
        print_event(&log->events[i]);
        i++;
    }
}

void find_type(const event_log *log, event_type type){
    int i = 0, found = 0;
    while(i < log->count){
        if(log->events[i].type == type){
            print_event(&log->events[i]);
            found = 1;
        }
        i++;
    }
    if(!found){
        printf("Nie znaleziono zdarzen tego rodzaju.\n");
    }
}

void find_id(const event_log *log, int id){
    int i = 0;
    while(i < log->count){
        if(log->events[i].id == id){
            print_event(&log->events[i]);
            return;
        }
        i++;
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
    int i = 0, found = 0;
    while(i < log->count){
        if(is_dangerous(&log->events[i])){
            print_event(&log->events[i]);
            found = 1;
        }
        i++;
    }
    if(!found){
        printf("Brak zagrozen.\n");
    }
}

void report(const event_log *log){
    int i = 0, temperatures = 0, logins = 0, messages = 0, threats = 0;
    long long attempts = 0;
    double max_temperature = 0;

    while(i < log->count){
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
        i++;
    }
    printf("Wszystkie zdarzenia: %d\n", log->count);
    printf("Temperatury: %d, logowania: %d, komunikaty: %d\n", temperatures, logins, messages);
    if(temperatures > 0){
        printf("Najwyzsza temperatura: %.2f C\n", max_temperature);
    }
    else{
        printf("Brak pomiarow temperatury.\n");
    }
    printf("Suma nieudanych prob: %lld\n", attempts);
    printf("Liczba zagrozen: %d\n", threats);
}

int main(){
    event_log log = {0};
    event_data data;

    printf("=== Pusty rejestr ===\n");
    print_all(&log);
    report(&log);

    data.temperature = 100;
    add_event(&log, TEMPERATURE, data);
    data.temperature = 101.5;
    add_event(&log, TEMPERATURE, data);
    data.attempts = 2;
    add_event(&log, LOGIN_FAILURE, data);
    data.attempts = 3;
    add_event(&log, LOGIN_FAILURE, data);
    strcpy(data.text, "Sprawdzic modul zasilania");
    add_event(&log, DIAGNOSTIC, data);

    printf("\n=== Wszystkie zdarzenia ===\n");
    print_all(&log);
    printf("\n=== Temperatury ===\n");
    find_type(&log, TEMPERATURE);
    printf("\n=== Wyszukiwanie ID 5 i 99 ===\n");
    find_id(&log, 5);
    find_id(&log, 99);
    printf("\n=== Zagrozenia ===\n");
    print_threats(&log);
    printf("\n=== Raport ===\n");
    report(&log);

    printf("\n=== Niepoprawne dane ===\n");
    data.attempts = -1;
    if(!add_event(&log, LOGIN_FAILURE, data)){
        printf("Odrzucono ujemna liczbe prob.\n");
    }
    if(!add_event(&log, (event_type)99, data)){
        printf("Odrzucono nieznany rodzaj.\n");
    }
    data.temperature = NAN;
    if(!add_event(&log, TEMPERATURE, data)){
        printf("Odrzucono niepoprawna temperature.\n");
    }
    data.text[0] = '\0';
    if(!add_event(&log, DIAGNOSTIC, data)){
        printf("Odrzucono pusty komunikat.\n");
    }
    printf("Rejestr po odrzuceniu wpisow:\n");
    print_all(&log);

    printf("\n=== Test pelnego rejestru ===\n");
    data.attempts = 0;
    while(log.count < MAX_EVENTS){
        add_event(&log, LOGIN_FAILURE, data);
    }
    if(!add_event(&log, LOGIN_FAILURE, data)){
        printf("Odrzucono wpis: rejestr jest pelny (%d zdarzen).\n", log.count);
    }
    return 0;
}
