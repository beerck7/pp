import unittest
import test_zadanie1


class Walidacja(unittest.TestCase):
    uruchom = test_zadanie1.Programy.uruchom
    pliki = [
        "rozgrzewka/01_suma_srednia.c",
        "rozgrzewka/02_parzystosc.c",
        "rozgrzewka/03_rok_przestepny.c",
        "rozgrzewka/04_rzut_kostka.c",
        "glowne/argo.c",
        "wprawki/02_bagaz.c",
        "wprawki/03_automat_biletowy.c",
        "wprawki/04_uklad_siedzen.c",
        "wprawki/05_trojkat_prostokatny.c",
    ]

    def test_koniec_wejscia(self):
        for plik in self.pliki:
            with self.subTest(plik=plik):
                self.uruchom(plik, "")

    def test_smieci_i_dlugi_wiersz(self):
        for plik in self.pliki:
            for wpis in ["abc", "2abc", "nan", "inf", "9" * 400]:
                with self.subTest(plik=plik, wpis=wpis[:20]):
                    wynik = self.uruchom(plik, wpis + "\n")
                    self.assertIn("Niepoprawne dane", wynik)

    def test_automat_odrzuca_czesc_grosza(self):
        wynik = self.uruchom("wprawki/03_automat_biletowy.c", "1\n1\n1e-3\n4\n")
        self.assertIn("Niepoprawne dane", wynik)
        self.assertIn("Wydano bilety", wynik)

    def test_bagaz_granice(self):
        for waga, komunikat in [(0, "bez doplaty"), (23, "bez doplaty"),
                                (23.01, "nadbagaz"), (32, "nadbagaz"),
                                (32.01, "nie moze"), (200, "nie moze")]:
            with self.subTest(waga=waga):
                self.assertIn(komunikat, self.uruchom("wprawki/02_bagaz.c", f"{waga}\n"))

    def test_temperatura_granice(self):
        for temp, tekst in [(-10, "Frost"), (-1, "Frost"), (0, "comfortable"),
                            (25, "comfortable"), (26, "High temperature"),
                            (35, "High temperature")]:
            with self.subTest(temp=temp):
                self.assertIn(tekst, self.uruchom("wprawki/01_temperatura.c", env={"TEST_TEMP": str(temp)}))


if __name__ == "__main__":
    unittest.main()
