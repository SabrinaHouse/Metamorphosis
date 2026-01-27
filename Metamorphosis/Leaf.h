#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Resources.h"


class Leaf
{
public:
	~Leaf();

	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	bool eaten;

private:
	b2Body* body;
};

