#include "Game.h"
#include <iostream>

Camera camera(100.0f);

Level1 level1(camera);
Level2 level2(camera);

unsigned int currentLevel = 0;
unsigned int maxLevel = 2;


void Begin(const sf::Window& window)
{
	switch (currentLevel) {
	case 0:
		level1.Begin(window);
		break;
	case 1:
		level2.Begin(window);
		break;
	}

}

void Update(float deltaTime)
{
	std::cout << currentLevel << std::endl;
	switch (currentLevel) {
	case 0:
		level1.Update(deltaTime);
		break;
	case 1:
		level2.Update(deltaTime);
		break;
	}
}
void Render(Renderer& renderer)
{
	switch (currentLevel) {
	case 0:
		level1.Render(renderer);
		break;
	case 1:
		level2.Render(renderer);
		break;
	}
}

void ChangeLevel() {
	currentLevel = (currentLevel + 1) % maxLevel;
}
