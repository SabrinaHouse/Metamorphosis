#include "Boarder.h"
#include "Resources.h"

void Boarder::Begin() {
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape leftSide{};
	leftSide.SetAsBox(20, 200);
	fixtureDef.shape = &leftSide;
	body->CreateFixture(&fixtureDef);

	/*
	b2PolygonShape rightSide{};
	rightSide.SetAsBox(20, 200);
	bodyDef.position.Set(-position.x, position.y);
	fixtureDef.shape = &rightSide;
	body->CreateFixture(&fixtureDef); */

}

void Boarder::Draw(Renderer& renderer) {
	//draw the boarder on both sides at the same time
	renderer.Draw(Resources::textures["Boarder.png"], position, sf::Vector2f(-50, 250));

	renderer.Draw(Resources::textures["Boarder.png"], sf::Vector2f(-position.x , position.y) , sf::Vector2f(50, 250));

}