#include "Levels.h"

void Levels::ChangeLevels() {
	currentLevel = (currentLevel + 1) % maxLevel;
}

int Levels::ReturnLevel() {
	return currentLevel;
}
