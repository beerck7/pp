# Podstawy programowania

Zadanie 1 — wejście/wyjście i instrukcje warunkowe w C.
Każdy plik to osobny program. Przygotowany jest cały zestaw, bo przekazane
polecenie nie rozstrzyga, czy na Moodle trzeba oddać również wprawki.

## Pliki

`zadanie-1/rozgrzewka/`:
- `01_suma_srednia.c` — suma i średnia dwóch liczb.
- `02_parzystosc.c` — parzystość dwóch liczb.
- `03_rok_przestepny.c` — sprawdzanie roku przestępnego.
- `04_rzut_kostka.c` — kostka z wybraną liczbą ścian.

`zadanie-1/glowne/argo.c` — gra Plasma / Cryo Shield / EMP.
Po rundzie można wybrać kolejny test albo zakończenie.

`zadanie-1/wprawki/`:
- `01_temperatura.c` — losowa temperatura i komunikat pogodowy.
- `02_bagaz.c` — kontrola wagi bagażu.
- `03_automat_biletowy.c` — cena biletów, wpłata i reszta.
- `04_uklad_siedzen.c` — porównanie rzędów po 3 i 5 miejsc.
- `05_trojkat_prostokatny.c` — sprawdzanie kąta prostego.

## Uruchomienie

Potrzebny jest GCC. Kompilujemy jeden plik, nie wszystkie do jednego programu.
Przykład dla ARGO na Linuxie:

```bash
mkdir -p build
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror zadanie-1/glowne/argo.c -o build/argo -lm
./build/argo
```

Na Windowsie z GCC/MinGW, w PowerShellu:

```powershell
New-Item -ItemType Directory -Force build
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror zadanie-1/glowne/argo.c -o build/argo.exe -lm
.\build\argo.exe
```

Dla pozostałych programów podmieniamy ścieżkę pliku i nazwę wyniku.
Kod był uruchamiany na Linuxie; komenda Windows wymaga własnej instalacji GCC.

## Wprowadzanie danych

Każdą liczbę podajemy w osobnym wierszu. Ułamki zapisujemy z kropką, np. `23.5`.
Programy odrzucają tekst zamiast liczby, dodatkowe znaki, zbyt długie wiersze
oraz wartości poza zakresem. Koniec wejścia kończy program.

Przyjęte ograniczenia tam, gdzie polecenie nie podaje górnej granicy:
- suma i parzystość: od -1 000 000 do 1 000 000;
- rok: od 1 do 1 000 000;
- kostka: od 4 do 1 000 000 ścian;
- liczba biletów, pasażerowie i długości boków: od 1 do 1 000 000;
- wpłata: od 0 do 10 000 000 zł, do dwóch miejsc po kropce;
- bagaż: od 0 do 200 kg, zgodnie z poleceniem.

W ARGO odpowiedź `t` oznacza kolejną rundę, a `n` zakończenie.
Kwoty po wczytaniu są przeliczane na grosze, aby porównywać ceny i liczyć resztę
na liczbach całkowitych. Kwadraty boków trójkąta są liczone w `long long`.

## Testy

Katalog `tests/` to dodatkowe narzędzie do sprawdzania programów, nie osobne
zadanie w Pythonie. Potrzebne są Python 3 i GCC:

```bash
python3 -m unittest discover -s tests -v
```

Testy kompilują i uruchamiają programy. Sprawdzają m.in. błędne dane, granice,
powtarzanie rund i wszystkie kombinacje wyborów ARGO. W testach losowanie jest
kontrolowane przez osobny plik testowy; oddawany kod C nadal używa `rand()`.

## Co warto umieć wyjaśnić

- Dlaczego średnią liczymy przez `2.0`, a nie `2`?
- Co sprawdza `a % 2 == 0`?
- Dlaczego rok 1900 nie jest przestępny, a 2000 jest?
- Co robi `srand(time(NULL))` i dlaczego wywołujemy je raz?
- Dlaczego po błędnym wpisie trzeba ponowić pytanie?
- Do czego służy dodatkowe `%c` w `sscanf`?
- Jak `(n + 2) / 3` wyznacza liczbę rzędów?
- Dlaczego rzutowanie na `long long` jest przed mnożeniem boków?

## Pomoc AI

Programy, testy i dokumentacja zostały przygotowane z pomocą AI, co zasady
przedmiotu dopuszczają przy zwykłych zadaniach. Przed oddaniem trzeba uruchomić
programy samodzielnie i rozumieć kod — podczas rozmów AI nie jest dozwolone.
