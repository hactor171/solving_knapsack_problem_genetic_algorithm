#pragma once
#include<iostream>
#include"Plik.h"
#include <vector>
#include <time.h>
#include "Timer.h" 

using namespace std;

class genetyczny
{

public:

	genetyczny();

	void sortowanie(vector<vector<int>>&, vector<double>&, int, int);

	vector<int> Algorytm1(int, int, double,double, int, double **);

	double policzDlugoscS(vector<int>, double**, int);

	vector<int> znajdzOpt(int , double ** ) ;
	void wyswietlSciezke(vector<int>, double**, int);
	void policzblad(vector<int>, double**, int, int);
	bool elem_vector(vector<int> arr, int arrayLength, int elem);

	~genetyczny();
};

