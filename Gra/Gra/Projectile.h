#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Header.h"
#include "Tanks.h"
#include "Walls.h"
#include "LevelManager.h"


class Projectile
{
public:
	sf::Vector2f position;
	float direction;
	float speed;
	sf::FloatRect projectileBounds;
	bool active;
	

	Projectile(sf::Vector2f pos, float dir, float spe)
	{
		active = true;
		position = pos;
		direction = dir;
		speed = spe;
		bounces = 0;

		timeSinceCreation = sf::Clock();
		deltaTime = sf::Clock();
		animationDeltaTime = sf::Clock();

		frame = sf::IntRect(0, 0, 20, 20);

		projectile.setPosition(position);
		projectile.setRotation(direction);
		projectile.setTextureRect(frame);

		projectileTexture = std::make_shared<sf::Texture>();
		projectileTexture->loadFromFile("Assets\\Projectile.png");

		projectile.setTexture(*projectileTexture);

	}

	sf::Vector2f vectorFromRotation(float rotationDegrees)
	{
		float rotation = rotationDegrees * 3.14159 / 180 - 1.57079632679;
		sf::Vector2f out = sf::Vector2f(cos(rotation), sin(rotation));
		return out;
	}

	void update()
	{
		position += vectorFromRotation(direction) * speed * deltaTime.getElapsedTime().asSeconds();

		if (timeSinceCreation.getElapsedTime().asSeconds() > 5 or bounces > 2)
		{
			active = false;
		}
		if (animationDeltaTime.getElapsedTime().asMilliseconds() > 50)
		{
			if (frame.left > 20)
			{
				frame.left = 0;
			}
			else
			{
				frame.left += 20;
			}
			projectile.setTextureRect(frame);
			animationDeltaTime.restart();
		}

		deltaTime.restart();
	}

private:
	std::shared_ptr<sf::Texture> projectileTexture;
	sf::Sprite projectile;

	int bounces;

	sf::Clock timeSinceCreation;
	sf::Clock animationDeltaTime;
	sf::Clock deltaTime;

	sf::IntRect frame;
};