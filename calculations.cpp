
#include "Laws.hpp"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
	int n, m, maxk;
	n = 160;
	m = 120;
	maxk = 1000;
	Field_of_mass field(n, m);
	for(size_t i = 70; i < 110; i++) {
		for(size_t j = 50; j < 90; j++) {
			field.AddMass(i, j, 1e+11);
		}
	}
	for(size_t i = 50; i < 90; i++) {
		for(size_t j = 30; j < 70; j++) {
			field.AddMass(i, j, 1e+11);
		}
	}
	for(size_t i = 120; i < 130; i++) {
		for(size_t j = 40; j < 80; j++) {
			field.AddMass(i, j, 1e+12);
		}
	}
	std::vector<Field_of_mass> f;
	f.push_back(field);
	std::ofstream file;
	file.open("data/test7");
	file << maxk << ' ' << n << ' ' << m << std::endl;
	for(size_t k = 0; k < maxk; k++) {
		for(size_t i = 0; i < n; i++) {
			for(size_t j = 0; j < m; j++) {
			/*	if(k % 10 == 0) std::cout << f[k].GetMass(i, j) << ' ';*/
				file << f[k].GetMass(i, j) << ' ';
			}
		/*	if(k % 10 == 0) std::cout << std::endl;*/
			file << std::endl;
		}
	/*	if(k % 10 == 0) std::cout << std::endl;*/
		f.push_back(Laws::ResultField(f[k]));
		std::cout << k << std::endl;
	}

	file.close();

	return 0;
}
