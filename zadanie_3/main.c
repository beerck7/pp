// Zadanie główne
// Na pokładzie statku badawczego ARGO działa system diagnostyczny monitorujący stan czujników rozmieszczonych w różnych sekcjach statku. Każdy czujnik przesyła wartość rzeczywistą z przedziału [-100; 200]. Za prawidłowy odczyt uznaje się wartość z przedziału [0; 100]. Odczyty spoza tego zakresu wymagają sprawdzenia i ewentualnej korekty.

// System przechowuje odczyty z 8 czujników i umożliwia ich analizę oraz kalibrację.

// Program powinien wyświetlać menu umożliwiające:

// Wczytanie odczytów z czujników.
// Wyświetlenie aktualnych odczytów.
// Kalibrację czujników.
// Wykrycie i korektę nieprawidłowych odczytów.
// Zmianę odczytu wybranego czujnika.
// Zakończenie działania programu.
// Kalibracja polega na dodaniu podanej przez użytkownika wartości do wszystkich odczytów. Wartość korekty może być dodatnia lub ujemna. Po kalibracji niektóre odczyty mogą znaleźć się poza zakresem prawidłowej pracy czujników.

// Podczas diagnostyki program powinien wyszukiwać nieprawidłowe odczyty i umożliwiać użytkownikowi ich poprawienie. Jeżeli wszystkie odczyty są prawidłowe, program powinien wyświetlić odpowiedni komunikat.

// Zmiana pojedynczego odczytu polega na wskazaniu numeru czujnika i wprowadzeniu nowej wartości.

// Program powinien kontrolować poprawność wprowadzanych danych. W przypadku podania wartości niewłaściwego typu, wartości spoza dopuszczalnego zakresu lub nieistniejącej opcji użytkownik powinien otrzymać odpowiedni komunikat i możliwość ponownego wprowadzenia danych. Program powinien również poprawnie obsługiwać sytuacje, w których wybrana operacja nie może zostać wykonana, np. próbę kalibracji lub diagnostyki przed wczytaniem odczytów.

// Wymagania dotyczące funkcji

// Program należy podzielić na funkcje realizujące poszczególne operacje. W szczególności należy zaimplementować:

// void show_intro() wyświetla informacje o programie.
// int show_menu() wyświetla menu i zwraca numer wybranej opcji.
//  void read_sensors(double sensors[], int n) wczytuje odczyty i zapisuje je w tablicy.
// void display_sensors(const double sensors[], int n) wyświetla zapisane odczyty.
// void calibrate_sensors(double sensors[], int n, double offset) przeprowadza kalibrację wszystkich czujników.
// int find_faulty_sensor(const double sensors[], int n, double min_allowed, double max_allowed) zwraca indeks pierwszego nieprawidłowego odczytu lub -1, jeśli wszystkie odczyty są prawidłowe.
// void modify_sensor(double sensors[], int n, int index) umożliwia zmianę odczytu wskazanego czujnika.
// int read_value(double *value, double min, double max) pobiera pojedynczą wartość i sprawdza jej poprawność. Zwraca 1, jeśli wprowadzona wartość jest poprawna, i zapisuje ją pod wskazanym adresem, albo 0, jeśli dane są niepoprawne, pozostawiając wskazywaną wartość bez zmian.
// Funkcja main() powinna odpowiadać przede wszystkim za obsługę menu i wywoływanie odpowiednich funkcji. Tablica odczytów powinna być przekazywana do funkcji jako parametr wraz z liczbą elementów.

// Funkcja read_value() służy do wczytywania pojedynczej wartości liczbowej i sprawdzania, czy należy ona do podanego przedziału.

// int read-value(double *value, double min, double max);
// Funkcja otrzymuje adres zmiennej, w której może zapisać wczytaną wartość, oraz dolną i górną granicę dopuszczalnego przedziału. Jeżeli użytkownik wprowadzi poprawną wartość, funkcja zapisuje ją pod wskazanym adresem i zwraca 1. W przeciwnym przypadku zwraca 0, nie zmieniając dotychczasowej wartości zmiennej. Funkcja read_value() nie powinna samodzielnie ponawiać wczytywania danych. W razie niepowodzenia decyzję o ponowieniu operacji podejmuje funkcja, która ją wywołała.

// Przykładowe wywołanie:

// double measurement;
// if (read_value(&measurement, -100, 200)) {
//     printf("Odczyt: %.2f\n", measurement);
// } else {
//     printf("Nieprawidlowy odczyt.\n");
// }
// Funkcja przekazuje dwie różne informacje: wczytaną wartość przez wskaźnik oraz wynik operacji przez return.

#include <stdio.h>
#include <float.h>

void show_intro() {
    printf("SYSTEM DIAGNOSTYCZNY ARGO\n");
    printf("Program obsluguje 8 czujnikow\n");
    printf("Dopuszczalne odczyty: [-100, 200]\n");
    printf("Prawidlowe odczyty: [0, 100]\n");
}

int read_value(double *value, double min, double max) {
    double temp;
    int znak;
    int poprawne_dane = 1;

    if (scanf("%lf", &temp) != 1) {
        while ((znak = getchar()) != '\n' && znak != EOF) {
        }
        return 0;
    }

    while ((znak = getchar()) != '\n' && znak != EOF) {
        if (znak != ' ' && znak != '\t') {
            poprawne_dane = 0;
        }
    }

    if (poprawne_dane == 0 || !(temp >= min && temp <= max)) {
        return 0;
    }

    *value = temp;
    return 1;
}

int show_menu() {
    double wybor;

    while (1) {
        printf("\n MENU \n");
        printf("1. Wczytaj odczyty\n");
        printf("2. Wyswietl odczyty\n");
        printf("3. Kalibracja czujnikow\n");
        printf("4. Diagnostyka i korekta\n");
        printf("5. Zmien odczyt czujnika\n");
        printf("6. Zakoncz program\n");
        printf("Wybierz opcje: ");

        if (read_value(&wybor, 1, 6) == 1) {
            if (wybor == (int)wybor) {
                return (int)wybor;
            }
        }

        printf("Nieprawidlowa opcja. sprobuj jeszcze raz\n");
    }
}

void read_sensors(double sensors[], int n) {
    int i = 0;

    while (i < n) {
        printf("Podaj odczyt czujnika nr %d: ", i + 1);

        if (read_value(&sensors[i], -100, 200) == 1) {
            i++;
        } else {
            printf("Nieprawidlowa wartosc! Podaj liczbe z zakresu [-100, 200].\n");
        }
    }

    printf("Odczyty zostaly zapisane\n");
}

void display_sensors(const double sensors[], int n) {
    int i = 0;

    printf("\nAktualne odczyty:\n");

    while (i < n) {
        printf("Czujnik nr %d: %.2lf", i + 1, sensors[i]);

        if (sensors[i] < 0 || sensors[i] > 100) {
            printf(" - nieprawidlowy");
        }

        printf("\n");
        i++;
    }
}

void calibrate_sensors(double sensors[], int n, double offset) {
    int i = 0;

    while (i < n) {
        sensors[i] = sensors[i] + offset;
        i++;
    }

    printf("Kalibracja zakonczona\n");
}

int find_faulty_sensor(const double sensors[], int n, double min_allowed, double max_allowed) {
    int i = 0;

    while (i < n) {
        if (sensors[i] < min_allowed || sensors[i] > max_allowed) {
            return i;
        }

        i++;
    }

    return -1;
}

void modify_sensor(double sensors[], int n, int index) {
    if (index < 0 || index >= n) {
        printf("Nie ma takiego czujnika\n");
        return;
    }

    printf("Aktualny odczyt czujnika nr %d: %.2lf\n", index + 1, sensors[index]);

    while (1) {
        printf("Podaj nowy odczyt [-100, 200]: ");

        if (read_value(&sensors[index], -100, 200) == 1) {
            printf("Odczyt zostal zmieniony.\n");
            return;
        }

        printf("Nieprawidlowa wartosc, sprobuj jeszcze raz\n");
    }
}

void diagnose_sensors(double sensors[], int n) {
    int index = find_faulty_sensor(sensors, n, 0, 100);

    if (index == -1) {
        printf("Wszystkie odczyty sa prawidlowe\n");
        return;
    }

    while (index != -1) {
        printf("\nNieprawidlowy odczyt czujnika nr %d: %.2lf\n", index + 1, sensors[index]);

        printf("Podaj poprawiony odczyt [0, 100]: ");

        if (read_value(&sensors[index], 0, 100) == 1) {
            printf("Odczyt poprawiony.\n");
            index = find_faulty_sensor(sensors, n, 0, 100);
        } else {
            printf("Nieprawidlowa wartosc. sprobuj jeszcze raz\n");
        }
    }

    printf("\nWszystkie odczyty sa teraz prawidlowe\n");
}

int main() {
    double sensors[8];
    int n = 8;
    int wybor = 0;
    int wczytane = 0;

    double offset;
    double numer_czujnika;

    show_intro();

    while (wybor != 6) {
        wybor = show_menu();

        if (wybor == 1) {
            read_sensors(sensors, n);
            wczytane = 1;
        }

        else if (wybor == 2) {
            if (wczytane == 0) {
                printf("\nNajpierw wczytaj odczyty\n");
            } else {
                display_sensors(sensors, n);
            }
        }

        else if (wybor == 3) {
            if (wczytane == 0) {
                printf("\nNajpierw wczytaj odczyty\n");
            } else {
                printf("Podaj wartosc kalibracji: ");

                while (read_value(&offset, -100, 200) == 0) {
                    printf("Nieprawidlowa wartosc, podaj ponownie: ");
                }

                calibrate_sensors(sensors, n, offset);
            }
        }

        else if (wybor == 4) {
            if (wczytane == 0) {
                printf("\nNajpierw wczytaj odczyty\n");
            } else {
                diagnose_sensors(sensors, n);
            }
        }

        else if (wybor == 5) {
            if (wczytane == 0) {
                printf("\nNajpierw wczytaj odczyty\n");
            } else {
                printf("Podaj numer czujnika [1, 8]: ");

                while (1) {
                    if (read_value(&numer_czujnika, 1, n) == 1) {
                        if (numer_czujnika == (int)numer_czujnika) {
                            break;
                        }
                    }

                    printf("Nieprawidlowy numer, podaj ponownie: ");
                }

                modify_sensor(sensors, n, (int)numer_czujnika - 1);
            }
        }

        else if (wybor == 6) {
            printf("Zamykanie systemu\n");
        }
    }

    return 0;
}