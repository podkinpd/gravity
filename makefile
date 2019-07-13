testGr:
	clang++ -std=c++11 -Wall calculations.cpp -o test
visual:
	clang++ -std=c++11 -Wall test.cpp -o vis -lm -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm -f *.o
