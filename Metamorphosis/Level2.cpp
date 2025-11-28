#include "Level2.h"
#include "Camera.h"
#include "Branch.h"
#include "Twig.h"
#include "Resources.h"
#include "Renderer.h"
#include "Chrysalis.h"
#include "Physics.h"
#include <iostream>
#include <vector>

Chrysalis chrysalis;
Branch branch;
Twig twig;

//Sets up the layout of the branches and twigs.
// 0 = Branch-Left Twig-Right
// 1 = Branch-Right Twig-Left
std::vector<int> layout = { 0 , 1, 1, 0 , 1 , 1 , 0 , 0 , 1 , 1, 0 , 1, 1, 0 , 1 , 1 , 0 , 0 , 1 , 1 };

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

	leftEdge = (view.getCenter().x - (view.getSize().x / 2.0)) ;
	rightEdge = (view.getCenter().x + (view.getSize().x / 2.0)) ;

	chrysalis.Begin();

	for (int i = 0; i < layout.size(); i++)
	{

		//move further down each branch
		branch.position.y = 30 * i;
		twig.position.y = 30 * i;

		//alternate sides (branches and twigs are opposite from each other)
		if (layout[i] == 0) {
			branch.position.x = leftEdge + 35;
			twig.position.x = rightEdge - 10;

		}
		else if (layout[i] == 1) {
			branch.position.x = rightEdge - 35;
			twig.position.x = leftEdge + 10;
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
	for (int i = 0; i < layout.size(); i++)
	{

		//move further down each branch
		branch.position.y = 30 * i;
		twig.position.y = 30 * i;

		//alternate sides
		if (layout[i] == 0) {
			//ensure the images are loaded in the correct orientatiom
			branch.leftSide = true;
			twig.leftSide = false;
			branch.position.x = leftEdge + 35;
			twig.position.x = rightEdge - 10;
		}
		else if (layout[i] == 1) {
			//ensure the images are loaded in the correct orientatiom
			branch.leftSide = false;
			twig.leftSide = true;
			branch.position.x = rightEdge - 35;
			twig.position.x = leftEdge + 10;
		}

		branch.Draw(renderer);
		twig.Draw(renderer);
	}

	Physics::DebugDraw(renderer);
}
