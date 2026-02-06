#include "level4.h"
#include "Butterfly.h"
#include "Eggs.h"
#include "Wasp.h"
#include <iostream>

Butterfly butterfly;
Eggs eggs;
Wasp* wasp;

std::vector<Wasp*> wasps;

sf::Clock waspClock;

//find the edges of the screen
float32 northEdge;
float32 southEdge;
float32 westEdge;
float32 eastEdge;

//how far away the butterfly will be from the egg
int eggDistance = 25;

//how many total wasps have been spawned
int spawnedWasps = 0;

//how long a was takes to spawn
int waspTime = 2;

/*
WASP ORDER KEY:
0 - Top
1 - Bottom
2 - Left
3 - Right
*/

std::vector<int> waspOrder = { 0 , 1, 2, 3};

void Level4::Restart() {
	Physics::Init();

	spawnedWasps = 0;

	wasps.clear();

	butterfly.location = 3;
	butterfly.angle = 0;

	butterfly.Begin();

	eggs.Begin();
}

void Level4::Begin(const sf::Window& window) {
	Physics::Init();

	sf::View cameraView = camera->getView(window.getSize());

	northEdge =  -camera->getViewSize().y / 2 ;
	southEdge = camera->getViewSize().y / 2;
	westEdge =  -camera->getViewSize().y / 2;
	eastEdge = camera->getViewSize().y / 2;

	Restart();
}

void Level4::Update(float deltaTime) {
	Physics::Update(deltaTime);

	butterfly.Update(deltaTime);

	//change which side the butterfly is protecting based on what key the player pressed
	switch (butterfly.location) {
	case 1:
		butterfly.position.y = 0;
		butterfly.position.x = eggs.position.x + eggDistance;
		break;
	case 2:
		butterfly.position.y = 0;
		butterfly.position.x = eggs.position.x - eggDistance;
		break;
	case 3:
		butterfly.position.x = 0;
		butterfly.position.y = eggs.position.y - eggDistance;
		break;
	case 4:
		butterfly.position.x = 0;
		butterfly.position.y = eggs.position.y + eggDistance;
		break;
	}

	if (waspClock.getElapsedTime().asSeconds() >= waspTime) {
		if (spawnedWasps < waspOrder.size()) {
			wasp = new Wasp();
			switch (waspOrder[spawnedWasps]) {
				//NORTH
			case 0:
				wasp->horizontal = false;
				wasp->TopOrLeft = true;
				wasp->startPosition = { 0 , northEdge };
				break;
				//SOUTH
			case 1:
				wasp->horizontal = false;
				wasp->TopOrLeft = false;
				wasp->startPosition = { 0 , southEdge };
				break;
				//WEST
			case 2:
				wasp->horizontal = true;
				wasp->TopOrLeft = true;
				wasp->startPosition = { westEdge , 0 };
				break;
				//EAST
			case 3:
				wasp->horizontal = true;
				wasp->TopOrLeft = false;
				wasp->startPosition = { eastEdge , 0 };
				break;
			}
			wasps.push_back(wasp);
			wasp->Begin();
			spawnedWasps++;
			waspClock.restart();
		}
		
	}

	for (auto& wasp : wasps) {
		wasp->Update(deltaTime);

		if (wasp->hitButterfly){
			DeleteWasp(wasp);
			std::cout << "wasp despawned" << std::endl;
		}else if (wasp->hitEggs) {
			Restart();
			DeleteWasp(wasp);
			std::cout << "Die" << std::endl;
		}

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

void DeleteWasp(Wasp* wasp) {
	const auto& it = std::find(wasps.begin(), wasps.end(), wasp);
	if (it != wasps.end()) {
		delete* it;
		wasps.erase(it);
	}
}