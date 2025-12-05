#pragma once
#include "Renderer.h"
#include "Levels.h"
#include "Level1.h"
#include "Level2.h"

extern Camera camera;

class Game {
public:
	void Begin(const sf::Window& window);
	void Update(float deltaTime);
	void Render(Renderer& renderer);

	bool LevelComplete = false;
};
