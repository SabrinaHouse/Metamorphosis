#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"

class Wasp
{
public:
	~Wasp();

	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	b2Vec2 startPosition = {0 , 0};

	//whether its moving left and right OR up and down
	bool horizontal = true;
	//where it starts
	bool TopOrLeft = true;

private:
	b2Body* body;
	int movementSpeed = 60;
};

void DeleteWasp(Wasp* wasp);

