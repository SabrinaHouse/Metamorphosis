#include "Level2.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>
#include <vector>

#include "Branch.h"
#include "Ground.h"
#include "Boarder.h"
#include "Chrysalis.h"

Chrysalis chrysalis;
Branch branch;
Ground ground;
Boarder boarder;

sf::Clock cutsceneClock_2;

/*
BRANCH KEY:
 0 = Branch left 
 1 = Branch right 
 2 = Branch both sides
 3 = Branch far right
 4 = Branch far left
 5 = ground (finish!!)
 */

std::vector<int> layout = { 2 , 2 , 1 , 2 , 3 , 1 , 0 , 4 , 0 , 0 , 2 , 2 , 3 , 0 , 1 , 3 , 0 , 4 , 4 , 2 , 5};
//test layout
//std::vector<int> layout = { 2 , 0, 1, 2, 3, 4 , 5};

int rightEdge;
int leftEdge;

void Level2::Restart() {
	//reset all variables that change during the game
	cutsceneClock_2.restart();

	stageComplete = false;
	playerDied = false;

	Physics::Init(); 

	chrysalis.position = sf::Vector2f(0, 0);
	chrysalis.hitBranch = false;
	chrysalis.hitGround = false;
	chrysalis.Begin();

	//place the branches and boarder 100px away from the player on either side
	leftEdge = (chrysalis.position.x - 100);
	rightEdge = (chrysalis.position.x + 100);

	//make the first boarders
	boarder.position.x = leftEdge - 20;
	boarder.position.y = -150;
	boarder.Begin();

	boarder.position.x = rightEdge + 20;
	boarder.Begin();

	for (int i = 0; i < layout.size(); i++)
	{
		//move further down each branch
		branch.position.y = 150 * i;
		boarder.position.y = 150 * i;

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

		//make the boarder on both sides all the way down
		boarder.position.x = leftEdge - 20;
		boarder.Begin();

		boarder.position.x = rightEdge + 20;
		boarder.Begin();
	}
}

void Level2::Begin(const sf::Window& window) {
	camera->position = sf::Vector2f(0, 0);
	Restart();
}

void Level2::Update(float deltaTime) {
	//do not update game if in a cutscene
	if (cutsceneClock_2.getElapsedTime().asSeconds() > 3.1) {
		Physics::Update(deltaTime);
		chrysalis.Update(deltaTime);

		if (chrysalis.hitBranch) {
			playerDied = true;
		}
		if (chrysalis.hitGround) {
			cutsceneClock_2.restart();
		}
	}
	camera->position = chrysalis.position;
}

void Level2::Render(Renderer& renderer) {
	//draw cutscenes
	if (cutsceneClock_2.getElapsedTime().asSeconds() < 3 && !chrysalis.hitGround) {
		renderer.Draw(Resources::textures["Lvl2_Begin.png"], chrysalis.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (chrysalis.hitGround && cutsceneClock_2.getElapsedTime().asSeconds() < 3) {
		renderer.Draw(Resources::textures["Lvl2_End.png"], chrysalis.position, sf::Vector2f(camera->getViewSize().x, camera->getViewSize().y));
	}
	else if (chrysalis.hitGround && cutsceneClock_2.getElapsedTime().asSeconds() >= 3) {
		//win once cutscene has played
		stageComplete = true;
		cutsceneClock_2.stop();
	}
	//draw game if not in cutscene
	else {
		renderer.Draw(Resources::textures["Sky.png"], chrysalis.position, sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));
		chrysalis.Draw(renderer);

		//make the first boarders
		boarder.position.x = leftEdge - 20;
		boarder.position.y = -150;
		boarder.Draw(renderer);

		boarder.position.x = rightEdge + 20;
		boarder.Draw(renderer);

		for (int i = 0; i < layout.size(); i++)
		{

			//move further down each branch
			branch.position.y = 150 * i;
			boarder.position.y = 150 * i;

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

			boarder.Draw(renderer);

			//draw the ground (finish line!)
			if (layout[i] == 5) {
				ground.position.y = 150 * i;
				ground.Draw(renderer);
			}
		}

		//draw hitboxes if enabled
		Physics::DebugDraw(renderer);
	}
}
