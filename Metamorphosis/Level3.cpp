#include "Level3.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>
#include <vector>

#include "JuvenileButterfly.h"
#include "Bush.h"
#include "Vines.h"
#include "Flower.h"

JuvenileButterfly butterfly;
Bush bush;
Vines vine;
Flower flower;

sf::Clock cutsceneClock_3;

/*
MAP KEY:
0 = Center
1 = Low
2 = High
3 = Finish
*/

std::vector<int> map = { 0 , 1 , 2, 1 , 0 , 0, 1, 2, 2, 0, 1, 3};
// test map
//std::vector<int> map = { 0 , 1 , 2, 3};

float bottomEdge;
float topEdge;

void Level3::Restart() {
	//reset all variables that change during the game
	cutsceneClock_3.restart();

	stageComplete = false;
	playerDied = false;

	//find the edges of the screen relative to the camera
	bottomEdge = (camera->getViewSize().y / 2);
	topEdge =  -(camera->getViewSize().y / 2);

	Physics::Init();
	butterfly.position = sf::Vector2f(0, 0);
	butterfly.collided = false;
	butterfly.onFlower = false;
	butterfly.Begin();

	camera->position = sf::Vector2f(0, 0);

	for (int i = 0; i < map.size(); i++)
	{

		//move further out each section
		bush.position.x = (200 * i) + 150;
		vine.position.x = (200 * i) + 150;


		//change where the bush is based on the layout vector
		switch (map[i]) {
		case 0:
			//middle
			bush.position.y = bottomEdge - 5;
			bush.Begin();
			vine.position.y = topEdge + 5;
			vine.Begin();
			break;
		case 1:
			//low
			bush.position.y = bottomEdge + 20;
			bush.Begin();
			vine.position.y = topEdge + 30;
			vine.Begin();
			break;
		case 2:
			//high
			bush.position.y = bottomEdge - 30;
			bush.Begin();
			vine.position.y = topEdge - 20;
			vine.Begin();
			break;
		case 3:
			//win
			flower.position.x = (200 * i) + 150;
			flower.position.y = bottomEdge;
			flower.Begin();
			break;
		}

	}
}

void Level3::Begin(const sf::Window& window) {
	
	Restart();
}

void Level3::Update(float deltaTime) {
	//do not update game if in a cutscene
	if (cutsceneClock_3.getElapsedTime().asSeconds() > 3.1) {
		Physics::Update(deltaTime);
		butterfly.Update(deltaTime);

		//playerr dies if they hit a bush or vine OR if they go off screen
		if (butterfly.collided) {
			playerDied = true;
		}
		if (butterfly.position.y > bottomEdge || butterfly.position.y < topEdge) {
			playerDied = true;
		}
		//player wins when they land on flower
		if (butterfly.onFlower)
		{
			cutsceneClock_3.restart();
		}
	}
	
	//make the camera stop moving with the player when they reach the end
	if (butterfly.position.x < flower.position.x - 100) {
		camera->position.x = butterfly.position.x;
	}

}

void Level3::Render(Renderer& renderer) {
	//draw cutscene
	if (cutsceneClock_3.getElapsedTime().asSeconds() < 3 && !butterfly.onFlower) {
		renderer.Draw(Resources::textures["Lvl3_Begin.png"], butterfly.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (butterfly.onFlower && cutsceneClock_3.getElapsedTime().asSeconds() < 3) {
		camera->position = butterfly.position;
		renderer.Draw(Resources::textures["Lvl3_End.png"], butterfly.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (butterfly.onFlower && cutsceneClock_3.getElapsedTime().asSeconds() >= 3) {
		//win once cutscene has played
		stageComplete = true;
		cutsceneClock_3.stop();
	}
	//draw game if not in cutscene
	else {
		//make the sky stop moving when the camera does
		float skyPositionX;
		if (butterfly.position.x < flower.position.x - 100) {
			skyPositionX = butterfly.position.x;
		}
		else {
			skyPositionX = flower.position.x - 100;
		}

		renderer.Draw(Resources::textures["Sky.png"], sf::Vector2f(skyPositionX, 0), sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));

		for (int i = 0; i < map.size(); i++)
		{

			//move further out each section
			bush.position.x = (200 * i) + 150;
			vine.position.x = (200 * i) + 150;

			//change where the bush is based on the layout vector
			switch (map[i]) {
			case 0:
				//middle
				bush.position.y = bottomEdge - 5;
				bush.Draw(renderer);
				vine.position.y = topEdge + 5;
				vine.Draw(renderer);
				break;
			case 1:
				//low
				bush.position.y = bottomEdge + 20;
				bush.Draw(renderer);
				vine.position.y = topEdge + 30;
				vine.Draw(renderer);
				break;
			case 2:
				//high
				bush.position.y = bottomEdge - 30;
				bush.Draw(renderer);
				vine.position.y = topEdge - 20;
				vine.Draw(renderer);
				break;
			case 3:
				//win
				flower.position.x = (200 * i) + 150;
				flower.position.y = bottomEdge;
				flower.Draw(renderer);
				break;
			}

			butterfly.Draw(renderer);

		}

		//draw hitboxes if enabled
		Physics::DebugDraw(renderer);
	}
}