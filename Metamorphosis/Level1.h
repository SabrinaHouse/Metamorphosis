#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"


class Level1 {
public:
	Level1(Camera& c) {
		camera = &c;
	} 

	void Begin(const sf::Window& window);
	void Update(float deltaTime);
	void Render(Renderer& renderer);

	Camera *camera;

	bool stageComplete = false;
};

