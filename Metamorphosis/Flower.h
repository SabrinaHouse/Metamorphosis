#pragma once
#include "Resources.h"
#include "Physics.h"

class Flower
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

private:
	b2Body* body{};
};

