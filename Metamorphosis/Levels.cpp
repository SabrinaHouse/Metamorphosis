#include "Levels.h"
#include <iostream>

int currentLevel = 0;
int maxLevel = 3;

void ChangeLevels() {
	currentLevel = (currentLevel + 1) % maxLevel;
}

int CurrentLevel() {
	std::cout << currentLevel << std::endl;
	return currentLevel;
}
