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
	bool isPaused = false;

	Titles title;

	//create window
	sf::RenderWindow window 
	(
		sf::VideoMode(1600, 800), "[*]",
		sf::Style::Close, sf::ContextSettings(24, 0, 8)
	);

	// Create the background
	Background backGround;

	// Set the frame rate to 60 fps
	window.setFramerateLimit(60);

	// Turn off repeat keypress events on hold
	window.setKeyRepeatEnabled(false);

	// Get the current time
	sf::Clock clock;
	sf::Time elapsedTime;

	// Create the player tank
	Player player(sf::Vector2f(400, 400));

	// Create the enemy tanks
	Enemy enemyList[5] =
	{
		Enemy(sf::Vector2f(200, 400), 90, 1, sf::Color::Blue, sf::Color(0, 51, 126)),
		Enemy(sf::Vector2f(400, 200), 120, 0.5, sf::Color::Red, sf::Color(245, 0, 126)),
		Enemy(sf::Vector2f(600, 600), 180, 2, sf::Color::Green, sf::Color(245, 51, 0)),
		Enemy(sf::Vector2f(800, 400), 270, 0.8, sf::Color::Yellow, sf::Color(245, 51, 126)),
		Enemy(sf::Vector2f(1400, 400), 0, 5, sf::Color::Red, sf::Color(245, 0, 126)),
	};

	//Create walls
	Wall wall1(sf::Vector2f(400, 45), sf::Vector2f(40, 500), 45);
	
	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event)) //Event Loop
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
				isPaused = !isPaused;
		}

		if (!isPaused)
		{

			// Get the elapsed time since the last frame
			elapsedTime = clock.restart();

			window.clear();

			backGround.draw(window);

			for (int i = 0; i < 5; i++)
			{
				enemyList[i].fixTurretOn(player);
				enemyList[i].draw(window);
			}


			player.manageMovement(elapsedTime);
			player.draw(window);
			wall1.draw(window);

			window.display();

			title.titleAnim(window);

		}
		else 
		{
			window.clear(sf::Color::Black);
			clock.restart();

		}
		
	}

	return 0;
}