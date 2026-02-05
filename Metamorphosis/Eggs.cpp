#include "Eggs.h"

void Eggs::Begin() {
	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Eggs;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(15, 15);
	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Eggs::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Eggs.png"], position, sf::Vector2f(30.0, 25.0f));

}