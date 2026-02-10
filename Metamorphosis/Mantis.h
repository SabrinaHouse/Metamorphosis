#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"
#include "Animation.h"

class Mantis
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	bool LeftToRight;
	bool flipped = false;
	sf::Clock mantisClock;
	sf::Angle angle;

private:
	sf::Texture textureToDraw{};
	b2Body* body;
	int movementSpeed = 60;
	Animation runAnimation;

};


