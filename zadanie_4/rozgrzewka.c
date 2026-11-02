// W Akademii Magii im. Gedeona Szkarłatnego zainstalowano Eliksiromat - magiczny automat sprzedający uczniom mikstury lecznicze, eliksiry siły oraz napoje przywracające manę.

// Automat jest jeszcze w fazie testów. Twoim zadaniem jest opracowanie i przetestowanie wybranych funkcjonalności związanych ze sprzedażą mikstur, zarządzaniem zapasami oraz kontrolowaniem cen.

// Dla uproszczenia przyjmujemy, że:

// Eliksiromat oferuje trzy rodzaje mikstur.
// Liczba dostępnych mikstur jest przechowywana w tablicy stock[3] = {5, 3, 8}.
// Ceny mikstur (w złotych monetach) są przechowywane w tablicy prices[3] = {20, 35, 15}.
// Automat przechowuje również łączny utarg. Informacja ta powinna być dostępna dla funkcji obsługujących sprzedaż i raportowanie.
// 1. Numerowanie transakcji

// Każda sprzedaż zrealizowana przez Eliksiromat otrzymuje kolejny numer, rozpoczynając od 1. Numeracja powinna być zachowywana między kolejnymi wywołaniami funkcji. Napisz funkcję:

// int next_transaction(void);

// Funkcja nie przyjmuje argumentów i zwraca numer kolejnej transakcji. Do przechowywania licznika wykorzystaj lokalną zmienną static.

// W funkcji main() wywołaj funkcję kilkukrotnie i wyświetl otrzymane numery.

// Zastanów się:

// Dlaczego zwykła zmienna lokalna nie spełniłaby tego wymagania?
// Czy licznik transakcji jest dostępny bezpośrednio w funkcji main()?
// 2. Sprzedaż mikstury

// Zakup mikstury powoduje zmniejszenie jej zapasu o jedną sztukę i zwiększenie łącznego utargu Eliksiromatu o cenę sprzedanej mikstury. Napisz funkcję:

// int sell_potion(int *stock, int price);

// Funkcja powinna sprawdzić, czy mikstura jest dostępna. Jeśli tak, zmniejsza jej zapas o 1, aktualizuje łączny utarg i zwraca 1. Jeśli zapas jest pusty, nie zmienia żadnych danych i zwraca 0.

// W funkcji main() wykonaj kilka prób sprzedaży, w tym próbę zakupu mikstury, której zapas został wyczerpany. Po każdej operacji sprawdź stan zapasów i utarg.

// Zastanów się:

// Dlaczego parametr stock jest wskaźnikiem, a price zwykłą wartością?
// W jaki sposób funkcja aktualizuje łączny utarg, skoro nie otrzymuje adresu zmiennej przechowującej tę wartość jako argumentu?
// 3. Uzupełnianie zapasów

// Magazynier Akademii może uzupełniać zapasy wybranej mikstury. Napisz funkcję:

// void restock(int *stock, int amount);

// Funkcja powinna zwiększać wskazywany zapas o podaną liczbę sztuk. Nie może dopuszczać do uzupełniania zapasów o wartość ujemną.

// W main() uzupełnij zapasy dwóch wybranych mikstur i sprawdź ich nowe wartości.

// Zastanów się:

// Czym różni się modyfikacja *stock od modyfikacji samego stock?
// Czy zmiana parametru na int stock pozwoliłaby uzyskać ten sam efekt?
// 4. Zmiana cen mikstur

// W związku ze wzrostem cen magicznych składników Akademia postanowiła zmienić ceny wszystkich mikstur. Napisz funkcję:

// void change_prices(int *prices, int n, int change);

// Funkcja powinna zmieniać ceny n mikstur o podaną kwotę. Do przechodzenia po tablicy wykorzystaj arytmetykę wskaźników zamiast indeksowania.

// Nowa cena żadnej mikstury nie może być ujemna. Jeśli wynik zmiany byłby ujemny, przyjmij cenę 0.

// W main() przetestuj podwyżkę i obniżkę cen, a następnie wyświetl aktualny cennik.

// Zastanów się:

// Co oznacza wyrażenie prices + 1?
// Dlaczego przesunięcie wskaźnika o jeden nie oznacza przesunięcia adresu o jeden bajt?

#include <stdio.h>
#include <stdlib.h>

int laczny_utarg = 0;

int next_transaction(){
    static int licznik = 0;

    licznik++;

    return licznik;
}

int sell_potion(int *stock, int price){
    if(*stock <= 0){
        return 0;
    }

    *stock = *stock - 1;
    laczny_utarg = laczny_utarg + price;

    return 1;
}

void restock(int *stock, int amount){
    if(amount < 0){
        printf("Nie mozna dodac ujemnej liczby mikstur.\n");
        return;
    }

    *stock = *stock + amount;
}

void change_prices(int *prices, int n, int change){
    for(int i = 0; i < n; i++){
        int nowa_cena = *(prices + i) + change;

        if(nowa_cena < 0){
            nowa_cena = 0;
        }

        *(prices + i) = nowa_cena;
    }
}

int main(){
    int stock[3] = {5, 3, 8};
    int prices[3] = {20, 35, 15};

    /* 1. Numerowanie transakcji */
    printf("NUMERY TRANSAKCJI:\n");

    int i = 0;

    while(i < 5){
        printf("NR %d: %d\n", i + 1, next_transaction());
        i++;
    }

    /* 2. Sprzedaz mikstur */
    printf("\nSPRZEDAZ DRUGIEJ MIKSTURY:\n");

    /* Sa 3 sztuki, wiec czwarta proba sie nie uda. */
    for(i = 0; i < 4; i++){
        if(sell_potion(&stock[1], prices[1]) == 1){
            printf("Sprzedano miksture.\n");
        }
        else{
            printf("Brak mikstury w magazynie.\n");
        }

        printf("Zapasy: %d, %d, %d\n",
               stock[0], stock[1], stock[2]);
        printf("Laczny utarg: %d\n", laczny_utarg);
    }

    /* 3. Uzupelnianie zapasow */
    printf("\nUZUPELNIANIE ZAPASOW:\n");

    restock(&stock[0], 4);
    restock(&stock[1], 2);

    printf("Zapasy po uzupelnieniu: %d, %d, %d\n",
           stock[0], stock[1], stock[2]);

    /* Test ujemnej liczby. */
    restock(&stock[2], -3);

    printf("Zapasy po probie dodania -3: %d, %d, %d\n",
           stock[0], stock[1], stock[2]);

    /* 4. Zmiana cen */
    printf("\nZMIANA CEN:\n");

    change_prices(prices, 3, 10);

    printf("Ceny po podwyzce: %d, %d, %d\n",
           prices[0], prices[1], prices[2]);

    change_prices(prices, 3, -30);

    printf("Ceny po obnizce: %d, %d, %d\n",
           prices[0], prices[1], prices[2]);

    return 0;
}
