#include "Level3.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>

#include "JuvenileButterfly.h"

JuvenileButterfly butterfly;

void Level3::Begin(const sf::Window& window) {
	Physics::Init();
	butterfly.Begin();
}

void Level3::Update(float deltaTime) {
	Physics::Update(deltaTime);
	butterfly.Update(deltaTime);

	camera->position.x = butterfly.position.x;
}

void Level3::Render(Renderer& renderer) {
	butterfly.Draw(renderer);

	Physics::DebugDraw(renderer);
}