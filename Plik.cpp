#include "Plik.h"

using namespace std;

Plik::Plik()
{
}


Plik::~Plik()
{
}

void Plik::atsp(string filename)// wczytanie pliku formatu atsp
{
	ifstream fin;
	fin.open(filename, ios::in);
	string text = "";
	while (text != "DIMENSION:")
		fin >> text;
	fin >> liczba_m;

	while (text != "EDGE_WEIGHT_TYPE:")
		fin >> text;
	fin >> text;
	if (text == "EXPLICIT")
	{
		while (text != "EDGE_WEIGHT_FORMAT:")
			fin >> text;
		fin >> text;
		if (text == "FULL_MATRIX")
		{
			while (text != "EDGE_WEIGHT_SECTION")
				fin >> text;
			odleglosc = new double*[liczba_m];
			for (int i = 0; i < liczba_m; i++)
			{
				odleglosc[i] = new double[liczba_m];
			}
			for (int i = 0; i < liczba_m; i++)
			{
				for (int j = 0; j < liczba_m; j++)
				{
					fin >> odleglosc[i][j];
					if (i == j)
					{
						odleglosc[i][j] = MAX;
					}
				}
			}
		}
	}
	fin.close();

	wyswietl();
}
void Plik::tsp(string filename) // wczytanie pliku formatu tsp
{
	ifstream fin;
	string input;
	fin.open(filename, ios::in);
	while (input != "DIMENSION:")
		fin >> input;
	fin >> liczba_m;
	koordynaty = new double*[liczba_m];
	while (input != "EDGE_WEIGHT_TYPE:")
		fin >> input;
	fin >> input;
	if (input == "EXPLICIT")
	{
		while (input != "EDGE_WEIGHT_FORMAT:")
			fin >> input;
		fin >> input;
		if (input == "FULL_MATRIX")
		{
			while (input != "EDGE_WEIGHT_SECTION")
				fin >> input;
			odleglosc = new double*[liczba_m];
			for (int i = 0; i < liczba_m; i++)
			{
				odleglosc[i] = new double[liczba_m];
			}
			for (int i = 0; i < liczba_m; i++)
			{
				for (int j = 0; j < liczba_m; j++)
				{
					fin >> odleglosc[i][j];
					if (i == j)
					{
						odleglosc[i][j] = MAX;
					}
				}
			}

			fin.close();
			//wyswietl();
		}
		else if (input == "LOWER_DIAG_ROW")
		{
			while (input != "EDGE_WEIGHT_SECTION")
				fin >> input;
			odleglosc = new double*[liczba_m];
			for (int i = 0; i < liczba_m; i++)
			{
				odleglosc[i] = new double[liczba_m];
			}
			for (int i = 0; i < liczba_m; i++)
			{
				for (int j = 0; j <= i; j++)
				{
					fin >> odleglosc[i][j];
					odleglosc[j][i] = odleglosc[i][j];
					if (i == j)
					{
						odleglosc[i][j] = MAX;
					}
				}
			}

			fin.close();
			//wyswietl();
		}
		else if (input == "UPPER_ROW")
		{
			while (input != "EDGE_WEIGHT_SECTION")
				fin >> input;
			odleglosc = new double*[liczba_m];
			for (int i = 0; i < liczba_m; i++)
			{
				odleglosc[i] = new double[liczba_m];
			}
			for (int i = 0; i < liczba_m; i++)
			{
				for (int j = i + 1; j < liczba_m; j++)
				{
					fin >> odleglosc[i][j];
					odleglosc[j][i] = odleglosc[i][j];
					if (i == j)
					{
						odleglosc[i][j] = MAX;
					}
				}
				odleglosc[i][i] = 0;
			}
			fin.close();
			//wyswietl();
		}
		else if (input == "UPPER_DIAG_ROW")
		{
			while (input != "EDGE_WEIGHT_SECTION")
				fin >> input;
			odleglosc = new double*[liczba_m];
			for (int i = 0; i < liczba_m; i++)
			{
				odleglosc[i] = new double[liczba_m];
			}
			for (int i = 0; i < liczba_m; i++)
			{
				for (int j = i; j < liczba_m; j++)
				{
					fin >> odleglosc[i][j];
					odleglosc[j][i] = odleglosc[i][j];
					if (i == j)
					{
						odleglosc[i][j] = MAX;
					}
				}
			}
			fin.close();
			//wyswietl();
		}
	}
	if (input == "EUC_2D")
	{
		while (input != "NODE_COORD_SECTION")
			fin >> input;

		for (int i = 0; i < liczba_m; i++)
		{
			koordynaty[i] = new double[2];
			fin >> input;
			fin >> koordynaty[i][0];
			fin >> koordynaty[i][1];
		}
		fin.close();
		for (int i = 0; i < liczba_m; i++)
		{
			cout << "[" << i << "] " << koordynaty[i][0] << " " << koordynaty[i][1] << endl;
		}

		policEUC_2D();
		//wyswietl();
	}
	else if (input == "CEIL_2D")
	{
		while (input != "NODE_COORD_SECTION")
			fin >> input;

		for (int i = 0; i < liczba_m; i++)
		{
			koordynaty[i] = new double[2];
			fin >> input;
			fin >> koordynaty[i][0];
			fin >> koordynaty[i][1];
		}
		fin.close();
		for (int i = 0; i < liczba_m; i++)
		{
			cout << "[" << i << "] " << koordynaty[i][0] << " " << koordynaty[i][1] << endl;
		}

		policCEIL_2D();
		//wyswietl();
	}
	else if (input == "GEO")
	{
		while (input != "NODE_COORD_SECTION")
			fin >> input;

		for (int i = 0; i < liczba_m; i++)
		{
			koordynaty[i] = new double[2];
			fin >> input;
			fin >> koordynaty[i][0];
			fin >> koordynaty[i][1];
		}
		fin.close();
		for (int i = 0; i < liczba_m; i++)
		{
			cout << "[" << i << "] " << koordynaty[i][0] << " " << koordynaty[i][1] << endl;
		}
		policGEO();
		//wyswietl();
	}
	else if (input == "ATT")
	{
		while (input != "NODE_COORD_SECTION")
			fin >> input;

		for (int i = 0; i < liczba_m; i++)
		{
			koordynaty[i] = new double[2];
			fin >> input;
			fin >> koordynaty[i][0];
			fin >> koordynaty[i][1];
		}
		fin.close();
		for (int i = 0; i < liczba_m; i++)
		{
			cout << "[" << i << "] " << koordynaty[i][0] << " " << koordynaty[i][1] << endl;
		}
		policATT();
		//wyswietl();
	}
}

void Plik::policEUC_2D()
{
	odleglosc = new double*[liczba_m];
	for (int i = 0; i < liczba_m; i++)
	{
		odleglosc[i] = new double[liczba_m];
	}
	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			if (i != j)
				odleglosc[i][j] = sqrt(pow(koordynaty[i][0] - koordynaty[j][0], 2) + pow(koordynaty[i][1] - koordynaty[j][1], 2) + 0.5);
			else
				odleglosc[i][j] = MAX;
		}
	}
}
void Plik::policCEIL_2D()
{
	odleglosc = new double*[liczba_m];
	for (int i = 0; i < liczba_m; i++)
	{
		odleglosc[i] = new double[liczba_m];
	}
	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			if (i != j)
				odleglosc[i][j] = ceil(sqrt(pow(koordynaty[i][0] - koordynaty[j][0], 2) + pow(koordynaty[i][1] - koordynaty[j][1], 2) + 0.5));
			else
				odleglosc[i][j] = MAX;
		}
	}
}
void Plik::policGEO()
{
	int deg;
	float *lat, *lon, min, q1, q2, q3;
	static double RRR = 6378.388;
	lat = (float*)malloc(liczba_m * sizeof(float));
	lon = (float*)malloc(liczba_m * sizeof(float));
	odleglosc = new double*[liczba_m];
	for (int i = 0; i < liczba_m; i++)
	{
		odleglosc[i] = new double[liczba_m];
	}
	for (int i = 0; i < liczba_m; i++)
	{
		deg = (int)koordynaty[i][0];
		min = koordynaty[i][0] - deg;
		lat[i] = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

		deg = (int)koordynaty[i][1];
		min = koordynaty[i][1] - deg;
		lon[i] = M_PI * (deg + 5.0 * min / 3.0) / 180.0;
	}
	for (int i = 0; i < liczba_m; ++i)
	{
		for (int j = 0; j < liczba_m; ++j)
		{
			q1 = cos(lon[i] - lon[j]);
			q2 = cos(lat[i] - lat[j]);
			q3 = cos(lat[i] + lat[j]);
			if (i != j)
				odleglosc[i][j] = (int)RRR * acos(0.5*((1.0 + q1)*q2 - (1.0 - q1)*q3)) + 1.0;
			else
				odleglosc[i][j] = MAX;

		}

	}
}
void Plik::policATT()
{
	float xd, yd, rij;
	int tij;
	odleglosc = new double*[liczba_m];
	for (int i = 0; i < liczba_m; i++)
	{
		odleglosc[i] = new double[liczba_m];
	}

	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			xd = koordynaty[i][0] - koordynaty[j][0];
			yd = koordynaty[i][1] - koordynaty[j][1];

			rij = sqrt((xd*xd + yd*yd) / 10.0);
			tij = (int)rij;
			if (i != j)
				odleglosc[i][j] = (tij < rij) ? tij + 1 : tij;
			else
				odleglosc[i][j] = MAX;
		}
	}

}

void Plik::wyswietl()
{
	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			cout << odleglosc[i][j] << " ";
		}
		cout << endl;
	}
}