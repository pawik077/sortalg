#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "sorts.hh"
#include "tabgen.hh"
#define DataType int

int main() {
	std::ofstream file;
	file.open("res", std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Cannot open output file!";
		return 3;
	}
	int sizes[] = {10000, 50000, 100000, 500000, 1000000};
	double percent[] = {0, 25, 50, 75, 95, 99, 99.7, 100};
	std::string sortAlg[] = {"Quicksort", "Merge Sort", "Introsort"};
	for (int sorts = 0; sorts < 3; ++sorts) {
		file << "*** " << sortAlg[sorts] << "\n";
		for (int arrSize : sizes) {
			file << "\n** Array size: " << arrSize << "\n";
			for (double prc : percent) {
				if (prc == 100)
					file << "\n* Array reversed\n\n";
				else
					file << "\n* Percent sorted: " << prc << "\n\n";
				for (int i = 0; i < 100; ++i) {
					DataType *tab = new DataType[arrSize];
					fillTable<DataType>(tab, arrSize);
					if (prc == 100)
						std::sort(tab, tab + arrSize, std::greater<int>());
					else
						std::sort(tab, tab + static_cast<int>(arrSize * prc / 100));
					if (prc == 100) {
						if (!isReversed<DataType>(tab, arrSize)) {
							std::cerr << "Array not reversed properly!" << std::endl;
							return 2;
						}
					} else {
						if (!isSorted<DataType>(tab, static_cast<int>(arrSize * prc / 100))) {
							std::cerr << "Part of array not sorted!" << std::endl;
							return 2;
						}
					}
					std::chrono::time_point<std::chrono::steady_clock> tStart, tEnd;
					switch (sorts) {
						case 0:
							tStart = std::chrono::high_resolution_clock::now();
							quickSort<DataType>(tab, 0, arrSize - 1);
							tEnd = std::chrono::high_resolution_clock::now();
							break;
						case 1:
							tStart = std::chrono::high_resolution_clock::now();
							mergeSort<DataType>(tab, 0, arrSize - 1);
							tEnd = std::chrono::high_resolution_clock::now();
							break;
						case 2:
							tStart = std::chrono::high_resolution_clock::now();
							introSort(tab, tab, tab + arrSize - 1, log(arrSize) * 2);
							tEnd = std::chrono::high_resolution_clock::now();
							break;
						default:
							std::cerr << "You really shouldn't see this error message" << std::endl;
							break;
					}
					if (!isSorted<DataType>(tab, arrSize)) {
						std::cerr << "Array not sorted! Your code is bad and you should feel bad!" << std::endl;
						return 1;
					}
					file << std::chrono::duration<double, std::milli>(tEnd - tStart).count() << std::endl;
					delete tab;
				}
				if (prc == 100)
					std::cout << "Finished sorting " << arrSize << " element arrays presorted and reversed using " << sortAlg[sorts] << std::endl;
				else
					std::cout << "Finished sorting " << arrSize << " element arrays presorted in " << prc << " percent using " << sortAlg[sorts] << std::endl;
			}

		}
		file << '\n';
	}
	std::cout << "Finished sorting!";
	std::cin.get();
}