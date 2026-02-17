#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Butterfly
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	b2Vec2 bodyPosition = { position.x, position.y };
	int location = 3; //default position is North

	float32 angle;
	sf::Angle spriteAngle;

private:
	b2Body* body{};
	FixtureData fixtureData{};
};

