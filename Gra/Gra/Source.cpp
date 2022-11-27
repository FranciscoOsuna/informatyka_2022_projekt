/*
Temat projektu: 1. Obiekt sterowany przez u�ytkownika unika kontaktu z innymi obiektami
pojawiaj�cymi si� losowo w scenerii gry. Przyk�ad scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierk� tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czo�g poruszaj�cy si� po planszy omijaj�c przeszkody oraz pociski, przy
czym strzelaj�c w wrogie czo�gi.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				printf("Button pressed\n");
			if (event.type == sf::Event::Resized)
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
			}
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}