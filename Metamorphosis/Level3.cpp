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

/*
MAP KEY:
0 = Center
1 = Low
2 = High
3 = Finish
*/

std::vector<int> map = { 0 , 3};

float bottomEdge = butterfly.position.y + 80;
float topEdge = butterfly.position.y - 80;

void Level3::Restart() {
	Physics::Init();
	butterfly.position = sf::Vector2f(0, 0);
	butterfly.collided = false;
	butterfly.Begin();

	camera->position = sf::Vector2f(0, 0);

	for (int i = 0; i < map.size(); i++)
	{

		//move further out each section
		bush.position.x = (200 * i) + 150;
		vine.position.x = (200 * i) + 150;


		//change where the bush is based on the layout vector
		//make switch case if ur bored one day
		switch (map[i]) {
		case 0:
			bush.position.y = bottomEdge + 5;
			bush.Begin();
			vine.position.y = topEdge - 5;
			vine.Begin();
			break;
		case 1:
			bush.position.y = bottomEdge + 30;
			bush.Begin();
			vine.position.y = topEdge + 25;
			vine.Begin();
			break;
		case 2:
			bush.position.y = bottomEdge - 15;
			bush.Begin();
			vine.position.y = topEdge - 20;
			vine.Begin();
			break;
		case 3:
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
	Physics::Update(deltaTime);
	butterfly.Update(deltaTime);
	camera->position.x = butterfly.position.x;

	if (butterfly.collided) {
		Restart();
	}
	if (butterfly.onFlower)
	{
		stageComplete = true;
	}
}

void Level3::Render(Renderer& renderer) {
	renderer.Draw(Resources::textures["Sky.png"], sf::Vector2f(butterfly.position.x , 0) , sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));

	for (int i = 0; i < map.size(); i++)
	{

		//move further out each section
		bush.position.x = (200 * i) + 150;
		vine.position.x = (200 * i) + 150;

		//change where the bush is based on the layout vector
		switch (map[i]) {
		case 0:
			bush.position.y = bottomEdge + 5;
			bush.Draw(renderer);
			vine.position.y = topEdge - 5;
			vine.Draw(renderer);
			break;
		case 1:
			bush.position.y = bottomEdge + 30;
			bush.Draw(renderer); 
			vine.position.y = topEdge + 25;
			vine.Draw(renderer);
			break;
		case 2:
			bush.position.y = bottomEdge - 15;
			bush.Draw(renderer);
			vine.position.y = topEdge - 20;
			vine.Draw(renderer);
			break;
		case 3:
			flower.position.x = (200 * i) + 150;
			flower.position.y = bottomEdge;
			flower.Draw(renderer);
			break;
		}

		butterfly.Draw(renderer);

	}

	Physics::DebugDraw(renderer);
}