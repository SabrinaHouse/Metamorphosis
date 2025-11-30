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
	virtual void OnBeginContact() override;
	virtual void OnEndContact() override;

	void Reset();

	sf::Vector2f startPosition{};
	sf::Vector2f position{};
	bool hitBranch = false;

private:
	b2Body* body;
	float movementSpeed = 40;
};

