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

	// Turn devMode off
	bool devMode = false;

	bool zeroReload = false;


	// Create the player tank
	Player player(sf::Vector2f(200, 400));

	// Create enemies and walls from file
	readLevelFile("Levels\\Level1.txt");

	// Create a vector of wall bounds
	std::vector<sf::FloatRect> wallBounds = getWallBounds(walls);
	
	
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

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
				devMode = !devMode;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
				zeroReload = !zeroReload;
		}

		if (!isPaused && isFocused)
		{

			// Get the elapsed time since the last frame
			elapsedTime = clock.restart();

			window.clear();

			background.draw(window);

			for (int i = 0; i < enemies.size(); i++)
			{
				bool canShoot = 1;
				for (int j = 0; j < walls.size(); j++)
				{
					if (raycast(
						enemies[i].enemyPosition,
						player.giveBodyPosition(),
						walls[j].wallBounds,
						window,
					    devMode))
					{
						canShoot = 0;
					}
				}
				enemies[i].fixTurretOn(player);
				enemies[i].drawAndShoot(window, canShoot);
				for (int j = 0; j < enemies[i].projectiles.size(); j++)
				{

					enemies[i].projectiles[j].update();
					enemies[i].projectiles[j].draw(window);
					if (!enemies[i].projectiles[j].active)
					{
						enemies[i].projectiles.erase(enemies[i].projectiles.begin() + j);
					}
				}
 
				// i - enemy, j - wall, k - projectile
				for (int k = 0; k < enemies[i].projectiles.size(); k++) 
				{
					for (int j = 0; j < walls.size(); j++)
					{
						if (i >= enemies[i].projectiles.size())
						{
							break;
						}
						int colType = enemies[i].projectiles[k].collisionTypeDetection(walls[j].wallBounds);
						if (colType == 1)
						{
							enemies[i].projectiles[k].bounce(true);
						}
						else if (colType == 2)
						{
							enemies[i].projectiles[k].bounce(false);
						}
					}
				}
				
			}

			for (int i = 0; i < walls.size(); i++)
			{
				walls[i].draw(window, devMode);
			}


			player.manageMovement(elapsedTime, wallBounds, zeroReload);
			player.drawPlayer(window, devMode);
			for (int i = 0; i < player.projectiles.size(); i++)
			{
				player.projectiles[i].update();
				player.projectiles[i].draw(window);
				if (!player.projectiles[i].active)
				{
					player.projectiles.erase(player.projectiles.begin() + i);
				}

				for (int j = 0; j < walls.size(); j++)
				{
					if (i >= player.projectiles.size())
					{
						break;
					}
					int colType = player.projectiles[i].collisionTypeDetection(walls[j].wallBounds);
					if (colType == 1)
					{
						player.projectiles[i].bounce(true);
					}
					else if (colType == 2)
					{
						player.projectiles[i].bounce(false);
					}
				}
			}

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