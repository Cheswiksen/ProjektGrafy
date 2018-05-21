#include "Graf.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
int main()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = read_QPC();
	elapsed = read_QPC() - start;
	cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	Graf graf;
	string Name = "dane.txt";
	//graf.openMatrix(Name);
	graf.randGraf(99, 100);
	start = read_QPC();
	graf.KruskalMatrix();
	elapsed = read_QPC() - start;
	cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	//graf.showMatrix();
	//graf.showList();
	//graf.PrimMatrix();
	//graf.PrimLista();
	//graf.KruskalMatrix();
	//graf.KruskalLista();
	//graf.DijkstraMatrix();
	//graf.DijkstraLista();
	system("pause");
	return 0x29a;
}