#include "sorts.hh"

template<class T>
int partition(T* tab, int left, int right) {
	int pivot = tab[(left + right) / 2], i = left, j = right;
	while (true) {
		while (tab[j] > pivot) --j;
	  while (tab[i] < pivot) ++i;
	  if (i < j)  std::swap(tab[i++], tab[j--]);
    else return j;
    }
}

template<class T>
void quickSort(T* tab, int left, int right) {
	if (left < right) {
		int pi = partition(tab, left, right);
		quickSort(tab, left, pi);
		quickSort(tab, pi + 1, right);
	}
}

template<class T>
void merge(T* tab, int left, int middle, int right) {
	int i, j, k;
	int m = middle - left + 1;
	int n = right - middle;
	int* Left = new int[m];
	int* Right = new int[n];
	for (i = 0; i < m; ++i)
		Left[i] = tab[left + i];
	for (j = 0; j < n; ++j)
		Right[j] = tab[middle + 1 + j];
	i = j = 0; k = left;
	while (i < m && j < n) {
		if (Left[i] <= Right[j]) {
			tab[k] = Left[i];
			++i;
		} else {
			tab[k] = Right[j];
			++j;
		}
		++k;
	}
	while (i < m) {
		tab[k] = Left[i];
		++i; ++k;
	}
	while (j < n) {
		tab[k] = Right[j];
		++j; ++k;
	}
	delete Left;
	delete Right;
}

template<class T>
void mergeSort(T* tab, int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSort(tab, left, middle);
		mergeSort(tab, middle + 1, right);
		merge(tab, left, middle, right);
	}
}

template<class T>
void heapSort(T* Left, T* Right) {
	std::make_heap(Left, Right);
	std::sort_heap(Left, Right);
}

template<class T>
void insertionSort(T* tab, int left, int right) {
	for (int i = left + 1; i < right + 1; ++i) {
		int k = tab[i];
		int j = i;
		while (j > left && tab[j - 1] > k) {
			tab[j] = tab[j - 1];
			--j;
		}
		tab[j] = k;
	}
}

template<class T>
void introSort(T* tab, T* Left, T* Right, int maxdepth) {
	if ((Right - Left) < 16) insertionSort(tab, Left - tab, Right - tab);
	else if (maxdepth == 0) heapSort(Left, Right + 1);
	else {
		int pivot = partition(tab, Left - tab, Right - tab);
		introSort(tab, Left, tab + pivot, maxdepth - 1);
		introSort(tab, tab + pivot + 1, Right, maxdepth - 1);
	}
}
template void quickSort<int>(int*, int, int);
template void mergeSort<int>(int*, int, int);
template void introSort<int>(int*, int*, int*, int);