#include "Levels.h"
#include <iostream>

int currentLevel = 0;
int maxLevel = 7;

void ChangeLevels() {
	if (currentLevel + 1 < maxLevel) {
		currentLevel = currentLevel + 1;
	}
	else if (currentLevel + 1 == maxLevel) {
		currentLevel = 0;
	}
}

void SelectLevel(int chosenLevel) {
	currentLevel = chosenLevel;
}

int CurrentLevel() {
	//std::cout << currentLevel << std::endl;
	return currentLevel;
}
