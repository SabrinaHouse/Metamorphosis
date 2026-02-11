#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"

class Wasp
	: public ContactListener
{
public:
	~Wasp();

	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	//inherited from b2draw
	virtual void OnBeginContact(b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* other) override;

	sf::Vector2f position{};
	b2Vec2 startPosition = {0 , 0};

	//whether its moving left and right OR up and down
	bool horizontal = true;
	//where it starts
	bool TopOrLeft = true;

	//find what the wasp hit
	bool hitButterfly = false;
	bool hitEggs = false;

	int movementSpeed = 60;

	sf::Angle angle;

private:
	b2Body* body{};
};



