#include "level4.h"
#include "Butterfly.h"
#include "Eggs.h"
#include "Wasp.h"
#include <iostream>

Butterfly butterfly;
Eggs eggs;
Wasp* wasp;

std::vector<Wasp*> wasps;

/*
WASP ORDER KEY:
0 - Top
1 - Bottom
2 - Left
3 - Right
*/

std::vector<int> waspOrder = { 0 , 1, 2, 3};

void Level4::Restart() {

}

void Level4::Begin(const sf::Window& window) {
	Physics::Init();
	butterfly.position.y = eggs.position.y - 30;

	butterfly.Begin();

	eggs.Begin();

	for (int i = 0; i < waspOrder.size(); i++) {
		wasp = new Wasp();
		switch (waspOrder[i]) {
		case 0:
			wasp->horizontal = false;
			wasp->TopOrLeft = true;
			break;
		case 1:
			wasp->horizontal = false;
			wasp->TopOrLeft = false;
			break;
		case 2:
			wasp->horizontal = true;
			wasp->TopOrLeft = true;
			break;
		case 3:
			wasp->horizontal = true;
			wasp->TopOrLeft = false;
			break;
		}
		wasps.push_back(wasp);
	}

	for (auto& wasp : wasps) {
		wasp->Begin();
	}
}

void Level4::Update(float deltaTime) {
	Physics::Update(deltaTime);

	butterfly.Update(deltaTime);

	//change which side the butterfly is protecting based on what key the player pressed
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

	for (auto& wasp : wasps) {
		wasp->Update(deltaTime);
	}

}

void Level4::Render(Renderer& renderer) {
	butterfly.Draw(renderer);
	eggs.Draw(renderer);

	for (auto& wasp : wasps) {
		wasp->Draw(renderer);
	}

	Physics::DebugDraw(renderer);
}
