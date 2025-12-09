#include <SFML/Graphics.hpp>
#include "Physics.h"
#pragma once

class JuvenileButterfly
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};

private:
	b2Body* body{};
	FixtureData fixtureData{};
	float jumpPower = 60.0f;
};
