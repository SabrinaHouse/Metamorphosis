#include "Leaf.h"
#include "Resources.h"


void Leaf::Begin() {
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Leaf;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(8, 4);
	fixtureDef.shape = &polygonShape;
	//leaf should not stop movement, it is ONLY a sensor
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}
void Leaf::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Leaf.png"], position, sf::Vector2f(16.0, 8.0f));

}