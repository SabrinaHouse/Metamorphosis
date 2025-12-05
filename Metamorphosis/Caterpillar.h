#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Caterpillar
	: public ContactListener
{

public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	virtual void OnBeginContact(b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* other) override;

	int eatenLeaves;
	sf::Vector2f position{};

private:
	b2Body* body;
	float movementSpeed = 20;
};
