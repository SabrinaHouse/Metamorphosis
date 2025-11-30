#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Chrysalis
	: public ContactListener
{

public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	//inherited from contact listener
	virtual void OnBeginContact(b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* other) override;

	void Reset();

	sf::Vector2f startPosition{};
	sf::Vector2f position{};
	bool hitBranch;

private:
	FixtureData fixtureData{};

	b2Body* body;
	float movementSpeed = 40;
};

