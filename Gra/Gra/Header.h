#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Menu.h"



class Titles //manages title animations
{
public:

	void startTimer()
	{
		sf::Clock titleTimer;
	}

	Titles()
	{
		startTimer();
	}

	int i = 0;
	const char* titles[10] = {
		"   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-",
		"   --ANKS-", "   -T-NKS-", "   -TA-KS-", "   -TAN-S-", "   -TANK--" };
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

	void titleAnim(sf::RenderWindow& window)
	{
		sf::Time elapsedBetweenTitles = titleTimer.getElapsedTime();
		if (elapsedBetweenTitles.asMilliseconds() > 300)
		{
			window.setTitle(nextTitle());
			titleTimer.restart();
		}
	}

private:
	sf::Clock titleTimer;
};


class SetUpWindow //performs Start Up functions on window
{
public:
	SetUpWindow(sf::RenderWindow& window)
	{
		// Load the icon from a file
		icon.loadFromFile("Assets\\Icon.png");

		// Set the window icon
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		// Set the frame rate to 60 fps
		window.setFramerateLimit(60);

		// Turn off repeat keypress events on hold
		window.setKeyRepeatEnabled(false);

		// Hide mouse cursor
		window.setMouseCursorVisible(false);

		
	}

private:
	sf::Image icon;
};


class Background
{
public:
	Background()
	{
		backGround.setSize(sf::Vector2f(1600, 800));
		backGroundTexture.loadFromFile("Assets\\backGround.png");
		backGround.setTexture(&backGroundTexture);

		backGroundDark.setSize(sf::Vector2f(1600, 800));
		backGroundTextureDark.loadFromFile("Assets\\backGroundDark.png");
		backGroundDark.setTexture(&backGroundTextureDark);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(backGround);
	}

	void drawDark(sf::RenderWindow& window)
	{
		window.draw(backGroundDark);
	}

private:
	sf::RectangleShape backGround;
	sf::Texture backGroundTexture;

	sf::RectangleShape backGroundDark;
	sf::Texture backGroundTextureDark;
};


class Cursor
{
public:
	
	Cursor()
	{
		cursorTexture.loadFromFile("Assets\\cursor.png");
		cursorSprite.setOrigin(13,13);
		cursorSprite.setTexture(cursorTexture);
	}

	void draw(sf::RenderWindow& window)
	{
		cursorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		window.draw(cursorSprite);
	}
private:
	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
};


class Pause
{
public:
	Pause()
	{
		pauseTexture.loadFromFile("Assets\\pauseMessage.png");
		pauseBox.setOrigin(sf::Vector2f(pauseTexture.getSize()) / 2.0f);
		pauseBox.setPosition(800, 400);
		pauseBox.setTexture(pauseTexture);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(pauseBox);
	}
private:
	sf::Texture pauseTexture;
	sf::Sprite pauseBox;
};


class Leave
{
public:
	Leave()
	{
		leaveTexture.loadFromFile("Assets\\leaveMessage.png");
		leaveBox.setOrigin(sf::Vector2f(leaveTexture.getSize()) / 2.0f);
		leaveBox.setPosition(800, 400);
		leaveBox.setTexture(leaveTexture);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(leaveBox);
	}
private:
	sf::Texture leaveTexture;
	sf::Sprite leaveBox;
};