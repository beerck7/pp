# Zadanie 2 — pętle i tablice

Każdy plik C to osobny program. Bez dodatkowych bibliotek ani wspólnego nagłówka.

## Programy

| Plik | Działanie |
| --- | --- |
| `rozgrzewka/01_pomiary.c` | 5 dodatnich pomiarów: wszystkie próby, suma, maksimum |
| `rozgrzewka/02_trzy_rosnace.c` | Pierwsze 3 kolejne ściśle rosnące odczyty i liczba odczytów |
| `rozgrzewka/03_losowa_tablica.c` | 10 losowań z [min, max], maksimum i liczba wystąpień |
| `rozgrzewka/04_odwracanie.c` | Wypisanie 8 liczb od tyłu, potem odwrócenie tej samej tablicy |
| `glowne/argo.c` | Logowanie i monitor ostatnich 8 odczytów |
| `wprawki/01_energia.c` | Dodatnie pomiary do 0: suma, liczba, maksimum |
| `wprawki/02_cyfry.c` | Suma i maksimum cyfr, liczba parzystych cyfr (także zer) |
| `wprawki/03_zmiany_sensora.c` | Największy sąsiedni wzrost i spadek dla 8 odczytów |
| `wprawki/04_bufor.c` | Przesunięcie bufora z początkowymi danymi z przykładu |
| `wprawki/05_histogram.c` | 50 rzutów kostką, 6 liczników i histogram gwiazdkowy |
| `wprawki/06_seria_rosnaca.c` | Najdłuższy ciągły ściśle rosnący fragment 12 liczb |

## Kompilacja i testy

Z głównego katalogu repozytorium, na Linuxie z GCC:

```bash
mkdir -p build
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror zadanie-2/glowne/argo.c -o build/argo2 -lm
./build/argo2
python3 -m unittest discover -s tests -v
```

Dla innych programów podmień ścieżkę i nazwę wyniku. Testy wymagają Python 3;
kompilują i rzeczywiście uruchamiają programy. Losowania sprawdzają także przez
osobny plik podmieniany przy linkowaniu, bez zmiany kodu ćwiczeń.

## Dane i przyjęte założenia

- Jedna liczba, login lub hasło w wierszu; do 254 znaków bez końca wiersza.
  Dodatkowe tokeny, zły typ, zakres i za długi wiersz są odrzucane.
  EOF kończy program również podczas operacji; nie wypisujemy niepełnych wyników.
- Arkusz nie określa typu pomiarów w pierwszej rozgrzewce i energii:
  przyjęto `double`, z kropką dla ułamków. Wyniki są zaokrąglane do 2 miejsc
  tylko przy wyświetlaniu. Odrzucamy NaN, nieskończoność oraz błędy konwersji
  (także przepełnienie i niedomiar). Dodatni pomiar może być mniejszy od 0.01.
- Granice techniczne, nie wymagania prowadzącego: pomiary i liczby całkowite
  bez zakresu w arkuszu mieszczą się w [-1 000 000, 1 000 000]; energia w
  [0, 1 000 000], przy czym 0 kończy zbieranie. Kod cyfrowy: 1–2 147 483 647.
  Przyjęto GCC z co najmniej 32-bitowym `int`.
- Pętle o nieznanej długości mają limit 1 000 000: w pierwszej rozgrzewce
  wszystkich prób (również błędnych), w drugiej poprawnych odczytów, w energii
  dodatnich pomiarów. Po limicie jest komunikat; energia podaje zebrane wyniki,
  a rozgrzewki bez wymaganej liczby danych nie podają wyniku końcowego.
  Te granice chronią liczniki, sumy i różnice przed przepełnieniem.
- Wzrost i spadek liczymy tylko między sąsiadami, w kolejności wprowadzenia.
  Spadek podajemy jako dodatnią wielkość. Brak danego rodzaju zmiany jest
  nazwany wprost. Średnia ARGO używa dzielenia zmiennoprzecinkowego.
- Indeksy od 0. W serii rosnącej oba końce należą do fragmentu; równość
  przerywa serię, przy remisie wybieramy pierwszy fragment. To fragment ciągły,
  nie podciąg z pomijaniem elementów. Kolejność w ARGO: najstarszy odczyt pierwszy.
- ARGO: `argo` / `1234` to jawne DANE DEMONSTRACYJNE, nie prawdziwe poświadczenia.
  Login, hasło i opcja `0 = koniec` są założeniami, bo arkusz ich nie podaje.
  Każdy ekran logowania pozwala na 3 próby; błędny format też zużywa próbę.
  Menu: 1 dodaj, 2 zmień, 3 lista, 4 statystyki, 5 alarmy, 6 czyść, 7 wyloguj.
  Nieistniejący indeks wraca do menu bez zmiany danych. Wylogowanie zachowuje
  bufor, czyszczenie usuwa jego logiczną zawartość. Alarm: < -40 lub > 40;
  wartości -40 i 40 nie są alarmowe.

Arkusz nie rozstrzyga, które części trzeba przesłać na Moodle. Ten zestaw
obejmuje wszystkie ćwiczenia, ale nie jest potwierdzeniem oddania pracy.

## Do samodzielnego zrozumienia

- Dlaczego przy przesuwaniu bufora idziemy od początku, a nie od końca?
- Dlaczego przy odwracaniu wystarczą 4 zamiany i jedna zmienna pomocnicza?
- Co zmieniłoby `>=` zamiast `>` podczas szukania rosnącej serii?
- Dlaczego do średniej potrzebne jest dzielenie przez liczbę elementów jako `double`?
- Jak `% 10` i `/ 10` pozwalają analizować cyfry, w tym zero wewnątrz liczby?
