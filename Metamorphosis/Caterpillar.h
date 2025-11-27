#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Caterpillar
{

public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f startPosition{};
	sf::Vector2f position{};

private:
	b2Body* body;
	float movementSpeed = 20;
};
