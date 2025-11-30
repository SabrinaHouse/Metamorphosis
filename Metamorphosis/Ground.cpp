#include "Ground.h"
#include "Resources.h"

void Ground::Begin() {
	tag = "ground";
	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Ground;
	fixtureData->ground = this;

	//body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y + 200);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(300, 130);
	fixtureDef.shape = &polygonShape;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Ground::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Ground.png"], position, sf::Vector2f(500, 500));
}