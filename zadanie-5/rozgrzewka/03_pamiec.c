#include <stdio.h>
#include <stddef.h>

typedef struct {
    char flag;
    int value;
    char code;
} record_a;

typedef struct {
    int value;
    char flag;
    char code;
} record_b;

typedef union {
    char flag;
    int value;
    char code;
} record_c;

int main(){
    record_c c;

    printf("Rozmiar record_a: %zu bajtow\n", sizeof(record_a));
    printf("Rozmiar record_b: %zu bajtow\n", sizeof(record_b));
    printf("Rozmiar record_c: %zu bajtow\n", sizeof(record_c));

    printf("\nPrzesuniecia pol record_a:\n");
    printf("flag: %zu\n", offsetof(record_a, flag));
    printf("value: %zu\n", offsetof(record_a, value));
    printf("code: %zu\n", offsetof(record_a, code));

    printf("\nPrzesuniecia pol record_b:\n");
    printf("value: %zu\n", offsetof(record_b, value));
    printf("flag: %zu\n", offsetof(record_b, flag));
    printf("code: %zu\n", offsetof(record_b, code));

    printf("\nAdresy pol unii:\n");
    printf("flag: %p\n", (void *)&c.flag);
    printf("value: %p\n", (void *)&c.value);
    printf("code: %p\n", (void *)&c.code);

    if((void *)&c.flag == (void *)&c.value &&
       (void *)&c.flag == (void *)&c.code){
        printf("Wszystkie pola unii maja ten sam adres.\n");
    }
    else{
        printf("Pola unii maja rozne adresy.\n");
    }

    return 0;
}
