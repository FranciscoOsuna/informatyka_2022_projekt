#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Header.h"
#include "Tanks.h"
#include "Walls.h"
#include "LevelManager.h"

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
    sf::RectangleShape backgroundSquare;

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

class Button
{
public:
    sf::FloatRect buttonBounds;

    Button(sf::Vector2f position, sf::Vector2f size, sf::String content)
    {
        buttonColor = sf::Color(244, 185, 184);
        textColor = sf::Color(136, 123, 176);

        buttonSize = size;
        buttonPosition = position;

        buttonRect.setSize(size);
        buttonRect.setOrigin(size / 2.f);
        buttonRect.setPosition(position);
        buttonRect.setFillColor(buttonColor);
        
        buttonBounds = buttonRect.getGlobalBounds();

        font.loadFromFile("Assets\\font.otf");

        buttonText = sf::Text(content, font, 50);
        buttonText.setFillColor(sf::Color(textColor));

        buttonTextBounds = buttonText.getGlobalBounds();

        buttonText.setOrigin(buttonTextBounds.width/2.0, buttonTextBounds.height/2.0);
        buttonText.setPosition(sf::Vector2f(buttonRect.getPosition().x, buttonRect.getPosition().y - 10.f));
    }

    bool manage(sf::RenderWindow& window)
    {
        bool clicked = false;
        window.draw(buttonRect);
        window.draw(buttonText);
        sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));
        if (buttonBounds.contains(mousePosition.x, mousePosition.y))
        {
            enlarge();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                clicked = true;
            }
        }
        else
        {
            normalise();
        }
        return clicked;
    }

    void enlarge()
    {
        buttonRect.setPosition(buttonPosition - sf::Vector2f(2, 2));
        buttonRect.setSize(sf::Vector2f(buttonSize.x + 8, buttonSize.y + 8));
    }

    void normalise()
    {
        buttonRect.setPosition(buttonPosition + sf::Vector2f(3, 3));
        buttonRect.setSize(buttonSize);
    }

private:
    sf::RectangleShape buttonRect;
    sf::Text buttonText;
    sf::Font font;
    sf::FloatRect buttonTextBounds;
    sf::Vector2f buttonSize;
    sf::Vector2f buttonPosition;
    sf::Color buttonColor;
    sf::Color textColor;
};


class Timer 
{
public:

    float time;

    Timer()
    {
        time = 0;

        timerBox.setPointCount(4);
        timerBox.setPoint(0, sf::Vector2f(0, 0));
        timerBox.setPoint(1, sf::Vector2f(200, 0));
        timerBox.setPoint(2, sf::Vector2f(150, 40));
        timerBox.setPoint(3, sf::Vector2f(0, 40));

        timerBox.setFillColor(sf::Color(133, 210, 208));
    }

    sf::Text floatToText(float time)
    {
        // Get the elapsed time as a float value in seconds
        float elapsedTime = time;

        // Round the elapsed time to 3 decimal places
        float roundedTime = roundf(elapsedTime * 1000) / 1000;

        // Convert the rounded time to a string
        std::string timeString = std::to_string(roundedTime).substr(0,5);

        // Get font from file
        font.loadFromFile("Assets\\font.otf");

        // Create a text object with the elapsed time string
        sf::Text text(timeString, font);

        return text;
    }

    void pause()
    {
        if (!isPaused)
        {
            pausedTime = time;
            isPaused = true;
        }
    }

    void resume()
    {
        if (isPaused)
        {
            clock.restart();
            time = pausedTime;
            isPaused = false;
        }
    }


    void manage(sf::RenderWindow& window)
    {
        if (!isPaused) 
        {
            time += clock.getElapsedTime().asSeconds();
        }
        clock.restart();
        timerText = floatToText(time);
        timerText.setPosition(sf::Vector2f(30, 0));
        timerText.setOutlineThickness(1);
        timerText.setOutlineColor(sf::Color::Black);
        window.draw(timerBox);
        window.draw(timerText);
    }


private:
    bool isPaused;
    float pausedTime;
    sf::Clock clock;
    sf::ConvexShape timerBox;
    sf::Text timerText;
    sf::Font font;
};
