/*
Temat projektu: 1. Obiekt sterowany przez użytkownika unika kontaktu z innymi obiektami
pojawiającymi się losowo w scenerii gry. Przykład scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierką tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czołg poruszający się po planszy omijając przeszkody oraz pociski, przy
czym strzelając w wrogie czołgi.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Header.h"

int main()
{

	Titles title;
	sf::Clock titleTimer;

	sf::RenderWindow window(sf::VideoMode(1600, 800), "[*]", sf::Style::Close); //create window

	Tanks Player(sf::Vector2f(400, 400)); // Creates the player tank
	Tanks Enemy1(sf::Vector2f(800, 400), 180, 1.5, sf::Color::Red, sf::Color(245, 51, 126)); // Creates enemy tank

	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event)) //Event Loop
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		Player.draw(window);
		Enemy1.draw(window);

		window.display();


		title.titleAnim(window);
	}

	return 0;
}