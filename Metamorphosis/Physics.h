#pragma once
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class MyDebugDraw;

class Chrysalis;
class Branch;
class Ground;
class Caterpillar;
class Leaf;

class ContactListener
{
public:
	virtual void OnBeginContact(b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* other) = 0;
};

class Physics
{
public:
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);

	static b2World* world;
	static MyDebugDraw* debugDraw;
};

enum class FixtureDataType
{
	Chrysalis,
	Branch,
	Ground,
	Caterpillar,
	Leaf
};

struct FixtureData
{
	ContactListener* listener;
	FixtureDataType type;

	union
	{
		Chrysalis* chrysalis;
		Branch* branch;
		Ground* ground;
	};

	union
	{
		Caterpillar* caterpillar;
		Leaf* leaf;
	};
	
};



