#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Tanks
{
public:
	float speed = 0.1;

	sf::RectangleShape bodyRect;
	sf::RectangleShape gunRect;
	sf::CircleShape gunCircle;

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
		gunCircle.setOrigin(size.x / 3, size.y / 6);
		gunCircle.setPosition(position);
		gunCircle.setFillColor(color2);
		gunCircle.setOutlineColor(sf::Color::Black);
		gunCircle.setOutlineThickness(2);
		gunCircle.setRotation(orient);

	}
	sf::Vector2f giveBodyPosition()
	{
		return bodyRect.getPosition();
	}


	float rotationFromVectorDifference(sf::Vector2f v1, sf::Vector2f v2)
	{
		float angle = (atan2((v2.y - v1.y), (v2.x - v1.x)) * 180 / 3.14159) - 90;
		return angle;
	}

	sf::Vector2f vectorFromRotation(sf::RectangleShape& body) // Returns a vector according to body orientation
	{
		float rotation = body.getRotation() * 3.14159 / 180 - 1.57079632679;
		sf::Vector2f out = sf::Vector2f(cos(rotation), sin(rotation));
		return out;
	}

	virtual void draw(sf::RenderWindow& window)
	{
		// Draw the shapes to the window in the desired order
		window.draw(bodyRect);
		window.draw(gunRect);
		window.draw(gunCircle);
	}


};


class Enemy : public Tanks
{
public:

	Enemy(sf::Vector2f position, float orient = 0, float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan, sf::Color color2 = sf::Color::Blue)
		: Tanks(position, orient, sizeMult, color1, color2) {}

	void fixTurretOn(Tanks target)
	{
		float orient = rotationFromVectorDifference(gunCircle.getPosition(), target.giveBodyPosition());
		gunRect.setRotation(orient);
	}

	void draw(sf::RenderWindow& window) override
	{
		Tanks::draw(window);
	}
};


class Player : public Tanks
{
public:
	Player(sf::Vector2f position, float orient = 0, float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan, sf::Color color2 = sf::Color::Blue)
		: Tanks(position, orient, sizeMult, color1, color2) {}

	void turretControl(sf::RenderWindow& window)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		float orient = rotationFromVectorDifference(gunCircle.getPosition(), mousePos);
		gunRect.setRotation(orient);
	}

	void draw(sf::RenderWindow& window) override
	{
		turretControl(window);

		Tanks::draw(window);
	}


	void manageMovement(sf::Time deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			speed = 0.1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			speed = 0.2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sf::Vector2f movementVector = vectorFromRotation(bodyRect);
			gunCircle.move(speed * deltaTime.asMilliseconds() * movementVector);
			bodyRect.move(speed * deltaTime.asMilliseconds() * movementVector);
			gunRect.move(speed * deltaTime.asMilliseconds() * movementVector);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sf::Vector2f movementVector = -vectorFromRotation(bodyRect);
			gunCircle.move(speed * deltaTime.asMilliseconds() * movementVector);
			bodyRect.move(speed * deltaTime.asMilliseconds() * movementVector);
			gunRect.move(speed * deltaTime.asMilliseconds() * movementVector);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			bodyRect.rotate(-speed * deltaTime.asMilliseconds() * 1.2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			bodyRect.rotate(speed * deltaTime.asMilliseconds() * 1.2);
		}
	}

};