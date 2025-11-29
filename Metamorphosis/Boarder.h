#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Boarder
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

private:
	b2Body* body;
};

