#include "level4.h"
#include "Butterfly.h"
#include "Eggs.h"
#include "Wasp.h"
#include <iostream>

Butterfly butterfly;
Eggs eggs;
Wasp* wasp;

sf::Clock cutsceneClock_4;

std::vector<Wasp*> wasps;

sf::Clock waspClock;

//find the edges of the screen
float32 northEdge;
float32 southEdge;
float32 westEdge;
float32 eastEdge;

//how far away the butterfly will be from the egg
int eggDistance = 25;

//how many total wasps have been spawned / despawned
int spawnedWasps = 0;
int despawnedWasps = 0; 

//how long a was takes to spawn
float waspTime = 2;

//wasp movement speed
int waspSpeed = 60;

/*
WASP ORDER KEY:
0 - Top
1 - Bottom
2 - Left
3 - Right
*/

//std::vector<int> waspOrder = { 0 , 1, 2, 3, 3 , 2, 1, 0, 2, 3, 1, 2, 3, 3, 1, 2, 0, 2, 3, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 1, 3, 0};
std::vector<int> waspOrder = { 0, 2, 1, 3, 0 };

void Level4::Restart() {
	cutsceneClock_4.restart();

	Physics::Init();

	playerDied = false;
	stageComplete = false;

	spawnedWasps = 0;
	despawnedWasps = 0;
	waspTime = 2;
	waspSpeed = 60;

	wasps.clear();

	butterfly.location = 3;
	butterfly.angle = 0;

	butterfly.Begin();
	eggs.position = { 0, 0 };
	eggs.Begin();

	camera->position = { 0, 0 };

}

void Level4::Begin(const sf::Window& window) {
	Physics::Init();

	stageComplete = false;

	sf::View cameraView = camera->getView(window.getSize());

	northEdge =  -camera->getViewSize().y / 2 ;
	southEdge = camera->getViewSize().y / 2;
	westEdge =  -camera->getViewSize().y / 2;
	eastEdge = camera->getViewSize().y / 2;

	Restart();
}

void Level4::Update(float deltaTime) {
	if (cutsceneClock_4.getElapsedTime().asSeconds() > 3.1) {

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

		if (waspClock.getElapsedTime().asSeconds() > waspTime) {
			if (spawnedWasps < waspOrder.size()) {
				wasp = new Wasp();
				switch (waspOrder[spawnedWasps]) {
				case 0: 
					//NORTH
					wasp->horizontal = false;
					wasp->TopOrLeft = true;
					wasp->startPosition = { 0 , northEdge };
					break;
				case 1:
					//SOUTH
					wasp->horizontal = false;
					wasp->TopOrLeft = false;
					wasp->startPosition = { 0 , southEdge };
					break;
				case 2:
					//WEST
					wasp->horizontal = true;
					wasp->TopOrLeft = true;
					wasp->startPosition = { westEdge , 0 };
					break;
				case 3:
					//EAST
					wasp->horizontal = true;
					wasp->TopOrLeft = false;
					wasp->startPosition = { eastEdge , 0 };
					break;
				}

				wasps.push_back(wasp);
				wasp->movementSpeed = waspSpeed;
				wasp->Begin();
				spawnedWasps++;
				waspTime = waspTime - 0.055f;
				waspSpeed = waspSpeed + 5;
				waspClock.restart();
			}

		}

		for (auto& wasp : wasps) {
			wasp->Update(deltaTime);

			//delete wasps marked as hit
			if (wasp->hitButterfly) {
				DeleteWasp(wasp);
				//count how many wasps have passed
				despawnedWasps++;
			}
			else if (wasp->hitEggs) {
				playerDied = true;
			}

		}

		//if you have passed all wasps, you win
		if (despawnedWasps == waspOrder.size()) {
			cutsceneClock_4.restart();
		}
	}
}

void Level4::Render(Renderer& renderer) {
	//draw cutscene
	if (cutsceneClock_4.getElapsedTime().asSeconds() < 3 && despawnedWasps != waspOrder.size()) {
		renderer.Draw(Resources::textures["Lvl4_Begin.png"], eggs.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (despawnedWasps == waspOrder.size() && cutsceneClock_4.getElapsedTime().asSeconds() < 3) {
		renderer.Draw(Resources::textures["Lvl4_End.png"], eggs.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (despawnedWasps == waspOrder.size() && cutsceneClock_4.getElapsedTime().asSeconds() >= 3) {
		//win once cutscene has played
		stageComplete = true;
		cutsceneClock_4.stop();
	}
	//draw game if not in cutscene
	else {
		renderer.Draw(Resources::textures["BackGround.png"], eggs.position, sf::Vector2f(300, 225));

		butterfly.Draw(renderer);
		//eggs.Draw(renderer);

		for (auto& wasp : wasps) {
			wasp->Draw(renderer);
		}

		//add a boarder to make the viewable space a square
		renderer.Draw(Resources::textures["Boarder.png"], sf::Vector2f(-camera->getViewSize().x / 2, 0), sf::Vector2f(150, camera->getViewSize().y));
		renderer.Draw(Resources::textures["Boarder.png"], sf::Vector2f(camera->getViewSize().x / 2, 0), sf::Vector2f(150, camera->getViewSize().y));

		//draw hitboxes
		Physics::DebugDraw(renderer);
	}
}

void DeleteWasp(Wasp* wasp) {
	const auto& it = std::find(wasps.begin(), wasps.end(), wasp);
	if (it != wasps.end()) {
		delete* it;
		wasps.erase(it);
	}
}