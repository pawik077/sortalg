#include "tabgen.hh"

template<class T>
void fillTable(T* tab, int n) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<T> dist(0, 4000000);
	for (int i = 0; i < n; ++i) tab[i] = dist(gen);
}

template<class T>
bool isSorted(T* tab, int n) {
	for (int i = 0; i < n - 1; ++i) 
		if (tab[i] > tab[i + 1]) return 0;
	return 1;
}

template<class T>
bool isReversed(T* tab, int n) {
	for (int i = 0; i < n - 1; ++i)
		if (tab[i] < tab[i + 1]) return 0;
	return 1;
}

template void fillTable<int>(int*, int);
template bool isSorted<int>(int*, int);
template bool isReversed<int>(int*, int);