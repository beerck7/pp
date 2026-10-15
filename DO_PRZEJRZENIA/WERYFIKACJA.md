# Sprawdzenie PP

Przed publikacją gałęzi przeglądowej ponownie wykonano:

```bash
python3 -m unittest discover -s tests -q
```

**Wynik: 101 testów zaliczonych.** Testy kompilują i wykonują programy C; obejmują zadania 1 i 2. W zadaniu 2 potwierdzono 11 samodzielnych plików C.

Kompilacja korzysta z `gcc -std=c11 -Wall -Wextra -Wpedantic -Werror`, a tam, gdzie potrzebne, z `-lm`. Sprawdzane są m.in. błędne dane, granice, EOF, bufor ARGO, statystyki, kolejne logowania oraz losowania kontrolowane w narzędziu testowym, bez ukrytych przełączników w programach.

Testy nie potwierdzają zgodności z nieznanym opisem formularza Moodle, oddania zadania ani samodzielnego opanowania kodu. Kod trzeba umieć wyjaśnić. Dane logowania ARGO są jawnie demonstracyjne.

Sam kod zadania 2 był już na main przed nową zasadą przeglądu. Bieżąca gałąź dodaje katalog przeglądu, nie przenosi tam ponownie kodu ani nie zmienia historii.

**Status nowych zmian: oczekują na akceptację.**
