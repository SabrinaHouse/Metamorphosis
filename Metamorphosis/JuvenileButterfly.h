#include <SFML/Graphics.hpp>
#include "Physics.h"
#pragma once

class JuvenileButterfly
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

	bool collided = false;

private:
	b2Body* body{};
	FixtureData fixtureData{};
	float jumpPower = 60.0f;
};
