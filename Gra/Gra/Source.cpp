/*
Temat projektu: 1. Obiekt sterowany przez użytkownika unika kontaktu z innymi obiektami
pojawiającymi się losowo w scenerii gry. Przykład scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierką tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czołg poruszający się po planszy omijając przeszkody oraz pociski, przy
czym strzelając w wrogie czołgi.
*/

#include <SFML/Graphics.hpp>
#include <iostream>


class Titles //manages title animations
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

		bool titleAnim(sf::RenderWindow &window, sf::Clock timer)
		{
			sf::Time elapsedBetweenTitles = timer.getElapsedTime();
			if (elapsedBetweenTitles.asMilliseconds() > 300)
			{
				window.setTitle(nextTitle());
				return 1;
			}
			return 0;
		}
};

int main()
{
	
	Titles title;
	sf::Clock titleTimer;

	sf::RenderWindow window(sf::VideoMode(1600, 800), "[*]");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event)) //Event Loop
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
		if(title.titleAnim(window, titleTimer)) titleTimer.restart();
	}
	return 0;
}