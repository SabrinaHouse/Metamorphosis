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

JuvenileButterfly butterfly;
Bush bush;

std::vector<int> map = { 0 , 1 , 2 , 0 , 1 , 2 };

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

		//change where the bush is based on the layout vector
		//make switch case if ur bored one day
		switch (map[i]) {
		case 0:
			bush.position.y = bottomEdge;
			bush.Begin();
			break;
		case 1:
			bush.position.y = bottomEdge + 35;
			bush.Begin();
			break;
		case 2:
			bush.position.y = bottomEdge - 25;
			bush.Begin();
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
}

void Level3::Render(Renderer& renderer) {
	renderer.Draw(Resources::textures["Sky.png"], sf::Vector2f(butterfly.position.x , 0) , sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));
	butterfly.Draw(renderer);

	for (int i = 0; i < map.size(); i++)
	{

		//move further out each section
		bush.position.x = (200 * i) + 150;

		//change where the bush is based on the layout vector
		switch (map[i]) {
		case 0:
			bush.position.y = bottomEdge;
			bush.Draw(renderer);
			break;
		case 1:
			bush.position.y = bottomEdge + 35;
			bush.Draw(renderer); 
			break;
		case 2:
			bush.position.y = bottomEdge - 25;
			bush.Draw(renderer);
			break;
		}
	}

	Physics::DebugDraw(renderer);
}