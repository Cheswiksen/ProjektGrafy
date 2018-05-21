#include "Graf.h"


Graf::Graf()
{
	sizeN = 0;
	start = 0;
	end = 0;
}


Graf::~Graf()
{
	for (int i = 0; i<sizeN; i++)
		delete[] Tab[i];
	delete[] Tab;

	for (int i = 0; i<sizeN; i++)
		delete[] TabN[i];
	delete[] TabN;

	delete[] TabList;
	delete[] TabListN;
	delete[] Fathers;
}

int Graf::getSize()
{
	return sizeN;
}

void Graf::setSize(int Size)
{
	sizeN = Size;
}

void Graf::openMatrix(string Name)
{
	int from, to, weight;
	int temp;
	ifstream file(Name, ios::in);
	if (!file.is_open())
	{
		return;
	}
	file >> temp;
	this->sizeN = temp;
	file >> temp;
	this->sizeE = temp;
	file >> temp;
	this->start = temp;
	file >> temp;
	this->end = temp;
	this->init();

	for (int j = 0; j < this->sizeE; j++)
	{
		file >> temp;
		from = temp;
		file >> temp;
		to = temp;
		file >> temp;
		weight = temp;
		this->Tab[from][to] = weight;
		this->TabN[from][to] = weight;
		this->TabN[to][from] = weight;
		this->TabList[from].push_back(make_pair(to, weight));
		this->TabListN[from].push_back(make_pair(to, weight));
		this->TabListN[to].push_back(make_pair(from, weight));
	}
	file.close();
}

void Graf::init()
{
	this->Tab = new int *[this->sizeN];
	for (int i = 0; i<this->sizeN; i++)
		Tab[i] = new int[sizeN];
	for (int i = 0; i < this->sizeN; i++)
		for (int j = 0; j < this->sizeN; j++)
			Tab[i][j] = -1;

	this->TabN = new int *[this->sizeN];
	for (int i = 0; i<this->sizeN; i++)
		TabN[i] = new int[sizeN];
	for (int i = 0; i < this->sizeN; i++)
		for (int j = 0; j < this->sizeN; j++)
			TabN[i][j] = -1;

	this->TabList = new list<pair<int, int>>[sizeN];
	this->TabListN = new list<pair<int, int>>[sizeN];
	this->Fathers = new int[sizeN];
	for (int i = 0; i < sizeN; i++)
		Fathers[i] = i;
}

void Graf::showMatrix()
{
	cout << endl << "Graf oryginalny:\n";
	for (int i = 0; i < this->sizeN; i++)
	{
		for (int j = 0; j < this->sizeN; j++)
		{
			cout << std::setw(5) << Tab[i][j]<<" ";
		}
		cout << endl;
	}
	/*cout << "\nGraf nieskierowany:\n";
	for (int i = 0; i < this->sizeN; i++)
	{
		for (int j = 0; j < this->sizeN; j++)
		{
			cout << std::setw(5) << TabN[i][j] << " ";
		}
		cout << endl;
	}*/
}

void Graf::showList()
{
	cout << endl << "Lista sasiedztwa" << endl;
	for (int i = 0; i < sizeN; i++)
	{
		cout << i << " ";
		for (list<pair <int, int>>::iterator it = this->TabList[i].begin(); it != this->TabList[i].end(); ++it)
			cout << ' ' << std::setw(5) << it->first;
		cout << endl;
	}
}

void Graf::PrimMatrix()
{
	list<int> Vert;
	pair<pair<int, int>, int> Min;
	Min.second = INT_MAX;
	list<pair<pair<int, int>, int>> Tree; //<from, to> waight
	for (int i = 0; i < sizeN; i++)
	{
		if (TabN[start][i] < Min.second && TabN[start][i] != (-1))
		{
			Min.first.first = start;
			Min.first.second = i;
			Min.second = TabN[start][i];
		}
	}
	Vert.push_back(Min.first.first);
	Vert.push_back(Min.first.second);
	//Tree.push_back(make_pair(make_pair(Min.first.first, Min.first.second), Min.second));
	Tree.push_back(Min);
	for (int i = 0; i < sizeN - 2; i++)
	{
		Min.second = INT_MAX;
		for (list<int>::iterator it = Vert.begin(); it != Vert.end(); ++it)
		{
			for (int j = 0; j < sizeN; j++)
			{
				if (TabN[*it][j] < Min.second && TabN[*it][j] != (-1) && !isCycle(Vert, j))
				{
					Min.first.first = *it;
					Min.first.second = j;
					Min.second = TabN[*it][j];
				}
			}
		}
		Vert.push_back(Min.first.second);
		//Tree.push_back(make_pair(make_pair(Min.first.first, Min.first.second), Min.second));
		Tree.push_back(Min);
	}
	/*cout << endl << "Prim Macierz: " << endl;
	int Suma = 0;
	for (list<pair<pair<int, int>, int>>::iterator it = Tree.begin(); it != Tree.end(); ++it)
	{
		cout << endl << "(" << it->first.first << " " << it->first.second << ") " << it->second;
		Suma += it->second;
	}

	cout << endl << "MST= " << Suma << endl;*/
}

void Graf::PrimLista()
{
	list<int> Vert;
	pair<pair<int, int>, int> Min; //<from, to> waight
	Min.second = INT_MAX;
	list<pair<pair<int, int>, int>> Tree; //<from, to> waight
	for (list<pair <int, int>>::iterator it = TabListN[0].begin(); it != TabListN[0].end(); ++it)
	{
		if (it->second < Min.second)
		{
			Min.first.first = 0;			//skad
			Min.first.second = it->first;	//dokad
			Min.second = it->second;		//waga
		}
	}
	Vert.push_back(Min.first.first);
	Vert.push_back(Min.first.second);
	Tree.push_back(Min);
	for (int i = 1; i < sizeN - 1; i++)
	{
		Min.second = INT_MAX;
		for (list<int>::iterator it = Vert.begin(); it != Vert.end(); ++it)
		{
			for (list<pair <int, int>>::iterator it2 = this->TabListN[*it].begin(); it2 != this->TabListN[*it].end(); ++it2)
			{
				if (it2->second < Min.second && !isCycle(Vert, it2->first))
				{
					Min.first.first = *it;			//skad
					Min.first.second = it2->first;	//dokad
					Min.second = it2->second;		//waga
				}
			}
		}
		Vert.push_back(Min.first.second);
		Tree.push_back(Min);
	}
	/*cout << endl << "Prim Lista: " << endl;
	int Suma = 0;
	for (list<pair<pair<int, int>, int>>::iterator it = Tree.begin(); it != Tree.end(); ++it)
	{
		cout << endl << "(" << it->first.first << " " << it->first.second << ") " << it->second;
		Suma += it->second;
	}
	cout << endl << "MST= " << Suma << endl;*/
}

void Graf::KruskalMatrix()
{
	for (int i = 0; i < sizeN; i++)
		Fathers[i] = i;
	list<pair<pair<int, int>, int>> Listed; //<<z, do> waga>
	list<pair<pair<int, int>, int>> Tree;
	for (int i = 0; i < sizeN; i++)
		for (int j = 0; j < sizeN; j++)
		{
			if (Tab[i][j] != (-1))
			{
				Listed.push_back(make_pair(make_pair(i, j), Tab[i][j]));
			}			
		}
	Listed.sort([](const pair<pair<int, int>, int>& A, const pair<pair<int, int>, int>& B) { return A.second < B.second; });
	cout << endl;
	for (list<pair<pair<int, int>, int>>::iterator it = Listed.begin(); it != Listed.end(); ++it)
	{
		if (find(it->first.first) != find(it->first.second))
		{
			Tree.push_back(make_pair(make_pair(it->first.first, it->first.second),it->second));
			unite(it->first.first, it->first.second);
		}
	}
	int Suma = 0;
	//cout << endl << "Kruskal Macierz:" << endl;
	//for (list<pair<pair<int, int>, int>>::iterator it = Tree.begin(); it != Tree.end(); ++it)
	//{
	//	cout << "(" << it->first.first << " " << it->first.second << ")" << "  " << it->second << endl;
	//	Suma += it->second;
	//}
	//cout << "MST= " << Suma << endl;
}

void Graf::KruskalLista()
{
	for (int i = 0; i < sizeN; i++)
		Fathers[i] = i;
	list<pair<pair<int, int>, int>> Listed; //<<z, do> waga>
	list<pair<pair<int, int>, int>> Tree;
	for (int i = 0; i < sizeN; i++)
	{
		for (list<pair <int, int>>::iterator it = TabList[i].begin(); it != TabList[i].end(); ++it)
		{
			Listed.push_back(make_pair(make_pair(i, it->first), it->second));
		}
	}
	Listed.sort([](const pair<pair<int, int>, int>& A, const pair<pair<int, int>, int>& B) { return A.second < B.second; });
	cout << endl;
	for (list<pair<pair<int, int>, int>>::iterator it = Listed.begin(); it != Listed.end(); ++it)
	{
		if (find(it->first.first) != find(it->first.second))
		{
			Tree.push_back(make_pair(make_pair(it->first.first, it->first.second), it->second));
			unite(it->first.first, it->first.second);
		}
	}
	/*int Suma = 0;
	cout << endl << "Kruskal Lista:" << endl;
	for (list<pair<pair<int, int>, int>>::iterator it = Tree.begin(); it != Tree.end(); ++it)
	{
		cout << "(" << it->first.first << " " << it->first.second << ")" << "  " << it->second << endl;
		Suma += it->second;
	}
	cout << "MST= " << Suma << endl;*/
}

void Graf::DijkstraMatrix()
{
	int *Path;
	Path = new int[sizeN];
	int *koszt;
	koszt = new int[sizeN];
	bool *sptSet;
	sptSet = new bool[sizeN];
	for (int i = 0; i < sizeN; i++)
		koszt[i] = INT_MAX, sptSet[i] = false;
	koszt[start] = 0;
	for (int count = 0; count < sizeN - 1; count++)
	{
		int u = minDistance(koszt, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < sizeN; v++)
			if (!sptSet[v] && Tab[u][v] != (-1) && koszt[u] != INT_MAX && (koszt[u] + Tab[u][v]) < koszt[v])
			{
				koszt[v] = koszt[u] + Tab[u][v];
				Path[v] = u;
			}

	}
	//wyswietlanie
	/*cout << endl << "Dijkstra Matrix:" << endl << "wierzcholek | koszt" << endl;
	for (int i = 0; i < sizeN; i++)
		cout << setw(3) << i << "|" << setw(3) << koszt[i] << endl;
	cout << "drogi:" << endl;
	Path[start] = 0;
	int K;
	for (int i = 0; i < sizeN; i++)
	{
		cout << setw(3) << i << "|" << std::setw(3) << Path[i];
		K = Path[i];
		while (1)
		{
			if (K != start)
			{
				cout << std::setw(3) << Path[K];
				K = Path[K];
			}
			else
			{
				break;
			}
		}
		cout << endl;
	}*/
}

void Graf::DijkstraLista()
{
	int *Path, u;
	Path = new int[sizeN];
	int *koszt;
	koszt = new int[sizeN];
	bool *sptSet;
	sptSet = new bool[sizeN];
	for (int i = 0; i < sizeN; i++)
		koszt[i] = INT_MAX, sptSet[i] = false;
	koszt[start] = 0;
	for (int count = 0; count < sizeN - 1; count++)
	{
		u = minDistance(koszt, sptSet);
		sptSet[u] = true;		
		for (list<pair <int, int>>::iterator it = TabList[u].begin(); it != TabList[u].end(); ++it)
		{
			if (!sptSet[it->first] && koszt[u] != INT_MAX && (koszt[u] + it->second) < koszt[it->first])
			{
				koszt[it->first] = koszt[u] + it->second;
				Path[it->first] = u;
			}				
		}
	}
	/*cout << endl << "Dijkstra Lista:" << endl << "wierzcholek | koszt" << endl;
	for (int i = 0; i < sizeN; i++)
		cout << setw(3) << i << "|" << setw(3) << koszt[i] << endl;
	cout << "drogi:" << endl;
	Path[start] = 0;
	int K;
	for (int i = 0; i < sizeN; i++)
	{
		cout << setw(3) << i << "|" << std::setw(3) << Path[i];
		K = Path[i];
		while (1)
		{
			if (K != start)
			{
				cout << std::setw(3) << Path[K];
				K = Path[K];
			}
			else
			{
				break;
			}
		}
		cout << endl;
	}*/
}

bool Graf::isCycle(list<int> Vert, int S)
{
	for (list<int>::iterator it = Vert.begin(); it != Vert.end(); ++it)
	{
		if (*it == S)
		{
			return true;
		}
	}
	return false;
}

int Graf::find(int x)
{
	if (Fathers[x] == x)
	{
		return x;
	}
	return find(Fathers[x]);
}

void Graf::unite(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	Fathers[fx] = fy;
}

int Graf::minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < sizeN; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;	
}

void Graf::randGraf(int percent, int size)
{
	start = 0;
	end = 2;
	sizeE = 0;
	sizeN = size;
	init();
	float edgesRatio = (float)percent / 100;
	int maxEdges = edgesRatio * ((sizeN*(sizeN - 1)) / 2);
	int edgesNumber = 0;
	int randomWeight = rand() % 21 + 1;
	int randomEdge1 = rand() % sizeN;
	int randomEdge2 = rand() % sizeN;
	// Algorytm Gawla-Kaluzy
	srand(time(NULL));
	for (int i = 0; i < sizeN; i++)
	{
		// Tworzenie spojnego szkieletu o duzych wagach
		randomWeight = (rand() % 21 + 1) + 90;
		//Tab[i][(i + 1) % sizeN] = randomWeight;
		randomEdge1 = i;
		randomEdge2 = (i + 1) % sizeN;
		if (Tab[randomEdge2][randomEdge1] != (-1) || Tab[randomEdge1][randomEdge2] != (-1))
		{
			i--;
			continue;
		}
		edgesNumber++;
		sizeE++;
		this->Tab[randomEdge1][randomEdge2] = randomWeight;
		this->TabN[randomEdge1][randomEdge2] = randomWeight;
		this->TabN[randomEdge2][randomEdge1] = randomWeight;
		this->TabList[randomEdge1].push_back(make_pair(randomEdge2, randomWeight));
		this->TabListN[randomEdge1].push_back(make_pair(randomEdge2, randomWeight));
		this->TabListN[randomEdge2].push_back(make_pair(randomEdge1, randomWeight));
	}

	while (edgesNumber < maxEdges)
	{
		// Pozostale krawedzie o malych wagach (10 +/-10) sa tworzone losowo
		randomWeight = rand() % 21 + 1;
		randomEdge1 = rand() % sizeN;
		randomEdge2 = rand() % sizeN;
		if (randomEdge1 == randomEdge2)
			// Jezeli wylosowano dwa razy ten sam wierzcholek, zamiast losowac od nowa...
			// ...drugi zwiekszamy o dwa - nie o jeden, bo takie krawedzie juz mamy...
			// ...dzieki temu powinnismy zaoszczedzic troche czasu
			randomEdge2 = (randomEdge2 + 2) % sizeN;

		

		if (Tab[randomEdge2][randomEdge1] != (-1) || Tab[randomEdge1][randomEdge2] != (-1))
		{
			continue;
		}
		this->Tab[randomEdge1][randomEdge2] = randomWeight;
		this->TabN[randomEdge1][randomEdge2] = randomWeight;
		this->TabN[randomEdge2][randomEdge1] = randomWeight;
		this->TabList[randomEdge1].push_back(make_pair(randomEdge2, randomWeight));
		this->TabListN[randomEdge1].push_back(make_pair(randomEdge2, randomWeight));
		this->TabListN[randomEdge2].push_back(make_pair(randomEdge1, randomWeight));
		edgesNumber++;
		sizeE++;


	}
}
