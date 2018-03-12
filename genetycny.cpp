#include "genetyczny.h"



genetyczny::genetyczny()// konstruktor
{
	
	srand(time(NULL));
}
genetyczny::~genetyczny()// destruktor
{
}

void genetyczny::sortowanie(vector<vector<int>> &dane, vector<double> &dlugosc_dane, int left, int right)
{
	int i = left;
	int j = right;
	double x = dlugosc_dane[(left + right) / 2];
	do {
		while (dlugosc_dane[i] < x)
			i++;

		while (dlugosc_dane[j] > x)
			j--;

		if (i <= j) {

			vector<int> tempVec;
			double tempDist;
			tempVec = dane[i]; 
			dane[i] = dane[j]; 
			dane[j] = tempVec; 
			tempDist = dlugosc_dane[i];
			dlugosc_dane[i] = dlugosc_dane[j];
			dlugosc_dane[j] = tempDist;

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) sortowanie(dane, dlugosc_dane, left, j);

	if (right > i) sortowanie(dane, dlugosc_dane, i, right);

}

bool genetyczny::elem_vector(vector<int> arr, int arrayLength, int elem) {
	for (int i = 0; i < arrayLength; i++) {
		if (elem == arr[i])
			return 1;
	}
	return 0;
}


vector<int> genetyczny::Algorytm1(int ilosc_i, int ilosc_pop1, double pr1, double pm1, int liczba_m1, double**odleglosc1)
{
	vector <vector<int>> populacja;
	vector<double> dlugosci;
	int ilosc_iter = ilosc_i;
	int ilosc_pop = ilosc_pop1;
	double pr = pr1;
	double pm = pm1;
	vector<int> najlepsza_sciezka;
	int p1, p2;
	for (int i = 0; i < ilosc_pop; i++)
	{
		vector<int> szukana_sciezka = znajdzOpt(liczba_m1, odleglosc1);
		//wyswietlSciezke(szukana_sciezka, odleglosc1, liczba_m1);
		double dlugosc_sciezka = policzDlugoscS(szukana_sciezka, odleglosc1, liczba_m1);
		populacja.push_back(szukana_sciezka);
		dlugosci.push_back(dlugosc_sciezka);
	}

	for (int a = 0; a < ilosc_iter; a++)
	{
		///////////////////////////////////////
		////Selekcja 
		///////////////////////////////////////
		vector<vector<int>> nowa_populacja;
		vector<double>		nowe_dlugosci;

		sortowanie(populacja, dlugosci, 0, dlugosci.size() - 1);

		int rozmiar_pop = dlugosci.size();
		//Liczymy sumę wartości funkcji celu
		int f_sum = rozmiar_pop * (rozmiar_pop + 1) / 2; 

		for (int i = 0; i < rozmiar_pop; i++)
		{
			//Liczymy wkład każdego osobnika w sumę
			double wklad = i / f_sum; 
			if (((double)rand() / RAND_MAX) > wklad)  
			{
				nowa_populacja.push_back(populacja[i]);
				nowe_dlugosci.push_back(dlugosci[i]);
			}
		}

		populacja = nowa_populacja;
		dlugosci = nowe_dlugosci;

		///////////////////////////////////////
		////Koniec Selekcji
		///////////////////////////////////////

		int rozmiar_pop1 = dlugosci.size();

		for (int j = 0; j < rozmiar_pop1 / 2; j++)
		{

			///////////////////////////////////////
			////Krzyżowanie
			///////////////////////////////////////
			if (((double)rand() / RAND_MAX) < pr)
			{
				p1 = rand() % rozmiar_pop1;
				p2 = rand() % rozmiar_pop1;
				while (p1 == p2)
				{
					p2 = rand() % rozmiar_pop1;
				}
				int przedzial = populacja[p1].size() - 1;
				int punkt1 = (rand() % przedzial);
				int punkt2 = punkt1 + 1 + (rand() % (przedzial - punkt1));
				vector<int> potomek1(populacja[p1].size());

				int dlugo_poz = punkt2 - punkt1;

				for (int i = punkt1; i < punkt2; i++)
				{
					potomek1[i] = populacja[p2][i];
				}

				vector<int> Sciezka_pom(dlugo_poz);
				for (int i = 0; i < dlugo_poz; i++)
				{
					Sciezka_pom[i] = populacja[p2][punkt1 + i];
				}

				int i = punkt2, j = punkt2, count = 0;
				while (count < populacja[p1].size()) {
					j = j % populacja[p1].size();
					i = i % populacja[p1].size();
					if (!elem_vector(Sciezka_pom, dlugo_poz, populacja[p1][i])) {
						potomek1[j] = populacja[p1][i];
						j++;
					}
					i++;
					count++;
				}

				///////////////////////////////////////
				////Mutacja
				///////////////////////////////////////
				if (((double)rand() / RAND_MAX) < pm)
				{
					int Point1 = rand() % (potomek1.size() - 1); 
					int Point2 = Point1 + 1 + (rand() % (potomek1.size() - 1 - Point1)); 
					int dlugosc = Point2 - Point1;

					for (int i = 0; i <= dlugosc; i++)
					{
						int Temp = potomek1[Point1 + i]; // temp = a
						potomek1[Point1 + i] = potomek1[Point2 - i]; // a = c
						potomek1[Point2 - i] = Temp; // c = temp ( = a)
					}
				}
				///////////////////////////////////////
				////Koniec mutacji
				///////////////////////////////////////

				populacja.push_back(potomek1);
				double p1_dlugosc = policzDlugoscS(potomek1, odleglosc1, liczba_m1);
				dlugosci.push_back(p1_dlugosc);
			}
			///////////////////////////////////////
			////Koniec krzyżwania
			///////////////////////////////////////
		
		}

		sortowanie(populacja, dlugosci, 0, dlugosci.size() - 1);

		if (dlugosci.size() > ilosc_pop1)
		{
			populacja.resize(ilosc_pop1);
			dlugosci.resize(ilosc_pop1);
		}
	
}

    najlepsza_sciezka = populacja[0];

	return najlepsza_sciezka;


}


vector<int> genetyczny::znajdzOpt(int liczba_m, double** odleglosc)  // funkcja ktora znajduje optymalne rozwiazanie z losowego wieszchowka
{
	int pocz_wieszch = (rand() % liczba_m) + 0;
	int nastepny_ind = 0;
	
	vector<bool> odwiedzone(liczba_m);
	for (int i = 0; i < liczba_m; i++)
	{
		odwiedzone[i] = false;
	}

	vector<int> sciezka(liczba_m);
	odwiedzone[pocz_wieszch] = true;
	sciezka[0] = pocz_wieszch;
	for (int j = 1; j < liczba_m; j++)
	{
	    int k = (rand() % liczba_m) + 0;
		while (odwiedzone[k] == true)
		{
			k = (rand() % liczba_m) + 0;
		}
		
		nastepny_ind = k;
	    odwiedzone[nastepny_ind] = true;
		sciezka[j] = nastepny_ind;
	}
	return sciezka;
	
}


double genetyczny::policzDlugoscS(vector<int> sciezka, double **odleglosc, int liczba_m)  // funkcja jaka liczy dlugosc sciezki 
{
	double dlugosc = 0;
	for (int i = 1; i < liczba_m; i++)
		dlugosc = dlugosc + odleglosc[sciezka[i - 1]][sciezka[i]];
	dlugosc = dlugosc + odleglosc[sciezka[liczba_m - 1]][sciezka[0]];
	return dlugosc; // zwracamy poprawna dlugosc
}

void genetyczny::policzblad(vector<int> sciezka, double** odleglosc, int liczba_m, int dobryW)// funkcja licznia bladu, dobry wynik musi byc podany z konsoli 
{
	cout << "Blad wynosi: " << (policzDlugoscS(sciezka, odleglosc, liczba_m) - dobryW) * 100 / dobryW << " %" << endl;
}

void genetyczny::wyswietlSciezke(vector<int> sciezka, double** odleglosc, int liczba_m)  // funkcja wyswietlenia sciezki
{
	for (int i = 0; i < liczba_m; i++)
	{
		cout << sciezka[i] << " -> ";
	}
	cout << sciezka[0] << endl;
	cout << "Dlugosc sciezki: " << policzDlugoscS(sciezka, odleglosc, liczba_m) << endl;
}

