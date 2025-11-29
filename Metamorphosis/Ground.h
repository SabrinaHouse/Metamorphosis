#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Ground
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	bool leftSide = false;

private:
	b2Body* body;
};

