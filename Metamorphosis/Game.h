#pragma once
#include "Renderer.h"
#include "Levels.h"
#include "Level1.h"
#include "Level2.h"


void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);

extern Camera camera;
extern Levels levels;