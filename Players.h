#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Shape {
protected:
	float xPos;
	float zPos;
public:
	Player(float xPos, float yPos, sf::Color color);
};

class RedBoi : public Player {
public:
	RedBoi(float xPos, float yPos);
};

class BlueBoi : public Player {
public:
	BlueBoi(float xPos, float yPos);
};