#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"


class Leaf
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

private:
	b2Body* body;
};

