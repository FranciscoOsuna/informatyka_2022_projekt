#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Menu.h"
#include <fstream>
#include <string>


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

class ReturnBox
{
public:
	ReturnBox()
	{
		font.loadFromFile("Assets\\font.otf");

		returnTexture.loadFromFile("Assets\\returnMessage.png");
		returnBox.setOrigin(sf::Vector2f(returnTexture.getSize()) / 2.0f);
		returnBox.setPosition(800, 400);
		returnBox.setTexture(returnTexture);
		timerResult.setPosition(sf::Vector2f(700, 600));
	}

	void draw(sf::RenderWindow& window,std::string content)
	{
		timerResult = sf::Text(content, font, 50);
		timerResult.setPosition(sf::Vector2f(730, 315));
		window.draw(returnBox);
		window.draw(timerResult);
	}
private:
	sf::Font font;
	sf::Text timerResult;
	sf::Texture returnTexture;
	sf::Sprite returnBox;
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

class Saves {
public:
	Saves() {
		font.loadFromFile("Assets\\font.otf");

		for (int i = 0; i < 5; i++) {
			array[i] = 99.9f;
		}
	}

	void setValue(int index, float value) {
		array[index] = value;
	}

	void readFromBinaryFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);
		file.read((char*)array, sizeof(array));
		file.close();
	}

	void saveToBinaryFile(const std::string& filename) {
		std::ofstream file(filename, std::ios::binary);
		file.write((char*)array, sizeof(array));
		file.close();
	}

	float getRoundedFloat(int index, float array[]) {
		// Round the float to 2 decimal places
		return roundf(array[index] * 100) / 100;
	}


	std::string getValueAsString(int ind) {
		std::ostringstream ss;
		ss << getRoundedFloat(ind, array);
		return ss.str();
	}

	void draw(sf::RenderWindow& window)
	{
		bool refreshed = false;
		if (refreshed == false)
		{
			record1 = sf::Text(getValueAsString(0), font, 50);
			record2 = sf::Text(getValueAsString(1), font, 50);
			record3 = sf::Text(getValueAsString(2), font, 50);
			record4 = sf::Text(getValueAsString(3), font, 50);
			record5 = sf::Text(getValueAsString(4), font, 50);

			record1.setPosition(sf::Vector2f(140, 250));
			record2.setPosition(sf::Vector2f(440, 250));
			record3.setPosition(sf::Vector2f(740, 250));
			record4.setPosition(sf::Vector2f(1040, 250));
			record5.setPosition(sf::Vector2f(1340, 250));

			refreshed = true;
		}
		window.draw(record1);
		window.draw(record2);
		window.draw(record3);
		window.draw(record4);
		window.draw(record5);
	}

	float array[5];
	sf::Font font;
	sf::Text record1;
	sf::Text record2;
	sf::Text record3;
	sf::Text record4;
	sf::Text record5;
};



