#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Twig
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	bool leftSide = true;

private:
	b2Body* body;
};

