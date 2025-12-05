#include "Game.h"
#include "Physics.h"
#include "Resources.h"
#include <iostream>

Camera camera(200.0f);

Level1 level1(camera);
Level2 level2(camera);


void Begin(const sf::Window& window)
{

	for (auto& file : std::filesystem::directory_iterator("./Resources/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png") {
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
	switch (CurrentLevel()) {
	case 0:
		level1.Begin(window);
		break;
	case 1:
		level2.Begin(window);
		break;
	case 2:
		break;
	}

}

void Update(float deltaTime)
{
	//std::cout << currentLevel << std::endl;
	switch (CurrentLevel()) {
	case 0:
		level1.Update(deltaTime);
		break;
	case 1:
		level2.Update(deltaTime);
		break;
	case 2:
		break;
	}
}
void Render(Renderer& renderer)
{
	switch (CurrentLevel()) {
	case 0:
		level1.Render(renderer);
		break;
	case 1:
		level2.Render(renderer);
		break;
	case 2:
		break;
	}
}
