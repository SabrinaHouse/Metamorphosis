#include "Level1.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>
#include <vector>

#include "Caterpillar.h"
#include "Leaf.h"
#include "Mantis.h"
#include "Boarder.h"

Caterpillar caterpillar;
Leaf* leaf;
Mantis* mantis;
Boarder* boarder;

std::vector<Leaf*> leaves;
std::vector<Mantis*> mantises;
std::vector<Boarder*> boarders;

int coinFlip;

/*
MAP KEY
0 = empty space
1 = Player
2 = Leaf
3 = Left/Right moving Mantis
4 = Up/Down moving Mantis
5 = top/bottom boarder
6 = side boarder
7 = corner boarder
*/

/*
* std::vector<std::vector<int>> 
map = {
	{7, 5, 5, 5, 5, 5, 7},
	{6, 2, 0, 3, 0, 2, 6},
	{6, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 1, 0, 0, 6},
	{6, 0, 0, 0, 4, 0, 6},
	{6, 2, 0, 3, 0, 2, 6},
	{7, 5, 5, 5, 5, 5, 7}
};
*/

std::vector<std::vector<int>>
map = {
	{7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
	{6, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 6},
	{6, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, 6},
	{6, 4, 0, 0, 0, 0, 2, 0, 3, 4, 0, 6},
	{6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6},
	{6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 4, 0, 0, 0, 4, 3, 0, 0, 6},
	{6, 0, 2, 0, 0, 0, 0, 0, 0, 2, 4, 6},
	{6, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 6},
	{6, 2, 0, 0, 0, 0, 0, 3, 2, 0, 0, 6},
	{10, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,9}
};


void Level1::CreateMap(std::vector<std::vector<int>> map) {
	//How far away each item will be from each other
	int distance = 50;

	for (int i = 0; i < map.size(); i++) {

		for (int j = 0; j < map[i].size(); j++) {
			switch (map[i][j]) {
			case 0:
				break;

			case 1:
				caterpillar.position = sf::Vector2f(j * distance, i * distance);
				break;

			case 2:
				leaf = new Leaf();
				leaf->position = sf::Vector2f(j * distance, i * distance);
				leaves.push_back(leaf);
				break;

			case 3:
				mantis = new Mantis();

				//randomly decide which direccted the mantis will start moving in
				coinFlip = (rand() % 2);
				if (coinFlip == 1) {
					mantis->flipped = true;
				}

				mantis->LeftToRight = true;
				mantis->position = sf::Vector2f(j * distance, i * distance);
				mantises.push_back(mantis);
				break;

			case 4:
				mantis = new Mantis();

				//randomly decide which direccted the mantis will start moving in
				coinFlip = (rand() % 2);
				if (coinFlip == 1) {
					mantis->flipped = true;
				}

				mantis->LeftToRight = false;
				mantis->position = sf::Vector2f(j * distance, i * distance);
				mantises.push_back(mantis);
				break;
			case 5:
				boarder = new Boarder();
				boarder->typeOfBoarder = 0;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			case 6:
				boarder = new Boarder();
				boarder->typeOfBoarder = 1;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			case 7:
				boarder = new Boarder();
				boarder->typeOfBoarder = 2;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			case 8:
				boarder = new Boarder();
				boarder->typeOfBoarder = 3;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			case 9:
				boarder = new Boarder();
				boarder->typeOfBoarder = 4;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			case 10:
				boarder = new Boarder();
				boarder->typeOfBoarder = 5;
				boarder->position = sf::Vector2f(j * distance, i * distance);
				boarders.push_back(boarder);
				break;
			}
		}

	}
}

void Level1::Restart() {
	stageComplete = false;

	leaves.clear();
	mantises.clear();
	boarders.clear();

	Physics::Init();

	CreateMap(map);
	caterpillar.Begin();

	for (auto& leaf : leaves) {
		leaf->Begin();
	}

	for (auto& mantis : mantises) {
		mantis->Begin();
	}

	for (auto& boarder : boarders) {
		boarder->Begin();
	}
}

void Level1::Begin(const sf::Window& window) {
	Restart();
}

void Level1::Update(float deltaTime) {
	Physics::Update(deltaTime);

	caterpillar.Update(deltaTime);

	for (auto& leaf : leaves) {
		if (leaf->eaten == true) {
			caterpillar.eatenLeaves++;
			DeleteLeaf(leaf);
		}
	}

	for (auto& mantis : mantises) {
		mantis->Update(deltaTime);
	}

	if (caterpillar.hitMantis == true) {
		//ensure mantises and leaves dont stack between deaths
		Restart();
	}

	camera->position = caterpillar.position;
}

void Level1::Render(Renderer& renderer) {
	renderer.Draw(Resources::textures["Dirt.png"], caterpillar.position , sf::Vector2f(camera->getViewSize().x * 1.5, camera->getViewSize().y * 1.5));

	caterpillar.Draw(renderer);

	for (auto& leaf : leaves) {
		leaf->Draw(renderer);
	}

	for (auto& mantis : mantises) {
		mantis->Draw(renderer);
	}

	for (auto& boarder : boarders) {
		boarder->Draw(renderer);
	}

	Physics::DebugDraw(renderer);

	if (caterpillar.eatenLeaves >= 10) {
		stageComplete = true;
	}

	//draw the progress bar corresponding to the amount of leaves eaten
	switch (caterpillar.eatenLeaves) {
	case 0:
		renderer.Draw(Resources::textures["ProgressBar0.png"], 
			{caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f)}, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 1:
		renderer.Draw(Resources::textures["ProgressBar1.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 2:
		renderer.Draw(Resources::textures["ProgressBar2.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 3:
		renderer.Draw(Resources::textures["ProgressBar3.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 4:
		renderer.Draw(Resources::textures["ProgressBar4.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 5:
		renderer.Draw(Resources::textures["ProgressBar5.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 6:
		renderer.Draw(Resources::textures["ProgressBar6.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 7:
		renderer.Draw(Resources::textures["ProgressBar7.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 8:
		renderer.Draw(Resources::textures["ProgressBar8.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 9:
		renderer.Draw(Resources::textures["ProgressBar9.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	case 10:
		renderer.Draw(Resources::textures["ProgressBar10.png"],
			{ caterpillar.position.x, (caterpillar.position.y - camera->getViewSize().y / 2.2f) }, sf::Vector2f(camera->getViewSize().x * .75, 10));
		break;
	}
}

void DeleteLeaf(Leaf* leaf) {
	const auto& it = std::find(leaves.begin(), leaves.end(), leaf);
	if (it != leaves.end()) {
		delete *it;
		leaves.erase(it);
	}
}

