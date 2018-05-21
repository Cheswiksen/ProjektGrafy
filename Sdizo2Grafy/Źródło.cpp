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
	//start = read_QPC();
	//elapsed = read_QPC() - start;
	//cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	//Graf graf;
	//string Name = "dane.txt";
	////graf.openMatrix(Name);
	//graf.randGraf(99, 100);
	//start = read_QPC();
	//graf.KruskalMatrix();
	//elapsed = read_QPC() - start;
	//cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	////graf.showMatrix();
	////graf.showList();
	////graf.PrimMatrix();
	////graf.PrimLista();
	////graf.KruskalMatrix();
	////graf.KruskalLista();
	////graf.DijkstraMatrix();
	////graf.DijkstraLista();
	Graf manu;
	int answer = 0;
	string nazwa;
	
	do {
		cout << "\n\n\n1. Wczytaj z pliku\n2. Generuj graf\n3. Wyswietl\n4. Prim lista\n5. Prim macierz\n6. Kruskal lista\n7. Kruskal macierz\n8. Dijkstra lista\n9. Dijkstra macierz\n10. Wyjscie\n\n";
		cin >> answer;
		switch (answer)
		{
		case 1:
			cout << "podaj nazwe pliku:";
			cin >> nazwa;
			manu.openMatrix(nazwa);
			system("cls");
			break;
		case 2:
			int a, b;
			cout << "podaj gestosc:";
			cin >> a;
			cout << "podaj ilosc wierzcholkow:";
			cin >> b;
			manu.randGraf(a, b);
			system("cls");
			break;
		case 3:
			manu.showMatrix();
			manu.showList();
			break;
		case 4:
			start = read_QPC();
			manu.PrimLista();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;
		case 5:
			start = read_QPC();
			manu.PrimMatrix();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;
		case 6:
			start = read_QPC();
			manu.KruskalLista();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;
		case 7:
			start = read_QPC();
			manu.KruskalMatrix();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;		
		case 8:
			start = read_QPC();
			manu.DijkstraLista();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;
		case 9:
			start = read_QPC();
			manu.DijkstraMatrix();
			elapsed = read_QPC() - start;
			cout << "\nTime [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			break;
		case 10:
			return 997;
			break;
		default:
			break;
		}
	} while (answer != 10);
	system("pause");
	return 0x29a;
}