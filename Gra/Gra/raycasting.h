#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Header.h"


bool raycast(sf::Vector2f start, sf::Vector2f end, sf::FloatRect obstacle, sf::RenderWindow& window, bool devMode)
{
	// Create the end rectangle of a given size and 
	sf::RectangleShape endRect = sf::RectangleShape(sf::Vector2f(50, 50));
	endRect.setPosition(end.x - 25, end.y - 25);
	//set end bounds
	sf::FloatRect endBounds = endRect.getGlobalBounds();
	//create ray object
	sf::RectangleShape ray = sf::RectangleShape(sf::Vector2f(3,3));
	//set ray position to start
	ray.setPosition(start);
	//get direction from start to end in radians
	float direction = (atan2((end.y - start.y), (end.x - start.x)));
	sf::Vector2f directionVector = sf::Vector2f(cos(direction), sin(direction));
	sf::FloatRect rayBounds = ray.getGlobalBounds();
	
	while (!rayBounds.intersects(endBounds))
	{
		ray.move(directionVector*3.f);
		rayBounds = ray.getGlobalBounds();
		if (rayBounds.intersects(obstacle))
		{
			return true;
		}
		if (devMode)
		{
			window.draw(ray);
		}
	}
	return false;
}
