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

Caterpillar caterpillar;
Leaf* leaf;
Mantis* mantis;

std::vector<Leaf*> leaves;
std::vector<Mantis*> mantises;


/*
MAP KEY
0 = empty space
1 = Player
2 = Leaf
3 = Left/Right moving Mantis
4 = Up/Down moving Mantis
*/

std::vector<std::vector<int>> 
map = {
	{2, 0, 3, 0, 2},
	{0, 0, 0, 0, 0},
	{4, 0, 1, 0, 4},
	{0, 0, 0, 0, 0},
	{2, 0, 3, 0, 2}
};

void Level1::CreateMap(std::vector<std::vector<int>> map) {
	//How far away each item will be from each other
	int distance = 50;

	for (int i = 0; i < map.size(); i++) {

		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == 1) {
				caterpillar.position = sf::Vector2f(j * distance, i * distance);
			}
			else if (map[i][j] == 2) {
				leaf = new Leaf();
				leaf->position = sf::Vector2f(j * distance, i * distance);
				leaves.push_back(leaf);
			}
			else if (map[i][j] == 3) {
				mantis = new Mantis();
				mantis->LeftToRight = true;
				mantis->position = sf::Vector2f(j * distance, i * distance);
				mantises.push_back(mantis);
			}
			else if (map[i][j] == 4) {
				mantis = new Mantis();
				mantis->LeftToRight = false;
				mantis->position = sf::Vector2f(j * distance, i * distance);
				mantises.push_back(mantis);
			}
		}

	}
}


void Level1::Begin(const sf::Window& window) {
	Physics::Init();

	CreateMap(map);
	caterpillar.Begin();

	for (auto& leaf : leaves) {
		leaf->Begin();
	}

	for (auto& mantis : mantises) {
		mantis->Begin();
	}
}
void Level1::Update(float deltaTime) {
	Physics::Update(deltaTime);

	caterpillar.Update(deltaTime);

	for (auto& leaf : leaves) {
		if (leaf->eaten == true) {
			caterpillar.eatenLeaves++;
			std::cout << caterpillar.eatenLeaves << std::endl;
			DeleteLeaf(leaf);
		}
	}

	for (auto& mantis : mantises) {
		mantis->Update(deltaTime);
	}

	camera->position = caterpillar.position;
}

void Level1::Render(Renderer& renderer) {
	caterpillar.Draw(renderer);

	for (auto& leaf : leaves) {
		leaf->Draw(renderer);
	}

	for (auto& mantis : mantises) {
		mantis->Draw(renderer);
	}

	Physics::DebugDraw(renderer);

	if (caterpillar.eatenLeaves >= 10) {
		stageComplete = true;
	}
}

void DeleteLeaf(Leaf* leaf) {
	const auto& it = std::find(leaves.begin(), leaves.end(), leaf);
	if (it != leaves.end()) {
		delete *it;
		leaves.erase(it);
	}
}

