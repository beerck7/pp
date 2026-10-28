// Zadanie główne
// Na pokładzie statku badawczego ARGO działa system monitorowania parametrów jednego z modułów pokładowych. Każdy odczyt jest wartością całkowitą z przedziału [-50; 50]. System przechowuje ograniczoną liczbę ostatnich odczytów i umożliwia ich bieżącą analizę. Za odczyt alarmowy uznaje się wartość spoza przedziału [-40; 40]. 

// Przed uzyskaniem dostępu do systemu użytkownik musi się zalogować. Ma na to maksymalnie trzy próby. Po trzech błędnych próbach program kończy działanie.

// Po poprawnym zalogowaniu program powinien wyświetlać menu umożliwiające:

// Dodanie nowego odczytu.
// Zmianę wybranego odczytu.
// Wyświetlenie zapisanych odczytów.
// Wyświetlenie podstawowych statystyk.
// Wyświetlenie odczytów przekraczających ustalony poziom alarmowy.
// Wyczyszczenie zapisanych danych.
// Wylogowanie.
// System przechowuje maksymalnie 8 ostatnich odczytów. Jeżeli użytkownik doda nowy odczyt po zapełnieniu pamięci, najstarsza wartość powinna zostać usunięta, a pozostałe odpowiednio przesunięte.

// Statystyki powinny obejmować średnią wartość odczytów, liczbę odczytów większych od średniej oraz największy wzrost i największy spadek pomiędzy kolejnymi odczytami.
// Po wylogowaniu użytkownik wraca do ekranu logowania, ale zapisane odczyty pozostają w pamięci systemu.

// Program powinien kontrolować poprawność wprowadzanych danych. Błędne dane użytkownika nie mogą prowadzić do odwołania poza granice tablicy. W przypadku podania wartości niewłaściwego typu, wartości spoza dopuszczalnego zakresu lub nieistniejącej opcji użytkownik powinien otrzymać odpowiedni komunikat i możliwość ponownego wprowadzenia danych. Program powinien również poprawnie obsługiwać sytuacje, w których wybrana operacja nie może zostać wykonana, np. próbę analizy pustego bufora lub odwołania się do nieistniejącego odczytu.


#include <stdio.h>

int wczytajInt(int *liczba){
    int wynik = scanf("%d", liczba);
    int c, poprawne = 1;

    if(wynik == EOF) return -1;

    while((c = getchar()) != '\n' && c != EOF){
        if(c != ' ' && c != '\t' && c != '\r'){
            poprawne = 0;
        }
    }

    if(wynik != 1 || poprawne == 0) return 0;
    return 1;
}

int pobierz(int *liczba, int min, int max){
    int wynik;

    while(1){
        wynik = wczytajInt(liczba);

        if(wynik == -1) return 0;

        if(wynik == 1 && *liczba >= min && *liczba <= max){
            return 1;
        }

        printf("Niepoprawne dane! Podaj liczbe od %d do %d: ", min, max);
    }
}

int main(){
    int tab[8];
    int ile = 0;
    int pin, proby, zalogowany;
    int opcja, odczyt, indx;
    int i, suma, powyzej;
    int wzrost, spadek, roznica;
    int alarmy;
    float srednia;

    while(1){
        proby = 0;
        zalogowany = 0;

        while(proby < 3){
            printf("\nPodaj PIN: ");

            int wynik = wczytajInt(&pin);
            if(wynik == -1) return 0;

            if(wynik == 1 && pin == 1234){
                zalogowany = 1;
                printf("Zalogowano pomyslnie!\n");
                break;
            }

            proby++;
            printf("Bledny PIN! Pozostalo prob: %d\n", 3-proby);
        }

        if(zalogowany == 0){
            printf("Przekroczono limit prob. Koniec programu.\n");
            return 0;
        }

        while(1){
            printf("\nSYSTEM ARGO\n");
            printf("1 - Dodaj odczyt\n");
            printf("2 - Zmien odczyt\n");
            printf("3 - Wyswietl odczyty\n");
            printf("4 - Statystyki\n");
            printf("5 - Odczyty alarmowe\n");
            printf("6 - Wyczysc dane\n");
            printf("7 - Wyloguj\n");
            printf("Wybierz opcje: ");

            if(!pobierz(&opcja, 1, 7)) return 0;

            switch(opcja){

                case 1:
                    printf("Podaj odczyt [-50,50]: ");
                    if(!pobierz(&odczyt, -50, 50)) return 0;

                    if(ile < 8){
                        tab[ile] = odczyt;
                        ile++;
                    }
                    else{
                        i = 0;
                        while(i < 7){
                            tab[i] = tab[i+1];
                            i++;
                        }
                        tab[7] = odczyt;
                    }

                    printf("Dodano odczyt!\n");
                    break;

                case 2:
                    if(ile == 0){
                        printf("Brak odczytow do zmiany!\n");
                        break;
                    }

                    i = 0;
                    while(i < ile){
                        printf("%d: %d\n", i+1, tab[i]);
                        i++;
                    }

                    printf("Podaj numer odczytu do zmiany: ");
                    if(!pobierz(&indx, 1, ile)) return 0;

                    printf("Podaj nowa wartosc [-50,50]: ");
                    if(!pobierz(&odczyt, -50, 50)) return 0;

                    tab[indx-1] = odczyt;
                    printf("Zmieniono odczyt!\n");
                    break;

                case 3:
                    if(ile == 0){
                        printf("Bufor jest pusty!\n");
                    }
                    else{
                        i = 0;
                        while(i < ile){
                            printf("%d: %d\n", i+1, tab[i]);
                            i++;
                        }
                    }
                    break;

                case 4:
                    if(ile == 0){
                        printf("Brak danych do analizy!\n");
                        break;
                    }

                    suma = 0;
                    i = 0;

                    while(i < ile){
                        suma += tab[i];
                        i++;
                    }

                    srednia = (float)suma / ile;
                    powyzej = 0;
                    i = 0;

                    while(i < ile){
                        if(tab[i] > srednia){
                            powyzej++;
                        }
                        i++;
                    }

                    printf("Srednia: %.2f\n", srednia);
                    printf("Powyzej sredniej: %d\n", powyzej);

                    if(ile < 2){
                        printf("Za malo danych do analizy zmian!\n");
                    }
                    else{
                        wzrost = 0;
                        spadek = 0;
                        i = 1;

                        while(i < ile){
                            roznica = tab[i] - tab[i-1];

                            if(roznica > wzrost){
                                wzrost = roznica;
                            }

                            if(-roznica > spadek){
                                spadek = -roznica;
                            }

                            i++;
                        }

                        printf("Najwiekszy wzrost: %d\n", wzrost);
                        printf("Najwiekszy spadek: %d\n", spadek);
                    }
                    break;

                case 5:
                    if(ile == 0){
                        printf("Brak odczytow!\n");
                        break;
                    }

                    alarmy = 0;
                    i = 0;

                    while(i < ile){
                        if(tab[i] < -40 || tab[i] > 40){
                            printf("Alarm! Odczyt %d: %d\n", i+1, tab[i]);
                            alarmy++;
                        }
                        i++;
                    }

                    if(alarmy == 0){
                        printf("Brak odczytow alarmowych!\n");
                    }
                    break;

                case 6:
                    ile = 0;
                    printf("Wyczyszczono wszystkie dane!\n");
                    break;

                case 7:
                    printf("Wylogowano!\n");
                    break;

                default:
                    printf("Niepoprawna opcja!\n");
                    break;
            }

            if(opcja == 7){
                break;
            }
        }
    }

    return 0;
}
