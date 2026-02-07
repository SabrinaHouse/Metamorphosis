#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Animation.h"


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
	bool hitMantis;
	sf::Vector2f position{};

private:
	sf::Texture textureToDraw{};
	Animation runAnimation;

	b2Body* body;
	float movementSpeed = 80;
};
