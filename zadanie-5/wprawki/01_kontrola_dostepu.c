#include <stdio.h>

typedef enum {
    PUBLIC,
    RESTRICTED,
    CONFIDENTIAL
} access_level;

typedef struct {
    int card_number;
    char surname[50];
    access_level access_level;
} access_card;

int can_enter(const access_card *card, access_level required){
    if(card->access_level < PUBLIC || card->access_level > CONFIDENTIAL){
        return 0;
    }
    if(required < PUBLIC || required > CONFIDENTIAL){
        return 0;
    }
    if(card->access_level >= required){
        return 1;
    }
    return 0;
}

int main(){
    access_card card = {123, "Kowalski", RESTRICTED};
    int required;

    printf("Karta nr %d, wlasciciel: %s\n", card.card_number, card.surname);
    printf("Podaj wymagany poziom (0 - PUBLIC, 1 - RESTRICTED, 2 - CONFIDENTIAL): ");
    if(scanf("%d", &required) != 1 || required < PUBLIC || required > CONFIDENTIAL){
        printf("Niepoprawny poziom dostepu.\n");
        return 1;
    }
    if(can_enter(&card, (access_level)required)){
        printf("Dostep przyznany.\n");
    }
    else{
        printf("Dostep odmowiony.\n");
    }
    return 0;
}
