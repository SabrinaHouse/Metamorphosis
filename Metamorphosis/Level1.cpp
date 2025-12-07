#include "Level1.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>
#include <vector>

#include "Caterpillar.h"
#include "Leaf.h"

Caterpillar caterpillar;
Leaf leaf;

void Level1::Begin(const sf::Window& window) {
	Physics::Init();
	leaf.position = sf::Vector2f(16, 32);
	caterpillar.Begin();
	leaf.Begin();
}
void Level1::Update(float deltaTime) {
	Physics::Update(deltaTime);
	caterpillar.Update(deltaTime);
	leaf.Update(deltaTime);
	camera->position = caterpillar.position;
}

void Level1::Render(Renderer& renderer) {
	caterpillar.Draw(renderer);

	leaf.Draw(renderer);

	Physics::DebugDraw(renderer);

	if (caterpillar.eatenLeaves >= 10) {
		stageComplete = true;
	}
}

