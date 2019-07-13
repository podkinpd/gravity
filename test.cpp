#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <string>

sf::Color getColor(double m) {
	if(m < 1e+5) return sf::Color(0, 0, 0);
	else {
		return sf::Color(fmin(fmax(std::log(m) / std::log(10) - 5, 0) * 32, 255),/* 50 - fabs(m - 5e+11) / 1e+12 * 50, 50 - fabs(m - 5e+11) / 1e+12 * 50*/0, 0);
	}
}

int main()
{
	std::string imname("images/image");
	std::string imext(".png");
	std::ifstream inf;
	inf.open("data/test7");
	int mk, n, m;
	inf >> mk >> n >> m;
	double d;
	for(size_t q = 0; q < mk; q++) {
		std::vector<std::vector<double>> mass(n);
		for(size_t w = 0; w < n; w++) {
			for(size_t e = 0; e < m; e++) {
				inf >> d;
				mass[w].push_back(d);
			}
		}
		sf::Image im;
		im.create(800, 600);

 /*   sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
*/
		for(size_t i = 0; i < 800; i++) {
			for(size_t j = 0; j < 600; j++) {
				im.setPixel(i, j, getColor(mass[i/5][j/5]));
			}
		}
		im.saveToFile(imname + std::to_string(q) + imext);
	}
    return 0;
}
