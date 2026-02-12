#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"
#include "Wasp.h"
#include "Animation.h"

class Level4
{
public:
	Level4(Camera& c) {
		camera = &c;
	}

	void Restart();
	void Begin(const sf::Window& window);
	void Update(float deltaTime);
	void Render(Renderer& renderer);

	Camera* camera;

	bool stageComplete = false;
	bool playerDied = false;
};

void DeleteWasp(Wasp* wasp);