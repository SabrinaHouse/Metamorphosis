#pragma once
#include "Renderer.h"
#include "Level1.h"
#include "Level2.h"


void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
void ChangeLevel();

extern Camera camera;
