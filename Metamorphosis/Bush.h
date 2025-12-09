#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Bush
{
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
};

