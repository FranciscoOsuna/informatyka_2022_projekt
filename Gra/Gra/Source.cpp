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
#include "Menu.h"


int main()
{

	// Set booleans to initial values
	bool isPaused = false;
	bool isLeaving = false;
	bool isFocused = true;
	bool devMode = false;
	bool zeroReload = false;
	bool inMainMenu = true;
	bool inLevelSelect = false;
	bool inManageSaves = false;
	bool playerHit = false;
	bool levelFinished = false;
	bool leaveAccepted = false;

	// Set the default level to one
	int level = 1;

	// Create player color variables for character creation
	sf::Color playerColor1 = sf::Color::Cyan;
	sf::Color playerColor2 = sf::Color::Blue;
	sf::Color newColor1 = sf::Color::Cyan;
	sf::Color newColor2 = sf::Color::Blue;

	// Create a sample "player" for character creation
	Tanks sampleTank(sf::Vector2f(200, 400), 225, 3, playerColor1, playerColor2);

	// Initialise an instance of the Title class
	Titles title; // This manages the title animations

	// Create window
	sf::RenderWindow window 
	(
		sf::VideoMode(1600, 800), "[*]",
		sf::Style::Close, sf::ContextSettings(24, 0, 8)
	);

	// Class initiations
	Pause pause;
	Leave leave;
	Background background;
	Cursor cursor;
	Timer timer;
	Saves saves;

	// Create color grids for character customisation
	ColorSquareGrid colorSquareGrid1(sf::Vector2f(400, 50));
	ColorSquareGrid colorSquareGrid2(sf::Vector2f(400, 400));

	// Create main menu buttons
	Button startGameButton(sf::Vector2f(1200, 200), sf::Vector2f(500, 150), sf::String("Start Game"));
	Button levelSelectButton(sf::Vector2f(1200, 400), sf::Vector2f(500, 150), sf::String("Level Select"));
	Button manageSavesButton(sf::Vector2f(1200, 600), sf::Vector2f(500, 150), sf::String("Manage Saves"));

	// Create level select buttons
	Button backButton(sf::Vector2f(800, 700), sf::Vector2f(500, 150), sf::String("Back"));
	Button level1(sf::Vector2f(200, 400), sf::Vector2f(100, 100), sf::String("1"));
	Button level2(sf::Vector2f(500, 400), sf::Vector2f(100, 100), sf::String("2"));
	Button level3(sf::Vector2f(800, 400), sf::Vector2f(100, 100), sf::String("3"));
	Button level4(sf::Vector2f(1100, 400), sf::Vector2f(100, 100), sf::String("4"));
	Button level5(sf::Vector2f(1400, 400), sf::Vector2f(100, 100), sf::String("5"));

	// Create leave menu buttons
	Button yesButton(sf::Vector2f(730, 420), sf::Vector2f(110, 60), sf::String("YES"));
	Button noButton(sf::Vector2f(870, 420), sf::Vector2f(110, 60), sf::String("NO"));

	// Create return button
	ReturnBox returnBox;
	Button returnButton(sf::Vector2f(800, 420), sf::Vector2f(250, 60), sf::String("RETURN"));

	// Create read and write buttons
	Button read1(sf::Vector2f(400, 200), sf::Vector2f(300, 100), sf::String("Read 1"));
	Button read2(sf::Vector2f(800, 200), sf::Vector2f(300, 100), sf::String("Read 2"));
	Button read3(sf::Vector2f(1200, 200), sf::Vector2f(300, 100), sf::String("Read 2"));

	Button write1(sf::Vector2f(400, 500), sf::Vector2f(300, 100), sf::String("Write 1"));
	Button write2(sf::Vector2f(800, 500), sf::Vector2f(300, 100), sf::String("Write 2"));
	Button write3(sf::Vector2f(1200, 500), sf::Vector2f(300, 100), sf::String("Write 2"));



	// Manages Icon, Framerate, Keypress event settings, hides cursor
	SetUpWindow setUp(window);

	// Get the current time
	sf::Clock clock;
	sf::Time elapsedTime;


	// Create the player tank
	Player player(sf::Vector2f(200, 400));

	// Create enemies and walls from file
	if (level == 1) 
	{
		readLevelFile("Levels\\Level1.txt");
	}
	else if (level == 2) 
	{
		readLevelFile("Levels\\Level2.txt");
	}
	else if (level == 3) 
	{
		readLevelFile("Levels\\Level3.txt");
	}
	else if (level == 4) 
	{
		readLevelFile("Levels\\Level4.txt");
	}
	else
	{
		readLevelFile("Levels\\Level5.txt");
	}

	// Create a vector of wall bounds
	std::vector<sf::FloatRect> wallBounds = getWallBounds(walls);
	
	
	while (window.isOpen()) // Program Loop
	{
		//Event Loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if closed manually
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
				

			// Toggle pause
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
				isPaused = !isPaused;

			// Toggle leave message
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				isLeaving = !isLeaving;

			// Toggle isFocused depending on window focus
			if (event.type == sf::Event::LostFocus)
				isFocused = false;
			if (event.type == sf::Event::GainedFocus)
				isFocused = true;

			// Toggle developer mode
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
				devMode = !devMode;

			// Toggle instant reload
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
				zeroReload = !zeroReload;

			// Reset
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4) || playerHit)
			{
				playerHit = false;
				timer.time = 0;
				player.projectiles.clear();
				player.reset();
				walls.clear();
				wallBounds.clear();
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i].projectiles.clear();
				}
				enemies.clear();

				if (level == 1)
				{
					readLevelFile("Levels\\Level1.txt");
				}
				else if (level == 2)
				{
					readLevelFile("Levels\\Level2.txt");
				}
				else if (level == 3)
				{
					readLevelFile("Levels\\Level3.txt");
				}
				else if (level == 4)
				{
					readLevelFile("Levels\\Level4.txt");
				}
				else
				{
					readLevelFile("Levels\\Level5.txt");
				}
				wallBounds = getWallBounds(walls);

			}
		}

		if (leaveAccepted)
		{
			window.close();
			break;
		}

		// Leaving loop
		if (isLeaving)
		{
			timer.pause();
			bool wasInMenu = inMainMenu;

			window.clear(sf::Color(133, 210, 208));

			if (!wasInMenu)
			{
				background.drawDark(window);
			}
			
			leave.draw(window);

			if (yesButton.manage(window))
			{
				leaveAccepted = true;
			}

			if (noButton.manage(window))
			{
				isLeaving = false;
			}

			clock.restart();
			cursor.draw(window);
			window.display();
		}

		// Main menu loop
		if (inMainMenu && !isLeaving &&!inLevelSelect)
		{
			timer.time = 0;
			timer.pause();
			window.clear(sf::Color(133, 210, 208));

			newColor1 = colorSquareGrid1.manage(window, playerColor1);
			if (newColor1 != playerColor1)
			{
				playerColor1 = newColor1;
			}

			newColor2 = colorSquareGrid2.manage(window, playerColor2);
			if (newColor2 != playerColor2)
			{
				playerColor2 = newColor2;
			}

			player.changeColors(playerColor1, playerColor2);
			sampleTank.changeColors(playerColor1, playerColor2);


			sampleTank.draw(window);

			if (startGameButton.manage(window))
			{
				timer.restart();
				playerHit = false;
				player.projectiles.clear();
				player.reset();
				walls.clear();
				wallBounds.clear();
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i].projectiles.clear();
				}
				enemies.clear();

				if (level == 1)
				{
					readLevelFile("Levels\\Level1.txt");
				}
				else if (level == 2)
				{
					readLevelFile("Levels\\Level2.txt");
				}
				else if (level == 3)
				{
					readLevelFile("Levels\\Level3.txt");
				}
				else if (level == 4)
				{
					readLevelFile("Levels\\Level4.txt");
				}
				else
				{
					readLevelFile("Levels\\Level5.txt");
				}
				wallBounds = getWallBounds(walls);
				inMainMenu = false;
			}

			if (levelSelectButton.manage(window))
			{
				inMainMenu = false;
				inLevelSelect = true;
			}

			if (manageSavesButton.manage(window))
			{
				inMainMenu = false;
				inManageSaves = true;
			}


			clock.restart();

			cursor.draw(window);
			window.display();
		}

		// Level select loop
		else if (inLevelSelect)
		{
			timer.time = 0;
			timer.pause();
			window.clear(sf::Color(133, 210, 208));

			if (level == 1)
			{
				level1.buttonColor = sf::Color(160, 32, 240);
				level2.buttonColor = level2.defaultColor;
				level3.buttonColor = level3.defaultColor;
				level4.buttonColor = level4.defaultColor;
				level5.buttonColor = level5.defaultColor;
			}
			else if (level == 2)
			{
				level1.buttonColor = level2.defaultColor;
				level2.buttonColor = sf::Color(160, 32, 240);
				level3.buttonColor = level3.defaultColor;
				level4.buttonColor = level4.defaultColor;
				level5.buttonColor = level5.defaultColor;
			}
			else if (level == 3)
			{
				level1.buttonColor = level2.defaultColor;
				level2.buttonColor = level2.defaultColor;
				level3.buttonColor = sf::Color(160, 32, 240);
				level4.buttonColor = level4.defaultColor;
				level5.buttonColor = level5.defaultColor;
			}
			else if (level == 4)
			{
				level1.buttonColor = level2.defaultColor;
				level2.buttonColor = level2.defaultColor;
				level3.buttonColor = level3.defaultColor;
				level4.buttonColor = sf::Color(160, 32, 240);
				level5.buttonColor = level5.defaultColor;
			}
			else
			{
				level1.buttonColor = level2.defaultColor;
				level2.buttonColor = level2.defaultColor;
				level3.buttonColor = level3.defaultColor;
				level4.buttonColor = level4.defaultColor;
				level5.buttonColor = sf::Color(160, 32, 240);
			}

			if (backButton.manage(window))
			{
				inLevelSelect = false;
				inMainMenu = true;
			}
			if (level1.manage(window))
			{
				level = 1;
			}
			if (level2.manage(window))
			{
				level = 2;
			}
			if (level3.manage(window))
			{
				level = 3;
			}
			if (level4.manage(window))
			{
				level = 4;
			}
			if (level5.manage(window))
			{
				level = 5;
			}

			saves.draw(window);
			clock.restart();

			cursor.draw(window);
			window.display();
		}

		// Manage saves loop
		else if (inManageSaves)
		{
			timer.time = 0;
			timer.pause();
			window.clear(sf::Color(133, 210, 208));
			if (backButton.manage(window))
			{
				inManageSaves = false;
				inMainMenu = true;
			}
			if (read1.manage(window))
			{
				saves.readFromBinaryFile("Saves\\Save1");
			}
			if (read2.manage(window))
			{
				saves.readFromBinaryFile("Saves\\Save2");
			}
			if (read3.manage(window))
			{
				saves.readFromBinaryFile("Saves\\Save2");
			}
			if (write1.manage(window))
			{
				saves.saveToBinaryFile("Saves\\Save1");
			}
			if (write2.manage(window))
			{
				saves.saveToBinaryFile("Saves\\Save2");
			}
			if (write3.manage(window))
			{
				saves.saveToBinaryFile("Saves\\Save3");
			}

			clock.restart();

			cursor.draw(window);
			window.display();
		}

		// Level finished loop
		else if (levelFinished)
		{
			timer.pause();
			if (timer.time < saves.array[level-1])
			{
				saves.array[level-1] = timer.time;
			}
			window.clear(sf::Color(133, 210, 208));
			background.drawDark(window);

			returnBox.draw(window, timer.timeString);

			if (returnButton.manage(window))
			{
				inMainMenu = true;
				levelFinished = false;
			}
			cursor.draw(window);
			window.display();
		}

		// Game loop
		else if (!isPaused && isFocused && !isLeaving && !inMainMenu && !levelFinished)
		{

			timer.resume();
			// Get the elapsed time since the last frame
			elapsedTime = clock.restart();

			window.clear();

			background.draw(window);

			if (enemies.empty())
			{
				levelFinished = true;
			}

			// For each enemy
			for (int i = 0; i < enemies.size(); i++) 
			{
				bool canShoot = 1;

				// For each wall for each enemy
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

				// For each projectile for each enemy
				for (int j = 0; j < enemies[i].projectiles.size(); j++) 
				{

					if (enemies[i].projectiles[j].projectileBounds.intersects(player.playerBounds))
					{
						playerHit = true;
					}

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
				if (enemies[i].hit)
				{
					enemies.erase(enemies.begin() + i);
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
				if (player.projectiles[i].projectileBounds.intersects(player.playerBounds)
					&& player.projectiles[i].bounces > 0)
				{
					playerHit = true;
				}
					
				for (int j = 0; j < enemies.size(); j++) 
				{
					if (player.projectiles[i].projectileBounds.intersects(enemies[j].bodyRect.getGlobalBounds()))
					{
						enemies[j].hit = true;
					}
				}

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

			timer.manage(window);
			cursor.draw(window);

			window.display();

		}

		// Pause loop
		else if(!isLeaving)
		{
			timer.pause();
			window.clear(sf::Color::Black);
			background.drawDark(window);

			pause.draw(window);
			
			clock.restart();
			cursor.draw(window);
			window.display();
		}
		title.titleAnim(window);
	}

	return 0;
}