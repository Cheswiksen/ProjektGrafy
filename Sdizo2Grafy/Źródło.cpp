#include <iostream>
#include "Graf.h"
using namespace std;

int main()
{
	Graf graf;
	string Name = "dane.txt";
	graf.openMatrix(Name);
	graf.showMatrix();
	graf.showList();
	graf.PrimMatrix();
	graf.PrimLista();
	graf.KruskalMatrix();
	graf.KruskalLista();
	system("pause");
	return 0x29a;
}