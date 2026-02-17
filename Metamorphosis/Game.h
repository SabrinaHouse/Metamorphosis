#pragma once
#include "Renderer.h"
#include "Levels.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

//each level will use the same camera
extern Camera camera;

class Game {
public:
	void Begin(const sf::Window& window);
	void Update(float deltaTime);
	void Render(Renderer& renderer);

	//game states
	bool LevelComplete = false;
	bool playerDead = false;

	//Menu States
	bool inMenu = false;
	bool gameComplete = false;
	bool enterEndScreen = false;
	bool inDeathScreen = false;
	bool enterDeathScreen = false;

	
};
