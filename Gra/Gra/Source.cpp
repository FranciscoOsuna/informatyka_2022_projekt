/*
Temat projektu: 1. Obiekt sterowany przez użytkownika unika kontaktu z innymi obiektami
pojawiającymi się losowo w scenerii gry. Przykład scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierką tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czołg poruszający się po planszy omijając przeszkody oraz pociski, przy
czym strzelając w wrogie czołgi.
*/

#include <SFML/Graphics.hpp>
#include <iostream>


class Titles
{
	public:
		int i = 0;
		const char* titles[10] = { 
			"   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-",
			"   --ANKS-", "   -T-NKS-", "   -TA-KS-", "   -TAN-S-", "   -TANK--"};
		std::string currentTitle = titles[0];

		std::string nextTitle()
		{
			if (i >= 10)
			{
				i = 0;
			}
			currentTitle = titles[i];
			i++;
			return currentTitle;
		}


};

int main()
{
	Titles title;
	sf::Clock clock;
	sf::Time elapsed;

	sf::RenderWindow window(sf::VideoMode(1600, 800), "[*]");
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

		elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() > 300)
		{
			window.setTitle(title.nextTitle());
			clock.restart();
		}
	}
	return 0;
}