#include <iostream>
#include <fstream>
#include <string>
#include "Plik.h"
#include "genetyczny.h"
#include "Timer.h"

using namespace std;
int main()
{
	Plik *plik = new Plik();
	genetyczny *gen = new genetyczny();
	Timer* timer = new Timer();
	vector<int>  sciezka;
	char w;
	bool a, b;
	a = b = true;
	while (a) {
		cout << endl;
		cout << "\n== Menu Glowne ==\n" << endl;
		cout << "Wybierz:" << endl;
		cout << "-1-. Praca z danymi" << endl;
		cout << "-2-. Algorytm" << endl;
		cout << "-3-. Zakonc program" << endl;
		cout << "\nWpisz potrzebne: ";
		cin >> w;
		cout << endl;
		system("cls");
		switch (w) {
		case '1': {
			b = true;
			while (b)
			{
				cout << "\n<<Menu - Generowania danych>>\n" << endl;
				cout << "Wybierz opcje:" << endl;
				cout << "-1- Wczytaj dane z pliku(atsp):" << endl;
				cout << "-2- Wczytaj dane z pliku(tsp):" << endl;
				cout << "\n-a- Powrot do ==Menu Glowne==\n" << endl;
				cout << "\nWpisz potrzebne: ";

				cin >> w;
				system("cls");
				switch (w)
				{
				case '1': {
					string nazwa;
					cout << "Podaj nazwe pliku:";
					cin >> nazwa;
					plik->atsp(nazwa);
					break;
				}
				case '2': {
					string nazwa;
					cout << "Podaj nazwe pliku:";
					cin >> nazwa;
					plik->tsp(nazwa);
					break;
				}
				case 'a': {
					b = false;
					break;
				}
				}

			}
			break;
		}
		case '2': {
			int it = 0, optimal;
			string text = "";
			double r, pr, pm;
			cout << "Podaj parametry:" << endl;
			cout << "Ilosc iteracji:" << endl;
			cin >> it;
			cout << "Rozmiar populacji:" << endl;
			cin >> r;
			cout << "Prawdopodobienstwo krzyzowania:" << endl;
			cin >> pr;
			cout << "Prawdopodobienstwo mutacji:" << endl;
			cin >> pm;
			cout << "Czy chcesz policzyc blad ? " << endl;
			cout << "Wpisz odpowiedz: ";
			cin >> text;
			cout << endl;

			if (text == "Tak" || text == "tak")
			{
				cout << "Wpisz optymalne rozwiazanie: ";
				cin >> optimal;
				for (int i = 0; i < 1; i++)
				{
					
					timer->startTimer();
					sciezka = gen->Algorytm1(it, r, pr, pm, plik->liczba_m, plik->odleglosc);
					timer->endTimer();
					cout << "Czas wykonania :" << timer->endTimer() << endl;
					gen->wyswietlSciezke(sciezka, plik->odleglosc, plik->liczba_m);
					gen->policzblad(sciezka, plik->odleglosc, plik->liczba_m, optimal);
				}

			}
			else if (text == "Nie" || text == "nie")
			{
				timer->startTimer();
				sciezka = gen->Algorytm1(it, r, pr, pm, plik->liczba_m, plik->odleglosc);
				timer->endTimer();
				cout << "Czas wykonania :" << timer->endTimer() << endl;
				gen->wyswietlSciezke(sciezka, plik->odleglosc, plik->liczba_m);

			}
			break;
		}
		case '3':
		{
			a = false;
			break;
		}

		}
	}
}

