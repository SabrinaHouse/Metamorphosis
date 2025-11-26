#include "Game.h"
#include "Camera.h"
#include "Branch.h"
#include "Resources.h"
#include "Renderer.h"
#include "Chrysalis.h"
#include "Physics.h"
#include <iostream>

Chrysalis chrysalis;
Camera camera(100.0f);
Branch branch;
int numOfBranches = 6;

int rightEdge;
int leftEdge;

void Begin(const sf::Window& window) {

	for (auto& file : std::filesystem::directory_iterator("./Resources/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png") {
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	sf::View view = camera.getView(window.getSize());

	leftEdge = (view.getCenter().x - (view.getSize().x / 2.0)) + 25;
	rightEdge = (view.getCenter().x + (view.getSize().x / 2.0)) - 25;

	chrysalis.Begin();

	for (int i = 0; i < numOfBranches; i++)
	{

		//move further down each branch
		branch.position.y = 20 * i;

		//alternate sides
		if (i % 2 == 0) {
			branch.position.x = leftEdge;
		}
		else {
			branch.position.x = rightEdge;
		}
		
		branch.Begin();
		branch.leftSide = !branch.leftSide;

		std::cout << "Branch Spawned" << std::endl;
		std::cout << std::to_string(branch.position.x) << ", " << std::to_string(branch.position.y) << std::endl;
	}
}
void Update(float deltaTime) {
	Physics::Update(deltaTime);
	chrysalis.Update(deltaTime);
	camera.position = chrysalis.position;

}
void Render(Renderer& renderer, const sf::Window& window) {
	chrysalis.Draw(renderer);
	for (int i = 0; i < numOfBranches; i++)
	{

		//move further down each branch
		branch.position.y = 20 * i;

		//alternate sides
		sf::View view = camera.getView(window.getSize());
		if (i % 2 == 0) {
			branch.position.x = leftEdge;
		}
		else {
			branch.position.x = rightEdge;
		}

		branch.Draw(renderer);
		branch.leftSide = !branch.leftSide;

		//std::cout << "Branch Dawn" << std::endl;
		//std::cout << std::to_string(branch.position.x) << ", " << std::to_string(branch.position.y) << std::endl;
	}

	Physics::DebugDraw(renderer);
}
