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

class SetUp //performs Start Up functions
{
public:
	SetUp(sf::RenderWindow& window)
	{
		// Load the icon from a file
		icon.loadFromFile("Icon.png");

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
		float rotation = body.getRotation() * 3.14159/180 - 1.57079632679;
		sf::Vector2f out = sf::Vector2f(cos(rotation),sin(rotation));
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
			bodyRect.rotate(-speed * deltaTime.asMilliseconds()*1.2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			bodyRect.rotate(speed * deltaTime.asMilliseconds() * 1.2);
		}
	}

};

class Background
{
public:
	Background()
	{
		backGround.setSize(sf::Vector2f(1600, 800));
		backGroundTexture.loadFromFile("backGround.png");
		backGround.setTexture(&backGroundTexture);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(backGround);
	}

private:
	sf::RectangleShape backGround;
	sf::Texture backGroundTexture;
};

class Wall
{
public:
	Wall(sf::Vector2f size, sf::Vector2f position, float rotation = 0)
	{

		wall.setPosition(position.x+2,position.y+1);
		wall.setTextureRect(sf::IntRect(0, 0, size.x-4, size.y-2));
		wall.setTexture(wallTexture);
		wall.setRotation(rotation);

		wallTexture.loadFromFile("wallTexture.png");
		wallTexture.setRepeated(true);

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
	sf::Sprite wall;
	sf::RectangleShape wallOutline;

};

class Cursor
{
public:
	
	Cursor()
	{
		cursorTexture.loadFromFile("cursor.png");
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
		pauseTexture.loadFromFile("pauseMessage.png");
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
