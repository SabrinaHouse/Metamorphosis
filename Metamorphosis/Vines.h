#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Vines
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

private:
	b2Body* body{};
};

