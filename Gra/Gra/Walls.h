#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Wall
{
public:

	Wall(sf::Vector2f size, sf::Vector2f position, float isVertical = 0)
	{
		

		if (isVertical)
		{
			rotation = 90;
		}
		else
		{
			rotation = 0;
		}
		Wall::wallTexture.loadFromFile("Assets\\wallTexture.png");
		Wall::wallTexture.setRepeated(true);

		wall.setPosition(position.x + 2, position.y + 1);
		wall.setTextureRect(sf::IntRect(0, 0, size.x - 4, size.y - 2));
		wall.setTexture(wallTexture);
		wall.setRotation(rotation);

		wallOutline.setPosition(position);
		wallOutline.setSize(size);
		wallOutline.setRotation(rotation);
		wallOutline.setFillColor(sf::Color::Black);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(wallOutline);
		window.draw(wall);
	}

private:
	sf::Texture wallTexture;
	float rotation;
	sf::Sprite wall;
	sf::RectangleShape wallOutline;

};