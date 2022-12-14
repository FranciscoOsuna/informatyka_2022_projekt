/*
Temat projektu: 1. Obiekt sterowany przez użytkownika unika kontaktu z innymi obiektami
pojawiającymi się losowo w scenerii gry. Przykład scenerii: Space Invaders

zakres indywidualny: Gra inspirowana minigierką tanks gry wii play (2006) na nintendo wii.
Gracz gra jako czołg poruszający się po planszy omijając przeszkody oraz pociski, przy
czym strzelając w wrogie czołgi.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>



class Titles //manages title animations
{
	public:
		int i = 0;
		const char* titles[10] = {
			"   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-", "   -TANKS-",
			"   --ANKS-", "   -T-NKS-", "   -TA-KS-", "   -TAN-S-", "   -TANK--"};
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

		bool titleAnim(sf::RenderWindow &window, sf::Clock timer)
		{
			sf::Time elapsedBetweenTitles = timer.getElapsedTime();
			if (elapsedBetweenTitles.asMilliseconds() > 300)
			{
				window.setTitle(nextTitle());
				return 1;
			}
			return 0;
		}
};

class Tanks {
public:
	sf::Vector2f Size;
	sf::Vector2f Position;
	sf::Color Color;
	float Speed;
	float Acceleration;
	float Orientation;

	Tanks(sf::Vector2f position, float speed = 0, float accel = 0, float orient = -90,
		sf::Vector2f size = sf::Vector2f(50,30), sf::Color color = sf::Color::Cyan) 
	{
		Position = position;
		Speed = speed;
		Acceleration = accel;
		Orientation = orient;
		Size = size;
		Color = color;
	}
};

void updateTank(sf::RectangleShape &object, Tanks source)
{
	object.setSize(source.Size);
	object.setFillColor(source.Color);
	object.setPosition(source.Position);
	object.setRotation(source.Orientation);
	object.setOrigin(source.Size.x / 2, source.Size.y / 2);
}

sf::Vector2f moveFromRotation(float rotation) //for movement according to faced direction
{
	sf::Vector2f out = sf::Vector2f (0.01*cos(rotation*3.14159/180), 0.01*sin(rotation * 3.14159 / 180));
	return out;
}



int main()
{
	
	Titles title;
	sf::Clock titleTimer;

	sf::RenderWindow window(sf::VideoMode(1600, 800), "[*]", sf::Style::Close); //create window


	Tanks player(sf::Vector2f(200, 200));
	sf::RectangleShape playersTank(player.Size);
	updateTank(playersTank, player);


	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event)) //Event Loop
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//player movement controls
		{ 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				playersTank.rotate(-0.01);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				playersTank.rotate(0.01);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				playersTank.move(moveFromRotation(playersTank.getRotation()));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				playersTank.move(-moveFromRotation(playersTank.getRotation()));
			}
		}

		window.clear();

		window.draw(playersTank);

		window.display();

		if(title.titleAnim(window, titleTimer)) titleTimer.restart();
	}
	return 0;
}