#include "Ground.h"
#include "Resources.h"

void Ground::Begin() {

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

void Ground::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Ground.png"], position, sf::Vector2f(500, 500));
}