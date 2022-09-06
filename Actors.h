#pragma once
#include <SFML/Graphics.hpp>

class Actor : sf::RectangleShape {
protected:
	sf::Vector2f velocity;
public:
	Actor(sf::Vector2f pos);
	Actor(float xPos, float yPos);
public:
	sf::Vector2f getVelocity();
};

class Puck : public Actor {
public:
	Puck(sf::Vector2f pos);
};