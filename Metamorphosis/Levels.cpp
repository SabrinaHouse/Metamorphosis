#include "Levels.h"
#include <iostream>

int currentLevel = 2;
int maxLevel = 4;

void ChangeLevels() {
	currentLevel = (currentLevel + 1) % maxLevel;
}

int CurrentLevel() {
	//std::cout << currentLevel << std::endl;
	return currentLevel;
}
