#include "Game.h"
#include "Physics.h"
#include "Resources.h"
#include <iostream>

Camera camera(200.0f);

Level1 level1(camera);
Level2 level2(camera);
Level3 level3(camera);
Level4 level4(camera);

void Game::Begin(const sf::Window& window)
{

	for (auto& file : std::filesystem::directory_iterator("./Resources/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png") {
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
	switch (CurrentLevel()) {
	case 0:
		LevelComplete = false;
		level1.Begin(window);
		break;
	case 1:
		LevelComplete = false;
		level2.Begin(window);
		break;
	case 2:
		LevelComplete = false;
		level3.Begin(window);
		break;
	case 3:
		LevelComplete = false;
		level4.Begin(window);
		break;
	}

}

void Game::Update(float deltaTime)
{
	//std::cout << currentLevel << std::endl;
	switch (CurrentLevel()) {
	case 0:
		level1.Update(deltaTime);
		if (level1.stageComplete) {
			LevelComplete = true;
		}
		break;
	case 1:
		level2.Update(deltaTime);
		if (level2.stageComplete) {
			LevelComplete = true;
		}
		break;
	case 2:
		level3.Update(deltaTime);
		if (level3.stageComplete) {
			LevelComplete = true;
		}
		break;
	case 3:
		if (level4.stageComplete) {
			LevelComplete = true;
		}
		level4.Update(deltaTime);
		break;
	}
}

void Game::Render(Renderer& renderer)
{
	switch (CurrentLevel()) {
	case 0:
		level1.Render(renderer);
		break;
	case 1:
		level2.Render(renderer);
		break;
	case 2:
		level3.Render(renderer);
		break;
	case 3:
		level4.Render(renderer);
		break;
	}
}
