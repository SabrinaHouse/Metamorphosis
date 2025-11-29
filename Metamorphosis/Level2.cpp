#include "Level2.h"
#include "Camera.h"
#include "Branch.h"
#include "Ground.h"
#include "Resources.h"
#include "Renderer.h"
#include "Chrysalis.h"
#include "Physics.h"
#include <iostream>
#include <vector>

Chrysalis chrysalis;
Branch branch;
Ground ground;

/*
Sets up the layout of the branches and twigs.
 0 = Branch left 
 1 = Branch right 
 2 = Branch both sides
 3 = Branch far right
 4 = Branch far left
 5 = ground (finish!!)
 */
std::vector<int> layout = { 2 , 2 , 1 , 2 , 3 , 1 , 0 , 4 , 1 , 0 , 0 , 2 , 2 , 3 , 0 , 1 , 3 , 0 , 4 , 4 , 2 , 5};

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
		branch.position.y = 150 * i;

		//change where the branch is based on the layout vector
		if (layout[i] == 0) {
			branch.position.x = leftEdge + 35;
			branch.Begin();
		}
		else if (layout[i] == 1) {
			branch.position.x = rightEdge - 35;
			branch.Begin();
		}
		else if (layout[i] == 2) {
			branch.position.x = rightEdge - 20;
			branch.Begin();
			branch.position.x = leftEdge + 20;
			branch.Begin();
		}
		else if (layout[i] == 3) {
			branch.position.x = rightEdge - 55;
			branch.Begin();
		}
		else if (layout[i] == 4) {
			branch.position.x = leftEdge + 55;
			branch.Begin();
		}
		//make the ground (finish line!)
		else if (layout[i] == 5) {
			ground.position.y = 150 * i;
			ground.Begin();
		}
		
	}
}
void Level2::Update(float deltaTime) {
	Physics::Update(deltaTime);
	chrysalis.Update(deltaTime);
	camera->position = chrysalis.position;
}

void Level2::Render(Renderer& renderer) {

	renderer.Draw(Resources::textures["Sky.png"], chrysalis.position, sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));
	chrysalis.Draw(renderer);

	for (int i = 0; i < layout.size(); i++)
	{

		//move further down each branch
		branch.position.y = 150 * i;

		//alternate sides
		if (layout[i] == 0) {
			//ensure the images are loaded in the correct orientation
			branch.leftSide = true;
			branch.position.x = leftEdge + 35;
			branch.Draw(renderer);
		}
		else if (layout[i] == 1) {
			//ensure the images are loaded in the correct orientation
			branch.leftSide = false;
			branch.position.x = rightEdge - 35;
			branch.Draw(renderer);
		}
		else if (layout[i] == 2) {
			// two branches on different sides
			branch.leftSide = false;
			branch.position.x = rightEdge - 20;
			branch.Draw(renderer);
			branch.leftSide = true;
			branch.position.x = leftEdge + 20;
			branch.Draw(renderer);
		}
		else if (layout[i] == 3) {
			branch.leftSide = false;
			branch.position.x = rightEdge - 55;
			branch.Draw(renderer);
		}
		else if (layout[i] == 4) {
			branch.leftSide = true;
			branch.position.x = leftEdge + 55;
			branch.Draw(renderer);
		}
		//draw the ground (finish line!)
		else if (layout[i] == 5) {
			ground.position.y = 150 * i;
			ground.Draw(renderer);
		}
	}
}
