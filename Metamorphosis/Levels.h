#pragma once
class Levels
{
public:
	unsigned int currentLevel = 0;
	unsigned int maxLevel = 2;

	void ChangeLevels();
	int ReturnLevel();
};

