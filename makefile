calcGr:
	clang++ -std=c++11 -Wall calculations.cpp -o calc
concalc:
	clang++ -std=c++11 -Wall concalculations.cpp -o concalc
visual:
	clang++ -std=c++11 -Wall visualisation.cpp -o vis -lm -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm -f *.o
