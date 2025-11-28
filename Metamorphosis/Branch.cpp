#include "Branch.h"
#include "Resources.h"
#include "Physics.h"


void Branch::Begin() {

	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(2, 1);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void Branch::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Branch.png"], position, sf::Vector2f(leftSide ? 100.0f : -100.0, 50));
}