# PP — zadanie 2 do przejrzenia

**Od teraz nowe zmiany przechodzą przez akceptację na osobnej gałęzi.**

Zadanie 2 zostało opublikowane na `main` przed tym ustaleniem. Nie cofamy ani nie przepisujemy tamtej historii. Ta gałąź porządkuje przegląd i zasady następnych zmian; nie udaje, że istniejący kod dopiero czeka na pierwszą publikację.

## Materiały

- [Lista 11 programów, kompilacja i założenia](../zadanie-2/README.md).
- [Główny program ARGO](../zadanie-2/glowne/argo.c).
- [Rozgrzewka](../zadanie-2/rozgrzewka/) i [wprawki](../zadanie-2/wprawki/).
- [Wynik weryfikacji](WERYFIKACJA.md).

## Co sprawdzić samodzielnie

- [ ] Logowanie ARGO oraz trzy błędne próby.
- [ ] Dziewiąty odczyt usuwa najstarszy z bufora ośmiu wartości.
- [ ] Wylogowanie zachowuje odczyty.
- [ ] -40 i 40 nie alarmują, -41 i 41 alarmują.
- [ ] Pusty bufor i jeden odczyt są poprawnie obsługiwane przy statystykach.
- [ ] Tekst zamiast liczby, zły zakres i dodatkowy token są odrzucane.
- [ ] Seria rosnąca jest ciągła; równość ją przerywa, indeksy są od zera.
- [ ] Potrafisz wyjaśnić przesuwanie bufora, średnią i analizę cyfr przez `% 10` oraz `/ 10`.

Dane logowania są demonstracyjne. Granice techniczne i opcję zakończenia opisano jako założenia, nie wymagania prowadzącego. Nic nie zostało wysłane do Moodle; arkusz nie rozstrzyga jednoznacznie zakresu oddawania rozgrzewki i wprawek.

**Decyzja dotycząca następnych zmian: oczekuje.** Publikacja przeglądowej gałęzi nie oznacza automatycznego merge na main.
