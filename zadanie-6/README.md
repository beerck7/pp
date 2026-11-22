# Zadanie 6: wskazniki i pamiec dynamiczna

Kazdy program z wlasna funkcja `main()` kompilujemy osobno. W plikach
`rozgrzewka.c` i `wprawki.c` czesc programow pozostaje zakomentowana; aby je
uruchomic, odkomentuj jeden program naraz. W `wprawki.c` aktywna jest wprawka 6.
Rozgrzewka 3 ma dwa osobne pliki: `rozgrzewka_03a.c` i `rozgrzewka_03b.c`.
Oba ograniczaja n do 46340, aby kwadraty miescily sie w 32-bitowym int.

Po `free` wskaznik sam nie zmienia swojej wartosci, a zawartosc zwolnionego
obszaru nie jest gwarantowana. Odczyt po `free` ma niezdefiniowane zachowanie;
eksperyment nie jest wlaczony w programie.

## Odpowiedzi do rozgrzewki 1

- Przekazanie adresu pozwala funkcji zmienic oryginalny czujnik i uniknac
  kopiowania struktury przy odczycie. Strukture mozna tez przekazac przez wartosc.
- `->` daje dostep do pola struktury przez wskaznik.
- `const` chroni dane przed zmiana przez wskaznik w funkcji drukujacej.

## Odpowiedzi do wprawek

- Elementy tablicy dynamicznej struktur leza kolejno w pamieci.
- `realloc` moze przeniesc tablice; zachowuje dotychczasowe elementy w obszarze,
  ktory pozostaje po zmianie rozmiaru. Wskaznik pomocniczy pozwala zachowac stary
  adres, jesli operacja sie nie powiedzie.
- Po zmniejszeniu z 8 do 4 elementow zostaja 1, 2, 3, 4. Nie wolno czytac
  `arr[5]`, a zmiana adresu nie jest konieczna.
- Liczba elementow to ilosc zapisanych danych, pojemnosc to ilosc miejsc.
  Podwajanie pojemnosci ogranicza liczbe realokacji. Po bledzie trzeba zachowac
  stary wskaznik i zwolnic pamiec lub zakonczyc operacje bez utraty danych.
- Samo `realloc` nie przesuwa elementow w srodku: trzeba je przesunac recznie.
  Bledny indeks nalezy odrzucic. Zmniejszanie przydzialu po usunieciu jest
  opcjonalne, chociaz w tym cwiczeniu polecenie wymaga wykonania proby.
