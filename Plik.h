#pragma once

#include <string>
#include <fstream>
#include <iostream>
#define M_PI 3.14159265358979323846

using namespace std;
static const double MAX = numeric_limits<double>::infinity();

class Plik
{
private:
	double** koordynaty = nullptr;
public:
	Plik();
	int liczba_m;
	double** odleglosc = nullptr;
	void atsp(string filename);
	void tsp(string filename);
	void wyswietl();
	void policEUC_2D();
	void policCEIL_2D();
	void policATT();
	void policGEO();
	~Plik();
};

