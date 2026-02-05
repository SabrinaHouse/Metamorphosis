#include "level4.h"
#include "Butterfly.h"

Butterfly butterfly;

void Level4::Restart() {

}

void Level4::Begin(const sf::Window& window) {
	Physics::Init();

	butterfly.Begin();
}

void Level4::Update(float deltaTime) {

}

void Level4::Render(Renderer& renderer) {
	butterfly.Draw(renderer);
}
