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
	butterfly.Update(deltaTime);

	switch (butterfly.location) {
	case 1:
		butterfly.position.y = 0;
		butterfly.position.x = eggs.position.x + 30;
		break;
	case 2:
		butterfly.position.y = 0;
		butterfly.position.x = eggs.position.x - 30;
		break;
	case 3:
		butterfly.position.x = 0;
		butterfly.position.y = eggs.position.y - 30;
		break;
	case 4:
		butterfly.position.x = 0;
		butterfly.position.y = eggs.position.y + 30;
		break;
	}
}

void Level4::Render(Renderer& renderer) {
	butterfly.Draw(renderer);
	eggs.Draw(renderer);
	Physics::DebugDraw(renderer);
}
