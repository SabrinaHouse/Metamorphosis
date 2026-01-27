#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"

class Mantis
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	bool LeftToRight;

private:
	b2Body* body;
};


