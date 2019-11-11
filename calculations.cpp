#include "Laws.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::string GetStdoutFromCommand(std::string cmd) {

	std::string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	data = data.substr(0, data.length() - 1);
	return data;
}

std::string GetNextFileName() {
	return std::string("/home/gravity_data/data/test") + GetStdoutFromCommand("ls /home/gravity_data/data | wc -l");
}
	
int main(int argc, char* argv[]) {
	int n, m, maxk;
	n = 160;
	m = 120;
	maxk = 100;
	Field_of_mass field(n, m), temp(n, m);
	int cx1 = 60, cy1 = 60, cx2 = 100, cy2 = 60;
	Vector v(0, 4e-5, 0);
	Vector v1(0, -4e-5, 0);
	for(size_t i = 0; i < 160; i++) {
		for(size_t j = 0; j < 120; j++) {
			if ((i-cx1)*(i-cx1) + (j-cy1)*(j-cy1) < 400) { 
				field.AddMass(i, j, 1e+10);
				field.SetSpeed(i, j, v);
			}
			if ((i-cx2)*(i-cx2) + (j-cy2)*(j-cy2) < 400) {
				field.AddMass(i, j, 1e+10);
				field.SetSpeed(i, j, v1);
			}
			if ((i-cx1)*(i-cx1) + (j-cy1)*(j-cy1) < 100) { 
				field.AddMass(i, j, 2e+10);
				field.SetSpeed(i, j, v);
			}
			if ((i-cx2)*(i-cx2) + (j-cy2)*(j-cy2) < 100) {
				field.AddMass(i, j, 2e+10);
				field.SetSpeed(i, j, v1);
			}
		}
	}
//	field.SetMass(80, 60, 1e+17);
	/*
	for(size_t i = 50; i < 90; i++) {
		for(size_t j = 30; j < 70; j++) {
			field.AddMass(i, j, 1e+11);
		}
	}
	for(size_t i = 120; i < 130; i++) {
		for(size_t j = 40; j < 80; j++) {
			field.AddMass(i, j, 1e+12);
		}
	}*/
//	std::vector<Field_of_mass> f;
//	f.push_back(field);
	std::ofstream file;
	file.open(GetNextFileName());
	file << maxk << ' ' << n << ' ' << m << std::endl;
	for(size_t k = 0; k < maxk; k++) {
		for(size_t i = 0; i < n; i++) {
			for(size_t j = 0; j < m; j++) {
			/*	if(k % 10 == 0) std::cout << f[k].GetMass(i, j) << ' ';*/
				file << field.GetMass(i, j) << ' ' << field.GetSpeed(i, j) << ' ';
			}
		/*	if(k % 10 == 0) std::cout << std::endl;*/
			file << std::endl;
		}
	/*	if(k % 10 == 0) std::cout << std::endl;*/
		system("date");
		field = Laws::ResultField(field);
		std::cout << k << std::endl;
	}
	system("date");
	file.close();

	return 0;
}
