#include "Bush.h"
#include "Resources.h"


void Bush::Begin() {
	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Obstacle;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(40, 55);
	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Bush::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Bush.png"], position, sf::Vector2f(120, 150));

}