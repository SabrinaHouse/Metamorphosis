#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Boarder
{
public:
	void Begin();
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

	int typeOfBoarder;
	/*
	decides what type of boarder to draw (only applicable in level 1)

	0 = top/bottom
	1 = side
	2 = corner
	*/

private:
	b2Body* body;
};

