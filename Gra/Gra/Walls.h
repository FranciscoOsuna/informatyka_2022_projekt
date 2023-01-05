#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Wall
{
public:

	sf::FloatRect wallBounds;
	sf::RectangleShape wallBoundsRect;

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
		wallTexture = std::make_shared<sf::Texture>();
		wallTexture->loadFromFile("Assets\\wallTexture.png");
		wallTexture->setRepeated(true);

		wall.setPosition(position);
		wall.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		
		wall.setTexture(*wallTexture);

		wall.setRotation(rotation);

		wallOutline.setPosition(position.x-1, position.y-1);
		wallOutline.setSize(sf::Vector2f(size.x+2,size.y+2));
		wallOutline.setRotation(rotation);
		wallOutline.setFillColor(sf::Color::Black);

		wallBounds = wallOutline.getGlobalBounds();
		wallBoundsRect =  sf::RectangleShape(sf::Vector2f(wallBounds.width, wallBounds.height));
		wallBoundsRect.setPosition(wallBounds.left, wallBounds.top);
	}

	void draw(sf::RenderWindow& window, bool devMode)
	{
		window.draw(wallOutline);
		window.draw(wall);

		if (devMode)
		{
			window.draw(wallBoundsRect);
		}
	}

private:
	std::shared_ptr<sf::Texture> wallTexture;
	float rotation;
	sf::Sprite wall;
	sf::RectangleShape wallOutline;

};

std::vector<sf::FloatRect> getWallBounds(const std::vector<Wall>& walls) {
	std::vector<sf::FloatRect> wallBounds;
	for (const Wall& wall : walls) {
		wallBounds.push_back(wall.wallBounds);
	}
	return wallBounds;
}