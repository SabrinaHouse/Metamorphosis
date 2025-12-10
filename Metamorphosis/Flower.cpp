#include "Flower.h"
#include "Resources.h"


void Flower::Begin() {
	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Flower;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(45, 70);
	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Flower::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Flower.png"], position, sf::Vector2f(150, 200));

}