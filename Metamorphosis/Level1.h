#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"
#include "Leaf.h"


class Level1 {
public:
	Level1(Camera& c) {
		camera = &c;
	} 
	void Restart();
	void Begin(const sf::Window& window);
	void Update(float deltaTime);
	void Render(Renderer& renderer);

	void CreateMap(std::vector<std::vector<int>> map);

	Camera *camera;

	bool stageComplete = false;

};

void DeleteLeaf(Leaf* leaf);

