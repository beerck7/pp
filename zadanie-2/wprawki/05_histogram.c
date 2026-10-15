#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int wystapienia[6] = {0};

    srand((unsigned int)time(NULL));
    for (int i = 0; i < 50; i++) {
        int wynik = 1 + rand() % 6;
        wystapienia[wynik - 1]++;
    }
    for (int i = 0; i < 6; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < wystapienia[i]; j++)
            printf("*");
        puts("");
    }
    return 0;
}
