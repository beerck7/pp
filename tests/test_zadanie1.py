import os
import pathlib
import re
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]

class Programy(unittest.TestCase):
    def uruchom(self, plik, dane="", env=None):
        zrodlo = ROOT / "zadanie-1" / plik
        self.assertTrue(zrodlo.is_file(), f"Brak programu: {plik}")
        with tempfile.TemporaryDirectory() as katalog:
            program = pathlib.Path(katalog) / "program"
            polecenie = ["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror",
                         str(zrodlo), "-o", str(program), "-lm"]
            if env:
                los = None
                if "ARGO_LOS" in env:
                    los = int(env["ARGO_LOS"]) - 1
                elif "TEST_TEMP" in env:
                    los = int(env["TEST_TEMP"]) + 10
                if los is not None:
                    stub = pathlib.Path(katalog) / "losowanie.c"
                    stub.write_text(f"int rand(void) {{ return {los}; }}\n")
                    polecenie.append(str(stub))
            kompilacja = subprocess.run(polecenie, capture_output=True, text=True)
            self.assertEqual(kompilacja.returncode, 0, kompilacja.stderr)
            
            run_env = os.environ.copy()
            if env:
                run_env.update(env)

            wynik = subprocess.run([str(program)], input=dane,
                                   text=True, capture_output=True, timeout=3, env=run_env)
            self.assertEqual(wynik.returncode, 0, wynik.stderr)
            return wynik.stdout

    def test_suma(self):
        wynik = self.uruchom("rozgrzewka/01_suma_srednia.c", "2\n3\n")
        self.assertIn("Suma: 5", wynik)
        self.assertIn("Srednia: 2.50", wynik)

    def test_suma_walidacja_i_eof(self):
        wynik = self.uruchom("rozgrzewka/01_suma_srednia.c", "abc\n2.5\n4\n5\n")
        self.assertIn("Niepoprawne dane", wynik)
        self.assertIn("Podaj liczbe calkowita", wynik)
        self.assertIn("Suma: 9", wynik)
        self.assertIn("Srednia: 4.50", wynik)

    def test_parzystosc_obie_parzyste(self):
        wynik = self.uruchom("rozgrzewka/02_parzystosc.c", "4\n8\n")
        self.assertIn("obie liczby sa parzyste", wynik.lower())

    def test_parzystosc_obie_nieparzyste(self):
        wynik = self.uruchom("rozgrzewka/02_parzystosc.c", "3\n7\n")
        self.assertIn("obie liczby sa nieparzyste", wynik.lower())

    def test_parzystosc_jedna_parzysta_druga_nieparzysta(self):
        wynik = self.uruchom("rozgrzewka/02_parzystosc.c", "4\n7\n")
        self.assertIn("jedna liczba jest parzysta", wynik.lower())

    def test_rok_przestepny_400(self):
        wynik = self.uruchom("rozgrzewka/03_rok_przestepny.c", "2000\n")
        self.assertIn("jest przestepny", wynik.lower())

    def test_rok_przestepny_4_nie_100(self):
        wynik = self.uruchom("rozgrzewka/03_rok_przestepny.c", "2024\n")
        self.assertIn("jest przestepny", wynik.lower())

    def test_rok_nieprzestepny_100(self):
        wynik = self.uruchom("rozgrzewka/03_rok_przestepny.c", "1900\n")
        self.assertIn("nie jest przestepny", wynik.lower())

    def test_rok_nieprzestepny_zwykly(self):
        wynik = self.uruchom("rozgrzewka/03_rok_przestepny.c", "2023\n")
        self.assertIn("nie jest przestepny", wynik.lower())

    def test_rok_przestepny_walidacja(self):
        wynik = self.uruchom("rozgrzewka/03_rok_przestepny.c", "tekst\n-10\n2020\n")
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("jest przestepny", wynik.lower())

    def test_kostka_rzut_i_zakres(self):
        for _ in range(5):
            wynik = self.uruchom("rozgrzewka/04_rzut_kostka.c", "6\n")
            m = re.search(r"(wynik|wyrzucono):\s*(\d+)", wynik, re.IGNORECASE)
            self.assertIsNotNone(m, f"Brak wyniku rzutu w: {wynik}")
            wartosc = int(m.group(2))
            self.assertTrue(1 <= wartosc <= 6, f"Wartosc poza zakresem [1, 6]: {wartosc}")

    def test_kostka_walidacja(self):
        wynik = self.uruchom("rozgrzewka/04_rzut_kostka.c", "abc\n3\n0\n10\n")
        self.assertIn("niepoprawne dane", wynik.lower())
        m = re.search(r"(wynik|wyrzucono):\s*(\d+)", wynik, re.IGNORECASE)
        self.assertIsNotNone(m)
        wartosc = int(m.group(2))
        self.assertTrue(1 <= wartosc <= 10)

    def test_argo_wszystkie_9_wynikow(self):
        scenariusze = [
            (1, 1, "remis"),
            (1, 2, "zwyciestwo uzytkownika"),
            (1, 3, "zwyciestwo systemu"),
            (2, 1, "zwyciestwo systemu"),
            (2, 2, "remis"),
            (2, 3, "zwyciestwo uzytkownika"),
            (3, 1, "zwyciestwo uzytkownika"),
            (3, 2, "zwyciestwo systemu"),
            (3, 3, "remis"),
        ]
        for gracz, argo, oczekiwany in scenariusze:
            with self.subTest(gracz=gracz, argo=argo):
                wynik = self.uruchom("glowne/argo.c", f"{gracz}\nn\n", env={"ARGO_LOS": str(argo)})
                self.assertIn(oczekiwany, wynik.lower())

    def test_argo_petla_i_walidacja(self):
        dane = "0\n4\nzle\n1\nniepoprawne\nt\n2\nn\n"
        wynik = self.uruchom("glowne/argo.c", dane, env={"ARGO_LOS": "1"})
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("niepoprawna odpowiedz", wynik.lower())
        self.assertIn("remis", wynik.lower())

    def test_argo_odrzuca_dodatkowy_tekst(self):
        wynik = self.uruchom("glowne/argo.c", "1\nt smieci\nn\n")
        self.assertIn("Niepoprawna odpowiedz", wynik)
        self.assertEqual(wynik.count("Twoj wybor:"), 1)

    def test_temperatura_mroz(self):
        wynik = self.uruchom("wprawki/01_temperatura.c", env={"TEST_TEMP": "-5"})
        self.assertIn("frost. wear warm clothes.", wynik.lower())

    def test_temperatura_komfortowa(self):
        wynik = self.uruchom("wprawki/01_temperatura.c", env={"TEST_TEMP": "20"})
        self.assertIn("weather conditions are comfortable.", wynik.lower())

    def test_temperatura_upal(self):
        wynik = self.uruchom("wprawki/01_temperatura.c", env={"TEST_TEMP": "30"})
        self.assertIn("high temperature. avoid overheating.", wynik.lower())

    def test_temperatura_losowa_zakres(self):
        for _ in range(5):
            wynik = self.uruchom("wprawki/01_temperatura.c")
            m = re.search(r"(-?\d+)\s*c", wynik, re.IGNORECASE)
            self.assertIsNotNone(m)
            temp = int(m.group(1))
            self.assertTrue(-10 <= temp <= 35, f"Temperatura poza zakresem [-10, 35]: {temp}")

    def test_bagaz_bez_doplaty(self):
        for waga in ["0\n", "15.5\n", "23\n"]:
            wynik = self.uruchom("wprawki/02_bagaz.c", waga)
            self.assertIn("zaakceptowany bez doplaty", wynik.lower())

    def test_bagaz_nadbagaz(self):
        for waga in ["23.1\n", "28\n", "32\n"]:
            wynik = self.uruchom("wprawki/02_bagaz.c", waga)
            self.assertIn("dodatkowy koszt za nadbagaz", wynik.lower())

    def test_bagaz_odrzucony(self):
        for waga in ["32.1\n", "50\n", "200\n"]:
            wynik = self.uruchom("wprawki/02_bagaz.c", waga)
            self.assertIn("nie moze zostac przyjety", wynik.lower())

    def test_bagaz_walidacja_i_ponowienie(self):
        wynik = self.uruchom("wprawki/02_bagaz.c", "tekst\n-1\n201\n20\n")
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("zaakceptowany bez doplaty", wynik.lower())

    def test_automat_dokladna_wplata(self):
        wynik = self.uruchom("wprawki/03_automat_biletowy.c", "1\n2\n8.00\n")
        self.assertIn("wydano bilety", wynik.lower())
        self.assertNotIn("reszta:", wynik.lower())

    def test_automat_reszta(self):
        wynik = self.uruchom("wprawki/03_automat_biletowy.c", "1\n1\n10.00\n")
        self.assertIn("wydano bilety", wynik.lower())
        self.assertIn("reszta: 6.00 zl", wynik.lower())
        wynik2 = self.uruchom("wprawki/03_automat_biletowy.c", "2\n1\n2.50\n")
        self.assertIn("wydano bilety", wynik2.lower())
        self.assertIn("reszta: 0.50 zl", wynik2.lower())

    def test_automat_za_malo(self):
        wynik = self.uruchom("wprawki/03_automat_biletowy.c", "1\n2\n5.00\n")
        self.assertIn("niewystarczajaca kwota", wynik.lower())

    def test_automat_walidacja_i_ponowienie(self):
        dane = "0\n3\nabc\n1\n-2\n0\n1000001\n2\nabc\n-5\n8.123\n8.00\n"
        wynik = self.uruchom("wprawki/03_automat_biletowy.c", dane)
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("wydano bilety", wynik.lower())

    def test_uklad_siedzen_wariant_a_lepszy(self):
        wynik = self.uruchom("wprawki/04_uklad_siedzen.c", "6\n")
        self.assertIn("wariant a", wynik.lower())
        self.assertIn("bez pustych miejsc", wynik.lower())
        self.assertIn("wariant a", wynik.lower())

    def test_uklad_siedzen_wariant_b_lepszy(self):
        wynik = self.uruchom("wprawki/04_uklad_siedzen.c", "10\n")
        self.assertIn("wariant b", wynik.lower())
        self.assertIn("bez pustych miejsc", wynik.lower())

    def test_uklad_siedzen_remis(self):
        wynik = self.uruchom("wprawki/04_uklad_siedzen.c", "14\n")
        self.assertIn("taka sama", wynik.lower())
        wynik15 = self.uruchom("wprawki/04_uklad_siedzen.c", "15\n")
        self.assertIn("taka sama", wynik15.lower())
        self.assertIn("bez pustych miejsc", wynik15.lower())

    def test_uklad_siedzen_walidacja_i_ponowienie(self):
        wynik = self.uruchom("wprawki/04_uklad_siedzen.c", "abc\n-4\n0\n7\n")
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("wariant a", wynik.lower())

    def test_trojkat_prostokatny_kolejnosci(self):
        for dane in ["3\n4\n5\n", "5\n3\n4\n", "4\n5\n3\n"]:
            wynik = self.uruchom("wprawki/05_trojkat_prostokatny.c", dane)
            self.assertIn("potwierdzaja kat prosty", wynik.lower())
            self.assertNotIn("nie potwierdzaja", wynik.lower())

    def test_trojkat_nie_jest_prostokatny(self):
        wynik = self.uruchom("wprawki/05_trojkat_prostokatny.c", "3\n4\n6\n")
        self.assertIn("nie potwierdzaja kata prostego", wynik.lower())

    def test_trojkat_duze_liczby_overflow_check(self):
        wynik = self.uruchom("wprawki/05_trojkat_prostokatny.c", "600000\n800000\n1000000\n")
        self.assertIn("potwierdzaja kat prosty", wynik.lower())

    def test_trojkat_walidacja_i_ponowienie(self):
        dane = "0\n-5\nabc\n1000001\n3\n4\n5\n"
        wynik = self.uruchom("wprawki/05_trojkat_prostokatny.c", dane)
        self.assertIn("niepoprawne dane", wynik.lower())
        self.assertIn("potwierdzaja kat prosty", wynik.lower())


if __name__ == "__main__":
    unittest.main()
