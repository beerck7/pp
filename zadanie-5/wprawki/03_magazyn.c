#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    char name[50];
    int stock;
    double price;
} product;

void add_stock(product *item, int amount){
    if(amount <= 0 || item->stock < 0 || amount > INT_MAX - item->stock){
        printf("Niepoprawna ilosc.\n");
        return;
    }
    item->stock += amount;
}

int sell_product(product *item, int amount){
    if(amount <= 0 || item->stock < 0 || amount > item->stock){
        return 0;
    }
    item->stock -= amount;
    return 1;
}

double calculate_value(const product *item){
    return item->stock * item->price;
}

int main(){
    product item = {1, "Klawiatura", 10, 50.0};
    printf("Produkt: %s, stan: %d\n", item.name, item.stock);
    add_stock(&item, 5);
    printf("Po dostawie: %d\n", item.stock);
    if(sell_product(&item, 3)){
        printf("Sprzedano 3 sztuki.\n");
    }
    if(!sell_product(&item, 100)){
        printf("Nie mozna sprzedac 100 sztuk.\n");
    }
    printf("Stan: %d, wartosc: %.2f\n", item.stock, calculate_value(&item));
    return 0;
}
