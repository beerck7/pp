#include <stdio.h>

typedef enum {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
} priority;

typedef struct {
    int number;
    priority level;
    int resolved;
} ticket;

int change_priority(ticket *item, int new_priority){
    if(new_priority < LOW || new_priority > CRITICAL){
        return 0;
    }
    item->level = new_priority;
    return 1;
}

int main(){
    ticket item = {123, LOW, 0};
    printf("Priorytet poczatkowy: %d\n", item.level);
    if(change_priority(&item, HIGH)){
        printf("Zmieniono priorytet na: %d\n", item.level);
    }
    if(!change_priority(&item, 99)){
        printf("Odrzucono niepoprawny priorytet.\n");
    }
    printf("Priorytet po odrzuconej zmianie: %d\n", item.level);
    return 0;
}
