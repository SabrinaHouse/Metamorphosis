#pragma once
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class MyDebugDraw;

//forward declarations for each class to avoid circular dependencies
class Chrysalis;
class Branch;
class Ground;
class Caterpillar;
class Leaf;
class Mantis;
class JuvenileButterfly;
class Bush;
class Vines;
class Flower;
class Butterfly;
class Eggs;
class Wasp;


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
	//lvl 1
	Caterpillar,
	Leaf,
	Mantis,

	//lvl 2
	Chrysalis,
	Branch,
	Ground,

	//lvl 3
	JuvenileButterfly,
	Obstacle,
	Flower,

	//lvl 4
	Butterfly,
	Eggs,
	Wasp
};

struct FixtureData
{
	ContactListener* listener;
	FixtureDataType type;

	//level 1 data types
	union
	{
		Caterpillar* caterpillar;
		Leaf* leaf;
		Mantis* mantis;
	};

	//level 2 data types
	union
	{
		Chrysalis* chrysalis;
		Branch* branch;
		Ground* ground;
	};

	// level 3 data types
	union
	{
		JuvenileButterfly* juvenileButterfly;
		Bush* bush;
		Vines* vine;
		Flower* flower;
	};

	// level 4 data types

	union
	{
		Butterfly* butterfly;
		Eggs* eggs;
		Wasp* wasp;
	};
};



