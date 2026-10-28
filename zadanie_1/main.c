#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    int tryb_gracz, c, tryb_argo, ponownie;
    do{
    printf("Dostepne tryby:\n1. Plasma\n2. Cryo Shield\n3. EMP\n");
    printf("Wybierz jeden z trybow: \n");
    
    while (scanf("%d", &tryb_gracz) != 1 || tryb_gracz < 1 || tryb_gracz > 3) {
        printf("Niepoprawny wybor!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Wybierz tryb: ");
    }

    tryb_argo = rand()%3+1;
    
    printf("Twoj wybor: %d\n", tryb_gracz);
    printf("Wybor ARGO: %d\n", tryb_argo);

    if (tryb_gracz == tryb_argo) {
        printf("Remis!\n");
    }
    else if ((tryb_gracz == 1 && tryb_argo == 2) ||
             (tryb_gracz == 2 && tryb_argo == 3) ||
             (tryb_gracz == 3 && tryb_argo == 1)) {
        printf("Wygrales!\n");
    }
    else {
        printf("ARGO wygrywa!\n");
    }

    printf("Grasz ponownie? (1 - tak, 0 - nie): ");
    if (scanf("%d", &ponownie) != 1) {
        printf("Niepoprawna odpowiedz. Koniec programu.\n");
        return 1;
    }

    } while (ponownie == 1);

    return 0;
}

