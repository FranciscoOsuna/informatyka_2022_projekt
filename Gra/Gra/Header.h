#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>



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


class Tanks
{
public:

	Tanks(sf::Vector2f position, float orient = 0,
		float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan,
		sf::Color color2 = sf::Color::Blue)
	{
		sf::Vector2f size = sizeMult * sf::Vector2f(30, 50);

		// Set the parameters of the body
		bodyRect.setSize(size);
		bodyRect.setOrigin(size / 2.0f);
		bodyRect.setPosition(position);
		bodyRect.setFillColor(color1);
		bodyRect.setOutlineColor(sf::Color::Black);
		bodyRect.setOutlineThickness(2);
		bodyRect.setRotation(orient);


		// Set the parameters of the gun
		gunRect.setSize(sf::Vector2f(size.x / 5, size.y * 0.8));
		gunRect.setOrigin(size.x / 10, size.y / 8);
		gunRect.setPosition(position);
		gunRect.setFillColor(color2);
		gunRect.setOutlineColor(sf::Color::Black);
		gunRect.setOutlineThickness(2);
		gunRect.setRotation(orient);

		// Set the parameters of the base of the gun
		gunCircle.setRadius(size.x / 3);
		gunCircle.setOrigin(size / 3.0f);
		gunCircle.setPosition(position);
		gunCircle.setFillColor(color2);
		gunCircle.setOutlineColor(sf::Color::Black);
		gunCircle.setOutlineThickness(2);
		gunCircle.setRotation(orient);

	}

	sf::Vector2f vectorFromRotation(sf::RectangleShape& body) // Returns a vector according to body orientation
	{
		float rotation = body.getRotation() * 3.14159 / 180;
		sf::Vector2f out = sf::Vector2f(0.02 * cos(rotation), 0.02 * sin(rotation));
		return out;
	}

	void draw(sf::RenderWindow& window)
	{
		// Draw the shapes to the window in the desired order
		window.draw(bodyRect);
		window.draw(gunRect);
		window.draw(gunCircle);
	}

private:
	sf::RectangleShape bodyRect;
	sf::RectangleShape gunRect;
	sf::CircleShape gunCircle;
};