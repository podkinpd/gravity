#include <iostream>
#include <fstream>

int main() {
	int n, m , k;
	std::ifstream inf;
	inf.open("data/test3");
	inf >> k >> n >> m;
	double mass, dmass;
	for(size_t q = 0; q < k; q++) {
		mass = 0;
		for(size_t w = 0; w < n; w++) {
			for(size_t e = 0; e < m; e++) {
				inf >> dmass;
				mass += dmass;
			}
		}
		std::cout << q << ":  " <<  mass / 1e+13 << std::endl;
	}
	return 0;
}

