#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Header.h"
#include "Tanks.h"
#include "Walls.h"
#include "LevelManager.h"

class MainMenu 
{
public:

private:
	Tanks MenuTank;

};

class ColorSquare // Creates a 20x20 Rectangle of a given color
{
public:
    sf::FloatRect colorSqBounds;

	ColorSquare(sf::Color color, sf::Vector2f position) 
	{
		size = 50;
        sqPosition = position;
        normalise();
        colorSq.setFillColor(color);
        colorSqBounds = colorSq.getGlobalBounds();
	}

    void enlarge()
    {
        colorSq.setSize(sf::Vector2f(size + 6, size + 6));
        colorSq.setPosition(sqPosition - sf::Vector2f(3, 3));
    }

    void normalise()
    {
        colorSq.setSize(sf::Vector2f(size, size));
        colorSq.setPosition(sqPosition);
    }

	void draw(sf::RenderWindow& window)
	{
		window.draw(colorSq);
	}
private:
    sf::Vector2f sqPosition;
	sf::RectangleShape colorSq;
	int size;
};

class ColorSquareGrid // Creates a 4x4 Grid of ColorSquares
{
public:
    std::vector<ColorSquare> squares;
    sf::Vector2f startingPosition;

    ColorSquareGrid(sf::Vector2f position)
    {
        startingPosition = position;
        int currentColor = 0;
        sf::Vector2f currentPosition = position;

        for (int i = 0; i < 4; i++)  //Rows
        {
            currentPosition.x = startingPosition.x;
            currentPosition.y += 60;

            for (int j = 0; j < 4; j++) // Columns
            {
                currentPosition.x += 60;
                ColorSquare square(colorList[currentColor], currentPosition);
                squares.push_back(square);
                currentColor += 1;
            }
        }
    }

    sf::Color manage(sf::RenderWindow& window, sf::Color oldColor) 
    {
        bool chosen = false;
        int colorChosen = 0;
        for (int i = 0; i < squares.size(); i++)
        {
            sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));
            if (squares[i].colorSqBounds.contains(mousePosition.x, mousePosition.y))
            {
                squares[i].enlarge();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    chosen = true;
                    colorChosen = i;
                }
            }
            else
            {
                squares[i].normalise();
            }
            squares[i].draw(window);
        }
        if (chosen)
        {
            return colorList[colorChosen];
        }
        return oldColor;
    }

private:


    sf::Color colorList[16] =
    {
        sf::Color::Black,
        sf::Color(105,105,105), // DimGray
        sf::Color(220,220,220), // DarkGray
        sf::Color::White,
        
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,

        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color(255, 128, 0),  // Orange
        sf::Color(128, 0, 128),  // Purple

        sf::Color(128, 128, 0),  // Olive
        sf::Color(0, 128, 128),  // Teal
        sf::Color(128, 0, 0),    // Maroon
        sf::Color(0, 0, 128)     // Navy
    };
};