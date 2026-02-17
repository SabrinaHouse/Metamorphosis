#pragma once
#include "Resources.h"
#include "Physics.h"

class Eggs
{
public:
	void Begin();

	sf::Vector2f position{};

private:
	b2Body* body{};
};

