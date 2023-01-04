#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Header.h"
#include "Tanks.h"
#include "Walls.h"


std::vector<Wall> walls;
std::vector<Enemy> enemies;

void readLevelFile(const std::string& fileName) {
    // Open the file for reading
    std::ifstream file(fileName);

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Split the line into tokens, using whitespace as the delimiter
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;
        while (lineStream >> token) {
            tokens.push_back(token);
        }
        // Parse the object type and create an instance of the appropriate class
        if (tokens.size() > 0)
        {
            if (tokens[0] == "Wall") {
            // Parse the necessary parameters for a Wall object and create an instance
            int width = std::stoi(tokens[1]);
            int height = std::stoi(tokens[2]);
            int x = std::stoi(tokens[3]);
            int y = std::stoi(tokens[4]);
            bool isVert = std::stoi(tokens[5]);
            // ...
            Wall wall(sf::Vector2f(width, height), sf::Vector2f(x, y), isVert);
            walls.push_back(wall);
        }
        else if (tokens[0] == "Enemy") {
            // Parse the necessary parameters for an Enemy object and create an instance
            int x = std::stoi(tokens[1]);
            int y = std::stoi(tokens[2]);
            int a = std::stoi(tokens[3]);
            float k = std::stof(tokens[4]);
            float r1 = std::stof(tokens[5]);
            int g1 = std::stoi(tokens[6]);
            int b1 = std::stoi(tokens[7]);
            int r2 = std::stoi(tokens[8]);
            int g2 = std::stoi(tokens[9]);
            int b2 = std::stoi(tokens[10]);
            // ...
            Enemy enemy(sf::Vector2f(x, y), a, k, sf::Color(r1, g1, b1), sf::Color(r2, g2, b2));
            enemies.push_back(enemy);
        }
        }
        
    }
}

void clearLevel() {
    walls.clear();
    enemies.clear();
}