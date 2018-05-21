#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <list>
#include <iomanip>
#include <vector>
#include <stack>#include <ctime>#include <windows.h>
#pragma once

using namespace std;

class Graf
{
public:
	Graf();
	~Graf();
	int getSize();
	void setSize(int Size);
	void openMatrix(string Name);
	void init(); //inicjacja dopiero po dodaniu sizeN!
	void showMatrix();
	void showList();
	void PrimMatrix();
	void PrimLista();
	void KruskalMatrix();
	void KruskalLista();
	void DijkstraMatrix();
	void DijkstraLista();
	bool isCycle(list<int> Vert, int S);
	int find(int x);
	void unite(int x, int y);
	int minDistance(int dist[], bool sptSet[]);
	void randGraf(int percent, int size);
private:
	int **Tab;		//matrix oryginalny
	int **TabN;		//matrix nieskierowany
	list<pair <int, int>> *TabList;	//Tablica list Tablist[wierzcho쿮k].first-do k퉐, .second -waga
	list<pair <int, int>> *TabListN;//Tablica list Nieskierowana Tablist[wierzcho쿮k].first-do k퉐, .second -waga
	int sizeN;		//wielkosc macierzy
	int sizeE;		//liczba krawedzi
	int start;
	int end;
	int *Fathers;
	bool * BeenThere;
};

