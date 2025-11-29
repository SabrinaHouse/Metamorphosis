#include "Game.h"
#include "Physics.h"
#include <iostream>

Camera camera(110.0f);
Levels levels;

Level1 level1(camera);
Level2 level2(camera);


void Begin(const sf::Window& window)
{
	switch (levels.ReturnLevel()) {
	case 0:
		//level1.Begin(window);
		//break;
	case 1:
		level2.Begin(window);
		break;
	}

}

void Update(float deltaTime)
{
	//std::cout << currentLevel << std::endl;
	switch (levels.ReturnLevel()) {
	case 0:
		//level1.Update(deltaTime);
		//break;
	case 1:
		level2.Update(deltaTime);
		break;
	}
}
void Render(Renderer& renderer)
{
	switch (levels.ReturnLevel()) {
	case 0:
		//level1.Render(renderer);
		//break;
	case 1:
		level2.Render(renderer);
		break;
	}
}
