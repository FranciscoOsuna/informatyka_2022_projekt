/*
Temat projektu: 1. Obiekt sterowany przez u¿ytkownika unika kontaktu z innymi obiektami
pojawiaj¹cymi siê losowo w scenerii gry. Przyk³ad scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierk¹ tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czo³g poruszaj¹cy siê po planszy omijaj¹c przeszkody oraz pociski, przy
czym strzelaj¹c w wrogie czo³gi.
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