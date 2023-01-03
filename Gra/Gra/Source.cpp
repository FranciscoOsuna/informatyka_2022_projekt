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
#include "Tanks.h"
#include "Walls.h"
#include "LevelManager.h"


int main()
{
	bool isPaused = false;
	bool isFocused = true;

	Titles title;

	//create window
	sf::RenderWindow window 
	(
		sf::VideoMode(1600, 800), "[*]",
		sf::Style::Close, sf::ContextSettings(24, 0, 8)
	);

	// Class initiations
	// Initiate pausebox;
	Pause pause;

	// Initiate background
	Background background;

	// Initiate cursor
	Cursor cursor;

	// Manages Icon, Framerate, Keypress event settings, hides cursor
	SetUp setUp(window);

	// Get the current time
	sf::Clock clock;
	sf::Time elapsedTime;


	// Create the player tank
	Player player(sf::Vector2f(400, 400));

	Wall wall1(sf::Vector2f(200, 40), sf::Vector2f(800, 400), 0);
	Wall wall2(sf::Vector2f(200, 40), sf::Vector2f(800, 400), 1);

	// Create enemies and walls from file
	readLevelFile("Levels\\Level1.txt");

	
	
	
	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event)) //Event Loop
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
				isPaused = !isPaused;

			if (event.type == sf::Event::LostFocus)
				isFocused = false;

			if (event.type == sf::Event::GainedFocus)
				isFocused = true;
		}

		if (!isPaused && isFocused)
		{

			// Get the elapsed time since the last frame
			elapsedTime = clock.restart();

			window.clear();

			background.draw(window);

			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i].fixTurretOn(player);
				enemies[i].draw(window);
			}

			for (int i = 0; i < walls.size(); i++)
			{
				walls[i].draw(window);
			}

			wall1.draw(window);
			wall2.draw(window);

			player.manageMovement(elapsedTime);
			player.draw(window);

			cursor.draw(window);

			window.display();

			title.titleAnim(window);

		}
		else //do when paused
		{
			window.clear(sf::Color::Black);
			background.draw(window);

			pause.draw(window);
			
			clock.restart();
			cursor.draw(window);
			window.display();
		}
		
	}

	return 0;
}