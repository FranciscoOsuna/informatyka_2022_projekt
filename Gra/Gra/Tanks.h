#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "raycasting.h"

class Projectile
{
public:
	sf::Vector2f position;
	float direction;
	float speed;
	sf::FloatRect projectileBounds;
	bool active;
	sf::Sprite projectile;
	int bounces = 0;


	Projectile(sf::Vector2f pos, float dir, float spe)
	{
		active = true;
		position = pos;
		direction = dir;
		speed = spe;

		timeSinceCreation = sf::Clock();
		deltaTime = sf::Clock();
		animationDeltaTime = sf::Clock();

		frame = sf::IntRect(0, 0, 20, 20);

		projectileTexture = std::make_shared<sf::Texture>();
		projectileTexture->loadFromFile("Assets\\Projectile.png");

		projectile.setTexture(*projectileTexture);

		projectile.setPosition(position);
		projectile.setRotation(direction);
		projectile.setTextureRect(frame);

	}

	sf::Vector2f vectorFromRotation(float rotationDegrees)
	{
		float rotation = rotationDegrees * 3.14159 / 180 - 1.57079632679;
		sf::Vector2f out = sf::Vector2f(cos(rotation), sin(rotation));
		return out;
	}


	int collisionTypeDetection(const sf::FloatRect object)
	{
		// Get the bounds of the projectile
		sf::FloatRect projectileBounds = projectile.getGlobalBounds();

		// Check if the projectile intersects the object
		if (projectileBounds.intersects(object))
		{
			// Get the position of the projectile
			sf::Vector2f projectilePos = projectile.getPosition();

			// Calculate the top and bottom of the object
			float objectTop = object.top;
			float objectBottom = object.top + object.height;

			// Check if the projectile is above the top or below the bottom of the object
			if (projectilePos.y < objectTop || projectilePos.y > objectBottom)
			{
				return 2;
			}

			// Calculate the left and right sides of the object
			float objectLeft = object.left;
			float objectRight = object.left + object.width;

			// Check if the projectile is to the left of the left side or to the right of the right side of the object
			if (projectilePos.x < objectLeft || projectilePos.x > objectRight)
			{
				return 1;
			}
		}

		// If the projectile is not intersecting the object, return 0
		return 0;
	}


	void bounce(bool isVerticalCollision)
	{
		bounces += 1;
		if (isVerticalCollision)
		{
			direction = -direction;
		}
		else
		{
			direction = 180 - direction;
		}
	}

	void update()
	{
		position += vectorFromRotation(direction) * speed * 200.f * deltaTime.getElapsedTime().asSeconds();
		projectile.setPosition(position);
		projectileBounds = projectile.getGlobalBounds();

		if (timeSinceCreation.getElapsedTime().asSeconds() > 5 || bounces>2)
		{
			active = false;
		}
		if (animationDeltaTime.getElapsedTime().asMilliseconds() > 100)
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

	void draw(sf::RenderWindow& window)
	{
		window.draw(projectile);
	}

private:
	std::shared_ptr<sf::Texture> projectileTexture;


	sf::Clock timeSinceCreation;
	sf::Clock animationDeltaTime;
	sf::Clock deltaTime;

	sf::IntRect frame;
};

class Tanks
{
public:
	float speed = 0.1;

	sf::RectangleShape bodyRect;
	sf::RectangleShape gunRect;
	sf::CircleShape gunCircle;
	float sizeMultiplier;

	std::vector<Projectile> projectiles;

	Tanks(sf::Vector2f position, float orient = 0,
		float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan,
		sf::Color color2 = sf::Color::Blue)
	{
		sizeMultiplier = sizeMult;
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

	void changeColors(sf::Color color1, sf::Color color2)
	{
		bodyRect.setFillColor(color1);
		gunRect.setFillColor(color2);
		gunCircle.setFillColor(color2);
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

	void shoot(float speed)
	{
		float gunRotationRadians = gunRect.getRotation() * 3.14159 / 180 +(3.14159/2);
		sf::Vector2f endOfGun =
			giveBodyPosition() +
			sf::Vector2f(cos(gunRotationRadians + 1.571), sin(gunRotationRadians + 1.571)) 
			* float(- 10.5) *sizeMultiplier +
			sf::Vector2f(cos(gunRotationRadians), sin(gunRotationRadians)) *
			bodyRect.getSize().y * float(1.05);

		Projectile projectile(endOfGun, gunRect.getRotation()+180, speed);
		projectile.projectile.setScale(float(sizeMultiplier), float(sizeMultiplier));
		projectiles.push_back(projectile);
	}


};


class Enemy : public Tanks
{
public:
	sf::Clock timeSinceShot;
	float reloadTime;
	sf::Vector2f enemyPosition;

	Enemy(sf::Vector2f position, float orient = 0, float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan, sf::Color color2 = sf::Color::Blue)
		: Tanks(position, orient, sizeMult, color1, color2) 
	{
		timeSinceShot = sf::Clock();
		reloadTime = (1.2 * sizeMult);
		enemyPosition = position;
	}

	void fixTurretOn(Tanks target)
	{
		float orient = rotationFromVectorDifference(gunCircle.getPosition(), target.giveBodyPosition());
		gunRect.setRotation(orient);
	}

	void drawAndShoot(sf::RenderWindow& window, bool canShoot)
	{
		Tanks::draw(window);
		if (timeSinceShot.getElapsedTime().asSeconds() > reloadTime && canShoot)
		{
			shoot(sizeMultiplier);
			timeSinceShot.restart();
		}
	}
};


class Player : public Tanks
{
public:
	sf::Clock timeSinceShot;
	sf::Vector2f originalPosition;
	float sizeMultiplier;
	sf::CircleShape playerCircle;
	sf::FloatRect playerBounds;
	sf::RectangleShape playerBoundsRect;
	float reloadTime;

	Player(sf::Vector2f position, float orient = 0, float sizeMult = 1,
		sf::Color color1 = sf::Color::Cyan, sf::Color color2 = sf::Color::Blue)
		: Tanks(position, orient, sizeMult, color1, color2)
	{
		timeSinceShot = sf::Clock();
		sizeMultiplier = sizeMult;
		playerCircle.setRadius(25 * sizeMultiplier);
		playerCircle.setOrigin(sf::Vector2f(25 * sizeMultiplier, 25 * sizeMultiplier));
		reloadTime = 0.5;
	}

	void turretControl(sf::RenderWindow& window)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		float orient = rotationFromVectorDifference(gunCircle.getPosition(), mousePos);
		gunRect.setRotation(orient);
	}

	void drawPlayer(sf::RenderWindow& window, bool devMode)
	{
		playerCircle.setPosition(bodyRect.getPosition());
		playerBoundsRect = sf::RectangleShape(sf::Vector2f(playerBounds.width, playerBounds.height));
		playerBoundsRect.setPosition(playerBounds.left, playerBounds.top);
		turretControl(window);
		if (devMode)
		{
			window.draw(playerBoundsRect);
		}
		Tanks::draw(window);
	}

	bool detectCollision(std::vector<sf::FloatRect>& Bounds)
	{
		playerCircle.setPosition(bodyRect.getPosition());
		playerBounds = playerCircle.getGlobalBounds();

		for (int i = 0; i < Bounds.size(); i++)
		{
			if (playerBounds.intersects(Bounds[i]))
			{
				return true;
			}
		}
		return false;
	}

	void manageMovement(sf::Time deltaTime, std::vector<sf::FloatRect>& wallBounds, bool reloadCheat)
	{
		originalPosition = bodyRect.getPosition();
		
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

			if (detectCollision(wallBounds))
			{
				bodyRect.setPosition(originalPosition);
				gunCircle.setPosition(originalPosition);
				gunRect.setPosition(originalPosition);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sf::Vector2f movementVector = -vectorFromRotation(bodyRect);
			gunCircle.move(speed * deltaTime.asMilliseconds() * movementVector);
			bodyRect.move(speed * deltaTime.asMilliseconds() * movementVector);
			gunRect.move(speed * deltaTime.asMilliseconds() * movementVector);

			if (detectCollision(wallBounds))
			{
				bodyRect.setPosition(originalPosition);
				gunCircle.setPosition(originalPosition);
				gunRect.setPosition(originalPosition);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			bodyRect.rotate(-speed * deltaTime.asMilliseconds() * 1.2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			bodyRect.rotate(speed * deltaTime.asMilliseconds() * 1.2);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
			&& timeSinceShot.getElapsedTime().asSeconds() > reloadTime)
		{
			if (reloadCheat)
			{
				reloadTime = 0;
			}
			else
			{
				reloadTime = 0.5;
			}
			shoot(sizeMultiplier);
			timeSinceShot.restart();
		}

	}

};