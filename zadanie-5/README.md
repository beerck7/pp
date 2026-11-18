# Zadanie 5 — główne: rejestr ARGO

Program zapisuje zdarzenia: temperaturę, liczbę nieudanych prób logowania
albo komunikat diagnostyczny. `main` pokazuje działanie na gotowych danych;
nie ma menu ani wczytywania z klawiatury. To opis obecnego kodu, nie lista
wymagań oddawania na Moodle.

## Najważniejsze elementy

- `event_type` (`enum`) określa rodzaj zdarzenia.
- `event_data` (`union`) przechowuje jedną z trzech wartości we wspólnej pamięci.
- `event` (`struct`) łączy ID, rodzaj i dane.
- `event_log` zawiera tablicę zdarzeń i licznik zajętych miejsc.
- `add_event(&log, ...)` dostaje adres rejestru, żeby dopisać do oryginału.
- `const` przy funkcjach wypisujących zabrania zmiany danych przez ich wskaźniki.

## Uproszczenia kodu

Sprawdzenie końca napisu jest zwykłą pętlą `while`, bez funkcji `memchr`.
Pętla najpierw sprawdza granicę tablicy, dopiero potem jej znak. Dzięki `&&`
nie odczytuje elementu poza tablicą. Pusty tekst jest odrzucany osobno.

Raport odczytuje pola wprost przez `log->events[i]`, tak jak pozostałe pętle.
Nie tworzy dodatkowego wskaźnika `item`. Pierwszy pomiar ustawia maksimum;
kolejne są z nim porównywane. Dzięki temu działają także ujemne temperatury.

Zostały nazwy funkcji, typy, progi alarmów, sprawdzanie danych i pokaz w `main`.
Kod nie jest celowo skracany kosztem czytelności lub poprawności.

## Dwie mniej oczywiste rzeczy, które zostały

`isfinite` z `math.h` sprawdza, czy temperatura nie jest NaN lub nieskończonością.
Nie zastępuje progu alarmowego: poprawna temperatura może być zagrożeniem.

Suma prób używa `long long` i formatu `%lld`, aby nie sumować wielu dużych
wartości w zwykłym `int`. `strcpy` kopiuje stały komunikat, który mieści się
w tablicy; do tablicy znaków nie przypisujemy tekstu operatorem `=`.

## Uruchomienie z katalogu repozytorium

```bash
mkdir -p build
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror zadanie-5/glowne/argo.c -o build/argo5 -lm
./build/argo5
```

Testy pomocnicze są poza programem C:

```bash
python3 -m unittest discover -s tests -p test_zadanie5.py -v
```
