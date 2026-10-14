#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int losuj_temperature(void)
{
    return -10 + (rand() % 46);
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int temp = losuj_temperature();
    printf("Wylosowana temperatura: %d C\n", temp);

    if (temp < 0) {
        puts("Frost. Wear warm clothes.");
    } else if (temp <= 25) {
        puts("Weather conditions are comfortable.");
    } else {
        puts("High temperature. Avoid overheating.");
    }
    return 0;
}
