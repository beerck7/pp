import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
FLAGS = ['-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-Werror']


def wiersze(wartosci):
    return ''.join(f'{x}\n' for x in wartosci)


class Program(unittest.TestCase):
    plik = ''

    def uruchom(self, dane='', losy=None):
        zrodlo = ROOT / 'zadanie-2' / self.plik
        self.assertTrue(zrodlo.is_file(), f'Brak programu: {self.plik}')
        with tempfile.TemporaryDirectory(prefix='pp2-', dir=os.environ.get('TMPDIR')) as katalog:
            program = Path(katalog) / 'program'
            cmd = ['gcc', *FLAGS, str(zrodlo), '-o', str(program), '-lm']
            if losy is not None:
                fixture = Path(katalog) / 'losowanie.c'
                wartosci = ','.join(str(x) for x in losy)
                fixture.write_text('int rand(void) { static unsigned int i; '
                                   f'const int losy[] = {{{wartosci}}}; '
                                   'return losy[i++ % (sizeof(losy)/sizeof(losy[0]))]; }\n')
                cmd.append(str(fixture))
            kompilacja = subprocess.run(cmd, capture_output=True, text=True)
            self.assertEqual(kompilacja.returncode, 0, kompilacja.stderr)
            wynik = subprocess.run([str(program)], input=dane, text=True,
                                   capture_output=True, timeout=3)
            self.assertEqual(wynik.returncode, 0, wynik.stderr)
            return wynik.stdout


class Pomiary(Program):
    plik = 'rozgrzewka/01_pomiary.c'

    def test_dodatnie_ulamki_i_liczenie_prob(self):
        out = self.uruchom(wiersze([0, -5, 1.5, 2, 3, 4, 5]))
        for fragment in ['Proby: 7', 'Suma: 15.50', 'Maksimum: 5.00']:
            self.assertIn(fragment, out)

    def test_bledy_tego_samego_pomiaru_tez_sa_probami(self):
        dane = wiersze(['abc', '1 2', 'nan', 'inf', '1e309', '1e-999',
                        '9' * 400, '1000001', 1, 2, 3, 4, 5])
        out = self.uruchom(dane)
        self.assertEqual(out.count('Niepoprawne dane'), 8)
        self.assertIn('Proby: 13', out)
        self.assertIn('Suma: 15.00', out)

    def test_eof_pusty_i_w_trakcie(self):
        for dane in ['', '1\n2\n', 'x' * 400]:
            with self.subTest(dane=dane[:10]):
                self.assertNotIn('Suma:', self.uruchom(dane))

    def test_granica_i_ostatni_wiersz_bez_newline(self):
        out = self.uruchom('1000000\n1\n1\n1\n1')
        self.assertIn('Suma: 1000004.00', out)
        self.assertIn('Maksimum: 1000000.00', out)


class TrzyRosnace(Program):
    plik = 'rozgrzewka/02_trzy_rosnace.c'

    def test_kolejne_nie_podciag(self):
        out = self.uruchom(wiersze([1, 3, 2, 4, 3, 5, 6]))
        self.assertIn('Trojka: 3 5 6', out)
        self.assertIn('Odczyty: 7', out)

    def test_rownosc_przerywa_serie(self):
        out = self.uruchom(wiersze([1, 2, 2, 3, 4]))
        self.assertIn('Trojka: 2 3 4', out)
        self.assertIn('Odczyty: 5', out)

    def test_walidacja_i_granice(self):
        for blad in ['abc', '1 2', '1.5', 'nan', 'inf', '1e309',
                     '9' * 400, '-1000001', '1000001', '']:
            with self.subTest(blad=blad[:10]):
                out = self.uruchom(wiersze([blad, -1000000, 0, 1000000]))
                self.assertIn('Niepoprawne dane', out)
                self.assertIn('Trojka: -1000000 0 1000000', out)
                self.assertIn('Odczyty: 3', out)

    def test_rzeczywisty_eof(self):
        for dane in ['', '1\n2\n', '9' * 400]:
            self.assertNotIn('Trojka:', self.uruchom(dane))


class LosowaTablica(Program):
    plik = 'rozgrzewka/03_losowa_tablica.c'

    def tablica(self, out):
        m = re.search(r'Tablica:([^\n]+)', out)
        self.assertIsNotNone(m, out)
        assert m is not None
        return list(map(int, m[1].split()))

    def test_normalne_losowanie(self):
        out = self.uruchom('-5\n5\n')
        tablica = self.tablica(out)
        self.assertEqual(len(tablica), 10)
        self.assertTrue(all(-5 <= x <= 5 for x in tablica))
        self.assertIn(f'Maksimum: {max(tablica)}', out)
        self.assertIn(f'Wystapienia: {tablica.count(max(tablica))}', out)

    def test_dolna_gorna_granica_i_krotnosc(self):
        for losy, oczekiwane, maksimum, ile in [
            ([0], [-2] * 10, -2, 10),
            ([4], [2] * 10, 2, 10),
            ([0, 4, 1, 4, 2, 4, 3, 0, 1, 2], [-2, 2, -1, 2, 0, 2, 1, -2, -1, 0], 2, 3),
        ]:
            out = self.uruchom('-2\n2\n', losy)
            self.assertEqual(self.tablica(out), oczekiwane)
            self.assertIn(f'Maksimum: {maksimum}', out)
            self.assertIn(f'Wystapienia: {ile}', out)

    def test_min_rowne_max(self):
        out = self.uruchom('-1000000\n-1000000\n')
        self.assertEqual(self.tablica(out), [-1000000] * 10)

    def test_zakres_i_bledne_dane(self):
        for blad in ['abc', '1 2', '1.5', 'nan', 'inf', '9' * 400, '-1000001', '1000001']:
            out = self.uruchom(wiersze([blad, 5, 4, 5]), [0])
            self.assertIn('Niepoprawne dane', out)
            self.assertEqual(self.tablica(out), [5] * 10)

    def test_eof_przed_kazda_granica(self):
        for dane in ['', '5\n', '9' * 400]:
            self.assertNotIn('Tablica:', self.uruchom(dane))


class Odwracanie(Program):
    plik = 'rozgrzewka/04_odwracanie.c'

    def test_od_tylu_i_zamiany(self):
        out = self.uruchom(wiersze([1, -2, 3, 3, 5, 6, 7, 8]))
        self.assertIn('Od tylu: 8 7 6 5 3 3 -2 1', out)
        self.assertIn('Po zamianach: 8 7 6 5 3 3 -2 1', out)

    def test_bledy_i_granice(self):
        for blad in ['tekst', '1 2', '1.1', 'nan', 'inf', '9' * 400, '-1000001', '1000001']:
            out = self.uruchom(wiersze([blad, -1000000, 1000000, 0, 0, 0, 0, 0, 0]))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Po zamianach: 0 0 0 0 0 0 1000000 -1000000', out)

    def test_eof_na_kazdym_elemencie(self):
        for ile in range(8):
            self.assertNotIn('Po zamianach:', self.uruchom('1\n' * ile))


class Argo(Program):
    plik = 'glowne/argo.c'
    login = 'argo\n1234\n'

    def test_logowanie_i_zakonczenie(self):
        out = self.uruchom(self.login + '0\n')
        self.assertIn('Zalogowano.', out)
        self.assertIn('0 - Koniec', out)

    def test_trzy_bledne_proby_koncza_program(self):
        out = self.uruchom('zly\nzle\n' * 3 + self.login)
        self.assertEqual(out.count('Bledne logowanie'), 3)
        self.assertIn('Limit prob', out)
        self.assertNotIn('Zalogowano.', out)

    def test_poprawne_trzecie_logowanie(self):
        out = self.uruchom('argo\nzle\n' * 2 + self.login + '0\n')
        self.assertEqual(out.count('Bledne logowanie'), 2)
        self.assertIn('Zalogowano.', out)

    def test_tokeny_i_dlugie_wiersze_logowania(self):
        for login, haslo in [('argo smieci', '1234'), ('argo', '1234 smieci'),
                             ('x' * 400, '1234'), ('argo', 'x' * 400), ('', '1234')]:
            out = self.uruchom(wiersze([login, haslo]) + self.login + '0\n')
            self.assertEqual(out.count('Bledne logowanie'), 1)
            self.assertEqual(out.count('Zalogowano.'), 1)

    def test_eof_logowanie_i_menu(self):
        for dane in ['', 'argo\n', self.login, 'x' * 400]:
            out = self.uruchom(dane)
            self.assertNotIn('Limit prob', out)

    def dodaj(self, wartosci):
        return ''.join(f'1\n{x}\n' for x in wartosci)

    def odczyty(self, out):
        return re.findall(r'^\[(\d+)\] (-?\d+)$', out, re.M)

    def test_dziewiaty_shift_i_edycja_ostatniego(self):
        out = self.uruchom(self.login + self.dodaj(range(1, 10)) + '2\n7\n50\n3\n0\n')
        self.assertEqual(self.odczyty(out), [(str(i), str(x)) for i, x in enumerate([2, 3, 4, 5, 6, 7, 8, 50])])

    def test_retencja_po_wylogowaniu_i_czyszczenie(self):
        out = self.uruchom(self.login + self.dodaj([10, 20]) + '7\n' + self.login + '3\n6\n3\n0\n')
        self.assertEqual(out.count('Zalogowano.'), 2)
        self.assertEqual(self.odczyty(out), [('0', '10'), ('1', '20')])
        self.assertIn('Wyczyszczono.', out)
        self.assertIn('Brak odczytow.', out)

    def test_nieistniejacy_indeks_nie_zmienia_bufora(self):
        out = self.uruchom(self.login + self.dodaj([10]) + '2\n7\n3\n0\n')
        self.assertIn('Nieistniejacy indeks', out)
        self.assertEqual(self.odczyty(out), [('0', '10')])

    def test_edycja_pustego_bufora(self):
        out = self.uruchom(self.login + '2\n3\n0\n')
        self.assertEqual(out.count('Brak odczytow.'), 2)

    def test_bledne_menu_typ_zakres_tokeny(self):
        for blad in ['8', '-1', 'abc', '1.5', '1 2', '9' * 400, 'nan', 'inf', '99999999999999999999']:
            out = self.uruchom(self.login + wiersze([blad, 3, 0]))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Brak odczytow.', out)
            self.assertNotIn('Odczyt: ', out)

    def test_bledne_odczyty_i_indeksy(self):
        for blad in ['abc', '-51', '51', '1.5', '1 2', 'nan', 'inf', '9' * 400]:
            out = self.uruchom(self.login + '1\n' + wiersze([blad, -50]) +
                               '2\n-1\n8\n0 1\n0\n' + wiersze([blad, 50, 3, 0]))
            self.assertIn('Niepoprawne dane', out)
            self.assertEqual(self.odczyty(out), [('0', '50')])

    def test_eof_w_dodawaniu_edycji_i_po_logout(self):
        for dane in ['1\n', self.dodaj([5]) + '2\n',
                     self.dodaj([5]) + '2\n0\n', '7\n', '7\nargo\n',
                     '1\n' + '9' * 400]:
            self.uruchom(self.login + dane)

    def test_alarmy_granice(self):
        out = self.uruchom(self.login + self.dodaj([-50, -41, -40, 0, 40, 41, 50]) + '5\n0\n')
        self.assertEqual(re.findall(r'Alarm \[(\d+)\]: (-?\d+)', out),
                         [('0', '-50'), ('1', '-41'), ('5', '41'), ('6', '50')])

    def test_brak_alarmow_i_puste_statystyki(self):
        out = self.uruchom(self.login + '4\n5\n' + self.dodaj([-40, 40]) + '5\n0\n')
        self.assertEqual(out.count('Brak odczytow.'), 2)
        self.assertIn('Brak alarmow.', out)

    def test_statystyki_chronologiczne(self):
        out = self.uruchom(self.login + self.dodaj([10, -20, 30, 25]) + '4\n0\n')
        for tekst in ['Srednia: 11.25', 'Powyzej sredniej: 2',
                      'Najwiekszy wzrost: 50', 'Najwiekszy spadek: 30']:
            self.assertIn(tekst, out)

    def test_jeden_element_i_brak_zmian(self):
        for wartosci, srednia in [([5], '5.00'), ([5, 5, 5], '5.00')]:
            out = self.uruchom(self.login + self.dodaj(wartosci) + '4\n0\n')
            for tekst in ['Srednia: ' + srednia, 'Powyzej sredniej: 0',
                          'Brak wzrostow.', 'Brak spadkow.']:
                self.assertIn(tekst, out)

    def test_tylko_wzrosty_lub_spadki(self):
        for wartosci, jest, brak in [([1, 3, 4], 'Najwiekszy wzrost: 2', 'Brak spadkow.'),
                                     ([4, 3, 1], 'Najwiekszy spadek: 2', 'Brak wzrostow.')]:
            out = self.uruchom(self.login + self.dodaj(wartosci) + '4\n0\n')
            self.assertIn(jest, out)
            self.assertIn(brak, out)

    def test_statystyki_po_shift_i_edycji(self):
        out = self.uruchom(self.login + self.dodaj([-50, 0, 0, 0, 0, 0, 0, 0, 0]) +
                           '2\n7\n40\n4\n0\n')
        for tekst in ['Srednia: 5.00', 'Powyzej sredniej: 1',
                      'Najwiekszy wzrost: 40', 'Brak spadkow.']:
            self.assertIn(tekst, out)


    def test_limit_logowania_po_wylogowaniu(self):
        out = self.uruchom(self.login + '7\n' + 'argo\nzle\n' * 3 + self.login)
        self.assertEqual(out.count('Zalogowano.'), 1)
        self.assertEqual(out.count('Bledne logowanie'), 3)
        self.assertIn('Limit prob', out)

    def test_bledny_dziewiaty_pomiar_nie_przesuwa_dwa_razy(self):
        out = self.uruchom(self.login + self.dodaj(range(1, 9)) + '1\n51\n50\n3\n0\n')
        self.assertEqual(self.odczyty(out), [(str(i), str(x)) for i, x in enumerate([2, 3, 4, 5, 6, 7, 8, 50])])

    def test_dodawanie_po_czyszczeniu(self):
        out = self.uruchom(self.login + self.dodaj(range(1, 9)) + '6\n' + self.dodaj([-5]) + '3\n4\n0\n')
        self.assertEqual(self.odczyty(out), [('0', '-5')])
        self.assertIn('Srednia: -5.00', out)


class Energia(Program):
    plik = 'wprawki/01_energia.c'

    def test_ulamki_i_sentinel(self):
        out = self.uruchom('1.5\n2.25\n3\n0\n999\n')
        for tekst in ['Suma: 6.75', 'Pomiary: 3', 'Maksimum: 3.00']:
            self.assertIn(tekst, out)

    def test_pusty_sentinel(self):
        out = self.uruchom('0\n')
        self.assertIn('Brak danych.', out)
        self.assertNotIn('Maksimum:', out)

    def test_zle_typy_zakresy_i_duze_wartosci(self):
        for blad in ['-1', '1000001', 'abc', '1 2', 'nan', 'inf', '1e309', '1e-999', '9' * 400]:
            out = self.uruchom(wiersze([blad, 1000000, 1000000, 0]))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Suma: 2000000.00', out)
            self.assertIn('Pomiary: 2', out)

    def test_rzeczywisty_eof(self):
        for dane in ['', '1\n2\n', '9' * 400]:
            self.assertNotIn('Suma:', self.uruchom(dane))


class Cyfry(Program):
    plik = 'wprawki/02_cyfry.c'

    def test_przyklad_i_zera(self):
        for kod, suma, maksimum, parzyste in [(58342, 22, 8, 3), (10020, 3, 2, 4),
                                             (1, 1, 1, 0)]:
            out = self.uruchom(str(kod))
            for tekst in [f'Suma cyfr: {suma}', f'Najwieksza cyfra: {maksimum}',
                          f'Cyfry parzyste: {parzyste}']:
                self.assertIn(tekst, out)

    def test_gorna_granica(self):
        cyfry = list(map(int, '2147483647'))
        out = self.uruchom('2147483647\n')
        self.assertIn(f'Suma cyfr: {sum(cyfry)}', out)
        self.assertIn(f'Najwieksza cyfra: {max(cyfry)}', out)
        self.assertIn(f'Cyfry parzyste: {sum(x % 2 == 0 for x in cyfry)}', out)

    def test_bledy_typu_zakresu_i_dlugosci(self):
        for blad in ['abc', '1 2', '1.5', 'nan', 'inf', '0', '-1', '2147483648', '9' * 400]:
            out = self.uruchom(wiersze([blad, 58342]))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Suma cyfr: 22', out)

    def test_rzeczywisty_eof(self):
        for dane in ['', '9' * 400]:
            self.assertNotIn('Suma cyfr:', self.uruchom(dane))


class ZmianySensora(Program):
    plik = 'wprawki/03_zmiany_sensora.c'

    def test_zmiany_sasiednie_nie_globalny_zakres(self):
        out = self.uruchom(wiersze([40, 44, 41, 52, 50, 49, 48, 47]))
        self.assertIn('Najwiekszy wzrost: 11', out)
        self.assertIn('Najwiekszy spadek: 3', out)

    def test_stale_rosnace_i_malejace(self):
        for wartosci, jest, brak in [([5] * 8, 'Brak wzrostow.', 'Brak spadkow.'),
                                     (list(range(8)), 'Najwiekszy wzrost: 1', 'Brak spadkow.'),
                                     (list(range(8, 0, -1)), 'Najwiekszy spadek: 1', 'Brak wzrostow.')]:
            out = self.uruchom(wiersze(wartosci))
            self.assertIn(jest, out)
            self.assertIn(brak, out)

    def test_zakres_roznic_i_walidacja(self):
        for blad in ['abc', '1.5', '1 2', 'nan', 'inf', '9' * 400, '-1000001', '1000001']:
            out = self.uruchom(wiersze([blad, -1000000, 1000000, -1000000, 0, 0, 0, 0, 0]))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Najwiekszy wzrost: 2000000', out)
            self.assertIn('Najwiekszy spadek: 2000000', out)

    def test_eof_na_kazdym_elemencie(self):
        for ile in range(8):
            self.assertNotIn('Najwiekszy', self.uruchom('1\n' * ile))


class Bufor(Program):
    plik = 'wprawki/04_bufor.c'

    def test_dokladny_przyklad(self):
        out = self.uruchom('25\n')
        self.assertIn('Przed: 12 15 17 14 20 21 19 18', out)
        self.assertIn('Po: 15 17 14 20 21 19 18 25', out)

    def test_walidacja_i_granice(self):
        for blad in ['abc', '1.5', '1 2', 'nan', 'inf', '9' * 400, '-1000001', '1000001']:
            for dobry in [-1000000, 1000000]:
                out = self.uruchom(wiersze([blad, dobry]))
                self.assertIn('Niepoprawne dane', out)
                self.assertIn(f'Po: 15 17 14 20 21 19 18 {dobry}', out)

    def test_rzeczywisty_eof(self):
        for dane in ['', 'abc\n', '9' * 400]:
            self.assertNotIn('Po:', self.uruchom(dane))


class Histogram(Program):
    plik = 'wprawki/05_histogram.c'

    def histogram(self, out):
        pasma = re.findall(r'^([1-6]): ([*]*)$', out, re.M)
        self.assertEqual([x for x, _ in pasma], ['1', '2', '3', '4', '5', '6'])
        zliczenia = [len(gwiazdki) for _, gwiazdki in pasma]
        self.assertEqual(sum(zliczenia), 50)
        return zliczenia

    def test_normalne_losowanie_50_rzutow(self):
        self.histogram(self.uruchom())

    def test_kazda_sciana(self):
        for los in range(6):
            out = self.uruchom(losy=[los])
            self.assertEqual(self.histogram(out), [50 if i == los else 0 for i in range(6)])

    def test_mieszane_wyniki(self):
        losy = [0, 0, 1, 2, 3, 4, 5]
        oczekiwane = [sum(losy[i % len(losy)] == x for i in range(50)) for x in range(6)]
        self.assertEqual(self.histogram(self.uruchom(losy=losy)), oczekiwane)


class SeriaRosnaca(Program):
    plik = 'wprawki/06_seria_rosnaca.c'

    def sprawdz(self, wartosci, dlugosc, poczatek, koniec):
        out = self.uruchom(wiersze(wartosci))
        for tekst in [f'Dlugosc: {dlugosc}', f'Poczatek: {poczatek}', f'Koniec: {koniec}']:
            self.assertIn(tekst, out)

    def test_przyklad(self):
        self.sprawdz([4, 6, 9, 3, 5, 7, 8, 2, 10, 11, 1, 0], 4, 3, 6)

    def test_rosnaca_do_konca_i_cala(self):
        self.sprawdz([9, 8, 7, 6, 5, 4, 0, 1, 2, 3, 4, 5], 6, 6, 11)
        self.sprawdz(list(range(12)), 12, 0, 11)

    def test_rownosci_i_remis_pierwszy(self):
        self.sprawdz([1, 2, 3, 0, 1, 2, 0, 1, 2, -1, -1, -1], 3, 0, 2)
        self.sprawdz([1, 2, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0], 4, 2, 5)
        self.sprawdz([5] * 12, 1, 0, 0)
        self.sprawdz(list(range(12, 0, -1)), 1, 0, 0)

    def test_fragment_nie_lis(self):
        self.sprawdz([1, 4, 2, 5, 3, 6, 4, 7, 5, 8, 6, 9], 2, 0, 1)

    def test_bledne_dane_i_granice(self):
        for blad in ['abc', '1.5', '1 2', 'nan', 'inf', '9' * 400, '-1000001', '1000001']:
            out = self.uruchom(wiersze([blad, -1000000] + [1000000] * 11))
            self.assertIn('Niepoprawne dane', out)
            self.assertIn('Dlugosc: 2', out)
            self.assertIn('Poczatek: 0', out)
            self.assertIn('Koniec: 1', out)

    def test_eof_na_kazdym_elemencie(self):
        for ile in range(12):
            self.assertNotIn('Dlugosc:', self.uruchom('1\n' * ile))
