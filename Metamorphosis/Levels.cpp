#include "Levels.h"

int currentLevel = 0;
int maxLevel = 2;

void ChangeLevels() {
	currentLevel = (currentLevel + 1) % maxLevel;
}

int CurrentLevel() {
	return currentLevel;
}
