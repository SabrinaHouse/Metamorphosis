#include "Level2.h"
#include "Camera.h"
#include "Branch.h"
#include "Twig.h"
#include "Resources.h"
#include "Renderer.h"
#include "Chrysalis.h"
#include "Physics.h"
#include <iostream>

Chrysalis chrysalis;
Branch branch;
Twig twig;
int numOfBranches = 6;

int rightEdge;
int leftEdge;

void Level2::Begin(const sf::Window& window) {
	camera->position = sf::Vector2f(0, 0);
	
	for (auto& file : std::filesystem::directory_iterator("./Resources/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png") {
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	sf::View view = camera->getView(window.getSize());

	leftEdge = (view.getCenter().x - (view.getSize().x / 2.0)) + 25;
	rightEdge = (view.getCenter().x + (view.getSize().x / 2.0)) - 25;

	chrysalis.Begin();

	for (int i = 0; i < numOfBranches; i++)
	{

		//move further down each branch
		branch.position.y = 20 * i;
		twig.position.y = 20 * i;

		//alternate sides (branches and twigs are opposite from each other)
		if (i % 2 == 0) {
			branch.position.x = leftEdge;
			twig.position.x = rightEdge;

		}
		else {
			branch.position.x = rightEdge;
			twig.position.x = leftEdge;
		}
		
		branch.Begin();
		twig.Begin();
	}
}
void Level2::Update(float deltaTime) {
	Physics::Update(deltaTime);
	chrysalis.Update(deltaTime);
	camera->position = chrysalis.position;
}

void Level2::Render(Renderer& renderer) {
	chrysalis.Draw(renderer);
	for (int i = 0; i < numOfBranches; i++)
	{

		//move further down each branch
		branch.position.y = 20 * i;
		twig.position.y = 20 * i;

		//alternate sides
		if (i % 2 == 0) {
			branch.position.x = leftEdge;
			twig.position.x = rightEdge;
		}
		else {
			branch.position.x = rightEdge;
			twig.position.x = leftEdge;
		}

		branch.Draw(renderer);
		twig.Draw(renderer);
		branch.leftSide = !branch.leftSide;
		twig.leftSide = !twig.leftSide;

		//std::cout << "Branch Dawn" << std::endl;
		//std::cout << std::to_string(branch.position.x) << ", " << std::to_string(branch.position.y) << std::endl;
	}

	Physics::DebugDraw(renderer);
}
