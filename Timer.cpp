#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Timer::Timer(void)
{
}


Timer::~Timer(void)
{
}
void Timer::startTimer()
{
	QueryPerformanceFrequency(&clockFrequency);
	QueryPerformanceCounter(&start);
}
double Timer::endTimer()
{
	QueryPerformanceCounter(&finish);
	delta.QuadPart = finish.QuadPart - start.QuadPart;
	return ((double)delta.QuadPart) / clockFrequency.QuadPart;
}
