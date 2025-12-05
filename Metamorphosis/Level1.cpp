#include "Level1.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Caterpillar.h"
#include "Physics.h"
#include <iostream>

Caterpillar caterpillar;

void Level1::Begin(const sf::Window& window) {
	Physics::Init();
	camera->position = sf::Vector2f(0, 0);
	caterpillar.Begin();
}
void Level1::Update(float deltaTime) {
	Physics::Update(deltaTime);
	caterpillar.Update(deltaTime);
	camera->position = caterpillar.position;
}

void Level1::Render(Renderer& renderer) {
	caterpillar.Draw(renderer);

	//Physics::DebugDraw(renderer);

}

