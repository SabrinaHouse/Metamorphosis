#include "level4.h"
#include "Butterfly.h"
#include "Eggs.h"

Butterfly butterfly;
Eggs eggs;

void Level4::Restart() {

}

void Level4::Begin(const sf::Window& window) {
	Physics::Init();


	butterfly.position.y = eggs.position.y - 30;
	butterfly.Begin();

	eggs.Begin();
}

void Level4::Update(float deltaTime) {

}

void Level4::Render(Renderer& renderer) {
	butterfly.Draw(renderer);
	eggs.Draw(renderer);
	Physics::DebugDraw(renderer);
}
