#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"

class Butterfly
	: public ContactListener
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	//inherited from b2draw
	virtual void OnBeginContact(b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* other) override;

	sf::Vector2f position{};

private:
	b2Body* body{};
	FixtureData fixtureData{};
};

