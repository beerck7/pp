"""Testy rejestru ARGO. Kod sprawdzający pozostaje poza programem studenta."""
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'zadanie-5/glowne/argo.c'
FLAGS = ['-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-Werror']


class ArgoZadanie5(unittest.TestCase):
    def uruchom(self, fragment=None):
        with tempfile.TemporaryDirectory(prefix='pp5-', dir=os.environ.get('TMPDIR')) as tmp:
            executable = Path(tmp) / 'argo'
            if fragment is None:
                source = SOURCE
            else:
                source = Path(tmp) / 'test.c'
                source.write_text(
                    '#include <assert.h>\n#include <limits.h>\n'
                    '#define main pokaz_argo\n'
                    f'#include "{SOURCE.as_posix()}"\n'
                    '#undef main\nint main(void) {\n' + fragment + '\nreturn 0;\n}\n')
            build = subprocess.run(['gcc', *FLAGS, str(source), '-o', str(executable), '-lm'],
                                   capture_output=True, text=True)
            self.assertEqual(build.returncode, 0, build.stderr)
            result = subprocess.run([str(executable)], capture_output=True, text=True, timeout=3)
            self.assertEqual(result.returncode, 0, result.stderr)
            return result.stdout

    def test_pusty_rejestr(self):
        out = self.uruchom('''
            event_log log = {0};
            print_all(&log);
            print_threats(&log);
            find_type(&log, DIAGNOSTIC);
            find_id(&log, 1);
            report(&log);
        ''')
        for text in ['Rejestr jest pusty.', 'Brak zagrozen.',
                     'Nie znaleziono zdarzen tego rodzaju.',
                     'Nie znaleziono zdarzenia o ID 1.', 'Wszystkie zdarzenia: 0',
                     'Brak pomiarow temperatury.', 'Suma nieudanych prob: 0']:
            self.assertIn(text, out)

    def test_id_i_kopia_danych_unii(self):
        self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.temperature = 101.5;
            assert(add_event(&log, TEMPERATURE, data) == 1);
            data.attempts = 3;
            assert(add_event(&log, LOGIN_FAILURE, data) == 1);
            strcpy(data.text, "Test diagnostyki");
            assert(add_event(&log, DIAGNOSTIC, data) == 1);
            data.text[0] = 'X';
            assert(log.count == 3);
            assert(log.events[0].id == 1 && log.events[0].type == TEMPERATURE);
            assert(log.events[0].data.temperature == 101.5);
            assert(log.events[1].id == 2 && log.events[1].data.attempts == 3);
            assert(log.events[2].id == 3);
            assert(strcmp(log.events[2].data.text, "Test diagnostyki") == 0);
        ''')

    def test_granice_zagrozen(self):
        self.uruchom('''
            event item = {0};
            item.type = TEMPERATURE;
            item.data.temperature = 100;
            assert(is_dangerous(&item) == 0);
            item.data.temperature = 100.5;
            assert(is_dangerous(&item) == 1);
            item.type = LOGIN_FAILURE;
            item.data.attempts = 2;
            assert(is_dangerous(&item) == 0);
            item.data.attempts = 3;
            assert(is_dangerous(&item) == 1);
            item.type = DIAGNOSTIC;
            strcpy(item.data.text, "Zwykly komunikat");
            assert(is_dangerous(&item) == 0);
        ''')

    def test_bledne_dane_nie_dodaja_wpisu(self):
        self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.temperature = -5;
            assert(add_event(&log, TEMPERATURE, data) == 1);
            data.temperature = NAN;
            assert(add_event(&log, TEMPERATURE, data) == 0);
            data.temperature = INFINITY;
            assert(add_event(&log, TEMPERATURE, data) == 0);
            data.temperature = -INFINITY;
            assert(add_event(&log, TEMPERATURE, data) == 0);
            data.attempts = -1;
            assert(add_event(&log, LOGIN_FAILURE, data) == 0);
            assert(add_event(&log, (event_type)99, data) == 0);
            assert(log.count == 1);
            assert(log.events[0].data.temperature == -5);
        ''')

    def test_tekst_pusty_bez_konca_i_koniec_na_ostatnim_miejscu(self):
        self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            assert(add_event(&log, DIAGNOSTIC, data) == 0);
            for(int i = 0; i < TEXT_SIZE; i++) {
                data.text[i] = 'A';
            }
            assert(add_event(&log, DIAGNOSTIC, data) == 0);
            assert(log.count == 0);
            data.text[TEXT_SIZE - 1] = '\\0';
            assert(add_event(&log, DIAGNOSTIC, data) == 1);
            assert(log.events[0].data.text[TEXT_SIZE - 1] == '\\0');
            data.text[1] = '\\0';
            assert(add_event(&log, DIAGNOSTIC, data) == 1);
            assert(strcmp(log.events[1].data.text, "A") == 0);
        ''')

    def test_pelna_tablica_i_bledny_licznik(self):
        self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.attempts = 1;
            for(int i = 0; i < MAX_EVENTS; i++) {
                assert(add_event(&log, LOGIN_FAILURE, data) == 1);
                assert(log.events[i].id == i + 1);
            }
            data.attempts = 9;
            assert(add_event(&log, LOGIN_FAILURE, data) == 0);
            assert(log.count == MAX_EVENTS);
            assert(log.events[MAX_EVENTS - 1].data.attempts == 1);
            log.count = -1;
            assert(add_event(&log, LOGIN_FAILURE, data) == 0);
            assert(log.count == -1);
        ''')

    def test_raport_ujemne_temperatury(self):
        out = self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.temperature = -10;
            add_event(&log, TEMPERATURE, data);
            data.temperature = -5;
            add_event(&log, TEMPERATURE, data);
            report(&log);
        ''')
        self.assertIn('Najwyzsza temperatura: -5.00 C', out)
        self.assertIn('Temperatury: 2, logowania: 0, komunikaty: 0', out)
        self.assertIn('Liczba zagrozen: 0', out)

    def test_suma_prob_miesci_sie_w_long_long(self):
        out = self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.attempts = INT_MAX;
            add_event(&log, LOGIN_FAILURE, data);
            add_event(&log, LOGIN_FAILURE, data);
            report(&log);
            printf("Oczekiwana suma: %lld\\n", 2LL * INT_MAX);
        ''')
        actual = re.search(r'Suma nieudanych prob: (\d+)', out)
        expected = re.search(r'Oczekiwana suma: (\d+)', out)
        self.assertIsNotNone(actual)
        self.assertIsNotNone(expected)
        assert actual is not None and expected is not None
        self.assertEqual(actual.group(1), expected.group(1))
        self.assertIn('Liczba zagrozen: 2', out)

    def test_wyszukiwanie_typu_i_id(self):
        out = self.uruchom('''
            event_log log = {0};
            event_data data = {0};
            data.temperature = 20;
            add_event(&log, TEMPERATURE, data);
            data.attempts = 3;
            add_event(&log, LOGIN_FAILURE, data);
            find_type(&log, LOGIN_FAILURE);
            find_id(&log, 1);
            find_id(&log, 99);
        ''')
        self.assertEqual(out.count('ID 2: Nieudane proby: 3'), 1)
        self.assertEqual(out.count('ID 1: Temperatura: 20.00 C'), 1)
        self.assertIn('Nie znaleziono zdarzenia o ID 99.', out)
        self.assertNotIn('Nie znaleziono zdarzenia o ID 1.', out)

    def test_pokaz_w_main(self):
        out = self.uruchom()
        for text in ['Wszystkie zdarzenia: 5',
                     'Temperatury: 2, logowania: 2, komunikaty: 1',
                     'Najwyzsza temperatura: 101.50 C', 'Suma nieudanych prob: 5',
                     'Liczba zagrozen: 2', 'Odrzucono ujemna liczbe prob.',
                     'Odrzucono nieznany rodzaj.', 'Odrzucono niepoprawna temperature.',
                     'Odrzucono pusty komunikat.', 'rejestr jest pelny (100 zdarzen).']:
            self.assertIn(text, out)


if __name__ == '__main__':
    unittest.main()
